

import math

cp = 4187
rho = 1000
k = 0.58

mu_in = 1.307
mu_out = 0.653
mu_out_wall = 0.467

# input
T1 = 40
T2 = 59
T3 = 10
D_inner = 6e-2
D_outer = 10e-2
mdot = 0.2
q = 5e3


# assume circular

L = (mdot * cp * (T1 - T3)) / (math.pi * D_outer * q)

h = q / (T2 - T1)

A_cs = math.pi * (D_inner / 2)**2

v = mdot / A_cs / rho

Re_in  = rho * v * D_inner / mu_in
Re_out = rho * v * D_inner / mu_out

Pr_out = cp * mu_out / k

Nu_D_out = 1.86 * (Re_out * Pr_out)**(1/3) * (D_inner / L)**(1/3) * (mu_out / mu_out_wall)**(0.14)

h2 = 

print "L    ",L
print "h    ",h
print "v    ",v
print "Re_in   ",Re_in
print "Nu_D_out",Nu_D_out


