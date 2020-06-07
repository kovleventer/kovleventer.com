import numpy as np

def pack_2real_fft(x, y):
    z = x + y * 1j
    Z = np.fft.fft(z)
    Zminconj = np.roll(np.flip(Z), 1).conj()
    Zx =  0.5  * (Z + Zminconj)
    Zy = -0.5j * (Z - Zminconj)
    return Zx, Zy

# Testing
x = np.array([1, 2, 4, 6, 7])
y = np.array([9, 4, 6, 3, 1])
print(np.fft.fft(x))
print(np.fft.fft(y))

X, Y = pack_2real_fft(x, y)
print(X)
print(Y)
