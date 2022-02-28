#!/usr/bin/local/python3.9

import sys

def main():
    n = int(sys.stdin.readline())
    courses = {}

    for _ in range(n):
        first, last, course = sys.stdin.readline().split()
        if course not in courses:
            courses[course] = set()
        courses[course].add(f'{first} {last}')

    for course in sorted(courses.keys()):
        print(course, len(courses[course]))

if __name__ == '__main__':
    main()
