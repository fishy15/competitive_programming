# :pray: :arrayman:
# :pray: :summitosity:
# :pray: :pusheenosity:
# :pray: :prodakcin:
# :pray: :spacewalker:
# :pray: :duk-duk-go:
# :pray: :gustav:
# :pray: :tmw:
# :pray: :eediosity:
# :pray: :chicubed:
# :pray: :arceus:
# :pray: :gamegame:
# :pray: :sinxiosity
# :pray: :eggyosity:
# :pray: :squares-are-fine:
# :pray: :see-jay:
# :pray: :stephiosity:
# :pray: :fatant:
# :pray: :mathbot:
# :pray: :dolphin:
# :pray: :stef:
# :pray: :geothermal:
# :pray: :mikey:
# :pray: :horse:
# :pray: :snek:

a = input()
b = input()
vowels = ['a', 'e', 'i', 'o', 'u']

if len(a) != len(b):
    print('No')
else:
    flag = True
    for i in range(len(a)):
        if (a[i] in vowels) ^ (b[i] in vowels):
            flag = False
            break
        
    if flag:
        print('Yes')
    else:
        print('No')