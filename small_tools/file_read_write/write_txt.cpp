#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // setprecision
using namespace std;

int main()
{
    float a = 6.0123456789;
    string txt_path = "C:/Users/`/Desktop/txt_path.txt";
    ofstream outfile(txt_path, ios::out);
    for(int i=0; i<100; ++i)
    {
        outfile << setprecision(16) << a << endl; 
    }    
    outfile.close();

    return 0;
}