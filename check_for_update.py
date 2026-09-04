import subprocess
import datetime
import time

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

    time.sleep(10 * 60)
