data = []
with open('input') as file:
    for line in file:
        data.append(list(line.strip()))

for c in range(len(data[0])):
    stop = -1
    for r in range(len(data)):
        if data[r][c] == 'O':
            data[r][c] = '.'
            data[stop+1][c] = 'O'
            stop += 1
        elif data[r][c] == '#':
            stop = r
        else:
            continue

s = 0
for i, line in enumerate(reversed(data), start=1):
    o_count = 0
    for ch in line:
        if ch == 'O':
            o_count += 1
    s += (o_count * i)

print("Part 1:", s)

seen = dict()
# the patterns we get repeat after some time
# 120th pattern happens to be the same as 1B
for i in range(120):
    # north
    for c in range(len(data[0])):
        stop = -1
        for r in range(len(data)):
            if data[r][c] == 'O':
                data[r][c] = '.'
                data[stop+1][c] = 'O'
                stop += 1
            elif data[r][c] == '#':
                stop = r
            else:
                continue

    # west
    for r in range(len(data)):
        stop = -1
        for c in range(len(data[0])):
            if data[r][c] == 'O':
                data[r][c] = '.'
                data[r][stop+1] = 'O'
                stop += 1
            elif data[r][c] == '#':
                stop = c
            else:
                continue

    # south
    for c in range(len(data[0])):
        stop = len(data)
        for r in reversed(range(len(data))):
            if data[r][c] == 'O':
                data[r][c] = '.'
                data[stop-1][c] = 'O'
                stop -= 1
            elif data[r][c] == '#':
                stop = r
            else:
                continue

    # east
    for r in range(len(data)):
        stop = len(data[0])
        for c in reversed(range(len(data[0]))):
            if data[r][c] == 'O':
                data[r][c] = '.'
                data[r][stop-1] = 'O'
                stop -= 1
            elif data[r][c] == '#':
                stop = c
            else:
                continue

    a = "\n".join(map(lambda x: "".join(x), data))
    if a in seen:
        if i > 1000:
            v = seen[a]
            print(i, v)
            break
        else:
            v = seen[a]
            print(i, v)
            seen[a].append(i)
    else:
        seen[a] = [i]


s = 0
for i, line in enumerate(reversed(data), start=1):
    o_count = 0
    for ch in line:
        if ch == 'O':
            o_count += 1
    s += (o_count * i)

print("Part 2:", s)