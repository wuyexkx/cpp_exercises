#include <vector>
// 侯捷老师，P13内容 https://www.bilibili.com/video/av19038490/?p=13

// 合成模式：将对象组织到树结构中，可以用来描述整体与部分的关系。就是一个处理对象的树结构的模式。
//          把部分与整体的关系用树结构表示出来。
//          使得客户端把一个个单独的成分对象和由他们复合而成的合成对象同等看待。

// ex: 文件系统
// 目录里边可以放文件，目录里可以放目录

class Component
{
    int value;
public:
    Component(int val) {value = val;}
    virtual void add(Component*) { }  // virtual，组件定义，子类如果是文件就不用自定义
};
// 文件
class Primitive : public Component
{
public:
    Primitive(int val): Component(val) { }
};
// 复合起来，既有文件夹又有文件
class Composite: public Component
{
    vector<Component*> c; // 既可以放Primitive对象也可放Component，因为Primitive继承自Component
public:
    Composite(int val) : Component(val) { }
    void add(Component* elem) // 既可以添加文件夹也可以添加文件
    {
        c.push_back(elem);
    }
};


// 原型模式 prototype pattern
// 在其他模式也可能出现这种情况：现在要创建未来的class
// prototype，未来创建的东西能被框架看到

