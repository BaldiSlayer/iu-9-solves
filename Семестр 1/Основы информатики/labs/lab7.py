import sys, string, random

def string_generation():
    return ''.join(random.choice(string.ascii_letters + string.digits + string.punctuation) for i in range(int(sys.argv[1])))

if __name__ == "__main__":
    if (len(sys.argv) - 1) < 2 or len(sys.argv) > 3:
        print(f'Please, call me like python lab7.py [len_s] [n]')
        exit(0)

    print(*[string_generation() for i in range(int(sys.argv[2]))], sep='\n')