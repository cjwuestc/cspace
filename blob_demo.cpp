#include <iostream>
#include <vector>
#include <caffe/blob.hpp>

using namespace caffe;
using namespace std;

int main() {
	const Blob<int> blob(1,2,3,4);
	// blob.Reshape(1,2,3,4);
	// cout << blob.shape_string() << endl;
    const vector<int>* shape_ = &blob.shape();
    vector<int> shape = const_cast<vector<int>&>(blob.shape());

    shape[0] = 2;
    cout << blob.shape_string() << endl;
    
    ostringstream stream;
    // 说明const_cast事实上并没有额外分配空间

    stream << shape[0] << " " << shape[1] << " " << shape[2] << " " << shape[3];
    stream << endl << (&shape_) 
            <<endl << (&shape);
    vector<int> shape_tmp(4);
    stream << endl << sizeof(shape_tmp)
            << endl << sizeof(int);  
    // int* p = &shape_; //错误：不能获取带有const关键字的内存区域
    // *p = 3;
    cout << stream.str() << endl;

    /**
    ostringstream stream;
    for(vector<int>::iterator itr = shape_.begin() ; 
            itr != shape_.end() ; itr++)
        stream << *itr << " ";
    cout << stream.str() <<endl;
    */
}
