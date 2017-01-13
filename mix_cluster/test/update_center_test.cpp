#include <include/cluster.hpp>
#include <armadillo>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
using namespace arma;

void Display_records(vector<record> records) {
    for(vector<record>::iterator records_itr_ = records.begin() ;
            records_itr_ != records.end() ; records_itr_ ++) {
        cout << records_itr_->first;
        printf("%d\n", records_itr_->second);
    }
}

void Display_centers(vector<vec> centers) {
    for(vector<vec>::iterator centers_itr_ = centers.begin() ;
            centers_itr_ != centers.end() ; centers_itr_++) {
        cout << *centers_itr_ << endl;
    }
}

int main() {
    //double A[2*2] = {1, 0, 1, 0};
    mat data;
    data<<1<<1<<2<<2<<100<<100<<101<<101<<endr
                <<1<<2<<1<<2<<100<<101<<100<<101<<endr;
    vector<record> records(8);
    for(vector<record>::iterator records_itr_ = records.begin() ;
            records_itr_ != records.end() ; records_itr_++) {
        records_itr_->first = data.col(records_itr_-records.begin());
        records_itr_->second = (records_itr_-records.begin())%2; 
    }
        
    vector<vec> centers(2);
    centers[0] = data.col(1);
    centers[1] = data.col(5);
    // Update_centers(records, centers);
    for(int i=0 ; i<10 ; i++) {
        Display_records(records);
        Display_centers(centers);
        Cluster_once(records, centers);
    }
}    
