#include <iostream>
#include <armadillo>
#include <sstream>

using namespace std;
using namespace arma;

int main() {
    vec vec1(2),vec2(2),vec3(2),vec4(2);
    vec1 << 1.0 << endr << 1.0;
    //cout << vec1;
    vec2 << 1.0 << endr << 0.0;
    vec3 << 2.0 << endr << 0.0; 
    mat A(2, 2);

    A = vec1*vec1.t()+vec2*vec2.t()+vec3*vec3.t();
    
    vec eigval;
    mat eigvec;

    eig_sym(eigval, eigvec, A);

    cout << "A matrix is: " << endl
         << A << endl
         << "eigen value: " << endl
         << eigval << endl
         << "eigen vector: " << endl
         << eigvec << endl
         << "cast is: " << endl
         << vec1.t()*eigvec.col(0) << ", " << vec2.t()*eigvec.col(0) << ", " << vec3.t()*eigvec.col(0) << endl
         << vec1.t()*eigvec.col(1) << ", " << vec2.t()*eigvec.col(1) << ", " << vec3.t()*eigvec.col(1) << endl;

}
