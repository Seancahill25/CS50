from cs50 import get_string
import sys

if len(sys.argv) == 2:
    key = int(sys.argv[1])
    message = get_string("plaintext: ")
else:
    print("Try again")
print("ciphertext: ")
for letter in range(len(message)):
    if message[letter].isalpha():
        if message[letter].isupper():
            print (chr(((ord(message[letter]) - 65) + key) % 26 + 65), end="")
        else:
            print (chr(((ord(message[letter]) - 97) + key) % 26 + 97), end="")
    else:
        print(message[letter],end="")
print()