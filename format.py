import os
import subprocess
import sys

def format_files(files):
    for file in files:
        subprocess.run(["clang-format", "-i", "-style=file", file])

if len(sys.argv) > 1:
    print(f"formatting file(s) {sys.argv[1:]}")
    format_files(sys.argv[1:])
    print("done.")
else:
    print("formatting...")
    format_files(["src/**/*.c", "lib/src/*.c", "enhancements/*.inc.c"])
    print("done.")
