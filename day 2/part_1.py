valid_policies = []
with open("input.txt", "r") as f:
    
    for i in f:
        policy_string = i.strip().split(" ")
        
        letter_range = [int(n) for n in policy_string[0].split("-")]
        letter = policy_string[1].replace(":", "")
        password = policy_string[2]

        characters = {}
        for l in password:
            if characters.get(l) == None:
                characters[l] = 1
            else:
                characters[l] += 1
        if characters.get(letter) != None and characters.get(letter) <= letter_range[1] and characters.get(letter) >= letter_range[0]:
            valid_policies.append(i.strip())

print(len(valid_policies))


