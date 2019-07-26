#include <iostream>
#include <vector>

// 继承搭配虚函数（inheritance with virtual function）[这样才有继承的威力]
// 用于子类重写父类函数
// non-virtual函数: 你不希望derived class重新定义(override)它.(override,只有虚函数在被重新定义时才叫 复写)
// virtual函数: 你希望子类重新定义它,且你对它已有默认定义.
// pure virtual函数: 你希望子类一定要重新定义它,你对它没有默认定义.

// (23个设计模式[OOD]之一 Template Method)模板方法,,不是C++里的template
// Application framework,应用程序的框架
class Shape{
public:
    virtual void draw() const = 0; // pure virtual 子类必须重新定义,shape很抽象
    virtual void error(const std::string& msg); // impure virtual 希望子类自己定义更详细的error
    int objectID() const; // non-virtual 不希望子类去定义

};

class Rectangle: public Shape { };
class Ellipse: public Shape { };


// 三种class关系中功能最强大的是
// 委托 + 继承 (delegation + inheritance)
// 23个设计模式[OOD]之二 observer观察者模式, 多个观察者同时观察同一份数据
// 例如三个不同窗口观察同一份数据

class Observer
{
public:
    virtual void update(Subject* sub, int value) = 0;
};
class Subject
{
    int m_value;
    vector<Observer*> m_views;
public:
    void attach(Observer* obs)
    {
        m_views.push_back(obs);
    }
    void set_val(int value)
    {
        m_value = value;
        notify();
    }
    void notify()
    {
        for(int i = 0; i < m_views.size(); ++i)
        {
            m_views[i]->update(this, m_value);
        }
    }
};


