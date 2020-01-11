M_sine = np.sin(2 * math.pi * np.outer(T, F))  # Matrix for synthesis
S = np.dot(M_sine, A)

M_cosine = np.cos(2 * math.pi * np.outer(T, F))  # Matrix for analysis
A_calc = np.linalg.solve(M_cosine, S)
print(A_calc)  # Should be the same as A
