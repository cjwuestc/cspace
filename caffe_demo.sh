#!/bin/sh
g++ -o caffe_demo caffe_demo.cpp -I /home/cjw/caffe/include -I /home/cjw/caffe/build/src -D CPU_ONLY -L /home/cjw/caffe/build/lib -lcaffe -lglog -lboost_system
cd
cd caffe
/home/cjw/cspace/caffe_demo
