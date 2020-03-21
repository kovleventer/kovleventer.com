import numpy as np
from scipy.io import wavfile
import matplotlib.pyplot as plt

sample_rate, data = wavfile.read(
	"321232__night-soundscapes__horror-train-effect.wav")

# Convert it to mono by averaging left and right channels
data = data.sum(axis=1) / 2

spectrum = np.fft.rfft(data)
frequencies = np.fft.rfftfreq(len(data), 1/sample_rate)  # Time between samples

# Plot the spectrum finally
plt.plot(frequencies, np.abs(spectrum))
plt.show()
