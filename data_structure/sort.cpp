#include <iostream>
#include <vector>

using namespace std;

// 三种低级排序算法
// --------------1.冒泡排序，交换次数太多，速度很慢--------------------
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
// --------------2.选择排序，一次循环完才交换数据---------------------
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
// --------3.插入排序,低级排序中最快,新出来的项插入已排好的序列----------
 void insertSort(vector<int>& nums)
 {
    int in, out;
    for(out=1; out<nums.size(); out++)
    {
        // in表示将要插入的索引,out表示取出的索引
        in = out; // 从最后开始比较
        int temp = nums[out]; // 暂存刚取出来的项
        while(in>0 && nums[in-1] >= temp) // 没有比较到第0个元素 并且 前一项 >= 刚取出来的项
        {
            nums[in] = nums[in-1]; // 每次都把 大的那一项放后面 in-1项腾出空位
            --in; // 继续往前找, --in将in-1项作为当前项
        } // 如果暂存值大于前一项直接赋值到当前项,如果不是就在while里找到正确的in值
        nums[in] = temp; // 将暂存值插入已排好的序列  
    }
 }


// 高级排序算法
// ---------快速排序,最流行最快,用递归-------------
// 1.选定左边的数为轴
// 2.从右往前与轴比较,当找到一个或者没有找到<轴的数的时候,开始从左往右查找
// 3.
void quickSort(vector<int>& nums, const int left, const int right)
{
    if(left >= right) return; // 递归结束条件

    // 一次选轴,左右都比较
    int pivot=nums[left], l=left, r=right;
    while(l < r)
    {
        // 划分
        // 找右边
        while(l < r && nums[r] >= pivot) { r--; } // 从右往左找到一个小于pivot的数, r为其索引, 没有找到索引r==l
        if(l < r) nums[l++] = nums[r];            // 如果在右边找到了小于pivot的数, 把此数放到轴对应所在位置l, 然后l++(l位置无需再比较,往后移动)
        // 找左边
        while(l < r && nums[l] < pivot) { l++; }  // 从左往右找到一个大于pivot的数, l为其索引, 没有找到索引r==l
        if(l < r) nums[r--] = nums[l];            // 如果在左边找到了大于pivot的数,把此数放到右边当前r去, 然后r--(r位置)
    }
    nums[l] = pivot; // 将轴至于左边

    // 从l处划分为 左右两部分 分别递归
    quickSort(nums, left, l-1);
    quickSort(nums, l+1, right);
}


int main()
{
    vector<int> nums {3, 3, 7, -5, 0, 3, 5, 33, 9, -2, -199, -5, 3, 45, 33, -21};
    vector<int> nums1{3, 3, 7, -5, 0, 3, 5, 33, 9, -2, -199, -5, 3, 45, 33, -21};
    vector<int> nums2{3, 3, 7, -5, 0, 3, 5, 33, 9, -2, -199, -5, 3, 45, 33, -21};
    vector<int> nums3{3, 3, 7, -5, 0, 3, 5, 33, 9, -2, -199, -5, 3, 45, 33, -21};


    cout << "\nbubbleSort: ";
    bubbleSort(nums);
    for(int i=0; i<nums.size(); i++) cout << nums[i] << " ";

    cout << "\nselectSort: ";
    selectSort(nums1);
    for(int i=0; i<nums1.size(); i++) cout << nums1[i] << " ";

    cout << "\ninsertSort: ";
    insertSort(nums2);
    for(int i=0; i<nums2.size(); i++) cout << nums2[i] << " ";
    
    
    cout << "\n quickSort: ";
    quickSort(nums3, 0, nums.size()-1);
    for(int i=0; i<nums3.size(); i++) cout << nums3[i] << " ";

    return 0;
}
