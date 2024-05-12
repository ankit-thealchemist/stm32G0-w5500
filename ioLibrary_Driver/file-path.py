from pathlib import Path

cwd = Path.cwd()
pattern = r".*\.(h|c)$"
suffexies = ['.h', '.c']
header_path = []
source_path = []

with open("source.txt", "a") as source, open("header.txt", "a") as header:
    for fileName in cwd.rglob('*'):
        if fileName.suffix == '.c':
            print(fileName.relative_to(cwd))
            source.write(str(fileName.relative_to(cwd))+'\n')

        if fileName.suffix == '.h':
            print(fileName.parent.relative_to(cwd))
            header.write(str(fileName.parent.relative_to(cwd))+'/\n')