import numpy as np

S = np.array([1.44, 1.98, 1.57, 2.86, 2.95,
              -1.24, -4.57, -3.37, -1.38, -0.23])

N = len(S) # 10
alpha = np.pi / 3

M = np.cos(2 * np.pi * np.outer(np.arange(N), np.arange(N)) / N + alpha)

A = np.linalg.solve(M, S)
print(A)
