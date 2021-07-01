import cs50

#get input from user
n = 10
while n > 8 or n < 1:
    n = cs50.get_int("Height (up to 8): ")

h = n #
l = 1


for i in range(h):
    while l < (n + 1):
        espaco = n-l
        print(" "*espaco, end="")
        for j in range(l):
            print("#", end="")
        l = l + 1
        print()
