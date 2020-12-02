with open("input.txt", "r") as f:
    numbers = [int(i) for i in f]

found = False

for i in numbers:
    if found:
        break

    for j in numbers: 
        if 2020 - (i + j) in numbers:
            print(i * numbers[numbers.index(2020 - (i + j))] * j)
            
            found = True
            break