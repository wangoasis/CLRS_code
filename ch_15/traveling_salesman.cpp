/*
    problem:15.1
    Describing an O(n^2)-time algorithm for determining an optimal
    bitonic tour. Assuming that no two points have the same x-coordinate.

    Assuming, input points are sorted with x-coordinate
*/

#include <iostream>
#include <vector>
using std::vector;
#include <math.h>

struct point 
{
    int x;
    int y;

    point(int x_i, int y_i)
    : x(x_i), y(y_i)
    { }
};

double distance(const point & p1, const point & p2)
{
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

int main()
{
    vector<point> p;
    int length = 7; // number of points

    p.push_back(point(0, 0)); // to make the index of existing point start from 1 
    p.push_back(point(0, 0));
    p.push_back(point(1, 6));
    p.push_back(point(2, 3));
    p.push_back(point(5, 2));
    p.push_back(point(6, 5));
    p.push_back(point(7, 1));
    p.push_back(point(8, 4));

    /*
    s[i][j] means two different routes to point i and point j:
    it satisfies three requirements
    1. the sum of two routes are shortest
    2. two routes covers all points from point 1 to point max(i,j)
    3. two routes doesn't have common points, except for the 
    start point and i==j(last point)
    Therefore, the problem becomes to get the value of s[n][n]
    where n is the number of points
    in this program, it assumes that i >= j
    */

    double s[length + 1][length + 1];

    for (int i = 0; i <= length; i++)
    {
        s[i][0] = 0;
        s[0][i] = 0;
        for (int j = i + 1; j <= length; j++)
            s[i][j] = 0;
    }

    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (i == j)
                s[i][j] = s[i][j - 1] + distance(p[i], p[j - 1]);
            else if(i == j + 1)
            {
                double min = 1000.0;

                for (int u = 1; u <= j; u++)
                // attention: u <= j, rather than u < j
                {
                    if (s[j][u] + distance(p[u], p[i]) < min)
                        min = s[j][u] + distance(p[u], p[i]);
                }
                s[i][j] = min;
            }
            else if(i > j + 1)
                s[i][j] = s[i - 1][j] + distance(p[i - 1], p[i]);
        }
    }

    for (int i = 1; i < length + 1; i++)
    {
        for (int j = 1; j < length + 1; j++)
            std::cout << s[i][j] << " ";
        std::cout << std::endl;
    }

    std::cout << "min distance: " << s[length][length] << std::endl;
}
