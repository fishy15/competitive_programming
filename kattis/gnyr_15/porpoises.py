#!/usr/local/bin/python3.9

import sys

# returns (fib(n), fib(n + 1))
def fib(n):
    if n <= 2:
        return tuple([0, 1, 1, 2][n:n+2])

    if n % 2 == 1:
        a, b = fib(n - 1)
        return (b, (a + b) % (10 ** 9))
    
    a, b = fib(n // 2)
    return ((a * (2 * b - a)) % (10 ** 9), (a ** 2 + b ** 2) % (10 ** 9))

def main():
    p = int(sys.stdin.readline())

    for _ in range(p):
        k, y = map(int, sys.stdin.readline().split())
        print(k, fib(y)[0])

if __name__ == '__main__':
    main()
