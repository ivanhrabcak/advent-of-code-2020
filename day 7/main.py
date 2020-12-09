# class Node:
#     def __init__(self, children, color):
#         self.children = children
#         self.color = color
    
#     def __str__(self):
#         return str(self.children) + ", " + self.color


def find_applying_rules(bag, rules):
    bag = bag.replace("bags", "").replace("bag", "")
    applying_rules = []
    for rule in rules:
        bag_contains = rule.split(" contain ")[1]
        if bag in bag_contains:
            applying_rules.append(rule)
    return applying_rules

def get_color(rule):
    return rule.split(" contain ")[0]

def get_containing_bags(rule):
    return rule.split(" contain ")[1].split(", ")

def solve(bag, counter, rules, bags_scanned):
    if len(find_applying_rules(bag, rules)) == 0:
        return counter

    for rule in find_applying_rules(bag, rules):
        print(get_color(rule))
        if get_color(rule) not in bags_scanned:
            bags_scanned.append(get_color(rule))
            return solve(get_color(rule), counter + 1, rules, bags_scanned)
            

rules = ""
with open("input.txt") as f:
    rules = f.read()
rules = rules.replace(" bags", "").replace(" bag", "").replace(" bags ", "").replace(" bag ", "")
rules = rules.split(".\n")
rules.pop()

target_color = "shiny gold"

print(solve(target_color, 0, rules, []))

# target_color_rules = find_applying_rules(target_color, rules)
# for rule in target_color_rules:
#     for color_rule in find_applying_rules(get_color(rule), rules):
#         print(color_rule)
#     print("---------------------------")

# applying_rules = []

# found_bag = False
# current_bag = target_color
# while not found_bag:
#     for rule in find_applying_rules(target_color, rules):
#         applying_rules = []
#         applying_rules.append(find_applying_rules(get_color(rule), rules))
#         print("there are all rules that apply to " + get_color(rule) + " " + str(applying_rules))
#         applying_rules.append(rule)

#         print("-----------------------------------------------------------------------------------------------------------------------------------")
#     break
# print(applying_rules)


