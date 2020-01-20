import numpy as np
import math

T = np.arange(6)  # 0, 1, 2, 3, 4, 5
F = np.array([0.1, 0.3, 0.8])  # Frequencies
A = np.array([3.1, 0.8, 1.4])  # Amplitudes
P = np.array([1.2, 1.3, 1.5])  # Phases

M = np.cos(math.pi * 2 * np.outer(T, F) - np.outer(np.ones((len(T),)), P))
S = np.dot(M, A)  # The resulting signal
print(S)
