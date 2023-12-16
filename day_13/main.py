datas = []
with open("./input") as file:
    data = []
    for line in file:
        if len(line.strip()) == 0:
            datas.append(data)
            data = []
            continue
        data.append(list(line.strip()))
    datas.append(data)

def calc(data, prevRowAnswer=None, prevColAnswer=None):
    allColMatches = dict()
    for line in data:
        for i in range(1, len(line)):
            j = 1
            match = True
            while (i-j) >= 0 and (i+j-1) < len(line):
                if line[i-j] == line[i+j-1]:
                    j += 1
                else:
                    match = False
                    break
            if match and ((i-j) < 0 or (i+j-1) >= len(line)):
                if i not in allColMatches:
                    allColMatches[i] = 0
                allColMatches[i] += 1

    allRowMatches = dict()
    for c in range(len(data[0])):
        for i in range(1, len(data)):
            j = 1
            match = True
            while (i-j) >= 0 and (i+j-1) < len(data):
                if data[i-j][c] == data[i+j-1][c]:
                    j += 1
                else:
                    match = False
                    break
            if match and ((i-j) < 0 or (i+j-1) >= len(data)):
                if i not in allRowMatches:
                    allRowMatches[i] = 0
                allRowMatches[i] += 1

    colAnswer = None
    rowAnswer = None
    for k, v in allColMatches.items():
        if v == len(data) and k != prevColAnswer:
            colAnswer = k
            break

    for k, v in allRowMatches.items():
        if v == len(data[0]) and k != prevRowAnswer:
            rowAnswer = k
            break

    return allColMatches, allRowMatches, colAnswer, rowAnswer

    

cols = []
rows = []

colsP2 = []
rowsP2 = []

for data in datas:
    allColMatches, allRowMatches, colAnswer, rowAnswer = calc(data, None, None)
    if colAnswer:
        cols.append(colAnswer)
    
    if rowAnswer:
        rows.append(rowAnswer)

    colWithSmudge = None
    for k, v in allColMatches.items():
        if v == len(data) - 1:
            colWithSmudge = k
            break

    rowWithSmudge = None
    for k, v in allRowMatches.items():
        if v == len(data[0]) - 1:
            rowWithSmudge = k
            break

    if colWithSmudge:
        for line in data:
            i = colWithSmudge
            j = 1
            while (i-j) >= 0 and (i+j-1) < len(line):
                if line[i-j] == line[i+j-1]:
                    j += 1
                else:
                    diffLeft = i-j
                    diffRight = len(line) - (i+j-1)
                    if diffLeft > diffRight:
                        line[i+j-1] = '#' if line[i+j-1] == '.' else '.'
                    else:
                        line[i-j] = '#' if line[i-j] == '.' else '.'
                    break

    if rowWithSmudge:
        for c in range(len(data[0])):
            i = rowWithSmudge
            j = 1
            while (i-j) >= 0 and (i+j-1) < len(data):
                if data[i-j][c] == data[i+j-1][c]:
                    j += 1
                else:
                    diffLeft = i-j
                    diffRight = len(data) - (i+j-1)
                    if diffLeft > diffRight:
                        data[i+j-1][c] = '#' if data[i+j-1][c] == '.' else '.'
                    else:
                        data[i-j][c] = '#' if data[i-j][c] == '.' else '.'
                    break

    _, _, colAnswer, rowAnswer = calc(data, rowAnswer, colAnswer)
    if colAnswer:
        colsP2.append(colAnswer)
    
    if rowAnswer:
        rowsP2.append(rowAnswer)


result =sum(cols) + sum(map(lambda x: x*100, rows))
print("Part 1 answer:", result)

result =sum(colsP2) + sum(map(lambda x: x*100, rowsP2))
print("Part 2 answer:", result)