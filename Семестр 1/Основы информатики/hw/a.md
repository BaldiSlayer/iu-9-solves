% Домашнее задание № 7. Оболочка и скрипты
% 15 декабря 2022 г.
% Михаил Филимонов, ИУ9-11Б
# Цель работы
Реализовать некоторые утилиты, такие как tree, grep, wc из ОС Linux 
на скриптовом языке программирования. Научится делать собственный т9.
# Реализация

# Задание 4. `speller.py`

```python
import sys

def spell_check(dictionary, text):
  # Load the dictionary
  with open(dictionary, "r") as file:
    words = set([line.strip() for line in file])

  # Initialize the list of misspelled words
  misspellings = []
  # Check the spelling of each word in the text
  line_number = 0
  for line in text:
    words_len = 0
    line_number += 1
    column_number = 0
    for word in line.split():
      column_number += 1
      if word.lower() not in words:
        misspellings.append((line_number, words_len, word))
      words_len+=len(word)+1

  # Return the list of misspellings
  return misspellings

def main():
  # Parse the command line arguments
  dictionary = sys.argv[1]
  text_file = sys.argv[2]

  # Read the text
  with open(text_file, "r") as file:
    text = file.readlines()

  # Check the spelling of the text
  misspellings = spell_check(dictionary, text)

  # Print the misspellings
  for line_number, words_len, word in misspellings:
    sys.stdout.write("{}.{} {}\n".format(line_number, words_len, word))

if __name__ == "__main__":
  main()
```  
  
# Задание 1. `tree.py`

```python
#!/usr/bin/python3

import argparse
import os
import errno
import sys


def get_tree(directories_only, path='.'):

	def get_tree_recursive(path):
		try:
			fs_objects = os.listdir(path)
		except:
			return {'files': []}

		if directories_only:
			files = []
		else:
			files = list(filter(lambda fs_object:
 os.path.isfile(os.path.join(path, fs_object)), fs_objects))
		
		directories = list(filter(lambda fs_object: not
 os.path.isfile(os.path.join(path, fs_object)), fs_objects))
		directory_dict = {'files': files}
		for directory in directories:
			directory_dict['_' + directory] =
 get_tree_recursive(os.path.join(path, directory))
		return directory_dict


	return (path, get_tree_recursive(path or '.'))


def display_tree(tree, output_path):
	if output_path is not None:
		sys.stdout = open(output_path, 'w+')

	SPACE = ' '
	TREE_SPACE = '   '
	CONNECTOR = '├──'
	CONNECTOR_END = '└──'
	LINE = '│'
	EMPTY_LINE = ' ' * len(LINE)
	BOLD = lambda text: '\033[1m' + text + '\033[0m'

	root = tree[0]
	tree = tree[1]
	print(BOLD(root))

	def display_tree_recursive(tree, prefix):
		if len(tree['files']) > 0:
			files = tree['files']
			for file in files[:-1]:
				print(prefix + CONNECTOR + SPACE + file)	

			print(prefix  + (CONNECTOR if len(tree) > 1 else 
CONNECTOR_END) + SPACE + files[-1])

		if len(tree) > 1:
			directories = list(tree.items())[1:]

			for directory, directory_tree in directories[:-1]:
				directory = directory[1:] #  убираем нижнее 
подчёркивание '_', добавленное в get_tree()
				print(prefix + CONNECTOR + SPACE + BOLD(directory))
				display_tree_recursive(directory_tree, prefix + 
LINE + TREE_SPACE)

			print(prefix + CONNECTOR_END + SPACE + BOLD(
 "_".join(directories[-1][0].split('_')[1:])))
			display_tree_recursive(directories[-1][1], prefix + 
TREE_SPACE + EMPTY_LINE)


	display_tree_recursive(tree, '')


def process_path_argument(parser, argument):
	if os.path.exists(argument):
		if not os.path.isfile(argument):
			parser.error(f'Требуется указать путь до файла')
		elif not os.access(argument, os.W_OK):
			parser.error(f'Нет доступа на запись в файл {argument}')
		else:
			return argument
	else:
		try:
			os.makedirs(os.path.dirname(argument))
		except OSError as error:
			if error.errno != errno.EEXIST:
				parser.error(f'Не удается создать файл
 {argument}. Ошибка: {error}')
		
		return argument


parser = argparse.ArgumentParser(add_help=False)
parser.add_argument('-d', dest='directories_only', action='store_true')
parser.add_argument('-o', dest='output_path', type=lambda path: process_path_argument(parser, path))
args, unknowns = parser.parse_known_args()

if __name__ == '__main__':
	
	for path in unknowns:
		if not os.path.exists(path) or not os.path.isdir(path) or not os.access(path, os.R_OK):
			sys.stderr.write(f'{__file__}: не удалось открыть директорию {path}\n')
		else:
			display_tree(get_tree(args.directories_only, path), args.output_path)
	
	if len(unknowns) == 0:
		display_tree(get_tree(args.directories_only), args.output_path)
```

