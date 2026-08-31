import subprocess


while True:
    output = ""

    subprocess.run(["git", "status"], stdout=output)


    print(f"Output: {output}")
