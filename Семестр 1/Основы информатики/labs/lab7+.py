def mem(func, *args):
    if not args in d:
        d[args] = test(args)
    return d[args]

def test(*args):
    print("I'm counting....")
    return sum(list(args[0]))

d = dict()
print(mem(test, 1, 3))
print(mem(test, 1, 2))
print(mem(test, 1, 3))
print(mem(test, 1, 3))
print(mem(test, 1, 3))
print(mem(test, 1, 3))
print(mem(test, 1, 3))
print(mem(test, 1, 3))
print(mem(test, 1, 3))
print(mem(test, 1, 3))