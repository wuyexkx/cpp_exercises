#include <iostream>
#include <vector>
using namespace std;


void merge(vector<int>& nums, const int st1, const int st2, const int end)
{
    vector<int>temp(nums.size());
    int l=st1, r=st2, iRst=0;
    while(l < st2 && r <= end)
    {
        if(nums[l] < nums[r])
            temp[iRst++] = nums[l++];
        else
            temp[iRst++] = nums[r++];
    }
    while(l < st2) temp[iRst++] = nums[l++];
    while(r <= end) temp[iRst++] = nums[r++];

    for(int i=st1; i<=end; i++)
        nums[i] = temp[i-st1];
}
void test(vector<int>& nums, const int left, const int right)
{
    if(left >= right) return;
    int mid = (left + right) / 2;
    test(nums, left, mid);
    test(nums, mid+1, right);
    merge(nums, left, mid+1, right);

}

int main()
{
    vector<int> v1{3,14,5,2,44,32,-2,-10, 0, 30};
    vector<int> v2{1,3,5,2,4,6};

    test(v1, 0, 9);
    for(auto v : v1)
        cout << v << " ";
    cout << endl; 
    return 0;
}
