import numpy as np
import math

T = np.array([0, 1, 2])  # Times where we sample; equivalent to np.arange(3)
F = np.array([0.1, 0.3, 0.8])  # Frequencies
A = np.array([3.1, 0.8, 1.4])  # Amplitudes

M = np.cos(2 * math.pi * np.outer(T, F))
S = np.dot(M, A)  # Our resulting signal sampled at three time values

A_calc = np.linalg.solve(M, S)
print(A_calc)  # Should be the same as A
