#include <iostream>
#include <armadillo>
#include <stdio.h>
#include <vector>

#include "caffe/caffe.hpp"
#include "caffe/common.hpp"
#include "include/cluster.hpp"

using namespace std;
using namespace arma;
using namespace caffe;

const int NUMS_ = 64;
const int LENGTH_ = 80;
const int K_ = 10;
const int CLUSTER_K_ = 10;

vector<record> get_records(const float* data_) {
    vector<record> result(NUMS_);
    //vec sum_(LENGTH_);
    //sum_.zeros();

    for(int i=0 ; i<NUMS_ ; i++) {
        vector<float> vector_(&data_[i*LENGTH_],&data_[(i+1)*LENGTH_]);
        vec value;
        for(int j=0 ; j<LENGTH_ ; j++)
            value << vector_[j] <<endr;
        result[i].first = value;
        result[i].second = -1;
        //sum_ += value;
    }

    return result;
}

vector<vec> get_centers(const vector<record>& records) {
    vector<vec> result(K_);
    for(int i=0 ; i<CLUSTER_K_ ; i++) {
        result[i] = records[i].first;
    }

    return result;
}

inline void display(float labels_[], float labels_tmp_[]) {
    int statistic_[K_][CLUSTER_K_] = {0};
    for(int i=0 ; i<NUMS_ ; i++) {
        int row_id_ = (int)(*(labels_+i));
        int col_id_ = static_cast<int>(labels_tmp_[i]);
        statistic_[row_id_][col_id_] ++;
        //printf("%f, %f, %d, %d\n", *(labels_+i), labels_tmp_[i], row_id_, col_id_);
    }

    for(int i=0 ; i<K_ ; i++) {
        for(int j=0 ; j<CLUSTER_K_ ; j++)
            printf("%d ", statistic_[i][j]);
        cout << endl;
    }
}

inline void scale(vector<record>& records) {
    vec sum = records[0].first;
    for(vector<record>::iterator itr_ = records.begin()+1 ;
            itr_!=records.end() ; itr_++)
        sum += itr_->first;
    for(int i=0 ; i<NUMS_ ; i++)
        records[i].first /= sum;
}

void getLabelsFromRecords(const vector<record>& records, float labels_tmp_[]) {
    for(int i=0 ; i<NUMS_ ; i++) {
        labels_tmp_[i] = (float)(records[i].second);
    }
}

int Cluster(const std::string solver_file_) {
    // resolve the solver file
    SolverParameter solver_parameter_;
    ReadSolverParamsFromTextFileOrDie(solver_file_, &solver_parameter_);
    
    caffe::Caffe::set_mode(caffe::Caffe::CPU);
    shared_ptr<Solver<float> >
        solver_ptr_(caffe::SolverRegistry<float>::CreateSolver(solver_parameter_));

    // get net_pt_
    shared_ptr<Net<float> > net_ptr_ = solver_ptr_->net();
    
    solver_ptr_->Step(1);
    vector<vector<Blob<float>*> > bottem_vecs_ = net_ptr_->bottom_vecs();
    
    const float* value = bottem_vecs_[5][0]->cpu_data();
    Blob<float>* label_blob_ = bottem_vecs_[8][1];
    
    const float* labels_cpu_data_ = label_blob_->cpu_data();
	float labels_[NUMS_];
	for(int i=0 ; i<NUMS_ ; i++) {
		labels_[i] = *(labels_cpu_data_+i);	
	}
    
    vector<record> records = get_records(value);
    scale(records);
    vector<vec> centers = get_centers(records);

    for(int i=0 ; i<5000 ; i++){
        int cluster_iterations_ = 1;
        float labels_tmp_[NUMS_];
 
        printf("cluster_iterations_ : %d\n" , cluster_iterations_);
        for(int j=0 ; j<cluster_iterations_ ; j++) {
            // cluster once
            Cluster_once(records, centers); 
            for(int k=0 ; k<NUMS_ ; k++) {
                /**
                for(int h=0 ; h<K_ ; h++) {
                    vec tmp = records[k].first - centers[h];
                    printf("%f, ", dot(tmp,tmp));
                }
                */
               // printf(":%d", records[i].second);
            }
            //cout << endl;
        }
        
        // update label
        getLabelsFromRecords(records, labels_tmp_);
        label_blob_->set_cpu_data(labels_tmp_);

        // net step once
        solver_ptr_->Step(1);
        records = get_records(bottem_vecs_[5][0]->cpu_data());
        scale(records);
        // display labels
        if(i%500 == 0)display(labels_, labels_tmp_);  
    } 
        
}

int main() {
    Cluster("/home/cjw/caffe/examples/mnist/lenet_solver.prototxt");
}
