
"""
Make a pie chart - see
http://matplotlib.sf.net/matplotlib.pylab.html#-pie for the docstring.

This example shows a basic pie chart with labels optional features,
like autolabeling the percentage, offsetting a slice with "explode",
adding a shadow, and changing the starting angle.

"""
from pylab import *

import libstatfs

# make a square figure and axes
figure(1, figsize=(6,6))
ax = axes([0.2, 0.2, 0.6, 0.6])

sd = libstatfs.stat_dir()
sd.read()

size = float(sd.size())

print size

l = sd.get_files() + sd.get_dirs()

# The slices will be ordered and plotted counter-clockwise.
#labels = 'Frogs', 'Hogs', 'Dogs', 'Logs'

labels = []
fracs = []

other = 0
for e in l:
    frac = float(e.size()) / size
    if frac < 0.01:
        other += e.size()
    else:
        labels.append(e.name)
        fracs.append(frac)

if other > 0:
    labels.append('other')
    fracs.append(float(other) / size)



#pie(fracs, explode=explode, labels=labels,
#    autopct='%1.1f%%', shadow=True, startangle=90)
pie(fracs, explode=list((max(fracs) - f)**2.0 for f in fracs), labels=labels, colors=('b', 'g', 'r', 'c', 'm', 'y'),
    autopct='%1.1f%%', shadow=True, startangle=90)

# The default startangle is 0, which would start
# the Frogs slice on the x-axis.  With startangle=90,
# everything is rotated counter-clockwise by 90 degrees,
# so the plotting starts on the positive y-axis.

#title('Raining Hogs and Dogs', bbox={'facecolor':'0.8', 'pad':5})

show()

