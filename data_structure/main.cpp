#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b)
{
    int c = a;
    a = b;
    b = c;
}

// 冒泡排序，交换次数太多，速度很慢
void bubbleSort(vector<int>& nums)
{
    // 我写的，把满足条件的放左边，每次比较到最后，左边移动
    for(int i=0; i<nums.size()-1; i++)
    {
        for(int j=i+1; j<nums.size(); j++)
            if(nums[i] > nums[j])
                swap(nums[i], nums[j]);
    }

    // 把满足条件的放右边。每次从0开始比较，右边移动
    // for(int i=0; i<nums.size()-1; i++)
    // {
    //     for(int j=0; j<nums.size()-1-i; j++)
    //         if(nums[j] > nums[j+1])
    //             swap(nums[j], nums[j+1]);

    // }

}
// 选择排序，一次循环完才交换数据
void selectSort(vector<int>& nums)
{
    // 
    for(int i=0; i<nums.size()-1; i++) // n-1
    {
        int index=i; // 每次内循环跟起点比较，因为这个起点一次循环完需要被替换
        for(int j=i+1; j<nums.size(); j++)
            if(nums[j] < nums[index])
                index = j;
        swap(nums[i], nums[index]); // 每次内循环完成 找到最小的数，交换一下
    }
}

int main()
{

    int a = 3, b = 4;
    swap(a,b);
    cout << "a: " << a << " b: " << b << endl;

    vector<int> nums{2, 4, 7, 1, 0, 3, 5, 8, 9, -2, -199, -5, 3, 45, 33, -21};


    selectSort(nums);
    for(int i=0; i<nums.size(); i++) cout << nums[i] << " ";

    return 0;
}
