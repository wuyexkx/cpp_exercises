#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

// 单例设计模式共享数据问题分析 解决
//      在主线程配置好需要配置的文件，在子线程中只读不写配置信息，没有什么问题     
//  
// std::call_once(); c++11的新函数，第二个参数是函数名a   （a()）
//      call_once()保证函数a只被调用一次, 具备互斥量的能力，效率比互斥量更高，消耗的资源更少
//      call_once()需要与一个标记结合使用，std::once_flag, once_flag是一个结构
//      call_once()就是通过这个标记决定对应函数a是否执行，调用成功后将改变状态。
// 
// 
std::mutex resource_mutex;
std::once_flag flag;
class MyCls
{
public:
    static MyCls* getInstance()
    {
        /* 第一种写法可以实现功能，但是效率低
        std::unique_lock<std::mutex> unqlock(resource_mutex); // 可以这么用，但是每次调用getInstance()时都会锁一下，耗时间
        // 单例模式下， 这种写法（饱），每次用成员函数都会调用getInstance()
        if(m_instance == nullptr)
        {
            m_instance = new MyCls; // 只希望这一行永远只执行一次 *****但是如果在多个线程中，这行可能被执行多次, 多个线程刚刚好在这儿发生切换*****
            static destrct de1; // static生命周期一直到程序结束
        }    
        return m_instance;  
        */
       /* 第二种写法，效率高了
       if(m_instance == nullptr) // 双重锁定，双重检查，效率高了，不再重复调用std::unique_lock<std::mutex> unqlock(resource_mutex); 
       {
            std::unique_lock<std::mutex> unqlock(resource_mutex); 
            if(m_instance == nullptr)
            {
            m_instance = new MyCls; // 只希望这一行永远只执行一次 *****但是如果在多个线程中，这行可能被执行多次, 多个线程刚刚好在这儿发生切换*****
            static destrct de1; // static生命周期一直到程序结束
            }    
       }
        return m_instance;  
        */
       /* 第三种写法 call_once()*/
       // 两个线程同时执行到这里，当一个线程执行crtIstc时，另一个一直等到这个线程执行完毕，（另一个等着，跟互斥量一样）
    //    这个线程执行完就做了标记，所以返回后在另一个线程中就不会执行creatInstance，从而保证creatInstance只被执行一次
       std::call_once(flag, creatInstance); 
       cout << "execute over.\n";
        return m_instance; 
    }
    static void creatInstance() // 辅助讲解第三种写法
    {
        cout << "creatInstance().\n" << endl;
        std::chrono::milliseconds dur(2000); 
        std::this_thread::sleep_for(dur); // 2秒

        m_instance = new MyCls;
        static destrct de1; // static生命周期一直到程序结束
    }
    void print() const { cout << "MyCls::print()." <<endl; }
    class destrct // 为了释放单例的new
    {
    public:
        ~destrct()
        {
            if(MyCls::m_instance)
            {
                delete MyCls::m_instance;
                MyCls::m_instance = nullptr;
            }
        }
    };
private:
    MyCls() { }
    MyCls(const MyCls& ths) { }
    static MyCls* m_instance;
};
MyCls *MyCls::m_instance = nullptr;

void print()
{
    cout << "sub thread starting.\n";
    MyCls* ptr = MyCls::getInstance();
    cout << "sub thread end.\n";
}

int main()
{
    // MyCls::getInstance()->print();
    std::thread mythread1(&MyCls::getInstance); // 在两个线程中调用
    std::thread mythread2(&MyCls::getInstance);
    mythread1.join();
    mythread2.join();

    // output:
        // creatInstance().  // 只执行了一直

        // execute over.
        // execute over.

    return 0;
}
