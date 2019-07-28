
// 类与类之间的三大关系

// ----------------------1.compsiton（复合）----------------------------Adapter
// 类的定义中包含其他类对象   container(queue) --- component(deque)
// 构造由内而外，
// container::container(...): component() {...};
// container的构造函数 首先调用component的default构造函数，然后才执行自己
// 编译器默认添加component()，调用的是默认构造函数。如果需要自定义就要像上面一样 写出来并指定合适的参数
// 析构由外向内，
// container::~container(...) { ... ~component(); }
// container的析构函数首先执行自己，然后才component得析构函数
// 生命周期同步（同时创建消失）

// sizeof: 40
template<class T>
class queue{
protected:
    deque<T> c;
};

// sizeof: 16*2 + 4 + 4
template<class T>
class deque{
protected:
    Itr<T> start;
    Itr<T> finish;
    T** map;
    unsigned int map_size;
};

// sizeof: 4 * 4
template<class T>
struct Itr{
    T* cur;
    T* first;
    T* last;
    T** node;
}; 


// --------------2.delegation(委托) [composition by reference]-------------Handle/Body(pImpl)
// 指针相连
class StringRep;
class String{
public:
    String();
    String(const char* s);
    String(const String& str); // 拷贝构造
    String& operator= (const  String& s); // 拷贝赋值   
    ~String();
private:    
    // 只提供接口，具体实现在外部，外部变动不影响这里
    StringRep* rep; // handle  [composition by reference] point to implement-pimpl
};

class StringRep{    // body
friend class String;
    StringRep(const char* );
    ~StringRep();
    int count;
    char* rep;
};


// -----------------------3.inheritance(继承)----------------------------
// c++有三种继承方式：public  private  protected

// public继承方式
// 父类的数据是被完整的继承下来

// 构造由内向外，
// Derived::Derived(...) Base() {...};
// Derived的构造函数首先调用Base的default构造函数，然后才执行自己。
// 
// 析构由外向内，
// Derived::~Derived(...) {... ~Base();};
// Derived的析构函数首先执行自己，然后才调用base的析构函数
// 
// Base class的析构函数必须是virtual，否则出现undefined behavior，
// 当设计的类会被继承，必须设计其析构函数类型为virtual

struct _List_node_base
{
    _List_node_base* _M_next;
    _List_node_base* _M_prev;
};

// _List_node继承自_List_node_base
// 父类的数据是被完整的继承下来，_List_node除了_M_data之外还有父类的两个指针数据
template<typename _Tp>
struct _List_node
    : public _List_node_base
{
    _Tp _M_data;
};

