#include <iostream>
#include <vector>

using namespace std;

// 迭代的方法
int binarySearch_I(const vector<int>& seqNums, const int x)
{
    int start=0, end=seqNums.size()-1, mid;
    while(start <= end)
    {
        mid = (start + end) / 2;
        if(x < seqNums[mid]) end = mid - 1;
        else if(x > seqNums[mid]) start = mid + 1; 
        else return mid;
    }
    return -1;
}
// 递归的方法
int binarySearch_R(const vector<int>& seqNums, const int x, const int start, const int end)
{
    int mid = (start + end) / 2;
    if(x == seqNums[mid]) return mid;
    if(x < seqNums[mid]) binarySearch_R(seqNums, x, start, mid-1);
    else if(x > seqNums[mid]) binarySearch_R(seqNums, x, mid+1, end);
}

int main()
{
    vector<int> seqNums{1,2,3,4,5};
    cout << "\nIteration: " << binarySearch_I(seqNums, 4) << endl;
    cout << "\nRecursion: " << binarySearch_R(seqNums, 4, 0, seqNums.size()-1) << endl;
    return 0;
}
