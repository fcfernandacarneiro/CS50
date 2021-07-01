import cs50

change = -1
coins = 0

while change < 0:
    change = cs50.get_float("Change owed:")

change = round(change*100) ## round to neart ingeter and converto to penny

#if change == 0:
#    coins = 0


while change != 0:

    while (change / 25) >= 1:
        coins = coins + int(change/25)
        change = change - int(change/25)*25

    while (change / 10) >= 1:
        coins = coins + int(change/10)
        change = change - int(change/10)*10

    while (change / 5) >= 1:
        coins = coins + int(change/5)
        change = change - int(change/5)*5

    #while (change / 1) >= 0:
    coins = coins + int(change/1)
    change = change - int(change/1)*1

print(coins)
