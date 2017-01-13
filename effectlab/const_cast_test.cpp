#include <iostream> 
#include <stdio.h>

using namespace std;

int main() {
    float array[10] = {1};
    const float* ptr_const_ = array;
    float* ptr_ = const_cast<float*>(ptr_const_);
    
    for(int i=0 ; i<10 ; i++)
        printf("%f,", *(ptr_+i));    
    
}
