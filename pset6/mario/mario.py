from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n >= 0 and n <= 23:
        break
    print("Try again")
for i in range(n):
    for j in range(n - i - 1):
        print(" ", end="")
    for h in range(i + 2):
        print("#", end="")
    print()



