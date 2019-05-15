# :pray: :arrayman:
# :pray: :summit:
# :pray: :pusheen:
# :pray: :prodakcin:
# :pray: :spacewalker:
# :pray: :duk:
# :pray: :gustav:
# :pray: :tmw:
# :pray: :eed:
# :pray: :chicubed:
# :pray: :arceus:
# :pray: :gamegame:
# :pray: :sinx:
# :pray: :eyg:
# :pray: :evan:
# :pray: :cj:
# :pray: :steph:
# :pray: :fatant:
# :pray: :mathbot:
# :pray: :dolphin:
# :pray: :stef:
# :pray: :geothermal:
# :pray: :mikey:
# :pray: :horse:
# :pray: :snek:
# :pray: :wayne:
# :pray: :wu:
# :pray: :vmaddur:
# :pray: :dorijanko:
# :pray: :gaming:
# :pray: :kassuno:
# :pray: :hyacinth:
# :pray: :chilli:
# :pray: :dhruv:
# :pray: :philip:
# :pray: :paiman:
# :pray: :camel:
# :pray: :tree:
# :pray: :tux:
# :pray: :jony:
# :pray: :kage:
# :pray: :ghost:

s = input().lower()
n = int(input())

flag = False

c1 = ['o', '0']
c2 = ['1', 'l', 'i']

for i in range(n):
    cur = input().lower()
    
    works = True

    if len(cur) != len(s):
        continue

    for i in range(len(s)):
        if s[i] == cur[i] or (s[i] in c1 and cur[i] in c1) or (s[i] in c2 and cur[i] in c2):
            pass
        else:
            works = False
            break
    
    if works:
        flag = True
        break

if flag:
    print('No')
else:
    print('Yes')

