import csv
import matplotlib.pyplot as plt

labels = []
times = []

# Wczytaj dane z results.csv
with open("out/results_avg.csv", newline='') as csvfile:
    reader = csv.reader(csvfile)
    next(reader)  # pomiń nagłówek
    for row in reader:
        if len(row) != 2:
            continue
        labels.append(row[0])
        times.append(float(row[1]))

# Sortowanie według czasu rosnąco
sorted_data = sorted(zip(times, labels))
sorted_times, sorted_labels = zip(*sorted_data)

# Tworzenie wykresu
plt.figure(figsize=(12, 6))
bars = plt.barh(sorted_labels, sorted_times, color='skyblue')
plt.xlabel("Czas wykonania (ms)")
plt.title("Porównanie wydajności różnych implementacji")

# Dodaj wartości liczbowo na końcu słupków
for bar in bars:
    width = bar.get_width()
    plt.text(width + 5, bar.get_y() + bar.get_height() / 2,
             f"{width:.1f} ms", va='center')

plt.tight_layout()
plt.show()

