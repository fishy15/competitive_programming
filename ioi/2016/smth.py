cur = '1'
def next():
    s = ''
    p = ''
    cnt = 0
    global cur
    for c in cur:
        if c == p:
            cnt += 1
        else:
            s += str(cnt)
            s += p
            cnt = 1
        p = c
    s += str(cnt)
    s += p
    cur = s[1:]

for i in range(50):
    next()
print(cur)
