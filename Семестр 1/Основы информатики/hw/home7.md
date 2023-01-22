# Задание 1

## Без рисования дерева
```python
import os

def list_files(startpath):
    for root, dirs, files in os.walk(startpath):
        level = root.replace(startpath, '').count(os.sep)
        indent = ' ' * 4 * (level)
        print('{}{}/'.format(indent, os.path.basename(root)))
        subindent = ' ' * 4 * (level + 1)
        for f in files:
            print('{}{}'.format(subindent, f))

list_files("/home/alexey/")
```

## Рабочий вариант
```python
import sys
from pathlib import Path

space =  '    '
branch = '│   '
tee =    '├── '
last =   '└── '


def tree(dir_path: Path, prefix: str=''):
    contents = list(dir_path.iterdir())
    pointers = [tee] * (len(contents) - 1) + [last]
    for pointer, path in zip(pointers, contents):
        yield prefix + pointer + path.name
        if path.is_dir():
            extension = branch if pointer == tee else space
            yield from tree(path, prefix=prefix+extension)


def solver(path):
    lst = list()
    for line in tree(Path.home() / path):
        lst.append(line)
    return lst

if __name__ == "__main__":
    if (len(sys.argv) - 1) < 2 or len(sys.argv) > 4 or sys.argv[1] not in ['-d', '-o']:
        print(f'Unknown cmd')
        exit(0)


    out = solver(str(sys.argv[2]))

    if sys.argv[1] == '-d':
        print(*out, '\n')
    else:
        with open(sys.argv[3], 'w') as f:
            for i in out:
                print(i, type(i))
                f.writelines(str(i) + '\n')
```
```
├── a.c
├── vgcheck
├── main.c
├── main.py
└── b.txt
```
```
python3 main.py -o "AaDS" "/home/alexey/AaDS/b.txt"
python3 main.py -d "AaDS"
```