## Задание 3. `grep.py`
```python
#!/usr/bin/python3

import argparse
import sys
import re


def get_contents(streams):
	contents = {}
	for stream in streams:
		contents[stream.name] = stream.read().strip()
	return contents


def grep(contents, pattern, ignore_case, display_line_number,
         regexp, max_count):
	prefix = ''
	if len(contents) > 1:
		prefix = '{filename}:'

	if display_line_number:
		prefix += '{line_number}:'

	prefix += ' ' * 4

	for name, text in contents.items():
		lines = text.split('\n')
		count = 0

		for i, line in enumerate(lines, 1):

			if max_count is not None and count == max_count:
				break

			output = ''
			if regexp is not None:
				if re.findall(regexp, line):
					output = prefix.format(filename=name,
                                                               line_number=i) + line
			elif ignore_case and pattern.lower() in line.lower()
			or pattern in line:
				output = prefix.format(filename=name,
                                                       line_number=i) + line

			if output:
				print(output)
				count += 1



def parse_unknowns(parser, unknowns):
	streams = []
	pattern = None
	for unknown in unknowns:
		try:
			streams.append(open(unknown, 'r'))
		except:
			if pattern is None:
				pattern	= unknown
			else:
				sys.stderr.write(f'{__file__}: не удается
                                                 открыть указанный файл {unknown}\n')
	return pattern, streams


parser = argparse.ArgumentParser()
parser.add_argument('-i', dest='ignore_case', action='store_true')
parser.add_argument('-n', dest='line_number', action='store_true')
parser.add_argument('-e', dest='regexp', type=str)
parser.add_argument('-m', dest='max_count', type=int)

args, unknowns = parser.parse_known_args()


if __name__ == '__main__':
	pattern, streams = parse_unknowns(parser, unknowns)
 	
	if not sys.stdin.isatty() and len(streams) == 0:
		streams.append(sys.stdin)

	if len(streams) == 0:
		parser.error('Требуется указать путь до файа
                             или передать текст в стандартный поток ввода')

	if args.regexp is None and pattern is None:
		parser.error('Требуется передать выражение для сопоставления')

	contents = get_contents(streams)
	grep(contents, pattern, args.ignore_case, args.line_number,
             args.regexp, args.max_count)```

```
# Тестирование
```
C:\Users\kkras\OneDrive\Рабочий стол>py grep.py -i 123 txt.txt dictionary.txt
txt.txt:    123
txt.txt:    123
txt.txt:    123
dictionary.txt:    123
dictionary.txt:    Р·РґРµСЃСЊ РµСЃС‚СЊ 123
dictionary.txt:    123
```


```
C:\Users\kkras\OneDrive\Рабочий стол>py grep.py -i 123 txt.txt
    123
    123
    123
C:\Users\kkras\OneDrive\Рабочий стол>py tree.py -d .
.
├── I семестр
│   ├── Алгоритмы и структуры данных
│   ├── Английский язык
│   ├── ЛАиАГ
│   │   ├── Модуль 1. Аналитическая геометрия
│   │   │   ├── NEW Коллок (вопросы)
│   │   │   │   ├── Полный список
│   │   │   │   └── Сокращенный список
│   │   │   ├── NEW Рк (подготовка)
│   │   │   ├── OLD Коллок
│   │   │   │   └── Ответы к коллоквиуму
│   │   │   └── OLD Рк (варианты + решения)
│   │   │       └── Еще решения
│   │   ├── Модуль 2. Алгебраические структуры
│   │   │   ├── 2020 Рк2 (практика)
│   │   │   │   └── 2020
│   │   │   └── 2020 Теория
│   │   ├── Модуль 3. Матрицы и СЛАУ
│   │   │   ├── 2020 Рк3 (практика)
│   │   │   └── Примеры вариантов
│   │   │       ├── 2019
│   │   │       └── старое
│   │   │           └── Некоторые решения
│   │   ├── Полезная литература
│   │   │   └── Рукописные лекции
│   │   └── Экзамен
│   │       ├── Билеты 2020 (не актуальны  на 2021-2022)
│   │       ├── Ответы к экзамену[1]
│   │       ├── Ответы к экзамену[2]
│   │       ├── Ответы к экзамену[3]
│   │       └── Примеры билетов
│   │           ├── новые задачи 2020
│   │           └── старые задачи и теория
│   ├── Математический анализ
│   │   ├── Домашки
│   │   │   ├── ДЗ2
│   │   │   └── ДЗ3
│   │   ├── Модуль 1. Введение в анализ
│   │   │   └── Ответы к коллоквиуму
│   │   ├── Модуль 2. Предел и непрерывность
│   │   │   ├── Ответы на теорию
│   │   │   └── Примеры вариантов
│   │   ├── Модуль 3. Производная
│   │   ├── Модуль 4. Дифференциальные исчисления
│   │   │   └── Примеры вариантов
│   │   ├── Полезная литература
│   │   └── Экзамен
│   │       ├── Ответы к экзамену
│   │       └── Примеры билетов
│   └── Основы информатики
│       ├── Лабораторные работы
│       ├── Полезная литература
│       └── Экзамен
│           └── Билеты
└── домашка
    ├── .idea
    └── cmake-build-debug
        ├── .cmake
        │   └── api
        │       └── v1
        │           └── query
        └── CMakeFiles
            ├── 3.23.2
            │   ├── CompilerIdC
            │   │   └── tmp
            │   └── CompilerIdCXX
            │       └── tmp
            └── CMakeTmp
   ```
# Вывод
Изучил некоторые утилиты линукс, научился работать с некоторыми 
библиотеками Python, реализовывать собственные функции для
текстовой редакции
