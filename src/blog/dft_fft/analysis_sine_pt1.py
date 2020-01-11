T = np.array([1, 2, 3])
F = np.array([0.1, 0.3, 0.8])
A = np.array([3.1, 0.8, 1.4])

M_sine = np.sin(2 * math.pi * np.outer(T, F))  # Matrix for synthesis
S = np.dot(M_sine, A)
print(S)
