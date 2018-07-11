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
    void operator=(const CFTriple &cf)
    { 
        n = cf.n;
        ls = cf.ls;
        ss = cf.ss;
    }
};
struct EdgeCluster
{
	vector<int> cluster1;
	vector<int> cluster2;
	float dist;
    void operator=(const EdgeCluster &ec)
    { 
        cluster1.insert(cluster1.begin(), ec.cluster1.begin(), ec.cluster1.end());
        cluster2.insert(cluster2.begin(), ec.cluster2.begin(), ec.cluster2.end());
        dist = ec.dist;
    }
};
vector< vector<float> > read_file(const char* filename, char pattern);
int my_comp(edge e1, edge e2);
void print_vec(const int& nData);
void write_labels(const char* label_file, vector< int> labels);
vector<int> avg_link_cluster(vector< vector<float> > data_set, vector<edge> result_set, int k_threshold);
void write_mst(const char* mst_file, vector< edge> all_edges);
vector<edge> prim_mst(vector< vector<float> > data_set);

int main()
{
	const double read_data_time = (double)clock()/CLOCKS_PER_SEC;
    // const char* source_file = "../data/data_f.dat";
    const char* source_file = "../data/gestalt.dat";
    string name(source_file);
    vector< vector<float> > data_set = read_file(source_file ,',');
    cout << source_file << '\t' << "total data number : " << data_set.size() << endl;
    cout << "dimension : " << data_set[0].size() << endl;
    cout << "read data from file using time : " << (double)clock()/CLOCKS_PER_SEC - read_data_time << "s. " << endl;

    const double prim_time = (double)clock()/CLOCKS_PER_SEC;
    vector<edge> mst = prim_mst(data_set);
    cout << "mst size: " << mst.size() << endl;
    const char* mst_file = "../result/gestalt_mst.txt";
    sort(mst.begin(), mst.end(), my_comp);
     // write_mst(mst_file, mst);
    cout << "compute mst using time : " << (double)clock()/CLOCKS_PER_SEC - prim_time << " s. " << endl;
    int k_threshold = 2;		// cluster number
    cout << "mst[0] : " << mst[0].start_p << "==" << mst[0].end_p << "==" << mst[0].dist << endl;
    vector<int> labels = avg_link_cluster(data_set, mst, k_threshold);
    const char* label_file = "../result/data_f_labels.txt";
    write_labels(label_file, labels);
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

void write_mst(const char* mst_file, vector< edge> all_edges)
{
    ofstream f_mst(mst_file, ios::out);
    for(int i = 0; i < all_edges.size(); i++)
    {
        f_mst << all_edges[i].start_p << '\t' << all_edges[i].end_p << '\t' << all_edges[i].dist << endl;
    }
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

vector<edge> prim_mst(vector< vector<float> > data_set)
{
    vector<edge> result_set;
    int start_point = 0, ds_size = data_set.size();
    vector<int> nodes_finished, nodes_unfinished;
    nodes_finished.push_back(start_point);
    vector<float> dist_arr(ds_size);
    vector<int> edge_arr(ds_size);
    float temp_dist1 = 1.0e14;
    int position = -1, i, j;
    for ( i = 0; i < ds_size; ++i)
    {
        if (i == start_point)
        {
            edge_arr[i] = -1;
            dist_arr[i] = 0;
            continue;
        }
        float t = com_dist(data_set[start_point], data_set[i]);
        dist_arr[i] = t;
        edge_arr[i] = start_point;
        if (t < temp_dist1)
        {
            temp_dist1 = t;
            position = i;
        }
    }
    nodes_finished.push_back(position);
    edge e;
    e.start_p = start_point;
    e.end_p = position;
    e.dist = temp_dist1;
    // cout << "add an edge : " << start_point << "==" << position << "==" <<temp_dist1 << endl;
    result_set.push_back(e);
    for ( j = 0; j < ds_size; ++j)
    {
        if (j != start_point && j != position)
        {
            nodes_unfinished.push_back(j); 
        }
    }
    int q_index = 0;
    while (nodes_unfinished.size() > 0)
    {
        float temp_dist2 = 1.0e14;
        int temp_posit = nodes_finished.size() - 1;
        for (int i = 0; i < nodes_unfinished.size(); ++i)
        {
            int new_node = nodes_finished[temp_posit];
            float d = com_dist(data_set[new_node], data_set[nodes_unfinished[i]]);
            if (d < dist_arr[nodes_unfinished[i]])
            {
                dist_arr[nodes_unfinished[i]] = d;
                edge_arr[nodes_unfinished[i]] = new_node;
            }
            if (dist_arr[nodes_unfinished[i]] < temp_dist2)
            {
                temp_dist2 = dist_arr[nodes_unfinished[i]];
                position = i;
                q_index = nodes_unfinished[i];
            }
        }
        nodes_finished.push_back(q_index);
        nodes_unfinished[position] = nodes_unfinished.back();
        nodes_unfinished.pop_back();
        e.start_p = edge_arr[q_index];
        e.end_p = q_index;
        e.dist = dist_arr[q_index];
        result_set.push_back(e);
    }
    return result_set;
}

int my_comp(edge e1, edge e2)
{
	return e1.dist > e2.dist;
}

int edge_cluster_comp(EdgeCluster e1, EdgeCluster e2)
{
    return e1.dist > e2.dist;
}

CFTriple get_cf(vector< vector<float> > data_set)
{
	CFTriple cf;
	int ds_size = data_set.size();
	int dim = data_set[0].size();
	cf.n = ds_size;
    cf.ls.insert(cf.ls.begin(), dim, 0);
    cf.ss = 0;
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

vector<float> operator+(const vector<float>& x, const vector<float>& y)
{
    assert(x.size() == y.size());     
    vector<float> sum(x.size());
    for (size_t i = 0; i < x.size(); ++i)
        sum[i] = x[i]+y[i];
    return sum;
}

float get_avg_link(CFTriple c1, CFTriple c2)
{
	float numerator = c2.n * c1.ss + c1.n * c2.ss + 2 * (c1.ls * c2.ls);
	int denominator = c1.n * c2.n;
	return sqrt(numerator / denominator);
}

float get_cen_link(CFTriple c1, CFTriple c2)
{
    vector<float> vec1(c1.ls.size()), vec2(c1.ls.size());
    for (int i = 0; i < c1.ls.size(); ++i)
    {
        vec1[i] = c1.ls[i] / c1.n;
        vec2[i] = c2.ls[i] / c2.n;
    }
    return com_dist(vec1, vec2);
}

bool in_cluster(int point, vector< int > cluster)
{
    vector< int >::iterator result = find(cluster.begin(), cluster.end(), point); 
    if ( result != cluster.end() ) 
    {
        return true;
    }
    return false;
}

float get_sing_link(vector< int > cluster1, vector< int > cluster2, vector<edge> mst)
{
    float min_dist = 1.0e14;
    for (int i = 0; i < mst.size(); ++i)
    {
        bool con1 = in_cluster(mst[i].start_p, cluster1) &&  in_cluster(mst[i].end_p, cluster2);
        bool con2 = in_cluster(mst[i].end_p, cluster1) &&  in_cluster(mst[i].start_p, cluster2);
        if (con1 || con2)
        {
            min_dist = mst[i].dist;
            break;
        }
    }
    return min_dist;
}

float get_comp_link(vector< int > cluster1, vector< int > cluster2, vector<edge> mst)
{
    float max_dist = 0;
    for (int i = mst.size(); i > 0; --i)
    {
        bool con1 = in_cluster(mst[i].start_p, cluster1) &&  in_cluster(mst[i].end_p, cluster2);
        bool con2 = in_cluster(mst[i].end_p, cluster1) &&  in_cluster(mst[i].start_p, cluster2);
        if (con1 || con2)
        {
            max_dist = mst[i].dist;
            break;
        }
    }
    return max_dist;
}


vector<int> avg_link_cluster(vector< vector<float> > data_set, vector<edge> result_set, int k_threshold)
{
    int e = result_set.size();
    int dimension = data_set[0].size();
    int ds_size = data_set.size();
    vector<int> labels(ds_size);
    vector<EdgeCluster> clusters(e);
    vector<CFTriple> cfs;
    vector< vector<CFTriple> > mst_cf;
    int i, j, k;
    for ( i = 0; i < ds_size; ++i)
    {
        vector< vector<float> > temp_data;
        temp_data.push_back(data_set[i]);
        cfs.push_back(get_cf(temp_data));
    }
    for ( j = 0; j < e; ++j)
    {
        clusters[j].cluster1.push_back(result_set[j].start_p);
        clusters[j].cluster2.push_back(result_set[j].end_p); 
        clusters[j].dist = result_set[j].dist; 
        vector<CFTriple> temp_cf;
        temp_cf.push_back(cfs[result_set[j].start_p]);
        temp_cf.push_back(cfs[result_set[j].end_p]);
        // print_cf(temp_cf); 
        mst_cf.push_back(temp_cf) ;
        // mst_cf[j] = temp_cf;
    }
    // print_mstcf(mst_cf);
    // cout << "finish init" << endl;
	CFTriple merge_cf;
	while (clusters.size() + 1 > k_threshold) 
	{
		EdgeCluster to_del = clusters[clusters.size()-1]; 
        clusters.pop_back();
        // cout << "clusters.size(): " << clusters.size() << endl;
        // print_edge_cluster(to_del);
        vector<CFTriple> temp_cf = mst_cf[mst_cf.size()-1] ;
        mst_cf.pop_back();
        vector<int> merge_cluster;
        merge_cluster.insert(merge_cluster.end(),to_del.cluster1.begin(),to_del.cluster1.end());
        merge_cluster.insert(merge_cluster.end(),to_del.cluster2.begin(),to_del.cluster2.end());
        merge_cf.n = temp_cf[0].n + temp_cf[1].n;
        merge_cf.ls = temp_cf[0].ls + temp_cf[1].ls;
        merge_cf.ss = temp_cf[0].ss + temp_cf[1].ss;
        // cout <<endl << merge_cf.n << "==";
        // print_float_arr(merge_cf.ls);
        // cout << merge_cf.ss << endl;
        int a; cin >> a;
        for ( i = 0; i < clusters.size(); ++i)
        {
            vector<int> cl1 = clusters[i].cluster1;
            vector<int> cl2 = clusters[i].cluster2;
            for ( j = 0; j < cl1.size(); ++j)
            {
                if ( in_cluster(cl1[j], to_del.cluster1) ) 
                {
                    clusters[i].cluster1 = merge_cluster;
                    mst_cf[i][0] = merge_cf;
                    break;
                }
            }
            for ( j = 0; j < cl2.size(); ++j)
            {
                if ( in_cluster(cl2[j], to_del.cluster2) ) 
                {
                    clusters[i].cluster2 = merge_cluster;
                    mst_cf[i][1] = merge_cf;
                    break;
                }
            }
            clusters[i].dist = get_sing_link(cl1, cl2, result_set);
            // clusters[i].dist = get_comp_link(cl1, cl2, result_set);
            // clusters[i].dist = get_avg_link(mst_cf[i][0], mst_cf[i][1]);
            // clusters[i].dist = get_cen_link(mst_cf[i][0], mst_cf[i][1]);
        }
        sort(clusters.begin(), clusters.end(), edge_cluster_comp);
	}
    // cout << "finish while " << endl;
    int current_label = 0;
    for ( k = 0; k < clusters.size(); ++k)
    {
        // cout << "clusters size : " << clusters.size() << endl;
        for ( i = 0; i < clusters[k].cluster1.size(); ++i)
        {
            labels[clusters[k].cluster1[i]] = current_label;
        }
        current_label += 1;
        // cout << "current_label : " << current_label << endl; 
        for ( i = 0; i < clusters[k].cluster2.size(); ++i)
        {
            labels[clusters[k].cluster2[i]] = current_label;
        }
        current_label += 1;
    }
    // cout << "finish for" << endl;
	return labels;
}

void write_labels(const char* label_file, vector< int> labels)
{
    ofstream f_label(label_file, ios::out);
    for(int i = 0; i < labels.size(); i++)
    {
        f_label << labels[i] << endl;
    }
}
