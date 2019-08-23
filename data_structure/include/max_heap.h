#ifndef __MAX_HEAP_H
#define  __MAX_HEAP_H

// 数据结构中的堆, 完全二叉树结构,用数组实现
// 这里以最大堆为例, 实现push 和 pop 和 top 三个操作
/*
==  <--- top
==  
==  <--- current 
==
*/
template<typename T>
void swap(T& a, T& b)
{
    T t = b;
    b = a;
    a = t;
}

template<class T>
class maxHeap
{
public:
    maxHeap(const int maxsize = 20)
    : arryHeap(new T[maxsize]), maxSize(maxsize), current(0) 
    { }
    ~maxHeap() { delete[] arryHeap; }
    void Push(const T item); // 添加节点
    void Pop();              // 删除根节点
    T Top() const;
    void show() const;
private:
    void bubUp();   // 向上冒泡, 在插入节点时依次和 父节点比较
    void bubDown(); // 向下冒泡, 在删除节点时依次和 子节点比较
    T* arryHeap;
    int maxSize;
    int current;
};
template<class T>
void maxHeap<T>::Push(const T item)
{
    if(current == maxSize) { std::cerr << "Heap has fulled.\n"; return; }
    arryHeap[current] = item; // 先把数据放到最后
    if(current) // 如果不是空的 才开始向上冒泡 
    {
        bubUp();
    }
    current++;  // 只要添加了节点就要++ 
}
template<class T>
void maxHeap<T>::bubUp()
{
    int positin = current;            // 从最末尾开始向上冒泡
    int fatherP = (positin - 1) >> 1; // 获取父节点位置 position为1时fatherP为0  position为0时fatherP为-1
    // 在当前节点不是根节点的前提下, 只要当前节点比父节点大 都要交换, 否则就停止,返回
    while(fatherP >= 0 && arryHeap[positin] > arryHeap[fatherP]) 
    {
        swap(arryHeap[positin], arryHeap[fatherP]);
        positin = fatherP;            // 刷新 当前位置
        fatherP = (positin - 1) >> 1; // 刷新 父节点位置
    }
}
template<class T>
void maxHeap<T>::Pop()
{
    if(!current) { std::cerr << "Heap is empty.\n"; return; }
    // 如果完全二叉树不为空
    arryHeap[0] = arryHeap[--current]; // 先把最后的节点 赋给 根节点, 然后丢弃根节点, ***current-1才是最后节点的数据***
    bubDown(); 

}
template<class T>
void maxHeap<T>::bubDown()
{
    int position = 0;
    int lchild = (position << 1) + 1;
    int rchild = lchild + 1;
    while(lchild < current) // 只要存在左节点,  当只有根节点时不操作
    {   
        // 如果比 左右子节点都小, 比较两个子节点大小, 然后跟大的交换  
        // (就算右节点不存在了,通过Top找不到,但是数据还算存在的,所以在比较时不会出错)
        if(arryHeap[position] < arryHeap[lchild] && arryHeap[position] < arryHeap[rchild]) 
        {
            if(arryHeap[lchild] > arryHeap[rchild])
            {
                swap(arryHeap[position], arryHeap[lchild]);
                position = lchild; // 记录向下冒泡的位置
            }    
            else
            {
                swap(arryHeap[position], arryHeap[rchild]);
                position = rchild; // 记录向下冒泡的位置
            }
        }    
        else if(arryHeap[position] < arryHeap[lchild]) // 只比左子节点的小
        {
            swap(arryHeap[position], arryHeap[lchild]);
            position = lchild;
        }
        else if(arryHeap[position] < arryHeap[rchild]) // 只比右子节点小
        {
            swap(arryHeap[position], arryHeap[rchild]);
            position = rchild;
        }
        else return;                                   // 既不比左子节点小 也不必右小, 完成, 结束
            
        lchild = (position << 1) + 1; // 继续查找
        rchild = lchild + 1;          // 继续查找 ***** rchild - lchild == 1 *******
    }
}
template<class T>
T maxHeap<T>::Top() const // 返回根节点
{
    if(!current)
    {
        std::cerr << "Heap is empty.\n";
        return 9999;
    } 
    return arryHeap[0];
}
template<class T>
void maxHeap<T>::show() const
{
    int i = 0;
    std::cout << "--------------------------\n";
    while(i < current) std::cout << arryHeap[i++] << " ";
    std::cout << "nums:" << current << std::endl;
    std::cout << "--------------------------\n";
}


#endif