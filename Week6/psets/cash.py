from cs50 import get_float

quarters = 25
dimes = 10
nickles = 5
pennies = 1
coins = 0

change = 0


while (True):
    # Promt user for changed owed
    value = get_float("Change Owed: ")
    # Condition to make sure value is a number greater than 0
    if (value > 0):
        # Should the value we recieve be higher than 0, then we'll break out of the while loop
        # If not we continue to prompt user for the Change Owed
        break

# Round the value we get
change = round(value * 100)
q = 0
d = 0
n = 0
p = 0
# While the change we get is greater or equal to a quarter(25)
while (change >= quarters):
    change = change - quarters
    q += 1
    coins += 1

print("Total Quarters: ", q)

# While the change we get is greater or equal to a dime(10)
while (change >= dimes):
    change = change - dimes
    d += 1
    coins += 1

print("Total Dimes: ", d)

# While the change we get is greater or equal to a nickle(5)
while (change >= nickles):
    change = change - nickles
    n += 1
    coins += 1

print("Total Nickles: ", n)

# While the change we get is greater or equal to a penny(1)
while (change >= pennies):
    change = change - pennies
    p += 1
    coins += 1

print("Total Pennies: ", p)


print("Total Coins: ", coins)

