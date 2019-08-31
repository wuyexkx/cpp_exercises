#include <iostream>
#include <vector>
#include <algorithm>
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
// ---------1.快速排序,最流行最快,用递归-------------
// 1.选定左边的数为轴
// 2.从右往前与轴比较,当找到一个或者没有找到<轴的数的时候,开始从左往右查找
// 3.重点是划分为两部分的方法
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
    quickSort(nums, left, l - 1); // 由于l 左右都逐渐向两端走
    quickSort(nums, l + 1, right); 
}
// 快排分开写
int partition(vector<int>& nums, const int left, const int right)
{
    int l = left, r = right;
    int p = nums[left];
    while(l < r)
    {
        while(l < r && nums[r] > p)  r--;
        if(l < r) nums[l++] = nums[r];

        while(l < r && nums[l] < p) l++;
        if(l < r) nums[r--] = nums[l];
    }
    nums[l] = p;
    return l;
}
void qs(vector<int>& nums, const int left, const int right)
{
    if(left >= right) return;
    int l = partition(nums, left, right);
    qs(nums, left, l-1);
    qs(nums, l+1, right);
}

// -----------2. 归并排序,速度与快速排序一样-------------
// 归并: 先递归拆分为单项(有序), 再依次合并相邻两组 为有序. 这样通过先递归的分解数列，再合并数列就完毕了归并排序。
// 将两个有序数列合并,第一个数列为a[st ~ mid],第二个数列为a[mid+1 ~ end], 不一定对称,合并结果保存在a[st ~ end]
void merge(int a[],int st, int mid, int end) // 合并两个有序数组 如 1,3,5  2,4,6 ---> 1,2,3,4,5,6
{
    int buf[end-st+1], i, j, iRst=0; // buf缓存比较的结果,最后赋值给a的相应项,iRst暂存需要的索引
    
    i = st;                 // i负责左边有序数列的索引
    j = mid + 1;            // j负责右边有序数列的索引
    while(i<=mid && j<=end) // 两个数列都没有比较完,继续比较 直到其中一个数列的项全部保存
    {
        if(a[i] <= a[j]) buf[iRst++] = a[i++];   // 左右比较取小的暂存, 
        else buf[iRst++] = a[j++];               // 暂存索引+1, 左右索引对应+1,不对应的不变,下次还需要比较
    }
    while(i <= mid) buf[iRst++] = a[i++];        // 因为左右各项是逐个比较的, 一定有一个已经排完,另一个末尾还剩下一些
    while(j <= end) buf[iRst++] = a[j++];        // 所以需要对应补充进去

    for(int k=st; k<=end; k++) a[k] = buf[k-st]; // 将排好的暂存赋值给a对应的项
}
void mergeSort(int a[], const int l, const int r)
{
    if(l >= r) return ;     // 递归结束条件
	int mid = (l + r) / 2;  // 计算出中间索引直
	mergeSort(a, l, mid);   // 
	mergeSort(a, mid+1, r); // 以上两行为递归分解，分解到最后为单个元素，再递归返回执行 下面这行，依次按序合并
	merge(a, l, mid, r);    // 再将二个有序数列合并	
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

    cout << "\n mergeSort: ";
    int nums4[10] = {3,2,2,4,5,1,9,3,0,1};
    mergeSort(nums4, 0, 9);
    for(int i=0; i < 10; i++) cout << nums4[i] << " ";
    
    return 0;
}
