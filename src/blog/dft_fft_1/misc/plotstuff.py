import numpy as np
import matplotlib.pyplot as plt
import math

#TODO clean this up

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

def y_(x):
    y1 = 3.1 * np.sin(2 * math.pi * .1 * x)
    y2 = 0.8 * np.sin(2 * math.pi * .3 * x)
    y3 = 1.4 * np.sin(2 * math.pi * .8 * x)
    y = y1 + y2 + y3
    return y

def third():
    fig, ax = plt.subplots()
    ax.set_aspect('equal')
    ax.spines['left'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.yaxis.tick_left()
    ax.spines['bottom'].set_position('zero')
    ax.spines['top'].set_color('none')
    ax.xaxis.tick_bottom()

    x = np.linspace(-3, 6, 2000)
    y = y_(x)
    X = np.array([1, 2, 3])
    Y = y_(X)

    ax.plot(x, y, "r")
    ax.stem(X, Y, basefmt=' ')
    plt.savefig("out.png", dpi=300, transparent=True)

def y4(x):
    y1 = 3.1 * np.cos(2 * math.pi * .1 * x - 1.2)
    y2 = 0.8 * np.cos(2 * math.pi * .3 * x - 1.3)
    y3 = 1.4 * np.cos(2 * math.pi * .8 * x - 1.5)
    y = y1 + y2 + y3
    return y

def fourth():
    fig, ax = plt.subplots()
    ax.set_aspect('equal')
    ax.spines['left'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.yaxis.tick_left()
    ax.spines['bottom'].set_position('zero')
    ax.spines['top'].set_color('none')
    ax.xaxis.tick_bottom()

    x = np.linspace(-2, 6, 2000)
    y = y4(x)
    X = np.array([0, 1, 2, 3, 4, 5])
    Y = y4(X)

    ax.plot(x, y, "r")
    ax.stem(X, Y, basefmt=' ')
    plt.savefig("out.png", dpi=300, transparent=True)

def fifth():
    fig, ax = plt.subplots()
    ax.spines['left'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.yaxis.tick_left()
    ax.spines['bottom'].set_position('zero')
    ax.spines['top'].set_color('none')
    ax.xaxis.tick_bottom()

    x = np.linspace(-1, 4, 2000)
    y1 = np.cos(2 * math.pi * 0.1 * x)
    y2 = np.cos(2 * math.pi * 1.1 * x)
    y3 = np.cos(2 * math.pi * 2.1 * x)
    X = np.arange(-1, 5)
    Y = np.cos(2 * math.pi * 0.1 * X)
    ax.plot(x, y1, "r")
    ax.plot(x, y2, "g")
    ax.plot(x, y3, "y")
    ax.stem(X, Y, basefmt=' ')
    plt.savefig("out.png", dpi=300, transparent=True)

def sixth():
    fig, ax = plt.subplots()
    ax.set_aspect('equal')
    ax.spines['left'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.yaxis.tick_left()
    ax.spines['bottom'].set_position('zero')
    ax.spines['top'].set_color('none')
    ax.xaxis.tick_bottom()

    x = np.linspace(-1, 4, 2000)
    y1 = np.sin(2 * math.pi * 0.3 * x)
    y2 = np.sin(2 * math.pi * 0.7 * x)
    X = np.arange(-1, 5)
    Y1 = np.sin(2 * math.pi * 0.3 * X)
    Y2 = np.sin(2 * math.pi * 0.7 * X)
    ax.plot(x, y1, "r")
    ax.plot(x, y2, "g")
    ax.stem(X, Y1, basefmt=' ')
    ax.stem(X, Y2,  "y", basefmt=' ', markerfmt="yo")
    plt.savefig("out.png", dpi=300, transparent=True)

def seventh():
    fig, ax = plt.subplots()
    ax.spines['left'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.yaxis.tick_left()
    ax.spines['bottom'].set_position('zero')
    ax.spines['top'].set_color('none')
    ax.xaxis.tick_bottom()

    x = np.linspace(0, 0.9, 10)
    y = np.array([1.00000000e-03, 1.55052537e+00, 6.99586883e-01, 4.00416141e-01,
 4.38951453e-04 ,1.00000000e-03, 4.38951453e-04, 4.00416141e-01,
 6.99586883e-01, 1.55052537e+00])

    plt.stem(x, y, basefmt=" ", markerfmt=" ")
    plt.savefig("out.png", dpi=300, transparent=True)

def eigtth():
    fig, ax = plt.subplots()
    ax.set_aspect('equal')
    ax.spines['left'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.yaxis.tick_left()
    ax.spines['bottom'].set_position('zero')
    ax.spines['top'].set_color('none')
    ax.xaxis.tick_bottom()

    x = np.linspace(-1, 4, 2000)
    ax.plot(x, np.cos(2*math.pi*0.5*x))
    ax.plot(x, np.sin(2*math.pi*0.5*x), "r")
    X = np.arange(-1, 5)
    ax.stem(X, np.cos(2*math.pi*0.5*X), "g", basefmt=' ', markerfmt="go")
    plt.savefig("out.png", dpi=300, transparent=True)

eigtth()


