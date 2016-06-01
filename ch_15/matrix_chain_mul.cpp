#include <iostream>
#include <climits>
#include <vector>
using std::vector;

void matrix_chain_order(int p[], 
                        int n,
                        vector<vector<int> > & m, 
                        vector<vector<int> > & s)
{
    int i, j, q;
    for (int length = 2; length <= n; length++) // length of chain
    {
        for (i = 1; i <= n - length + 1; i++) // start position of chain
        {
            j = length + i - 1; // end position of chain
            for (int k = i; k < j; k++) // iterate in a chain
            {
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void print_optimal_chain(vector<vector<int> > & s, int i, int j)
{
    if (i == j)
        std::cout << "A" << i;
    else
    {
        std::cout << "(";
        print_optimal_chain(s, i, s[i][j]);
        print_optimal_chain(s, s[i][j]+1, j);
        std::cout << ")";
    }
}

int main()
{
    int n = 6; // num of matrixs
    int dimen[n + 1] = {30, 35, 15, 5, 10, 20, 25};
    vector<vector<int> > m(n+1), s(n+1);
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            if (i == j)
            {
                m[i].push_back(0);
                s[i].push_back(0);
            }
            else
            {
                m[i].push_back(INT_MAX);
                s[i].push_back(INT_MAX);
            }
        }
    }
    matrix_chain_order(dimen, n, m, s);

/*  print matrix: m and s

    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
            std::cout << m[i][j] << " ";
        std::cout << std::endl;
    }
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
            std::cout << s[i][j] << " ";
        std::cout << std::endl;
    }
*/

    print_optimal_chain(s, 1, 6);
    std::cout << std::endl;
}
