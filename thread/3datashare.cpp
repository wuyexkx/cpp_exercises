#include <iostream>
#include <thread>
#include <vector>
#include <list>
using namespace std;

// 数据共享问题
// (1)只读不写数据, 多线程没有问题. 不需要特色处理
// (2)有读有写数据, 如果没有经过特殊处理,多个线程读写同一个数据一定 程序崩溃
//      最简单的处理办法, 读的时候不能写,写的时候不能读, 不能同时读,也不能同时写
// 案例
//      不同售票窗口 都在对同一座位操作
// 共享数据保护案例
//  网络游戏服务器, 两个线程, 一个线程保存玩家的命令到 队列, 一个线程从队列取出命令 并解析执行
//  
// 
// void print(vector<int> vctr)
// {
//     if(vctr.size() > 0)
//     for(auto v : vctr)
//         cout << v << " ";
//     cout << endl;
// }

class A
{
public:
    void capCmd()
    {
        for(int i=0; i<1000; i++)
        {
            cmdQueue.push_back(i);
            cout << "push command is: " << i << endl;
        }
    }
    void exeCmd()
    {
        for(int i=0; i<1000; i++)
        {   if(!cmdQueue.empty())
            {
                cout << "exe command is: " << cmdQueue.front() << endl;
                cmdQueue.pop_front();
            }
            else cout << "command queue is empty.\n";
        }
    }
private:
    list<int> cmdQueue;
};

int main()
{
    // vector<thread> threadVec;
    // vector<int> nums{1,2,3,4,5};
    // for(int i=0; i<10; i++)
    // {
    //     threadVec.push_back(thread(print, nums));
    // }
    // for(auto it=threadVec.begin(); it!=threadVec.end(); it++)
    // {
    //     it->join();
    // }
    
    A a;
    std::thread mythread1(&A::capCmd, &a);
    std::thread mythread2(&A::capCmd, &a);
    std::thread mythread3(&A::exeCmd, &a);

    mythread1.join();
    mythread2.join();
    mythread3.join();

    return 0;
}