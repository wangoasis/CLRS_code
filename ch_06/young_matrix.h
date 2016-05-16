#include <vector>
using std::vector;
#include <climits>

class young_matrix
{
public:
    // find min elements
    int min_element(void);
    // extract min element        
    int extract_min_element(void);
    void insert(int x);
    void print_matrix(void);
    bool exist_element(int);
private:
     void min_adjust(vector<vector<int>> &, int, int);
     void max_adjust(vector<vector<int>> &, int, int);
     vector<vector<int>> m { {2, 4, 5, 10}, 
                             {6, 8, 14, INT_MAX}, 
                             {9, 11, INT_MAX, INT_MAX} };
};
