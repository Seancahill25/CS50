from cs50 import get_float
coins = 0
while True:
    number = get_float("Change owed: ")
    break
change = round(number * 100)
while change >= 25:
    coins += 1
    change -= 25
while change >= 10:
    coins += 1
    change -= 10
while change >= 5:
    coins += 1
    change -= 5
while change >= 1:
    coins += 1
    change -= 1
print(coins)






