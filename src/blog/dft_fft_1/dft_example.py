import numpy as np
import math

S = np.array([1.44, 1.98, 1.57, 2.86, 2.95,         # Our original signal sampled
              -1.24, -4.57, -3.37, -1.38, -0.23])   # 4 additional times

N = len(S)  # 10

M = np.exp(-1j * 2 * math.pi * np.outer(np.arange(N), np.arange(N)) / N)
values = M.conj().dot(S) / N

A = abs(values)
print(A)
