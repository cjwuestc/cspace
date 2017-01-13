#include "include/cluster.hpp"
#include <stdio.h>

using namespace std;
using namespace arma; 

void Cluster_once(vector<record> &records, vector<vec> &centers) {
	for(vector<record>::iterator itr = records.begin() ;
            itr!=records.end() ; itr++){
        float min_value_ = 100.0;
        int min_label_ = -1;
        
        //search labels with minimum norm value 
        for(vector<vec>::iterator center_itr = centers.begin() ;
                center_itr!=centers.end() ; center_itr++){
            vec tmp = itr->first-*center_itr;
            double value = dot(tmp, tmp);
			//printf("%d, %d: %f  %f\n", itr-records.begin(), center_itr-centers.begin(), value, min_value_);
            if(value<min_value_) {
                min_value_ = value;
                //printf("%f", value); 
                min_label_ = center_itr-centers.begin();
            }
        }
		//printf("%d\n", min_label_);
        itr->second = min_label_;  			
	}

    Update_centers(records, centers);
}

void Update_centers(vector<record> &records, vector<vec> &centers) {
    map<int, pair<vec, int> > center_map_;
    for(vector<record>::iterator records_itr_ = records.begin();
            records_itr_ != records.end() ; records_itr_ ++) {
        int label_ = records_itr_ -> second;
        vec value_ = records_itr_ -> first;
        
        if(center_map_.find(label_) == center_map_.end()) 
            center_map_[label_] = make_pair(value_, 1);    
        else {
            center_map_[label_].first += value_;
            center_map_[label_].second ++; 
        }
    }
    
    for(map<int, pair<vec,int> >::iterator map_itr_ = center_map_.begin();
            map_itr_ != center_map_.end() ; map_itr_++ ) {
        int label_ = map_itr_ -> first;
        pair<vec, int> value_ = map_itr_ -> second;
        
        centers[label_] = value_.first/value_.second;  
    }

}
