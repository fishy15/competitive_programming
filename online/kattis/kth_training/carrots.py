#!/usr/local/bin/python3.9

import sys

def main():
    line = sys.stdin.readline()
    line = line.strip()
    data = line.split()
    print(data[1])

if __name__ == '__main__':
    main()
