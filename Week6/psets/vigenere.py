import sys
from sys import argv
from cs50 import get_string

# First we make sure that there's is a value within the argv
# <= vigenere.py will be the first thing in the command line
# if that's the only thing then we prompt the user that we need them to enter a keyword
if len(sys.argv) <= 1:
    sys.exit("Error: Please Enter Word")

# Since we only need one word/char from them this checks that
# if argv is greater or equal to 3 prompt the user must only put one word or characther
# argv is basically an array to it would look like ['vignere.py', '{User-Input}']
if len(sys.argv) >= 3:
    sys.exit("Error: Only one word or Character")

# This is for to make sure the keyword we get is alpha from A-Z/a-z
# Any numbers or special characters, spaces will give an error.
for a in (sys.argv[1]):
    if (a.isalpha()) == False:
        sys.exit("Error: Input must be a word")

# After we pass those conditions prompt the user for the plaintext
# this is going to be the text that we will end up encrypting
plainText = get_string("plaintext: ")

b = 0
j = 0

# this function will take in one character in a string
# and return a key value


def shift(char):
    # Here we transform the alpha character to its ASCII value
    value = ord(char)
    # If Value is upper case
    if(value >= 65 and value <= 90):
        return value - 65
    # If Value is lower case
    elif(value >= 97 and value <= 122):
        return value - 97


# store user keyword in a new variable called keyword
keyword = argv[1]
# store length of the keyword that was entered
keywordLength = len(keyword)
# store the length of the plaintext
length = len(plainText)
# decalred two open arrays
cipherText = []
plainText2 = []
# before we encrypt, create a for loop to change each charachter in plaintext to its ASCII value
# We can't shift the characters as is so first change it to ASCII after we shift the value based
# on the key, turn value back to alpha charachter
textLength = len(plainText)
for x in range(textLength):
    # now plaintext2 will turn these char into ASCII numbers
    # plainText2 would now look like ["65", "66", "67"] instead of "abc"
    plainText2.append(ord(plainText[x]))

# Loop through the entire range of the length (which is the length of the plainText)
for i in range(length):
    # here we call the shift function we declared passing in the keyword
    # we set an iterator j to keep control of the key.
    # so for when a value isn't alpha we want our key to momentarily stop and then start back up should a value be alpha
    # the modulo % will have our key repeat once it were to end and they're is still words to encipher
    key = shift(keyword[j % keywordLength])
    # check if the plainText at the ith index is indeed alpha
    if(plainText[i].isalpha()):
        # if it indeed alpha check if it's upper or lower
        if(plainText[i].isupper()):
            # here we cipher the text. minus 65 to get it to 0 on the ASCII table
            # then we add the key amount were shifting. Then we make sure its within 26
            # which is the amount of letters in the alphabet. Then we add in 65 back to get the new text to its new ASCII char/ which is an interger value currently
            # then we call chr to convert the interger to the new enciphered char
            # insert will allow us to play this value at the correct index within cipherText at the ith position
            # i is position
            cipherText.insert(i, chr((((plainText2[i] - 65) + key) % 26) + 65))
            # increment key
            j += 1
            # if alpha is lower
            # we do the same thing as before expect just different ASCII numbers to subtract and add by
        elif(plainText[i].islower()):
            cipherText.insert(i, chr((((plainText2[i] - 97) + key) % 26) + 97))
            # increment
            j += 1

    # Should the value not be alpha char we simply just insert it in the ith position of CipherText
    # key does not get incremented since we are not shifting the value
    else:
        cipherText.insert(i, plainText[i])

# here we just join the ciphertext so its no longer an array of chars turning it into a strig
cipherText = "".join(cipherText)

print("ciphertext:", cipherText)