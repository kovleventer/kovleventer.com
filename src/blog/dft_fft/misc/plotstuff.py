import numpy as np
import matplotlib.pyplot as plt
import math

def first():
    x = np.linspace(-2,4,2000)
    #y = np.sin(x)*3
    y = np.sin((x-0.4)*9*3.1415926535/3+0.4)*3
    X = np.linspace(0.4, 3.4, 5)
    Y = np.sin(X)*3
    print(np.polyfit(X, Y, 4))
    X = np.array([0, 1, 2, 3, 4])
    #y = x*x*x*x * 1.07654258e-01 + x*x*x * -6.78019854e-01 + x*x * 1.18217905e-01 + x * 2.97982218e+00 + -1.95138720e-03
    fig, ax = plt.subplots()
    #ax.plot(x, y, 'r')
    ax.stem(X, Y, basefmt=' ')
    ax.set_aspect('equal')
    ax.spines['left'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.yaxis.tick_left()
    ax.spines['bottom'].set_position('zero')
    ax.spines['top'].set_color('none')
    ax.xaxis.tick_bottom()



    print(X)
    print(Y)
    #plt.show()
    plt.savefig("out.png",dpi=300, transparent=True)

def second():
    fig, ax = plt.subplots()
    ax.set_aspect('equal')
    ax.spines['left'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.yaxis.tick_left()
    ax.spines['bottom'].set_position('zero')
    ax.spines['top'].set_color('none')
    ax.xaxis.tick_bottom()

    x = np.linspace(-4, 8, 2000)
    y1 = 3.1 * np.cos(2 * math.pi * .1 * x)
    y2 = 0.8 * np.cos(2 * math.pi * .3 * x)
    y3 = 1.4 * np.cos(2 * math.pi * .8 * x)

    ax.plot(x, y1, 'r')
    ax.plot(x, y2, 'g')
    ax.plot(x, y3, 'y')

    ax.plot(x, y1+y2+y3, linewidth="2.5")
    plt.savefig("out.png", dpi=300, transparent=True)
    #plt.show()

second()

