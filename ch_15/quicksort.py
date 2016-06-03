def quicksort(items, start, end):
    if (start < end):
        q = partition(items, start, end)
        quicksort(items, start, q - 1)
        quicksort(items, q + 1, end)

def partition(a, start, end):
    pivot = a[end]
    i = start - 1
    for j in range(start, end):
        if (a[j] <= pivot):
            i = i + 1;
            a[j], a[i] = a[i], a[j]
    i = i + 1    
    a[i], a[end] = a[end], a[i]
    return i

if __name__ == "__main__":
    items = [1, 3, 5, 4, 2, 9, 8, 6]
    quicksort(items, 0, len(items) - 1)
    print items
