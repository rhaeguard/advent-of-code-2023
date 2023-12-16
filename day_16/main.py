floor_plan = []

with open("input") as f:
    for line in f:
        floor_plan.append(list(line.strip()))
                          
height = len(floor_plan)
width = len(floor_plan[0])

def find_energized(beams):
    energized = [
        [0 for _ in range(width)] for _ in range(height)
    ]

    seen = set()

    while len(list(filter(lambda x: x[3], beams))) != 0:
        i = 0
        size = len(beams)
        while i < size:
            _r, _c, _, _ = beams[i]
            r, c, d, _ = beams[i]
            if d == 'r':
                c += 1
            elif d == 'l':
                c -= 1
            elif d == 'd':
                r += 1
            else:
                r -= 1 # up

            # validate values
            if r < 0 or r >= height or c < 0 or c >= width or ((_r, _c, d) in seen):
                beams[i][3] = False
                i += 1
                continue

            nd = d
            v = floor_plan[r][c]
            energized[r][c] = 1
            if v == '\\':
                if d == 'r':
                    nd = 'd'
                elif d == 'l':
                    nd = 'u'
                elif d == 'u':
                    nd = 'l'
                else:
                    nd = 'r'
                seen.add((_r, _c, d))
                beams[i] = [r, c, nd, True]
            elif v == '/':
                if d == 'r':
                    nd = 'u'
                elif d == 'l':
                    nd = 'd'
                elif d == 'u':
                    nd = 'r'
                else:
                    nd = 'l'
                seen.add((_r, _c, d))
                beams[i] = [r, c, nd, True]
            elif v == '|':
                if d == 'l' or d == 'r':
                    # create two beams
                    beams[i] = [r, c, 'u', True]
                    beams.append([r, c, 'd', True])
                    seen.add((_r, _c, d))
                else:
                    beams[i] = [r, c, d, True]
            elif v == '-':
                if d == 'u' or d == 'd':
                    # create two beams
                    beams[i] = [r, c, 'l', True]
                    beams.append([r, c, 'r', True])
                    seen.add((_r, _c, d))
                else:
                    beams[i] = [r, c, d, True]
            else:
                beams[i] = [r, c, d, True]
            i += 1

    s = 0
    for y in range(height):
        for x in range(width):
            s += 1 if energized[y][x] > 0 else 0
            
    return s

inp = [[0, -1, 'r', True]]
p1 = find_energized(inp)
print("Part 1", p1)

def get_config():
    for row in range(height):
        for col in range(width):
            if col == 0 or row == 0:
                if col == 0:
                    yield [row, -1, 'r', True]
                elif row == 0:
                    yield [-1, col, 'd', True]

    for row in range(height):
        for col in range(width):
            if col == width-1 or row == height-1:
                if col == width-1:
                    yield [row, width, 'l', True]
                elif row == height-1:
                    yield [height, col, 'u', True]

m = -1
for inp in list(get_config()):
    v = find_energized([inp])
    m = max(v, m)
        
print("Part 2", m)