import numpy as np

S = np.ones((8192,))
values = np.fft.rfft(S)
print(len(values))
