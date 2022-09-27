import cs50


def main():
    text = cs50.get_string("text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentence = count_sentence(text)
    index = math_index(letters, words, sentence)
    # 計算した結果がindexに格納されているのでそれに応じてレベルを表示
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        # indexをstring型にして表示
        print("Grade " + str(index))


def count_sentence(text):
    count = 0
    for i in range(len(text)):
        # . ! ? が文末に存在するのでこれの数をカウント
        asc = ord(text[i])
        if asc == 46 or asc == 33 or asc == 63:
            count += 1
    return count


def count_words(text):
    count = 0
    for i in range(len(text)):
        # 単語はスペース区切りなのでスペースの数をカウント
        asc = ord(text[i])
        if asc == 32:
            count += 1
    count += 1
    return count


def count_letters(text):
    count = 0
    # アルファベットの数をカウント
    for i in range(len(text)):
        if str.isalpha(text[i]):
            count += 1
    return count


def math_index(leng, words, sentence):
    # 計算式に当てはめて計算
    L = leng / words * 100
    S = sentence / words * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    # 小数点以下を丸める
    ans = round(index)
    return ans


main()