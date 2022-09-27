import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # データベースから情報を取得
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as shares, operation FROM stocks WHERE userID = ? GROUP BY symbol HAVING (SUM(shares)) > 0;",
        session["user_id"],
    )
    total_cash_stocks = 0

    # データベースの情報を変数に格納
    for stock in stocks:
        price = lookup(stock["symbol"])
        stock["name"] = price["name"]
        stock["price"] = price["price"]
        stock["total"] = stock["price"] * stock["shares"]
        total_cash_stocks = total_cash_stocks + stock["total"]

    total_cash = total_cash_stocks + user_cash[0]["cash"]

    return render_template("index.html", stocks=stocks, user_cash=user_cash[0], total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # もしPOSTだったら
    if request.method == "POST":

        # もしstockが入力されていなかったら
        if not request.form.get("symbol"):
            return apology("You must inout stock")

        quote = lookup(request.form.get("symbol"))

        # もしquoteの値が有効でなかったら
        if quote == None:
            return apology("Stock symbol is not valied")
        
        try:
            # もしsharesが有効でなかったら
            if not request.form.get("shares"):
                return apology("you must input shares")
        
            # もしsharesが0以下だったら
            if int(request.form.get("shares")) <= 0:
                return apology("you must input natural number")
                
        # ValueErrorを起こしたら
        except ValueError:
            return apology("you must input natural number")

        # 買う個数によって値段を計算
        price = int(request.form.get("shares")) * quote['price']

        # ユーザの残金に応じてエラーを出す
        user_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])

        if price > user_cash[0]["cash"]:
            return apology("You don't have enought money")

        # データベースを更新
        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?",
            price,
            session["user_id"],
        )
        # データベースに追加
        db.execute(
            "INSERT INTO stocks (userID, symbol, shares, price, operation, date) VALUES (?, ?, ?, ?, ?, ?)",
            session["user_id"],
            request.form.get("symbol").upper(),
            int(request.form.get("shares")),
            price,
            "buy",
            datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        )
        return redirect("/")

    else:
        return render_template("buy.html")
        

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM stocks WHERE userID = ?", session["user_id"])
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # もし入力フォームに何も入れられていなかったら
        if not request.form.get("symbol"):
            return apology("You must provide stock symbol")
        # 検索をする
        quote = lookup(request.form.get("symbol"))

        # 有効な値が入力されなかったら
        if quote == None:
            return apology("Stock symbol not valid")

        # 有効な値が入力されたら
        else:
            conv_price = usd(quote['price'])
            return render_template("quoted.html", quote=quote, price=conv_price)
    # もしGEtだったら
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirm = request.form.get("confirmation")
        exist_username = db.execute("SELECT * FROM users WHERE username = ?", username)
        
        # もしusernameが未入力だったら
        if not username:
            return apology("must provide username")
        
        # もしpasswordかconfirmが未入力だったら
        elif not password or not confirm:
            return apology("must provide password")

        # もしpasswordとconfirmが一致しなかったら
        elif password != confirm:
            return apology("password and password confirm must match")
            
        # usernameがかぶっていないかチェック
        elif len(exist_username) != 0:
            return apology("username already exists")

        else:
            # パスワードをハッシュ化し、データベースに追加
            hash = generate_password_hash(password, method="pbkdf2:sha256", salt_length=8)
            add_data = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # もしstockとsharesが未入力だったら
        if (not request.form.get("symbol")) or (not request.form.get("shares")):
            return apology("you must provide stock symbol and shares")

        # shareの値が0以下だったら
        if int(request.form.get("shares")) <= 0:
            return apology("you must provide valid number")

        have_symbol = db.execute("SELECT shares FROM stocks WHERE :symbol=symbol", symbol=request.form.get("symbol"))

        # もし持っている量以上の数を売ろうとしたら
        if int(request.form.get("shares")) > have_symbol[0]['shares']:
            return apology("You don't have enough to sell")

        quote = lookup(request.form.get("symbol"))

        # もしquoteが無効だったら
        if quote == None:
            return apology("symbol not valid")

        price = int(request.form.get("shares")) * quote['price']

        # usersデータベースの所持金額を更新
        db.execute(
            "UPDATE users SET cash=cash+:cost WHERE id=:id",
            cost=price,
            id=session["user_id"]
        )

        db.execute(
            "INSERT INTO stocks (userID, symbol, shares, price, operation, date) VALUES (?, ?, ?, ?, ?, ?)",
            session["user_id"],
            request.form.get("symbol").upper(),
            -int(request.form.get("shares")),
            price,
            "sell",
            datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        )
        return redirect("/")

    else:
        # リストメニューに出すためにstocksを取得
        stocks = db.execute(
            "SELECT symbol FROM stocks WHERE userID = ? GROUP BY symbol",
            session["user_id"],
        )
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


@app.route("/addmoney", methods=["GET", "POST"])
@login_required
def addmoney():
    if request.method == "POST":
        money = float(request.form.get("money"))
        db.execute(
            "UPDATE users SET cash=cash+:cost WHERE id=:id",
            cost=money,
            id=session["user_id"]
        )
        try:
            # もしmoneyが有効でなかったら
            if not request.form.get("money"):
                return apology("you must input shares")
        
            # もしmoneyが0以下だったら
            if float(request.form.get("money")) <= 0:
                return apology("you must input natural number")
                
        # ValueErrorを起こしたら
        except ValueError:
            return apology("you must input natural number")
        
        return redirect("/")
        
    else:
        return render_template("addmoney.html")