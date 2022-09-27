import cs50
from sys import argv, exit
import csv


def main():
    # コマンド引数が足りないor多かったらエラーメッセージ
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    with open(argv[1], "r") as dna_file:
        reader = csv.DictReader(dna_file)
        people = list(reader)

    with open(argv[2], "r") as text_file:
        # DNA配列が保存されたString
        dna_data = text_file.readline()
    # 繰り返しの最長のものをカウントする
    max_count = []

    # 名前は関係ないので1から始める
    for i in range(1, len(reader.fieldnames)):
        # AGATC AATG TATC
        dna = reader.fieldnames[i]
        # カウントなので最初は0を入れる
        max_count.append(0)

        for j in range(len(dna_data)):

            count = 0

            if dna_data[j:(j + len(dna))] == dna:
                k = 0
                while dna_data[(j + k):(j + k + len(dna))] == dna:
                    count += 1
                    k += len(dna)
                if count > max_count[i - 1]:
                    max_count[i - 1] = count
    # peopleのリストだけ繰り返す
    for i in range(len(people)):
        people_count = 0
        for j in range(1, len(reader.fieldnames)):
            if int(max_count[j - 1]) == int(people[i][reader.fieldnames[j]]):
                people_count += 1
            if people_count == (len(reader.fieldnames) - 1):
                # people_countが一致したら、名前を出力
                print(people[i]['name'])
                exit(0)

    print("No Match")


main()