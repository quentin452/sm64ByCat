import glob
import os
import heapq

def find_largest_files(files, n=100):
    sizes_files = [(os.path.getsize(file), file) for file in files]
    return heapq.nlargest(n, sizes_files)

directories = [
    "**/*.c", "**/*.h",
]

print("Largest files:")
for directory in directories:
    files = glob.glob(directory, recursive=True)
    if files:
        largest_files = find_largest_files(files)
        for size, file in largest_files:
            print(f"Directory: {directory}")
            print(f"File: {file}")
            print(f"Size: {size} bytes")
            print()
