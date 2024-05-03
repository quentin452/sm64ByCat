import glob
import os
import heapq
import logging

def find_largest_files(files, n=100):
    sizes_files = [(os.path.getsize(file), file) for file in files]
    return heapq.nlargest(n, sizes_files)

# Récupérer le nom du script sans l'extension
script_name = os.path.splitext(os.path.basename(__file__))[0]

# Configurer le logger pour écrire dans un fichier .txt
logging.basicConfig(filename=f'{script_name}.txt', level=logging.INFO)

directories = [
    "**/*.c", "**/*.h",
]

logging.info("Largest files:")
for directory in directories:
    files = glob.glob(directory, recursive=True)
    if files:
        largest_files = find_largest_files(files)
        for size, file in largest_files:
            logging.info(f"Directory: {directory}")
            logging.info(f"File: {file}")
            logging.info(f"Size: {size} bytes")
            logging.info("")
