#include <iostream>
#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

class Fruit {
    string name;
    string& colour;
    
    public:
        inline string name_() const {return name;}
        inline string colour_() const {return colour;}

        bool isSame(const Fruit& fruit) const {
            return (fruit.name==name);
        }
        
        Fruit(const string& name = "orange", const string& colour = "green") {
            this->name = string(name);
            this->colour = colour;
        }
};

int main(int argc, char** argv) {
    const Fruit apple("apple",string("red"));
     //cout << apple.isSame(Fruit()) <<endl;
    Fruit apple_2(apple);  
    cout << apple_2.name_() << endl;  
    // vector<int> vec_(10,1);
    // for(vector<int>::iterator itr_ = vec_.begin() ; itr_!=vec_.end() ; itr_++)
    //    *(itr_) = 2;
}
