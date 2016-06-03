import quicksort
import longest_commom_sub
import random

items = []
for i in range(10):
    items.append(random.randint(1, 100))
print items
items2 = items[:]
quicksort.quicksort(items2, 0, len(items2)-1)
c, b, max_len = longest_commom_sub.LCS(items, items2)
longest_commom_sub.print_LCS(b, items, len(items), len(items))
print "\nmax length: ", max_len
