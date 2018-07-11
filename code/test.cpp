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
        dist = e.dist;
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
bool my_comp(const edge &e1, const edge &e2);
void print_vec(const int& nData);
float operator*(const vector<float>& x, const vector<float>& y);

int main()
{
    vector<float> vec1,vec2;
    int b;
    for (int i = 0; i < 5; ++i)
    {
        cout << i << endl;
        cin>> b ;
    }
    // vec1.insert(vec1.begin(),3, 2);
    // edge e1,e2,e3;
    // e1.n = 1;
    // e1.ss = 6;
    // e1.dist = 23.2594;
    // e2.n = 0;
    // e2.ss = 1;
    // e2.dist =  26.0768;
    // e3.start_p = 6;
    // e3.end_p =  2;
    // e3.dist =  27.074;
    // vec1.push_back(2);
    // vec1.push_back(4);
    // vec1.push_back(6);
    // vector<edge>::iterator it = vec1.begin();
    // for (; it != vec1.end(); ++it)
    // {
    //     cout << (*it).start_p << "==" << (*it).end_p << "==" << (*it).dist << endl;
    // }
    // sort(vec1.begin(), vec1.end(), my_comp);
    // cout << "vec1 size: " << vec1.size() << endl;
    // vector<edge>::iterator iter = vec1.begin();
    // for (; iter != vec1.end(); ++iter)
    // {
    //     cout << (*iter).start_p << "==" << (*iter).end_p << "==" << (*iter).dist << endl;
    // }
    // cout << "*it" << *it << endl;
    // vec1[1] = vec1.back();
    // vec1.pop_back();
    // for_each(vec1.begin(),vec1.end(),print_vec);
    // vec2.push_back(3);
    // vec2.push_back(1);
    // vec2.push_back(5);
    // cout << vec1 * vec2 << endl;
    // vec2 = vec1;
    // for_each(vec2.begin(),vec2.end(),print_vec);
    // vec1.insert(vec1.end(),vec2.begin(),vec2.end());
    // for_each(vec1.begin(),vec1.end(),print_vec);
    
    // vec.erase(it);
    // for_each(vec.begin(),vec.end(),print_vec);
    // const double prim_time = (double)clock()/CLOCKS_PER_SEC;
    // vector< vector<float> > cluster;
    // vector<float> point,p1,p2;
    // point.push_back(1.4);
    // point.push_back(1.3);
    // p1.push_back(2.3);
    // p1.push_back(2.4);
    // p2.push_back(3.1);
    // p2.push_back(3.5);
    // cluster.push_back(point);
    // cluster.push_back(p1);
    // cluster.push_back(p2);
    // vector< vector<float> >::iterator result = find(cluster.begin(), cluster.end(), point); //查找3
    // cout << (*result)[0] << endl;
    // vector<edge> mst = prim(data_set,graph);
	// sort(result_set.begin(), result_set.end(), my_comp);
    // cout << "compute long edge mst using time : " << (double)clock()/CLOCKS_PER_SEC - prim_time << " s. " << endl;
    // int k_threshold = 2;		// cluster number
    // vector<int> labels = sum_link_cluster(data, result_set, k_threshold);
	// cout << "hello world!" << endl;
    // auto smallest = min_element(begin(v), end(v));  
    // cout << ”min element is ” << *smallest<< “ at position ” << distance(begin(v), smallest) << endl;  
	return 0;
}

bool my_comp(const edge &e1, const edge &e2)
{
    return e1.dist < e2.dist;
}

void print_vec(const edge& nData)
{
    cout<<nData.start_p << ", " << nData.end_p << ", " <<nData.dist <<endl;
}

float operator*(const vector<float>& x, const vector<float>& y)
{
    assert(x.size() == y.size());     
    float sum = 0.;
    for (size_t i = 0; i < x.size(); ++i)
        sum += x[i]*y[i];
    return sum;
}


void print_edge(edge e)
{
    cout << "edge: " << e.start_p << "==" << e.end_p << "==" << e.dist << endl;
}

void print_edge_cluster(EdgeCluster e)
{
    ofstream f_label("../result/edgecluster.csv", ios::app);
    // cout << "EdgeCluster : cluster1===" << endl;
    for (int i = 0; i < e.cluster1.size(); ++i)
    {
        f_label << e.cluster1[i] << " ";
    }
    f_label << ",";
    // cout << endl << "cluster2=====" ;
    for (int i = 0; i < e.cluster2.size(); ++i)
    {
        f_label << e.cluster2[i] << " ";
    }
    f_label << "," ;
    // f_label << endl << "dist====" ;
    f_label << e.dist << endl;
}

void print_float_arr(vector<float> array)
{
    for (int i = 0; i < array.size(); ++i)
    {
        cout << array[i] << " "; 
    }
    cout << "===";
}

void print_int(const int& data)
{
    cout << data << " ";
}

void print_cf(vector<CFTriple> cf)
{
    for (int i = 0; i < cf.size(); ++i)
    {
        cout <<endl << cf[i].n << "==";
        print_float_arr(cf[i].ls);
        cout << cf[i].ss;
    }
    cout << endl;
}

void print_mstcf(vector< vector<CFTriple> > mst_cf)
{
    for (int i = 0; i < mst_cf.size(); ++i)
    {
        for (int j = 0; j < mst_cf[i].size(); ++j)
        {
            cout <<endl << mst_cf[i][j].n << "==";
            print_float_arr(mst_cf[i][j].ls);
            cout << mst_cf[i][j].ss;
        }
        cout << endl;
    }
}

void print_clusters(vector<EdgeCluster> clusters)
{
    for (i = 0; i < clusters.size(); ++i)
    {
        int a;
        cout << "before while ... " << "cluster[0].cluster1" << endl;
        for_each(clusters[i].cluster1.begin(),clusters[i].cluster1.end(),print_int);
        cout << "clusters[i].cluster2: " << endl;
        for_each(clusters[i].cluster2.begin(),clusters[i].cluster2.end(),print_int);
        cin >> a;
    }
}
