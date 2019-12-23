from cs50 import get_string
from sys import argv

# Words in txt file
# create an empty set to store the words
banned_words = set()

# check if the argument vector is less than or equal to 2
# our second argument must be there in order to continue
# if not there prompt the user to enter a .txt file
if(len(argv)) != 2:
    exit("Please Enter .txt file")

# if so we store the infile globaly
# argv is an array/list
infile = argv[1]


def main():
    # call load which will load our file from the command line
    load()
    # call censor which passes in the loaded file from the command line
    censor(banned_words)


def load():
    # This try, exept, blocks are for handling errors
    # try will test a block of code for use
    # we want to attempt to open the infile from argv[1]
    # "r" is just the mode we set which is for read
    try:
        file = open(infile, "r")

    # if we locate an error we exept will help us handle that error
    # this is for if a user inputs a .txt file or pratically any file that does not exist
    # ex if user entered banned.tx this would handle that error
    except FileNotFoundError:
        print("File not Found")
        exit(1)

    # if no errors we finally execute the code fully
    # which we are reading each line within fine
    # striping away the newline in each line and adding the add it into
    # our banned_words set. After we close the file and return banned_words
    finally:
        for line in file:
            banned_words.add(line.rstrip("\n"))
        file.close()

    return banned_words


def censor(banned_words):
    # prompt user for the message
    # we split the message turning it into a list
    user_message = get_string("What message would you like to censor?\n").split(" ")

    # created censored_message as an empty string which will hold our new censored message
    censored_message = ""

    # we iterate through the user_message list
    for i in user_message:
        # check if i is within banned_words set
        # we set i to lower because all the words in banned list are lowercased
        # checking case-insensitivey
        if (i.lower() in banned_words):

            # if so we add an asterisk the length of the word. and add an added space after
            censored_message += "*" * len(i) + " "

        # should the word in question not be in the banned_words set, we simply just added
        # the word as is into censored_message
        else:
            censored_message += i + " "

    print(censored_message)


if __name__ == "__main__":
    main()
