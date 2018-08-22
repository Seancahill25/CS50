from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n > 0 or n < 23:
        break;
for i in range(n):
    for j in range(n - i - 1):
        print(" ", end="")
    for h in range(i + 2):
        print("#", end="")
    print()



