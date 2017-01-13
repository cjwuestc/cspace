#include <iostream>
//#include <stdio.h>
#include <map>
#include <string>
#include <sstream>
#include <memory>

using namespace std;

class Customer {
    private:
        string name_;
    public:
        Customer(const string& name = "apple"):name_(name){}
        inline const string& name() const {return name_;}
    
};

class CustomerFactory {
    private:
        static map<string, Customer*> map_;
    public:
        static Customer* createACustomer(const string& name) {
            Customer* customer = new Customer(name);
            map_.insert(make_pair(string(name), customer));
            return customer;
        }
        inline static int size() {
            return map_.size();
        }
        inline static void display() {
            ostringstream stream;
            for(map<string, Customer*>::iterator itr = map_.begin() ;
                    itr!=map_.end() ; itr++)
                stream << itr->first << ": " << itr->second <<endl;
            cout << stream.str() << endl;
        }
        
};

map<string, Customer*> CustomerFactory::map_ = map<string, Customer*>();

void creatAPtr() {
    Customer* ptr = CustomerFactory::createACustomer("apple");
}

void creatAAuto_ptr() {
    std::auto_ptr<Customer> auto_(CustomerFactory::createACustomer("auto_apple"));
}

int main() {
    creatAPtr();
    creatAAuto_ptr();

    std::ostringstream stream;
    stream << CustomerFactory::size() << endl;
    CustomerFactory::display();   
    cout << stream.str();
}
