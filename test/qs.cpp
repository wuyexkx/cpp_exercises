#include <iostream>
#include <vector>
using namespace std;

void qs(vector<int>& nums, const int left, const int mid, const int right)
{
    int st1 = left, st2 = mid + 1, index = 0;
    int len = right - left + 1;
    int buff[len];

    while(st1 <= mid && st2 <= right) 
    {
        if(nums[st1] > nums[st2])  
            buff[index++] = nums[st2++];
        else 
            buff[index++] = nums[st1++];
    } 
    while(st1 <= mid) buff[index++] = nums[st1++];
    while(st2 <= right) buff[index++] = nums[st2++];

    for(int i=0; i<len; i++)
       nums[left + i] = buff[i];
}
void sort1(vector<int>& nums, const int st, const int end)
{
    if(st >= end) return;
    int mid = (end + st) / 2;
    sort1(nums, st, mid);
    sort1(nums, mid+1, end);

    qs(nums, st, mid, end);
}


int main()
{
    vector<int> v1{3,14,5,2,44,32,-2,-10, 0, 30};
    vector<int> v2{1,3,5,2,4,6};

    sort1(v1, 0, 9);
    for(auto v : v1)
        cout << v << " ";
    cout << endl; 
    return 0;
}
