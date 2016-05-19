def tail_quicksort(array, start, end):
    while start < end:
        p = partition(array, start, end)
        if end - p >= p - start:
            tail_quicksort(array, start, p - 1)
            start, end = p + 1, end
        else:
            tail_quicksort(array, p + 1, end)
            start, end = start, p - 1
             
def partition(array, start, end):
    x = array[end]
    i = start - 1

    for j in range(start, end):
        if array[j] <= x:
            i = i + 1
            array[i], array[j] = array[j], array[i]

    array[i+1], array[end] = array[end], array[i+1]
    return i + 1

array = [2, 5, 4, 3, 1, 7, 6, 10, 9, 7]
tail_quicksort(array, 0, len(array) - 1)
print array
