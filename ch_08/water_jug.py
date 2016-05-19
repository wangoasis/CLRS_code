import random

def match(reds, blues):
    if not reds:
        return None
    r = random.randint(0, len(reds) - 1)
    v = reds[r]

    small_red = [item for item in reds if item < v]
    small_blue = [item for item in blues if item < v]
    large_red = [item for item in reds if item > v]
    large_blue = [item for item in blues if item > v]
    match(small_red, small_blue)
    match(large_red, large_blue)

reds = [3, 5, 4, 1, 2]
blues = [5, 4, 1, 2, 3]
match(reds, blues)
