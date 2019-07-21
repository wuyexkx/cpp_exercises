#include <iostream>
#include <vector>

using namespace std;

// 顺序查找，没有排序的数据。n个数，平均查找n/2次
int sequentialSearch(const vector<int>& nums, const int x)
{
    for(int i=0; i<nums.size(); i++)
    {
        if(nums[i] == x)
            return i;
    }
    return -1;
}

// 二分（折半）查找，已经排序的数据。10（2^30）亿数，30次查找
int binarySearch(const vector<int>& seqNums, const int x)
{
    int start=0, end=seqNums.size()-1, mid;
    while(start <= end) // 查到最后start等于end
    {
        mid = (start + end) / 2; // 更新中间索引
        if(x == seqNums[mid]) return mid; // 查看中间是否为目标，是则结束
        else if(x < seqNums[mid]) end = mid - 1; // 前半部分，更新end
        else if(x > seqNums[mid]) start = mid + 1; // 后半部分，更新start
    }
    return -1;
}


int main()
{
    vector<int> seqNums{1,2,3,5,7,9};
    cout << "index: " << binarySearch(seqNums, 9) << endl;
    
    return 0;
}

