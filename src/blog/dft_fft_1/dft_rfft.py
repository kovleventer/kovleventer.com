import numpy as np

S = np.ones((8192,))  # A signal with 8192 samples
values = np.fft.rfft(S)
print(len(values))
