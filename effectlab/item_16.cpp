#include <iostream>
#include <sstream>

using namespace std;

int main() {
    int* ptr1[10];
    int* ptr2 = *(ptr1+1);
    
    ostringstream stream;
    stream << sizeof(*ptr1)/sizeof(int) << endl
           << sizeof(*ptr2)/sizeof(int) << endl;
    
    delete ptr1;
    //stream //<< sizeof(ptr1)/sizeof(int) << endl
    //      << sizeof(ptr2)/sizeof(int) << endl;
    
    //delete[] ptr2;
    //stream << sizeof(ptr1)/sizeof(int) << endl;
    
    cout << stream.str();
    return 0;
    
}
