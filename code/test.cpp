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

int main()
{
    vector<edge> vec1,vec2;
    // vec1.insert(vec1.begin(),3, 2);
    edge e1,e2,e3;
    e1.start_p = 0;
    e1.end_p = 6;
    e1.dist = 23.2594;
    e2.start_p = 0;
    e2.end_p = 1;
    e2.dist =  26.0768;
    e3.start_p = 6;
    e3.end_p =  2;
    e3.dist =  27.074;
    vec1.push_back(e3);
    vec1.push_back(e1);
    vec1.push_back(e2);
    vector<edge>::iterator it = vec1.begin();
    for (; it != vec1.end(); ++it)
    {
        cout << (*it).start_p << "==" << (*it).end_p << "==" << (*it).dist << endl;
    }
    sort(vec1.begin(), vec1.end(), my_comp);
    cout << "vec1 size: " << vec1.size() << endl;
    vector<edge>::iterator iter = vec1.begin();
    for (; iter != vec1.end(); ++iter)
    {
        cout << (*iter).start_p << "==" << (*iter).end_p << "==" << (*iter).dist << endl;
    }
    // cout << "*it" << *it << endl;
    // vec1[1] = vec1.back();
    // vec1.pop_back();
    // for_each(vec1.begin(),vec1.end(),print_vec);
    // // vec2.push_back(3);
    // // vec2.push_back(4);
    // // vec2.push_back(5);
    // vec2 = vec1;
    // for_each(vec2.begin(),vec2.end(),print_vec);
    // vec1.insert(vec1.end(),vec2.begin(),vec2.end());
    // for_each(vec1.begin(),vec1.end(),print_vec);
    
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

bool my_comp(const edge &e1, const edge &e2)
{
    return e1.dist < e2.dist;
}

void print_vec(const edge& nData)
{
    cout<<nData.start_p << ", " << nData.end_p << ", " <<nData.dist <<endl;
}


// vector< vector<float> > get_graph(vector< vector<float> > data_set)
// {
//     vector< vector<float> > graph;
//     for(int i = 0; i < data_set.size(); i++)
//     {
//         vector<float> dist_arr;
//         for(int j = 0; j < data_set.size(); j++)
//         {
//             dist_arr.push_back(com_dist(data_set[i], data_set[j]));
//         }
//         graph.push_back(dist_arr);
//     }
//     return graph;
// }

// vector<edge> prim(vector< vector<float> > data_set, vector< vector<float> > graph)
// {
//     vector<edge> result_mst;
//     int ds_size = data_set.size();
//     bool flags(ds_size);
//     float low_cost(ds_size);
//     int i = 0, j = 0, k = 0;
//     for(i = 0; i < ds_size; i++)
//     {
//         low_cost[i] = graph[0][i];
//     }
//     int cnt = 0;
//     int start_i = 0, end_i = 0;
//    // cout << "size:" << ds_size << endl;
//     while (cnt < ds_size - 1)
//     {
//        // cout << "in while" << endl;
//         float min_dist = 65535;
//         for(i = 0; i < ds_size; i++)
//         {
//             if (low_cost[i] != 0 && low_cost[i] < min_dist && flags[i] == false)
//             {
//                 min_dist = low_cost[i];
//                 end_i = i;
//             }
//         }
//         flags[end_i] = true;
//         for(j = 0; j < graph[end_i].size(); j++)
//         {
//             if (min_dist == graph[end_i][j])
//             {
//                 start_i = j;
//             }
//         }
//         flags[start_i] = true;
//         edge e;
//         e.start_p = start_i;
//         e.end_p = end_i;
//         e.dist = min_dist;
//         result_mst.push_back(e);
//         for(k = 0; k < ds_size; k++)
//         {
//             if (graph[end_i][k] < low_cost[k] && flags[k] == false)
//             {
//                 low_cost[k] = graph[end_i][k];
//             }
//         }
//         cnt += 1;
//     }
//     return result_mst;
// }

