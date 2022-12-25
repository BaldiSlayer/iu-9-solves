def mem(func, *args):
    if not args in d:
        d[args] = func(args)
    return d[args]

def f(*args):
    print("I'm counting....")
    return sum(list(args[0]))

d = dict()
print(mem(f, 1, 3))
print(mem(f, 1, 2))
print(mem(f, 1, 3))
print(mem(f, 1, 3))
print(mem(f, 1, 3))
print(mem(f, 1, 3))
print(mem(f, 1, 3))
print(mem(f, 1, 3))
print(mem(f, 1, 3))
print(mem(f, 1, 3))
