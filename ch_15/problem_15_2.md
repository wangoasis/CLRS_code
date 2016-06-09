# problem 15.2: print neatly

First, we need to define the cost function that including words _i_ to words _j_ in a line. Therefore, we define a matrix cube[i, j]:
```
extra[i, j] = M - j + i - sum(li to lk)
if extra[i, j] < 0:
    cube[i, j] = INT_MAX
else if j == n:
    // last line
    cube[i, j] = 0
else:
    cube[i, j] = pow(extra[i, j], 3)
```
Then, we can calculate the array cost[i]:
```
if i == 0:
    cost[i] = 0
else:
    cost[i] = min(cost[k] + cube(k+1, i) ( 1 <= k <= i - 1)
```
Here is the pseudocode of solution:
```
print_neatly(l, n, M):
    // matrix extra[i, j], 1 <= i <= j <= n
    for i = 1 to n:
        extra[i, i] = M - li
        for j = i + 1 to n:
            extra[i, j] = extra[i, j - 1] -lj - 1
    // matrix cube[i, j], 1 <= i <= j <= n
    for i = 1 to n:
        for j = i to n:
            if extra[i, j] < 0:
                cube[i, j] = INT_MAX
            else if j == n:
                cube[i, j] = 0
            else:
                cube[i, j] = pow(extra[i, j], 3)
    // compute cost[j], 1 <= j <= n
    cost[0] = 0
    for j = 1 to n:
        cost[j] = INT_MAX
        for i = 1 to j - 1:
            if cost[i] + cube[i, j] < c[j]:
                c[j] = cost[i] + cube[i + 1, j]
                // use array p to save the position of changing lines
                // word i is the last word of a certain line
                p[j] = i
return c and p
```
