#include <iostream>
#include <caffe/caffe.hpp>
#include <caffe/common.hpp>
#include <vector>
#include <stdio.h>

using namespace std;

using caffe::Net;
using caffe::shared_ptr;
using caffe::Blob;

int train(std::string solver_file) {
    // resolve the solver file
    caffe::SolverParameter solver_parameter;
    caffe::ReadSolverParamsFromTextFileOrDie(solver_file, &solver_parameter);
  
    caffe::Caffe::set_mode(caffe::Caffe::CPU);
    shared_ptr<caffe::Solver<float> >
	solver(caffe::SolverRegistry<float>::CreateSolver(solver_parameter));
    //for(int i=0 ; i<10 ; i++)
    // solver->Step(10);
    // save the caffemodel file    
    // solver->Snapshot();
    
    shared_ptr<Net<float> > net_ptr_ = solver->net();
    // cout << net_ptr_->phase() << endl; // phase: Train
    
    // execute a forward progress
    /**
    float loss = 0;
    vector<Blob<float>*> net_output_blobs_ = net_ptr_->Forward(&loss);
    */

    
    shared_ptr<Blob<float> > result_blob_ = net_ptr_->blobs()[7];
    // printf("%d,%d,%d,%d", result_blob_->num(), result_blob_->channels(),
    //        result_blob_->height(), result_blob_->width());
    
    // printf("\n%d\n", net_ptr_->num_inputs());
    //Blob<float>* input_blob_ = net_ptr_->bottom_vecs()[1][0]; 
    //float data_[28*28] = {1};
    //input_blob_->Reshape(1,1,28,28);
     
    //cout << "input_blobs:" << net_ptr_->bottom_vecs()[1].size() << endl;    
    //input_blob_->set_cpu_data(data_);
    //input_blob_.insert(input_blob_.begin()+1, input_);
    //cout << "input_blobs:" << net_ptr_->bottom_vecs()[1].size() << endl;    
     
    net_ptr_->Reshape(); 
    vector<Blob<float>*> output_blobs_ = net_ptr_->Forward();
    printf("output size is:%d\n", output_blobs_.size());
    cout << output_blobs_[0]->shape_string() << endl;
    
    for(int i=0 ; i<net_ptr_->blobs().size() ; i++) 
        cout << net_ptr_->blobs()[i]->shape_string() << endl;
    
    //cout << "samples result:" << endl;
    vector<vector<Blob<float>*> > top_vecs_ = net_ptr_->top_vecs();
    printf("top_vecs size:%d\n", top_vecs_.size());
    printf("top_vecs[0] size:%d\n", top_vecs_[0].size());
    for(int i=0 ; i<top_vecs_.size() ; i++) {
        for(int j=0 ; j<top_vecs_[i].size() ; j++) {
            printf("top_vecs[%d][%d]:",i,j);
            cout << top_vecs_[i][j]->shape_string() <<endl;
        }
    }

    vector<vector<Blob<float>*> > bottem_vecs_ = net_ptr_->bottom_vecs();
    printf("bottem_vecs size:%d\n", bottem_vecs_.size());
    printf("bottem_vecs[0] size:%d\n", bottem_vecs_[0].size());
    for(int i=0 ; i<bottem_vecs_.size() ; i++) {
        for(int j=0 ; j<bottem_vecs_[i].size() ; j++) {
            printf("bottem_vecs[%d][%d]:",i,j);
            cout << bottem_vecs_[i][j]->shape_string() <<endl;
        }
    }

    printf("samples result is:%f\n", top_vecs_[8][0]->data_at(0,0,0,0));
    printf("result is: %f\n", output_blobs_[0]->data_at(0,0,0,0));
    cout << "bottom_vecs[8][1]:" << endl;
   
    float cpu_data_[64] = {1,0};
    //*(cpu_data_) = 1.0;
    for(int i=0 ; i<bottem_vecs_[8][1]->num() ; i++)
        printf("%f,", bottem_vecs_[8][1]->data_at(i,0,0,0));
    bottem_vecs_[8][1]->set_cpu_data(cpu_data_);
    cout << endl; 
    for(int i=0 ; i<bottem_vecs_[8][1]->num() ; i++)
        printf("%f,", net_ptr_->bottom_vecs()[8][1]->data_at(i,0,0,0));

    /**
    std::cout << net_ptr_->name() << std::endl;
    vector<string> layer_names_ = net_ptr_->layer_names();
    for(vector<string>::iterator itr = layer_names_.begin() ;
            itr != layer_names_.end() ; itr ++) {
        cout << *itr << endl;    
    }
    */

    
    // vector<Blob<float>* > input = net_ptr_->input_blobs();
    // printf("\nsize:d", net_ptr_ -> num_inputs());
    /**
    input->Reshape(1,1,28,28);

    net_ptr_->Reshape();
    
    net_ptr_->Forward();
    
    vector<Blob<float>* > output_ = net_ptr_->output_blobs();
    printf("%lu", output_.size());
   */  
}

int test(std::string model_file, string train_file) {
  // model_file : "xxx.prototxt"
  // train_file : "xxx.caffemodel"
	caffe::Net<float> caffe_net(model_file, caffe::TEST);
	caffe_net.CopyTrainedLayersFrom(train_file);
    
    printf("size: %lu\n", caffe_net.input_blobs().size());
  
    Blob<float>* bottem_ = caffe_net.input_blobs()[0]; // this function return a pointer;
  bottem_->Reshape(1,1,28,28);

  caffe_net.Reshape(); // this step reshape all blobs in net according to input blob
  
  float data_[28*28] = {1};
  bottem_->set_cpu_data(data_);
  
  caffe_net.Forward();
  
  Blob<float>* top_ = caffe_net.output_blobs()[0]; // Is there many output blobs in net???
  const float* begin  = top_ ->cpu_data();
  const float* end  = begin + top_ -> channels();
  std::vector<float> result(begin, end);
  
  for(std::vector<float>::iterator iter=result.begin() ; iter!=result.end() ; iter++)
	  std::cout <<  *iter << std::endl;
    
}

int main() {
  train("/home/cjw/caffe/examples/mnist/lenet_solver.prototxt");	
  //test("/home/cjw/caffe/examples/mnist/lenet.prototxt",
  //        "/home/cjw/caffe/_iter_10.caffemodel");
  return 0;
}
