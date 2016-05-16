#include "young_matrix.h"
#include <iostream>

int young_matrix::min_element()
{
    return m[0][0];
}   

int young_matrix::extract_min_element()
{
   if (m[0][0] == INT_MAX)
   {
       std::cerr << "empty young matrix" << std::endl;
       return -1;
   }
   int min = m[0][0]; 
   int col = m[0].size();
   int row = m.size();

   m[0][0] = m[row-1][col-1];
   max_adjust(m, 0, 0);

   return min;
}

void young_matrix::max_adjust(vector<vector<int>> &m, int x, int y)
{
    int smallest_x = x;
    int smallest_y = y;
    int col = m[0].size();
    int row = m.size();

    if (x < col - 1 && m[y][x] > m[y][x+1])
        smallest_x = x + 1;
    if (y < row - 1 && m[y][smallest_x] > m[y+1][x])
    {
        smallest_y = y + 1;
        smallest_x = x;
    }

    if (smallest_x != x || smallest_y != y)
    {
        std::swap(m[y][x], m[smallest_y][smallest_x]);
        max_adjust(m, smallest_x, smallest_y);
    }
}

void young_matrix::insert(int new_element)
{
    int col = m[0].size();
    int row = m.size();

    if (m[row-1][col-1] < INT_MAX) 
    {
        std::cerr << "matrix is full" << std::endl;
        return;
    }
    m[row-1][col-1] = new_element;
    min_adjust(m, row-1, col-1);
}

void young_matrix::min_adjust(vector<vector<int>> &m, int y, int x)
{
    int largest_x = x;
    int largest_y = y;
    int col = m[0].size();
    int row = m.size();

    if (x > 0 && m[y][x] < m[y][x-1])
        largest_x = x - 1;
    if (y > 0 && m[y][largest_x] < m[y-1][x])
    {
        largest_y = y - 1;
        largest_x = x;
    }

    if (largest_x != x || largest_y != y)
    {
        std::swap(m[y][x], m[largest_y][largest_x]);
        min_adjust(m, largest_y, largest_x);
    }
}

void young_matrix::print_matrix()
{
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[0].size(); j++)
            std::cout << m[i][j] << " "; 
        std::cout << std::endl;
    }
}

bool young_matrix::exist_element(int element)
{
    int row = m.size();
    int col = m[0].size();

    int x = row - 1;
    int y = 0;
    while (m[x][0] > element && x >= 0)
        x--;
    if (x == -1)
        return false;
    if (m[x][0] == element)
        return true;
    while (m[x][y] != element && y < col)
        y++;
    if (y < col)
        return true;
    else 
        return false;
}

