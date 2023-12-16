with open("input") as f:
    steps = f.readline().strip().split(",")

def hash(step, includeFn=lambda x: True):
    """
    Determine the ASCII code for the current character of the string.
    Increase the current value by the ASCII code you just determined.
    Set the current value to itself multiplied by 17.
    Set the current value to the remainder of dividing itself by 256.
    """

    cur_val = 0
    for ch in step:
        if includeFn(ch):
            cur_val += ord(ch)
            cur_val = cur_val * 17
            cur_val = cur_val % 256
    return cur_val


s = 0
for step in steps:
    s += hash(step)

print("Part 1 answer", s)

boxes=[[] for _ in range(256)]

part2_constraint = lambda x: x >= 'a' and x <= 'z'

for step in steps:
    if "=" in step:
        label, fl = step.split("=")
        box_no = hash(label, part2_constraint)
        box = boxes[box_no]
        if len(box) == 0:
            box.append((label, fl))
        else:
            for i, (ll, _) in enumerate(box):
                if ll == label:
                    box[i] = (label, fl)
                    break
            else:
                box.append((label, fl))
    else:
        label, _ = step.split("-")
        box_no = hash(label, part2_constraint)
        box = boxes[box_no]
        if len(box) == 0:
            continue

        for i, (ll, _) in enumerate(box):
            if ll == label:
                box.pop(i)
                break

s = 0
for i, box in enumerate(boxes):
    for j, (_, fl) in enumerate(box):
        value = (i+1) * (j+1) * int(fl)
        s += value

print("Part 2 answer", s)