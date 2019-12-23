from cs50 import get_int


while (True):
    # prompt user for height
    height = get_int("Height: ")
    # condition to make sure that value is a number between 1 and 8
    if(height > 0 and height < 9):
        # should user input a correct value you break out of this while loop.
        # if not we continue to prompt the user
        break

# i will iterate for the height of the entire staircase
for i in range(height):
    # this next two will iterate for the rows
    # j loop will add spaces for the range of height minus  1 - 0.
    # if j is at 0 and height is 7 that means we'll add 6 blank spaces
    for j in range(height - 1 - i):
        # end="" is so we remove the default new line that comes with python
        print(" ", end="")
    # for writing the hashes
    # k will itearate the range of i + 1 thus if I is 0 we'll add 1 #s
    # if k is 5 we'll add 6 #s
    for k in range(i + 1):
        print("#", end="")
    print()