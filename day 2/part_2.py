valid_policies = []
with open("input.txt", "r") as f:
    
    for i in f:
        policy_string = i.strip().split(" ")
        
        letter_range = [int(n) for n in policy_string[0].split("-")]
        letter = policy_string[1].replace(":", "")
        password = policy_string[2]

        is_letter_1_valid = password[letter_range[0] - 1] == letter
        is_letter_2_valid = password[letter_range[1] - 1] == letter
        
        if is_letter_1_valid != is_letter_2_valid:
            valid_policies.append(i)

print(len(valid_policies))


