import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.animation as manimation
import math

FFMpegWriter = manimation.writers['ffmpeg']
metadata = dict(title='Zero samples', artist='Matplotlib')
writer = FFMpegWriter(fps=60, metadata=metadata)

fig, ax = plt.subplots()
fig.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=None, hspace=None)

plt.xlim(-5, 5)
plt.ylim(-5, 5)

x = np.linspace(-5, 5, 2000)
X = np.linspace(-math.pi * 1.5, math.pi * 1.5, 7+6)
Y = np.sin(X * 4)
l, = ax.plot(x, np.sin(x*4), 'r')
l2 = ax.stem(X, Y, basefmt=' ')

#ax.set_aspect('equal')
ax.spines['left'].set_position('zero')
ax.spines['right'].set_color('none')
ax.yaxis.tick_left()
ax.spines['bottom'].set_position('zero')
ax.spines['top'].set_color('none')
ax.xaxis.tick_bottom()

with writer.saving(fig, "out.mp4", 300):
    for i in range(150):
        l.set_data(x, np.sin(x*4) * i / 32)
        writer.grab_frame()
    for i in range(150):
        l.set_data(x, np.sin(x*4) * (150-i) / 32)
        writer.grab_frame()