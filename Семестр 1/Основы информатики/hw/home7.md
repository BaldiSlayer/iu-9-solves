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

# Задание 2

```python

import re
import sys


def reading(path):
    a = []
    try:
        with open(path) as f:
            a = f.readlines()
    except:
        sys.stderr.write(f'{__file__}: не удается открыть указанный файл {path}\n')
        return False

    return a


if __name__ == "__main__":
    # <ключ> <файл, где ищем> <что ищем> <кол-во, если -m>
    if len(sys.argv) == 0:
        inp = input().split()
        if inp[0] == '-m':
            key, path, pattern, count = inp
            count = int(count)
        else:
            ey, path, pattern = inp
    else:
        key = sys.argv[1]
        path = sys.argv[2]
        pattern = sys.argv[3]

        if key == '-m':
            count = int(sys.argv[4])

    if key == '-i':
        # регистронезависимый поиск
        a = reading(path)

        if a:
            cnt = 0
            for i in a:
                if pattern.lower() in i.lower():
                    print(i)
                    cnt += 1

            print(f"Паттерн был найден {cnt} раз")
    elif key == '-n':
        # нумерация
        a = reading(path)

        if a:
            j = 0
            for i in a:
                j += 1
                if pattern in i:
                    print(j, i)
    elif key == '-e':
        a = reading()

        if a:
            for i in a:
                if re.match(pattern, i):
                    print(i)
    elif key == '-m':
        a = reading(path)

        if a:
            j = 0
            for i in a:
                if pattern in i:
                    j += 1
                    print(i)

                if j == count:
                    break

```


alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -n "/home/alexey/AaDS/b.tx" "a"
/home/alexey/AaDS/main.py: не удается открыть указанный файл /home/alexey/AaDS/b.tx

alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -m "/home/alexey/AaDS/b.txt" "a" 1
├── a.c


lexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -n "/home/alexey/AaDS/b.txt" "a"
1 ├── a.c

4 ├── main.py



alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -i "/home/alexey/AaDS/b.txt" "a"
├── a.c

├── ASDin.c

├── main.py

Паттерн был найден 3 раз




Содержимое файла b.txt

├── a.c
├── vgcheck
├── ASDin.c
├── main.py
└── b.txt
