#include <iostream>
#include <climits>

const int n = 5; 
double p[n + 1] = {-1, 0.15, 0.1, 0.05, 0.1, 0.2}; 
double q[n + 1] = {0.05, 0.1, 0.05, 0.05, 0.05, 0.1}; 
int root[n + 1][n + 1]; 
double w[n + 2][n + 2]; 
double e[n + 2][n + 2]; 

void optimal_bst(double *p, double *q, int n)
{
    
    for (int i = 1; i <= n + 1; ++i)
    {
        w[i][i - 1] = q[i - 1]; 
        e[i][i - 1] = q[i - 1]; 
    }
   
    for (int len = 1; len <= n; ++len)
    {
        for (int i = 1; i <= n - len + 1; ++i)
        {
            int j = i + len - 1; 
            e[i][j] = INT_MAX; 
            w[i][j] = w[i][j - 1] + p[j] + q[j]; 
  
            for (int k = i; k <= j; ++k)
            {
                double temp = e[i][k - 1] + e[k + 1][j] + w[i][j]; 
                if (temp < e[i][j])
                {
                    e[i][j] = temp; 
                    root[i][j] = k; 
                }
            }
        }
    }
}

void print_root()
{
    std::cout << "各子树的根：" << std::endl; 
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            std::cout << root[i][j] << " "; 
        std::cout << std::endl; 
    }
    std::cout << std::endl; 
}

void print_bst(int i, int j, int r)
{
    int rootChild = root[i][j]; 
    if (rootChild == root[1][n])
    {
       
        std::cout << "k" << rootChild << "是根" << std::endl; 
        print_bst(i, rootChild - 1, rootChild); 
        print_bst(rootChild + 1, j, rootChild); 
        return; 
    }
    
    if (j < i - 1)
        return; 
    else if (j == i - 1)
    {
        if (j < r)
            std::cout << "d" << j << "是" << "k" << r << "的左孩子" << std::endl; 
        else
            std::cout << "d" << j << "是" << "k" << r << "的右孩子" << std::endl; 
        return; 
    }
    else
    {
        if (rootChild < r)
            std::cout << "k" << rootChild << "是" << "k" << r << "的左孩子" << std::endl; 
        else
            std::cout << "k" << rootChild << "是" << "k" << r << "的右孩子" << std::endl; 
    }
    
    print_bst(i, rootChild - 1, rootChild); 
    print_bst(rootChild + 1, j, rootChild); 
}

int main()
{
    optimal_bst(p, q, n); 
    print_root(); 
    std::cout << "最优二叉树结构：" << std::endl; 
    print_bst(1, n, -1); 
}
