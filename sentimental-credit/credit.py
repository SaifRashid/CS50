from cs50 import get_string

number = ""

def main():
    global number
    number = get_string("Number: ")

    if len(number) == 15 and (number[0:2] == "34" or number[0:2] == "37"):
        print(luhn_algo("AMEX"))

    elif len(number) == 16 and (number[0:2] == "51" or number[0:2] == "52" or number[0:2] == "53" or number[0:2] == "42" or number[0:2] == "55"):
        print(luhn_algo("MASTERCARD"))

    elif (len(number) == 16 or len(number) == 13) and number[0] == "4":
        print(luhn_algo("VISA"))
    else:
        print("INVALID")


def luhn_algo(card_type):
    number_copy = number
    numberstimes2 = 0
    for i in range(int(len(number)/2)):
        tmp = int(number[len(number)-((i+1)*2)])
        tmp *= 2
        numberstimes2 += int(tmp / 10)
        numberstimes2 += tmp % 10

    for i in range(int(len(number)/2 + .5)):
        numberstimes2 += int(number[len(number)-2*i-1])

    if numberstimes2 % 10 == 0:
        return card_type
    else:
        return "INVALID"


main()