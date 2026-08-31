import subprocess
import datetime

while True:


    if subprocess.check_output(["git", "status"]):
        message = f"Periodic commit {datetime.datetime.now()}"
        
        # subprocess.run(["git", "add", "."])
        # subprocess.run(["git", "commit", "-m", ])
        print()
    else:
        pass


