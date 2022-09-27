import cs50
num = cs50.get_int("Number: ")
s_num = str(num)


def main():
    # カードの整合性チェック
    if luhn():
        # カード会社のチェック
        # もし15桁で最初が3で始まったら
        if len(s_num) == 15 and s_num[-15] == "3":
            print("AMEX")
        elif len(s_num) == 16 and s_num[-16] == "5":
            print("MASTERCARD")
        elif len(s_num) == 13 and s_num[-13] == "4":
            print("VISA")
        elif len(s_num) == 16 and s_num[-16] == "4":
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
        

def luhn():
    sum = 0
    # enumerateはカード番号の配列の番号をiに代入している
    # reversedはカード番号の右側からカウントするために配列番号を逆にしている
    for i, n in enumerate(reversed(s_num)):
        # もし最後から２番目の数字から一桁ごと飛ばしたものなら
        if i % 2 != 0:
            for j in str(int(n) * 2):
                sum += int(j)
        # もし、最後の数字から一桁ずつ飛ばしたものなら
        else:
            sum += int(n)
    # もし最後の桁が０なら（10で割ればわかる）
    if sum % 10 == 0:
        return True
    else:
        return False
                
    
main()