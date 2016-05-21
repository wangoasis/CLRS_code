def counting_sort(seq, k):

    count = [0] * k
    sn = len(seq)

    for i in range(sn):
        count[seq[i]] += 1

    ac = count[:]
    for i in range(1,k):
        ac[i] += ac[i-1]

    act = ac[:]
    i = sn - 1
    while i >= 0:
        elem = seq[i]
        if ac[elem] - count[elem] <= i <= ac[elem] - 1:
            act[elem] -= 1
            i -= 1
            continue
        seq[i] = seq[act[elem]-1]
        seq[act[elem]-1] = elem
        act[elem] -= 1

# test
if __name__ == '__main__':
    from random import randrange
    k = 25
    n = 30
    testinput = [randrange(k) for x in range(n)]
    print testinput
    counting_sort(testinput, k)
    print testinput
