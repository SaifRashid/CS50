from cs50 import get_int
while True:
    try:
        height = get_int("Height: ")
    except ValueError:
        print("Not an integer")

    if height >= 1 and height <= 8:
        break

for i in range(height):
    print(" " * (height - i - 1), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1), end="")
    print("")
