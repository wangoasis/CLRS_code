def LCS(items1, items2):
    m = len(items1)
    n = len(items2)
    max_length = 0
    c, b = [], []
    for i in range(m + 1):
        c.append([0] * (n + 1))
        b.append([""] * (n + 1))
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if items1[i-1] == items2[j-1]:
                c[i][j] = c[i-1][j-1] + 1
                if c[i][j] > max_length:
                    max_length = c[i][j]
                b[i][j] = "skew"
            elif c[i-1][j] >= c[i][j-1]:
                c[i][j] = c[i-1][j]
                b[i][j] = "up"
            else:
                c[i][j] = c[i][j-1]
                b[i][j] = "left"
    return c, b, max_length

def print_LCS(b, x, i, j):
    if i == 0 or j == 0:
        return 
    if b[i][j] == "skew":
        print_LCS(b, x, i - 1, j - 1)
        print x[i-1],
    elif b[i][j] == "up":
        print_LCS(b, x, i - 1, j)
    else:
        print_LCS(b, x, i, j - 1)

if __name__ == "__main__":
    x = ['A', 'B', 'C', 'B', 'D', 'A', 'B']
    y = ['B', 'D', 'C', 'A', 'B', 'A']
    print x
    print y
    c, b, max_length = LCS(x, y)
    print_LCS(b, x, 7, 6)
    print "length: ", max_length
