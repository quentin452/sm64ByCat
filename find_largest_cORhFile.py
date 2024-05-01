import glob
import os

def find_largest_file(files):
    max_size = 0
    largest_file = ""
    for file in files:
        size = os.path.getsize(file)
        if size > max_size:
            max_size = size
            largest_file = file
    return largest_file, max_size

directories = [
    "src/**/*.c", "src/**/*.h",
    "lib/src/*.c", "lib/src/*.h",
    "enhancements/*.inc.c", "enhancements/*.inc.h"
]

largest_files = {}
for directory in directories:
    files = glob.glob(directory, recursive=True)
    if files:
        largest_file, max_size = find_largest_file(files)
        largest_files[directory] = {"file": largest_file, "size": max_size}

print("Largest files:")
for directory, info in largest_files.items():
    print(f"Directory: {directory}")
    print(f"File: {info['file']}")
    print(f"Size: {info['size']} bytes")
    print()