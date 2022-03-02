import matplotlib.pyplot as plt
import numpy as np

X = [];
Y = [];

with open('task3_B_stat.txt') as file:
    for line in file:
        X.append(int(line.split()[7].lower()))
        Y.append(int(line.split()[13].lower()))

Y_average = [0];
for i in range(1, 101):
    n = 0
    Y_average.append(0)
    for j in range(len(X)):
        if X[j] == i:
            n += 1
            Y_average[i] += Y[j]
    if n == 0:
        Y_average[i] =0
    else: Y_average[i] = int(Y_average[i]/n)

plt.figure()
plt.plot(Y_average)
plt.xlabel(r'$Percentage Of Dislocation$', fontsize=12)
plt.ylabel(r'$Average Number Of Steps$', fontsize=12)
plt.grid(True)
plt.show()
