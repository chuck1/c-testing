#!/usr/bin/env python
import random
import itertools

def judge(puz, guess):
    c = [p==g for p,g in zip(puz,guess)]
    u = set(puz).intersection(set(guess))
    return len(u), len(c)
    

colors = set(range(8))

com = list(itertools.combinations(colors, 5))

puz = random.sample(colors, 5)

print "puz", puz

judge(puz, [0,1,2,3,4])


