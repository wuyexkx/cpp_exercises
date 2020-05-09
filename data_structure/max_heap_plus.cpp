#include<iostream>
using namespace std;


template<typename T>
class MaxHeap
{
public:
    MaxHeap() 
    :theSize(0), capacity(2) { array = new T[capacity]; }
    ~MaxHeap() { delete[] array; }
    void push(const T& item);
    const T top() const;
    void pop();
    void bubup();
    void bubdown();
    void swap(T& a, T& b) { T t=a; a = b; b = t; }
    bool empty() const { return (theSize == 0); }
    int size() const { return theSize; }
    void show() const { for (int i=0; i<theSize; ++i) cout << array[i] << " "; cout << endl; }

private:
    T* array;
    int capacity;
    int theSize;     // 指向最后的空位
};

template<typename T>
void MaxHeap<T>::push(const T& item)
{
    // 检查容量，扩容
    if (theSize == capacity) {
        T* newarray = new T[capacity *= 2]();
        memcpy(newarray, array, sizeof(T)*theSize);
        delete[] array;
        array = newarray;
    }
    
    // 把新元素放到最后 
    array[theSize] = item;
    // 向上冒泡
    bubup();
    ++theSize;
}
template<typename T>
const T MaxHeap<T>::top() const
{
    if (!empty()) return array[0];
    cerr << "max heap is empty." << endl;
    exit(1);
}
template<typename T>
void MaxHeap<T>::pop()
{
    if (empty()) {
        cerr << "max heap is empty." << endl;
        exit(1);   
    }
    
    // 把最后的数据 放到 root
    array[0] = array[theSize - 1];
    // 向下冒泡
    bubdown();
    --theSize;
}
template<typename T>
void MaxHeap<T>::bubup()
{
    if (empty()) return;

    int father = (theSize - 1) / 2;
    int crt = theSize;
    // 没到root节点，并且比father大才交换
    while (crt != 0 && array[crt] > array[father]) {
        swap(array[crt], array[father]);
        crt = father;
        father = (crt - 1) / 2;
    }
}
template<typename T>
void MaxHeap<T>::bubdown()
{
    // 从root向下
    int crt = 0;
    int lchild = (crt * 2) + 1;
    int rchild = lchild + 1;     
    
    // 循环条件是 左子节点存在
    while (lchild < theSize) {
        // 父比子都小，要检查右子存在
        if (rchild < theSize && \
            array[crt] < array[lchild] && array[crt] < array[rchild]) {
            // 左右子之间比较
            if (array[lchild] < array[rchild]) {
                swap(array[crt], array[rchild]);
                crt = rchild;
            }
            else {
                swap(array[crt], array[lchild]);
                crt = lchild;        
            }
        }
        // 父比左子小
        else if (array[crt] < array[lchild]) {
            swap(array[crt], array[lchild]);
            crt = lchild;
        }
        // 父比右子小，检查右子存在
        else if (rchild < theSize && array[crt] < array[rchild]) {
            swap(array[crt], array[rchild]);
            crt = rchild;
        }
        else return; // 完成返回
        
        lchild = (crt * 2) + 1;
        rchild = lchild + 1;     
    }
}


int main()
{
    MaxHeap<int> mh;

    int nums[] = {2,4,5,6,5,23,1,13,23,9,4,56,5,6,11,1,65,0};
    for (int i=0; i<sizeof(nums)/sizeof(*nums); ++i) mh.push(nums[i]);
    cout << "size: " << mh.size() << endl;
    mh.show();

    while (!mh.empty()) {
        cout << mh.top() << " ";
        mh.pop();
    }

// stdout
    // size: 18
    // 65 56 23 23 9 6 11 13 5 5 4 4 5 1 6 1 2 0
    // 65 56 23 23 13 11 9 6 6 5 5 5 4 4 2 1 1 0

    return 0;
}