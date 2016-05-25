# exercise 9.3-8
# let X[1...n] and Y[1...n] be two arrays, each contains n numbers already
# in sorted order, give an O(lgn)-time algorithm to find the median of all
# 2n elements in arrays X and Y

def median_2_lists(array_1, array_2):
    n = len(array_1)
    if array_1[n - 1] <= array_2[0]:
        return array_1[n - 1]
    if array_2[n - 1] <= array_1[0]:
        return array_2[n - 1]

    low, high = 0, n - 1
    while (low <= high):
        k = (high + low) / 2
        if array_2[n - k - 2] <= array_1[k] and array_1[k] <= array_2[n - k - 1]:
            return array_1[k] 
        elif array_2[n - k - 2] > array_1[k]:
            low = k + 1
        else:
            high = k - 1


list1 = [1, 3, 5, 6, 7, 9]
list2 = [2, 3, 6, 7, 8, 10]
list3 = [10, 11, 13, 14, 15, 16]
print median_2_lists(list1, list2)
print median_2_lists(list1, list3)
