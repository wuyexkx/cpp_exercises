#include <iostream>
#include "myutil.h"
#include "SeqStack.h"

using namespace std;


int main()
{
    SeqStack<int> st(100);
    st.Push(1);
    cout << st.Top() << endl;
    st.Push(55);
    cout << st.Top() << endl;
    st.Push(4000);
    cout << st.Top() << endl;

    cout << endl;
    st.Pop();
    cout << st.Top() << endl;

    return 0;
}
