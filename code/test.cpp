#include <iostream> 
#include <stdio.h>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>   //sqrt
#include <algorithm>  //vector sort
#include <stdlib.h>        //substr
#include <cassert>
using namespace std;

struct edge
{
    int start_p;
    int end_p;
    float dist;
    edge& operator = (edge &e){
        start_p = e.start_p;
        end_p = e.end_p;
        dist = e.end_p;
        return *this;
    }
};
struct CFTriple
{
	int n;
	vector<float> ls;
	float ss;
};
struct EdgeCluster
{
	vector<int> cluster1;
	vector<int> cluster2;
	float dist;
};
vector< vector<float> > read_file(const char* filename, char pattern);
vector< vector<float> > get_graph(vector< vector<float> > data_set);
vector<edge> prim(vector< vector<float> > data_set, vector< vector<float> > graph);
int my_comp(edge e1, edge e2);
void print_vec(const int& nData);

int main()
{
	
    vector<int> vec1,vec2;
    vec1.push_back(0);
    vec1.push_back(1);
    vec1.push_back(2);
    // for_each(vec1.begin(),vec1.end(),print_vec);
    // vec2.push_back(3);
    // vec2.push_back(4);
    // vec2.push_back(5);
    vec2 = vec1;
    for_each(vec2.begin(),vec2.end(),print_vec);
    // vec1.insert(vec1.end(),vec2.begin(),vec2.end());
    // for_each(vec1.begin(),vec1.end(),print_vec);
    // vector<int>::iterator it = vec.begin();
    // cout << "*it" << *it << endl;
    // vec.erase(it);
    // for_each(vec.begin(),vec.end(),print_vec);
    // const double prim_time = (double)clock()/CLOCKS_PER_SEC;
    // vector< vector<float> > graph = get_graph(data_set);
    // vector<edge> mst = prim(data_set,graph);
	// sort(result_set.begin(), result_set.end(), my_comp);
    // cout << "compute long edge mst using time : " << (double)clock()/CLOCKS_PER_SEC - prim_time << " s. " << endl;
    // int k_threshold = 2;		// cluster number
    // vector<int> labels = sum_link_cluster(data, result_set, k_threshold);
	// cout << "hello world!" << endl;
	return 0;
}

void print_vec(const int& nData)
{
    cout<<nData<<endl;
}
