from cs50 import get_float

while True:
    try:
        change = get_float("Change Owed: ")
    except ValueError:
        print("Not a float stupid")

    if change > 0:
        break


change *= 100

quarters = int(change / 25)
change = change - quarters * 25

dimes = int(change / 10)
change = change - dimes * 10

nickels = int(change / 5)
change = change - nickels * 5

pennies = change

print(quarters + dimes + nickels + pennies)