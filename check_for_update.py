#!/usr/bin/env python3

import subprocess
import datetime
import time
import argparse

parser = argparse.ArgumentParser(
    prog='check_for_update',
    description='Automatically commits code every [10] minutes',
    epilog='Hello and Goodbye :)'
)

parser.add_argument('-p', '--period')

args = parser.parse_args()

while True:
    if subprocess.check_output(["git", "status", "--porcelain"]):
        t = datetime.datetime.now()

        print("Making commit... ", end="")

        message = f"Automatic commit {t.strftime("%m%d%y%H%M%S")}"
        
        subprocess.run(["git", "add", "."])
        subprocess.run(["git", "commit", "-m", message])

        print(f"\"{message}\"")
    else:
        print("Skipping commit: no changes")

    time.sleep(int(args.period or 10) * 60)
