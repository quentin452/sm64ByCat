import glob
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
    files_to_format = glob.glob("src/**/*.[ch]", recursive=True) + \
                      glob.glob("lib/src/*.[ch]") + \
                      glob.glob("enhancements/*.inc.[ch]")
    format_files(files_to_format)
    print("done.")