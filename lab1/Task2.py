#Данная программа должна считвать данные из файла task2_stat.txt,
#каждая строка которого имеет вид Crystal size: <number_1>; real percentage: <number_2>; total number of steps: <number_3>.
#Кроме извлечения данные должны быть подготовлены для построения графика, где по оси X отложено значение number_2,
#по оси Y - среднее для каждого x значение number_3


import matplotlib.pyplot as plt
import numpy as np

X = [];
Y = [];

with open('task2_stat.txt') as file:
    for line in file:
        X.append(int(line.split()[8].lower()))
        Y.append(int(line.split()[14].lower()))

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
