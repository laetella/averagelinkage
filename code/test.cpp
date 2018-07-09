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

int main()
{
	const double read_data_time = (double)clock()/CLOCKS_PER_SEC;
    const char* source_file = "../data/data_f.dat";
    string name(source_file);
    vector< vector<float> > data_set = read_file(source_file ,',');
    cout << source_file << '\t' << "total data number : " << data_set.size() << endl;
    cout << "dimension : " << data_set[0].size() << endl;
    cout << "read data from file using time : " << (double)clock()/CLOCKS_PER_SEC - read_data_time << "s. " << endl;

    // const double prim_time = (double)clock()/CLOCKS_PER_SEC;
    // vector< vector<float> > graph = get_graph(data_set);
    // vector<edge> mst = prim(data_set,graph);
	// sort(result_set.begin(), result_set.end(), my_comp);
    // cout << "compute long edge mst using time : " << (double)clock()/CLOCKS_PER_SEC - prim_time << " s. " << endl;
    int k_threshold = 2;		// cluster number
    vector<int> labels = sum_link_cluster(data, result_set, k_threshold);
	// cout << "hello world!" << endl;
	return 0;
}

vector< vector<float> > read_file(const char* filename, char pattern)
{
    vector< vector<float> > data_set;
    ifstream fin(filename,ios::in);
    string str;
    string s;
    char* cs;
    int i = 0;
    vector<string> vs;
    while(getline(fin,str))
    {
        vector<float> temp_data;
        int line_size=str.size();
        string::size_type pos;
        for(i=0; i<line_size; i++)
        {
            pos=str.find(pattern,i);
            if(pos!= str.npos)
            {
                s = str.substr(i,pos-i);
                cs = &s[0];
                temp_data.push_back(atof(cs));
               // cout << temp_data[0] << endl;
                i=pos;
            }
            else
            {
                s = str.substr(i,line_size-1);
                cs = &s[0];
                temp_data.push_back(atof(cs));
               // cout << temp_data[1] << endl;
                break;
            }
        }
        data_set.push_back(temp_data);
    }
    return data_set;
}

float com_dist(vector<float> vec1, vector<float> vec2)
{
    float sum = 0.0;
    int dim = vec1.size();
    for(int i = 0; i < dim; i++)
    {
        sum += pow((vec2[i] - vec1[i]),2);
    }
   // cout << "com dist" <<endl;
    return sqrt(sum);
}

vector< vector<float> > get_graph(vector< vector<float> > data_set)
{
    vector< vector<float> > graph;
    for(int i = 0; i < data_set.size(); i++)
    {
        vector<float> dist_arr;
        for(int j = 0; j < data_set.size(); j++)
        {
            dist_arr.push_back(com_dist(data_set[i], data_set[j]));
        }
        graph.push_back(dist_arr);
    }
    return graph;
}

vector<edge> prim(vector< vector<float> > data_set, vector< vector<float> > graph)
{
    vector<edge> result_mst;
    int ds_size = data_set.size();
    bool flags[ds_size];
    float low_cost[ds_size];
    int i = 0, j = 0, k = 0;
    for(i = 0; i < ds_size; i++)
    {
        low_cost[i] = graph[0][i];
    }
    int cnt = 0;
    int start_i = 0, end_i = 0;
   // cout << "size:" << ds_size << endl;
    while (cnt < ds_size - 1)
    {
       // cout << "in while" << endl;
        float min_dist = 65535;
        for(i = 0; i < ds_size; i++)
        {
            if (low_cost[i] != 0 && low_cost[i] < min_dist && flags[i] == false)
            {
                min_dist = low_cost[i];
                end_i = i;
            }
        }
        flags[end_i] = true;
        for(j = 0; j < graph[end_i].size(); j++)
        {
            if (min_dist == graph[end_i][j])
            {
                start_i = j;
            }
        }
        flags[start_i] = true;
        edge e;
        e.start_p = start_i;
        e.end_p = end_i;
        e.dist = min_dist;
        result_mst.push_back(e);
        for(k = 0; k < ds_size; k++)
        {
            if (graph[end_i][k] < low_cost[k] && flags[k] == false)
            {
                low_cost[k] = graph[end_i][k];
            }
        }
        cnt += 1;
    }
    return result_mst;
}

int my_comp(edge e1, edge e2)
{
	return e1.dist < e2.dist;
}

vector<CFTriple> get_cf(vector< vector<float> > data_set)
{
	CFTriple cf;
	int ds_size = data_set.size();
	int dim = data_set[0].size();
	cf.n = ds_size;
	for (int i = 0; i < ds_size; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			cf.ls[j] += data_set[i][j];
			cf.ss += pow(data_set[i][j], 2);
		}
	}
	return cf;
}

float operator*(const vector<float>& x, const vector<float>& y)
{
    assert(x.size() == y.size());     
    float sum = 0.;
    for (size_t i = 0; i < x.size(); ++i)
        sum += x[i]*y[i];
    return sum;
}

float get_avg_link(CFTriple c1, CFTriple c2)
{
	float numerator = c2.n * c1.ss + c1.n * c2.ss + 2 * c1.ls * c2.ls;
	float denominator = c1.n * c2.n;
	return sqrt(numerator / denominator);
}

vector<int> avg_link_cluster(vector< vector<float> > data_set, vector<edge>& result_set, int k_threshold)
{
	vector<int> labels;
	int e = result_set.size();
	int dimension = data_set[0].size();
	vector<EdgeCluster> clusters;
	vector<CFTriple> cfs;
	vector< vector<CFTriple> > mst_cf;
	for (int i = 0; i < ds_size; ++i)
	{
		cfs.push_back(get_cf(data_set[i]));
	}
	for (int j = 0; j < e; ++j)
	{
		clusters[j]
		vector<CFTriple> temp_cf;
		temp_cf.push_back(cfs[result_set[j][0]]);
		temp_cf.push_back(cfs[result_set[j][1]]);
		mst_cf.push_back(temp_cf);
	}
	CFTriple merge_cf;
	while (clusters.size() + 1 > k_threshold) 
	{
		edge te_del =  
	}
	return labels;
}