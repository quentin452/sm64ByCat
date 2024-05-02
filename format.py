import glob
import os
import subprocess
import sys
import threading

def format_files(files):
    blacklist = ["sound_data.tbl.inc.c"]
    for file in files:
        if os.path.basename(file) not in blacklist:
            print(f"Formatting {file}...")
            subprocess.run(["clang-format", "-i", "-style=file", file], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        else:
            print(f"Skipping {file}...")

if len(sys.argv) > 1:
    print(f"formatting file(s) {sys.argv[1:]}")
    format_thread = threading.Thread(target=format_files, args=(sys.argv[1:],))
    format_thread.start()
    format_thread.join()
    print("done.")
else:
    print("formatting...")
    files_to_format = glob.glob("src/**/*.[chin]", recursive=True) + \
                      glob.glob("lib/src/*.[chin]", recursive=True) + \
                      glob.glob("data/**/*.[chin]", recursive=True) + \
                      glob.glob("enhancements/*.inc.[chin]", recursive=True)
    format_thread = threading.Thread(target=format_files, args=(files_to_format,))
    format_thread.start()
    format_thread.join()
    print("done.")