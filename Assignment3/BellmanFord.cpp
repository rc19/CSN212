/*
Implementation of Bellman Ford Algorithm
Note: Vertices are numbered from 0 to n-1
*/


#include<bits/stdc++.h>
using namespace std;
#define NMAX 100
#define pb push_back

struct edge{
	int s,d,wt;
};

vector<edge> adj;
vector<int> dist(NMAX);

void addEdge(int u,int v,int w){
	edge e;
	e.s = u;
	e.d = v;
	e.wt = w;
	adj.pb(e);
}

void bellmanFord(int n, int m, int src){
	//Initialize
	for(int i = 0;i < n;i++){
		dist[i] = INT_MAX;
	}
	int u,v,w;
	dist[src] = 0;
	
	//Calculate shortest path from src to every other vertex
	for(int i = 1;i < n;i++){
		for(int j = 0;j < m;j++){
			u = adj[j].s;
			v = adj[j].d;
			w = adj[j].wt;
			if(dist[u] != INT_MAX && dist[v] > dist[u]+w){
				dist[v] = dist[u]+w;
			}
		}
	}
	
	//Check for negative cycle
	for(int i = 0;i < m;i++){
		u = adj[i].s;
		v = adj[i].d;
		w = adj[i].wt;
		if(dist[u] != INT_MAX && dist[v] > dist[u]+w){
				cout<<"Negative Weight Cycle is present in the graph.";
				break;
			}
	}
}

void userInput(){
	adj.clear();
	int n,m,u,v,w,src;
	cout<<"Enter the number of vertices: ";
	cin>>n;
	cout<<"Enter the number of edges: ";
	cin>>m;
	for(int i = 0;i < m;i++){
		cout<<"Enter edge description (u,v,w): ";
		cin>>u>>v>>w;
		addEdge(u,v,w);
	}
	cout<<"Enter source vertex: ";
	cin>>src;
	bellmanFord(n,m,src);
	
	cout<<"Shortest distances from the src vertex to every vertex are: ";
	for(int i = 0;i < n;i++){
		cout<<dist[i]<<" ";
	}
	cout<<endl;
}

void testInput(){
	adj.clear();
	int n = 5;
	int m = 8;
	addEdge(0,1,-1);
	addEdge(0,2,4);
	addEdge(1,2,3);
	addEdge(1,3,2);
	addEdge(3,1,1);
	addEdge(3,2,5);
	addEdge(1,4,2);
	addEdge(4,3,-3);
	
	int src = 0;
	bellmanFord(n,m,src);
	
	cout<<"Shortest distances from the src vertex to every vertex are: ";
	for(int i = 0;i < n;i++){
		cout<<dist[i]<<" ";
	}
	cout<<endl;
}

int main(){
	userInput();
	//testInput();
	
	return 0;
}
