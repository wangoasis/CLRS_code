```
DYNAMIC-0-1-KNAPSACK(v,w,n,W)
    for w = 0 to W do
        c[0,w] = 0
    for i = 1 to n
        c[i,0] = 0
        for w = 1 to W
            if wi <= w
                if vi + c[i-1, w-wi] > c[i-1, w]
                    c[i,w] = vi + c[i-1,w-wi]
                else
                    c[i,w] = c[i-1,w]
            else
                c[i,w] = c[i-1,w]
    return c[n, W]
```
