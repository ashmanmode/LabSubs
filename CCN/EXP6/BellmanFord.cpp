#include <bits/stdc++.h>
using namespace std;

void printAns(vector<int> dist)
{
	for(int i=0;i<dist.size();i++)
	{
		if(dist[i]==INT_MAX)
			cout << i << " -> "<< -1 << endl; 
		else
			cout << i << " -> " << dist[i] << endl;
	}
}

struct edge
{
	int u;
	int v;
	int w;
};

struct graph
{
	int n;
	int m;

	struct edge* edges ;
};

struct graph* createGraph(int n,int m)
{
	struct graph* g = (struct graph*)malloc(sizeof(struct graph));
	g->n = n ;
	g->m = m ;
	g->edges = (struct edge*)malloc(m*sizeof(struct edge)) ;
}

void bellman(struct graph* g, int v)
{
	int n  = g->n;
	int m  = g->m;

	int *dist  = (int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
		dist[i] = INT_MAX;
	dist[v] = 0  ;

	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<m;j++)
		{

			if(dist[g->edges[j].v] > dist[g->edges[j].u] + g->edges[j].w)
				dist[g->edges[j].v] = dist[g->edges[j].u] + g->edges[j].w;
		}
	}

	for(int j=0;j<m;j++)
	{
		if(dist[g->edges[j].v] > dist[g->edges[j].u] + g->edges[j].w)
			cout << "Cycle" << endl ;
	}

	for(int i=0;i<n;i++)
	{
		if(dist[i]==INT_MAX)
			cout << i << " -> "<< -1 << endl; 
		else
			cout << i << " -> " << dist[i] << endl;
	}
}

//class for directed weighted graph
class Graph
{
public:
	Graph(int n);
	void printAL();    //prints adjancency list
	void addEgde(int u,int v, int w); 
	void dijkstra(int s);
	int size;
	vector< vector< pair<int,int> > > graph;
private:
	int getMin(vector<int>, vector<bool>);
};

Graph::Graph(int n)
{
	size = n ;
	vector< pair<int,int> > list;
	for(int i = 0 ; i < n ; i++ )
		graph.push_back(list);
}

void Graph::printAL()
{
	cout << "printing the Adjacency list " << endl ;
	for(int i = 0 ; i < graph.size() ;i++ )
	{
		cout << "v" << i << " - " ;
		for(int j = 0 ; j < graph[i].size() ; j++ )
			cout << graph[i][j].first << "," << graph[i][j].second << " " ;
		cout << endl ;
	}
}

void Graph::addEgde(int u,int v,int w)
{
	pair<int,int> tmp;
	tmp.first = v ; tmp.second = w ;
	graph[u].push_back(tmp);
} 

int Graph::getMin(vector<int> dist,vector<bool> set)
{
	int minIndex = -1;
	int minVal = INT_MAX ;
	for(int i=0;i<dist.size();i++)
	{
		if(!set[i] && dist[i] < minVal)
		{
			minVal = dist[i];
			minIndex = i;
		}
	}
	return minIndex;
}

void Graph::dijkstra(int s)
{
	// cout << "Dijkstra" << endl ;
	vector<bool> set(size,false);
	vector<int> dist(size,INT_MAX);
	dist[s] = 0 ;

	while(1)
	{
		int minInd = getMin(dist,set);
		if(minInd==-1)
			break;
		set[minInd] = true;

		for(int i=0;i<graph[minInd].size();i++)
		{
			int vert = graph[minInd][i].first;
			if(!set[vert] && dist[vert] > dist[minInd]+graph[minInd][i].second)
				dist[vert] = dist[minInd]+graph[minInd][i].second ;
		}
	}

	//Printing
	printAns(dist);
}

int main()
{
	cout << "Enter No. of Vertices followed by No. of edges " << endl ;
	int n,m,s;
	cin >> n >> m ; 

	//No. of edges now ;
	struct graph *g = createGraph(n,m);
	Graph gD(n);
	struct edge e ;
	cout << "Enter " << m << " edges as (source,destination,weight)" << endl ;
	for(int i=0;i<m;i++){
		cin >> e.u >> e.v >> e.w ;
		g->edges[i] = e ;
		gD.addEgde(e.u,e.v,e.w);
	}
	cout << "Enter the souce Vertex" << endl ;
	cin >> s ;
	cout << "Distances using Bellman Ford" << endl;
	bellman(g,s);

	cout << "Distances using Dijkstra" << endl ;
	gD.dijkstra(s);
	return 0;
}