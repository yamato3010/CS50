from cs50 import get_int
height = 0
while height < 1 or height > 8:
    height = get_int("Height: ")
    if height < 0:
        print("Do not enter negative values")
    elif height == 0:
        print("Please enter a value other than 0")
    elif height > 8:
        print("Please enter a value lower than 9")
for i in range(height):  # 縦
    for j in range(height - i - 1):
        print(" ", end="")
    for c in range(i + 1):
        print("#", end="")
    # 真ん中の穴
    print("  ", end="")

    for b in range(i + 1):
        print("#", end="")
    # 最後の改行
    print("")