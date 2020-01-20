import numpy as np
import math

T = np.arange(6)  # 0, 1, 2, 3, 4, 5
F = np.array([0.1, 0.3, 0.8])  # Frequencies
S = np.array([1.44, 1.98, 1.57, 2.86, 2.95, -1.24])
tf = np.outer(T, F)

M1 = np.cos(2 * math.pi * tf)  # The cosine part of M
M2 = np.sin(2 * math.pi * tf)  # The sine part of M
M = np.concatenate((M1, M2), 1)

values = np.linalg.solve(M, S)
A = np.sqrt(values[:3]**2 + values[3:]**2)  # Retrieving amplitudes
P = np.arctan2(values[3:], values[:3])  # Retrieving phases
print(A, P)
