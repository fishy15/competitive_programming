fin = open('cowsignal.in', 'r')
fout = open('cowsignal.out', 'w')

m, n, k = map(int, fin.readline().split())

for i in range(m):
    line = fin.readline()
    line2 = ''
    for i in range(len(line) - 1):
        line2 += line[i] * k

    for i in range(k):
        fout.write(line2)
        fout.write('\n')

fout.close()
