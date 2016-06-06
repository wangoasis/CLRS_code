# exercise 15.4-6
# O(n*lgn)

import random 

def pos(c, max_length, value):

    '''
    find the position of value in array c,
    since c is an increasing array, 
    it can be implemented with binary search
    '''
    low, high = 0, max_length
    mid = (low + high) / 2
    while (low <= high):
        if value < c[mid]:
            high = mid - 1
            mid = (low + high) / 2
        elif value > c[mid]:
            low = mid + 1
            mid = (low + high) / 2
        else:
            return mid 
    return low
    

if __name__ == "__main__":

    length = 10 # length of array
    items = []
    for i in range(length):
        items.append(random.randint(1, 50))
    print items

    # array c[i] means the smallest one of the last number of 
    # the monotonically increasing subsequence of length i
    # it can be proved that c is an increasing array
    c = [0] * 10
    c[1] = items[0]

    # max_length saves the value of current length of 
    # the longest monotonically increasing subsequence
    max_length = 1

    for i in range(1, len(items)):
        c_index = pos(c, max_length, items[i])
        c[c_index] = items[i]
        if c_index > max_length:
            # update max_length
            max_length = c_index

    print max_length
