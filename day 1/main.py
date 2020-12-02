with open("input.txt", "r") as f:
    numbers = [int(i) for i in f]

for n in numbers:
    if 2020 - n in numbers:
        print(n, numbers[numbers.index(2020 - n)])
        break