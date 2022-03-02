import matplotlib.pyplot as plt
import numpy as np

X = [];
Y = [];

with open('task1_stat.txt') as file:
    for line in file:
        X.append(int(line.split()[2].lower()))
        Y.append(int(line.split()[10].lower()))

Y_average = [];
index = 0
for i in range(4, 48, 4):
    Y_average.append(0)
    n = 0
    for j in range(len(X)):
        if X[j] == i:
            n += 1
            Y_average[index] += Y[j]
    if n == 0:
        Y_average[index] = 0
    else: Y_average[index] = int(Y_average[index]/n)
    index += 1

plt.figure()
plt.plot(range(4, 48, 4), Y_average, 'ro')
plt.xlabel(r'$Side Of Square$', fontsize=12)
plt.ylabel(r'$Average Number Of Steps$', fontsize=12)
plt.grid(True)
plt.show()
