% Домашнее задание № 7. Оболочка и скрипты
% 20 января 2023 г.
% Алексей Лисов, ИУ9-11Б

# Цель работы
Научиться работать со скриптовым языком программирования

# Задание 1

## Реализация
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

## Тестирование

### Запуск
```
python3 main.py -d "AaDS"
```

### Вывод
```
├── a.c
├── vgcheck
├── main.c
├── main.py
└── b.txt
```

### Запуск
```
python3 main.py -o "AaDS" "/home/alexey/AaDS/b.txt"
```

### Содержимое файла `"/home/alexey/AaDS/b.txt"`
```
├── a.c
├── vgcheck
├── main.c
├── main.py
└── b.txt
```

# Задание 2

## Реализация
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

## Тестирование

### Содержимое файла `b.txt`

```
├── a.c
├── vgcheck
├── ASDin.c
├── main.py
└── b.txt
```

### Запуск
```
alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -n "/home/alexey/AaDS/b.tx" "a"
```

### Вывод
```
/home/alexey/AaDS/main.py: не удается открыть указанный файл /home/alexey/AaDS/b.tx
```

### Запуск
```
alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -m "/home/alexey/AaDS/b.txt" "a" 1
```

### Вывод
```
├── a.c
```

### Запуск
```
alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -n "/home/alexey/AaDS/b.txt" "a"
```

### Вывод
```
1 ├── a.c

4 ├── main.py
```

### Запуск
```
alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -i "/home/alexey/AaDS/b.txt" "a"
```

### Вывод
```
├── a.c

├── ASDin.c

├── main.py

Паттерн был найден 3 раз
```

# Задание 3

## Реализация

```python
import os
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
    # <ключ> <файл, где ищем>
    if len(sys.argv) == 0:
        inp = input().split()
        key, path = inp
    else:
        key = sys.argv[1]
        path = sys.argv[2]

    if key == '-c':
        print(os.path.getsize(path))
    elif key == '-m':
        a = reading(path)

        if a:
            print(sum([len(i) for i in a]))
    elif key == '-w':
        a = reading(path)

        if a:
            s = ''
            for i in a:
                s += str(i)

            s = s.replace('.', ' ').replace(',', ' ').replace('!', ' ').replace('?', ' ')
            s = len(s.split())
            print(s)
    elif key == '-l':
        a = reading(path)

        if a:
            s = ''
            for i in a:
                s += str(i)

            print(s.count('\n'))
````

### Содержимое файла `b.txt`
```
Hi, i am alex. And i am a BMSTU student.
```

### Запуск
```
alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -c "/home/alexey/AaDS/b.txt"
```
### Вывод
```
84
```

### Запуск
```
alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -m "/home/alexey/AaDS/b.txt"
```
### Вывод
```
54
```

### Запуск
```
alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py -w "/home/alexey/AaDS/b.txt"
```
### Вывод
```
10
```

# Задание 4

## Реализация

```python
import sys

if __name__ == "__main__":
    # <ключ> <файл, где ищем>
    if len(sys.argv) != 3:
        sys.stderr.write(f'{__file__}: Неправильные параметры вызова')

    dct = str(sys.argv[1])
    #dct = "/home/alexey/AaDS/b.txt"
    try:
        with open(dct) as f:
            dictionary = f.readlines()
            dictionary = [i.replace('\n', '') for i in dictionary]
    except:
        sys.stderr.write(f'{__file__}: не удается открыть указанный файл {dct}\n')
        exit(0)

    text = str(sys.argv[2])
    # text = "/home/alexey/AaDS/text.txt"
    try:
        with open(text) as f:
            text = f.readlines()
            s = ''
            for i in text:
                s += str(i)

            s = s.replace('.', ' ').replace(',', ' ').replace('!', ' ').replace('?', ' ')

            now = ''
            begin = -2
            ind_i, ind_j = 0, 1 # идекс_столбца, индекс_строки

            for i in s:
                if i == '\n':
                    ind_i = 0
                    ind_j += 1
                else:
                    ind_i += 1

                if i != ' ' and i != '\n':
                    now += i
                    if begin == -2:
                        begin = [ind_j, ind_i]
                else:
                    if not now in dictionary and now != '':
                        print(f'{begin[0]},\t{begin[1]}\t{now}')
                    begin = -2
                    now = ''

            if not now in dictionary and now != '':
                print(begin, now)
            begin = -2
            now = ''


    except:
        sys.stderr.write(f'{__file__}: не удается открыть указанный файл {text}\n')
        exit(0)
```

### Содержимое файла `b.txt`
Он тут является словарем
```
hi
nice
to
meet
you
```

### Содержимое файла `"/home/alexey/AaDS/text.txt"`
```
hi nice
to meat u
```

### Запуск
```
alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py 
"/home/alexey/AaDS/b.txt" "/home/alexey/AaDS/text.txt"
```
### Вывод
```
2,	4	meat
2,	9	u
```

### Содержимое файла `"/home/alexey/AaDS/text.txt"`
```
hi noce
to meat u
```

### Запуск
alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py 
"/home/alexey/AaDS/b.txt" "/home/alexey/AaDS/text.txt"
### Вывод
1,	4	noce
2,	4	meat
2,	9	u


### Содержимое файла `"/home/alexey/AaDS/text.txt"`
```
hi noce
to meat
u
```

### Запуск
```
alexey@alexey-ASUS-TUF-Gaming-F15-FX506LI-FX506LI:~/AaDS$ python3 main.py 
"/home/alexey/AaDS/b.txt" "/home/alexey/AaDS/text.txt"
```
### Вывод
```
1,	4	noce
2,	4	meat
3,	1	u
```

# Вывод
Я научился работать со скриптовым языком программирования `Python`
и изучил в нём способы работы с файловой системой путем разработки
полезных утилит.
