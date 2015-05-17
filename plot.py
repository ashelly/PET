#!/usr/bin/env python

import sys,os
import glob
import math
import string
import numpy as np
import matplotlib.pyplot as plt

#the size of an evaluator which does nothing
try:
    NULSZ = os.stat('null_eval').st_size;
except:
    NULSZ = 0;

def getsize(name):
    """ gets the size of an evaluator and associated tables"""
    sz =0
    name = string.lower(name)
    try:
        sz = os.stat(name).st_size - NULSZ
        for datfilename in glob.glob(name+"_table?.dat"):
            sz += os.stat(datfilename).st_size
    except OSError:
        pass #no such file
    
    return sz

results = {}
resultfilename = sys.argv[1]

resultfile = open(resultfilename,"r")
processor,memory = "Unknown","?"
for line in resultfile:
    if "model" in line : 
        processor = line.split(':')[1]
    elif "MemTotal" in line : 
        memory = float(line.split()[1])/1e6
    else:
        try:
            label,enum,rand = line.split()
            data = results.get(label,[[],[],[]])
            data[0].append(float(enum))
            data[1].append(float(rand))
            data[2] = getsize(label)
            results[label]=data
        except ValueError:
            pass #skip bad lines
    

N = len(results)
enummeans = []
enumstd =  []
randmeans = []
randstd =  []
sizes = []
sorted_results = sorted(results.items(),key=lambda d: d[1][2])

for label,data in sorted_results:
    enummeans.append(np.mean(data[0]))
    enumstd.append(np.std(data[0]))
    randmeans.append(np.mean(data[1]))
    randstd.append(np.std(data[1]))
    sizes.append(math.log(getsize(label),10))
    
x_locs = np.arange(N)  # the x locations for the groups
width = 0.35       # the width of the bars

fig, ax = plt.subplots()

#speed axis
rects1 = ax.bar(x_locs, enummeans, width, color='r', yerr=enumstd)
rects2 = ax.bar(x_locs+width, randmeans, width, color='y', yerr=randstd)
ax.set_ylabel('MH/S')

#size axis
ax2 = ax.twinx()
ax2.plot(x_locs+width, sizes, '-')
ax2.set_ylim([0,10])
ax2.set_ylabel('size')
ax2.set_yticks([3,6,9])
ax2.set_yticklabels(['1 Kb','1 Mb','1 Gb'])

# title text, x axis
plt.suptitle('7 Card Hand Evaluator Speed',fontsize=16)
ax.set_title("{} with {} GB RAM".format(processor,memory),fontsize=8)
ax.set_xticks(x_locs+width)
ax.set_xticklabels( [d[0] for d in sorted_results])

ax.legend( (rects1[0], rects2[0]), ('enumerated', 'random') )


def autolabel(rects):
    # attach some text labels
    for rect in rects:
        height = rect.get_height()
        ax.text(rect.get_x()+rect.get_width()/2., 1.01*height, '%d'%int(height),
                ha='center', va='bottom')

autolabel(rects1)
autolabel(rects2)

plt.show()





