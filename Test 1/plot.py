import matplotlib.pyplot as plt
import numpy as np
import matplotlib

x = np.arange(1, 100, 0.1)
y = np.arange(1, 100, 0.1)

def f(x):
    a = 1
    c = 1
    return 3*a*x**2 + 2*c*x**2 - 2*a*x - 2*c*x  

def g(x):
    a = 1
    c = 1
    return 5*a*x**2 + (5*c*x**2)/2 - 4*a*x + (c*x)/2 

plt.plot(x,f(x), label = "Função do Dio")
plt.plot(y, g(x), '--', label = "Função do Moa")
matplotlib.rcParams.update({'font.size': 25})
plt.title(label = "Gráfico de comparação entre a função do Moa e a função do Dio", fontsize = "20")
plt.xlabel(xlabel = "n", fontsize = "20")
plt.ylabel(ylabel = "Counting", fontsize = "20")
plt.legend(fontsize = 20)
plt.show()

# f(n) = 3an² + 2cn² - 2an - 2cn Mine

# f(n) = 5an² + 5cn²/2 - 4an + cn/2 Moa