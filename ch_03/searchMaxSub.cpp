#include "searchMaxSub.h"
#include <vector>

//O(N^3)
int searchMaxSub::findMaxSub1(vector<int> & arr) const {
    int maxSum = 0;
    for(int i=0;i<arr.size();i++)
        for(int j=i;j<arr.size();j++) {
            int thisSum=0;
            for(int k=i;k<=j;k++)
                thisSum += arr[k];
            if(thisSum>maxSum)
                maxSum=thisSum;
        }
    return maxSum;
}

//O(N^2)
int searchMaxSub::findMaxSub2(vector<int> & arr) const {
    int maxSum=0;
    for(int i=0;i<arr.size();i++) {
        int thisSum=0;
        for(int j=i;j<arr.size();j++) {
            thisSum += arr[j];
            if(thisSum>maxSum)
                maxSum=thisSum;
        }
    }
    return maxSum;
}

//O(NlogN)
int searchMaxSub::findMaxSub3(vector<int> & arr) const {
    return maxSumRec(arr,0,arr.size()-1);
}

int searchMaxSub::maxSumRec(vector<int> & arr, int left, int right) const {
    if(left==right)
        if(arr[left]>0)
            return arr[left];
        else
            return 0;

    int center=(left+right)/2;
    int maxLeftSum=maxSumRec(arr,left,center);
    int maxRightSum=maxSumRec(arr,center+1,right);

    int maxLeftBorderSum=0, leftBorderSum=0;
    for(int i=center;i>=0;i--) {
        leftBorderSum += arr[i];
        if(leftBorderSum>maxLeftBorderSum)
            maxLeftBorderSum=leftBorderSum;
    }

    int maxRightBorderSum=0, rightBorderSum=0;
    for(int i=center+1;i<right;i++) {
        rightBorderSum+=arr[i];
        if(rightBorderSum>maxRightBorderSum) 
            maxRightBorderSum=rightBorderSum;
    }

    return max3(maxLeftSum,maxRightSum,maxLeftBorderSum+maxRightBorderSum);
}

int searchMaxSub::max3(int num_1, int num_2, int num_3) const {
    int ans = (num_1 > num_2 ? (num_1 > num_3 ? num_1 : num_3) : (num_2 > num_3 ? num_2 : num_3));
    return ans > 0 ? ans : 0;
}

//O(N)
int searchMaxSub::findMaxSub4(vector<int> & arr) const {
    int maxSum=0, thisSum=0;
    for(int i=0;i<arr.size();i++) {
        thisSum+=arr[i];
        if(thisSum>maxSum)
            maxSum=thisSum;
        else if(thisSum<0)
            thisSum=0;
    }
    return maxSum;
}
