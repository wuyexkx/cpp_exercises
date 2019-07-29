#include <iostream>
#include <vector>

using namespace std;

// --------------------------删除重复元素----------------------------
// 没有排序的列,去重复.暴力遍历
template<class T>
void removeDuplicates(vector<T>& nums)
{
    for(int i=0; i<nums.size(); i++)
    {          
        for(int j=i+1; j<nums.size(); j++)
        {   if(*(nums.begin() + i) == *(nums.begin() + j))
            {
                nums.erase(nums.begin() + j);
                j--; // 
            }  
        }  
    }
}
// 已排序的列,去重复. ***已排序列 只需考虑 前后两个数是否重复***
template<class T>
void removeSortedDuplicates(vector<T>& nums)
{
    for(int i=1; i<nums.size(); i++)
    {
        if(nums[i] == nums[i-1])
        {
            nums.erase(nums.begin() + i);
            i--; // 删完之后索引自动跳到下一个(因为i++),这里必须回来,否则每次删完都会跳过一个
        }
    }
}

int main()
{
    vector<int> nums2{1, 1, 2, 2, 2, 3, 3, 4, 5, 6, 6, 6}; // 已排序 6个不重复
    vector<int> nums1{3, 3, -12, 44, 3, 33, 33, 2, 33, 44, -12, 0}; // 未排序,6个不重复

    cout << "\n\n     origin data: ";
    for(int i=0; i<nums1.size(); i++) cout << nums1[i] << " ";

    removeDuplicates(nums1);
    // removeSortedDuplicates(nums1);
    cout << "\nremoveDuplicates: ";
    for(int i=0; i<nums1.size(); i++) cout << nums1[i] << " ";
    cout << endl;
}
