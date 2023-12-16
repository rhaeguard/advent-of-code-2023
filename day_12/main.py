def solve(pattern, numbers, seen):
    key = tuple(pattern + numbers)
    if key in seen:
        return seen[key]
    
    result = None
    if len(pattern) == 0 and len(numbers) == 0:
        result = 1
    elif len(pattern) == 0 and len(numbers) != 0:
        result = 0
    elif len(pattern) != 0 and len(numbers) == 0:
        for p in pattern:
            if p == '#':
                result = 0
                break
        else:
            result = 1
    elif pattern[0] == '.':
        result = solve(pattern[1:], numbers, seen)
    elif pattern[0] == '#':
        i = 0
        while i < len(pattern) and pattern[i] == '#':
            i += 1
        
        if i == numbers[0]:
            if i == len(pattern):
                result = solve(pattern[i:], numbers[1:], seen)
            elif pattern[i] == '.':
                result = solve(pattern[i:], numbers[1:], seen)
            else:
                pattern[i] = '.'
                result = solve(pattern[i:], numbers[1:], seen)
        elif i > numbers[0]:
            result = 0
        elif i < len(pattern) and pattern[i] == '.':
            result = 0
        elif i < len(pattern) and pattern[i] == '?':
            pattern[i] = '#'
            result = solve(pattern, numbers, seen)
        else:
            result = 0        
    else:
        pattern[0] = '.'
        a = solve(pattern, numbers, seen)
        pattern[0] = '#'
        b = solve(pattern, numbers, seen)
        result = a + b

    seen[key] = result
    return result

p1 = 0
p1_seen = dict()
p2 = 0
p2_seen = dict()

with open("input") as f:
    for i, line in enumerate(f):
        pattern, numbers = line.split()
        numbers = list(map(int, numbers.strip().split(",")))
        p1 += solve(list(pattern), numbers, p1_seen)

        pattern, numbers = line.split()
        pattern = "?".join([pattern] * 5)
        numbers = ",".join([numbers] * 5)

        numbers = list(map(int, numbers.strip().split(",")))
        p2 += solve(list(pattern), numbers, p2_seen)

print("Part 1:", p1)
print("Part 2:", p2)