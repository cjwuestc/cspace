#include <iostream>
#include <armadillo>
#include <vector>
#include <map>
//#include <utility>

using namespace std;
using namespace arma;

typedef pair<vec, int> record;

void Update_centers(vector<record>& records, vector<vec>& centers);
void Cluster_once(vector<record>& records, vector<vec>& centers);

