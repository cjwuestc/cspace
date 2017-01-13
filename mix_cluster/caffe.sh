#!/bin/sh
cd /home/cjw/cspace/mix_cluster
export CAFFE_HOME=/home/cjw/caffe
g++ -c -o build/caffe.o util/caffe.cpp -I /home/cjw/cspace/mix_cluster -I $CAFFE_HOME/include -I $CAFFE_HOME/build/src -D CPU_ONLY
g++ -o build/caffe build/caffe.o util/kmeans_cluster.o -I /home/cjw/cspace/mix_cluster -L $CAFFE_HOME/build/lib -larmadillo -lcaffe -lglog -lboost_system
