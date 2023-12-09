c = None
with open("input") as f:
    for line in f:
        c = len(line.split())
        l = list(map(int, line.split()))
        s = l == sorted(l)
        print(c, s)
        