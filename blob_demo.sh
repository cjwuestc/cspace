#!/bin/sh
export CAFFE_HOME=/home/cjw/caffe
g++ blob_demo.cpp -o blob_demo -I $CAFFE_HOME/include -I $CAFFE_HOME/build/src -L $CAFFE_HOME/build/lib -lcaffe -lboost_system -lglog -D CPU_ONLY 
