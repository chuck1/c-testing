#!/usr/bin/env python
import random
import itertools

class Guess(object):
    def __init__(self, g, solver, m, n):

        if not isinstance(g, list):
            raise ValueError()

        self.solver = solver
        self.g = g
        self.m = m
        self.n = n

        self.color_set_1 = set(self.g)
        self.color_set_2 = solver.colors.difference(set(self.g))
        
        gen_1 = itertools.combinations(self.color_set_1, m)
        gen_2 = itertools.combinations(self.color_set_2, 5 - m)
        
        self.cs1_com = list((set(l),self.color_set_1.difference(l)) for l in gen_1)
        self.cs2_com = list((set(l),self.color_set_2.difference(l)) for l in gen_2)

        # filter
        def flt(x):
            if not solver.colors_c.issubset(set(x[0])):
                return False

            if solver.colors_i.intersection(set(x[0])):
                return False

            return True
        
        self.cs1_com = filter(flt, self.cs1_com)

        # filter
        def flt_2(x):
            if solver.colors_i.intersection(set(x[0])):
                return False

            if solver.colors_c.intersection(set(x[1])):
                return False

            return True
        
        
        self.cs2_com = filter(flt_2, self.cs2_com)
        
        # cs2

        
        # assemble possible guesses

        self.guesses = []
        for a,_ in self.cs1_com:
            for b,_ in self.cs2_com:
                g = set(a).union(set(b))
                
                if not solver.colors_c.issubset(g):
                    #print "not subset"
                    #print colors_c,g
                    continue
                
                u = g.intersection(solver.colors_i)
                if u:
                    #print "contains incorrect colors"
                    #print u
                    continue

                # verify g against previous guesses
                fail = False
                for G in solver.guesses:
                    if not G.verify(g):
                        fail = True
                        break

                if fail:
                    continue

                self.guesses.append(g)
                

        if len(self.cs1_com) == 1:
            solver.colors_c = solver.colors_c.union(self.cs1_com[0][0])
            solver.colors_i = solver.colors_i.union(self.cs1_com[0][1])

        if len(self.cs2_com) == 1:
            solver.colors_c = solver.colors_c.union(self.cs2_com[0][0])
            solver.colors_i = solver.colors_i.union(self.cs2_com[0][1])

        if len(self.guesses) == 1:
            solver.colors_c = solver.colors_c.union(self.guesses[0])

            
        self.prnt()
    
    def filter_correct_colors(self, solver):
        return solver.filter_correct_colors(self.g)

    def verify(self, g):
        """
        If g contains all of the correct colors from a hypothesis, then
        the incorrect colors from that hypothesis must not appear in g.
        """

        #print "verify",g
        
        if g == self.g:
            return False
        
        for a,b in self.cs1_com:
            if a.issubset(g):
                #print a,"is subset"
                i = b.intersection(g)
                #print i
                if i:
                    #print "nonempty"
                    return False

        for a,b in self.cs2_com:
            if a.issubset(g):
                #print a,"is subset"
                i = b.intersection(g)
                #print i
                if i:
                    #print "nonempty"
                    return False

        return True


    def get_rand_guess(self):
        return random.choice(self.guesses)

    def prnt(self):
        print "guess               =", self.g
        print "colors in guess     =", self.color_set_1
        print "colors not in guess =", self.color_set_2
        
        print
        print "{:24}{:24}".format("correct","incorrect")
        print "{:24}{:24}".format("colors from","colors from")
        print "{:24}{:24}".format("color_set_1","color_set_1")
        
        for a,b in self.cs1_com:
            print "{:24}{:24}".format(a, b)
        
        print
        print "{:24}{:24}".format("correct","incorrect")
        print "{:24}{:24}".format("colors from","colors from")
        print "{:24}{:24}".format("color_set_2","color_set_2")
        
        for a,b in self.cs2_com:
            print "{:24}{:24}".format(a, b)

        print "guesses"
        for g in self.guesses:
            print " ",g

        print "--------------"
        print "colors_c", self.solver.colors_c
        print "colors_i", self.solver.colors_i
        print "--------------"

class Judge0(object):
    def __init__(self, puz):
        self.puz = puz
    def judge(self, guess):
        """
        return (a,b)
        a - number of correct colors
        b - number of correct locations
        """
        c = [p==g for p,g in zip(self.puz,guess)]
        u = set(self.puz).intersection(set(guess))
        return len(u), c.count(True)

class Judge1(object):
    def judge(self, guess):
        m = raw_input("number of correct colors: ")
        n = raw_input("number of correct locations: ")
        return m,n

class Solver(object):

    def __init__(self, judge):
        self.judge = judge

    def filter_correct_colors(self, g):

        l = lambda x: x if x in self.colors_c else -1

        r = [l(x) for x in g]

        return r
        
    def solve_colors(self, puz):
        
        self.colors = set(range(8))
        self.colors_c = set()
        self.colors_i = set()
    
        color_com = list(itertools.combinations(self.colors, 5))
        
        puz = random.sample(self.colors, 5)
        g = random.sample(self.colors, 5) 
        
        g = [0,1,5,6,7]
        
        #print "colors", colors
        
        self.guesses = []
        
        #print "puzzle", puz
        
        while True:
            m,n = self.judge.judge(g)
            
            G = Guess(g, self, m, n)
            self.guesses.append(G)
            
            if len(self.guesses[-1].guesses) == 1:
                break
        
            g = list(self.guesses[-1].get_rand_guess())
        
        
        print "determined colors in {} guesses".format(len(self.guesses))
    
        for g in self.guesses:
            r = g.filter_correct_colors(self)
            fmt = "{: 3}"*5
            print fmt.format(*g.g) + "   " + fmt.format(*r) + "  {}".format(g.n)

            

puz = [1,0,2,3,4]

judge = Judge0(puz)

S = Solver(judge)

S.solve_colors(puz)















