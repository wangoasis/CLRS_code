#ifndef searchMaxSub_H
#define searchMaxSub_H
#include<vector>
using std::vector;

//contains four methods to find maximum contiguous subsequence sum.
class searchMaxSub 
{
public:
    int findMaxSub1(vector<int> & arr) const;
    int findMaxSub2(vector<int> & arr) const;
    int findMaxSub3(vector<int> & arr) const;
    int findMaxSub4(vector<int> & arr) const;
private:
    int maxSumRec(vector<int> & arr, int left, int right) const;
    int max3(int num_1, int num_2, int num_3) const;
};
#endif
