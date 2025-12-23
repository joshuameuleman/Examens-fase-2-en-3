#- Naam: Joshua Meuleman

#- Datum: 14/11/2025

#- Data Analysis - Oefening 3



import sys
import argparse

try:
	import sounddevice as sd
	import soundfile as sf
	import numpy as np
	import matplotlib.pyplot as plt
except Exception as e:
	print("Fout bij importeren van benodigde packages:", e)
	print("Installeer de dependencies met:")
	print("  pip install sounddevice soundfile numpy matplotlib")
	sys.exit(1)


def record_play_save(filename: str = 'test.wav', duration: float = 5.0, samplerate: int = 44100, channels: int = 2):
	print(f"Opnemen: {duration} s, {samplerate} Hz, kanalen={channels}")
	try:
		recording = sd.rec(int(duration * samplerate), samplerate=samplerate, channels=channels, dtype='float32')
		sd.wait()
	except Exception as e:
		print("Fout tijdens opnemen:", e)
		print("Controleer of er een werkende microfoon is en dat de audio drivers toegankelijk zijn.")
		raise

	print("Opname voltooid. Afspelen...")
	try:
		sd.play(recording, samplerate)
		sd.wait()
	except Exception as e:
		print("Fout tijdens afspelen:", e)
		# Niet fataal: we blijven verder gaan om op te slaan en plotten

	try:
		sf.write(filename, recording, samplerate)
		print(f"Opname opgeslagen naar: {filename}")
	except Exception as e:
		print("Fout tijdens opslaan van bestand:", e)
		raise

	return recording, samplerate


def plot_channels(recording: np.ndarray, samplerate: int):
	# Zorg dat data 2D is: (n_samples, n_channels)
	if recording.ndim == 1:
		data = recording.reshape(-1, 1)
	else:
		data = recording

	n_samples, n_channels = data.shape
	t = np.arange(n_samples) / float(samplerate)

	plt.figure(figsize=(10, 4))
	if n_channels >= 1:
		plt.plot(t, data[:, 0], label='Left (L)')
	if n_channels >= 2:
		plt.plot(t, data[:, 1], label='Right (R)')

	plt.xlabel('Tijd (s)')
	plt.ylabel('Amplitude')
	plt.title('Opnamekanalen (L & R)')
	plt.legend()
	plt.tight_layout()
	plt.show()


def main():
	parser = argparse.ArgumentParser(description='Opname, afspelen, opslaan en plotten van audio (L & R).')
	parser.add_argument('--duration', '-d', type=float, default=5.0, help='Opnameduur in seconden')
	parser.add_argument('--samplerate', '-r', type=int, default=44100, help='Samplerate in Hz')
	parser.add_argument('--outfile', '-o', type=str, default='test.wav', help='Output wav-bestand')
	parser.add_argument('--channels', '-c', type=int, default=2, help='Aantal kanalen (1=mono, 2=stereo)')
	args = parser.parse_args()

	try:
		recording, sr = record_play_save(filename=args.outfile, duration=args.duration, samplerate=args.samplerate, channels=args.channels)
	except Exception:
		print("Opname mislukt. Stop.")
		sys.exit(1)

	try:
		plot_channels(recording, sr)
	except Exception as e:
		print("Fout tijdens plotten:", e)


if __name__ == '__main__':
	main()



