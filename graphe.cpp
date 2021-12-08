//~ Heavy Light Decomposition | Set 1 (Introduction)


#include <bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define pb push_back
#define vi vector<int>
#define vll vector<ll>
#define sz(x) (int)(x).size()
#define all(x) x.begin(),x.end()
#define MOD 1000000007
typedef long long int ll;

const int szmax = 200005;

template<typename T>T ind_min(vector<T>& v, T val){int ans = lower_bound(v.begin(), v.end(), val) - v.begin();if(ans==0 && v[0]!=val) ans = -1;return ans;}
template<typename T>T ind_max(vector<T>& v, T val){int ans = upper_bound(v.begin(), v.end(), val) - v.begin();if(ans==(int)v.size()-1 && v[(int)v.size()-1]!=val) ans=(int)v.size();return ans;}
template<typename T>T suporeq(vector<T>& v, T val){return v.end() - lower_bound(v.begin(), v.end(), val);}
template<typename T>T supstrict(vector<T>& v, T val){return v.end() - upper_bound(v.begin(), v.end(), val);}


class UnionFind {
public:
	vector<int>parent, rank, dsu_size;
	int components = 0, safe_edges = 0;

	UnionFind(int num) {
		components = num;
		num++;
		parent.resize(num); rank.resize(num); dsu_size.resize(num);
		for (int i = 0; i < num; i++) {parent[i] = i; rank[i] = 0; dsu_size[i] = 0;}
	}
	
	int unite(int u, int v) {
		u = find(u); v = find(v);
		if (u == v)return 0;
		components--;
		if (rank[u] < rank[v]){
			parent[u] = v;
			rank[v] = max(rank[v], 1+rank[u]);
			dsu_size[v] += dsu_size[u];
		}
		else {
			parent[v] = u;
			rank[u] = max(rank[u], 1+rank[v]);
			dsu_size[u] += dsu_size[v];
		}
		return 1;
	}
	int find(int node) {if (parent[node] == node)return node; else return parent[node] = find(parent[node]);}
	bool same(int u, int v) {return find(u) == find(v);}
};
class Edge{
public:
	int id, src, target, label;
	Edge(int target, int label=0, int src=-1, int id=-1){
		this->target = target;
		this->label = label;
		this->src = src;
		this->id = id;
	}
	bool operator <(const Edge& e) const{
		return (this->label < e.label);
	}
};
bool compareEdge(Edge a, Edge b){return a.label < b.label;}
class Graph {
public:
	map<int, vector<Edge> > adj;
	vector<int> nodelist;
	int V;
	
	Graph(){}
	Graph(int V){
		this->V = V;
	}
		
	void prnt(){
		printf("affichage du graphe : \n");
		for(int i=1;i<=V;i++){
			printf("%d : ",i);
			for(Edge e: adj[i]){
				printf("%d ",e.target);
			}printf("\n");
		}printf("\n\n");
	}

	void addEdge(int u, int v, int w=-1, int id=-1){
		adj[u].push_back(Edge(v,w,u,id));
		adj[v].push_back(Edge(u,w,v,id));
	}
};
class BFS{
public:	
	map<int, bool> visited;
	map<int, int> dist;
	Graph g;
	BFS(Graph g){
		this->g = g;
		for(int i=1;i<=g.V;i++){
			dist[i] = INF;
		}
	}
	
	void bfs(int s)
	{
		dist[s] = 0;
		list<int> queue;
		visited[s] = true;
		queue.push_back(s);
	 
		while(!queue.empty())
		{
			s = queue.front();
			//~ cout << s << " ";
			queue.pop_front();
			for (Edge e: g.adj[s])
			{
				dist[e.target] = min(dist[e.target], 1+dist[s]);
				if (!visited[e.target])
				{
					visited[e.target] = true;
					queue.push_back(e.target);
				}
			}
		}
	}
};
class DFS{
public:	
	map<int, bool> visited;
	Graph g;
	DFS(Graph g){
		this->g = g;
	}
	
	void dfs(int v, int parent, int cumul=0)
	{
		visited[v] = true;
		for (Edge e: g.adj[v]){
			if(e.target != parent){
				if (!visited[e.target])
					dfs(e.target, v, 1+cumul);
			}
		}
	}
};
class KruskaMST{
public:
	map<int, bool> visited;
	vector<Edge> edgeList;
	vector<Edge> mstEdges;
	
	Graph g;
	KruskaMST(Graph g){
		this->g = g;
		for(int i=1; i<g.V; i++){
			for(Edge e :g.adj[i]){
				edgeList.push_back(e);
			}
		}
	}
	
	int kruskal_mst(){
		sort(edgeList.begin(), edgeList.end(), compareEdge);
		UnionFind uf(g.V);
		int ans = 0;
		for(Edge e : edgeList){
			if(!uf.same(e.src, e.target)){
				uf.unite(e.src, e.target);
				ans += e.label;
				mstEdges.push_back(e);
			}
		}
		return ans;
	}
	
	void prnt(){
		printf("Affichage du résultat de kruskal\n");
		for(Edge e: edgeList){
			printf("%d %d\n", e.src, e.target);
		}printf("\n\n");
	}
};
class DijkstraSP{
public:
	map<int, int> dist;
	map<int, int> pred;

	Graph g;
	DijkstraSP(Graph g){
		this->g = g;
	}
	
	void dijkstraSP(int src){
		for(int i=1; i<=g.V;i++) {dist[i] = INF; pred[i]=-1;}
		set<Edge> pq;
		pq.insert(Edge(src,0));
		dist[src] = 0;
		while(!pq.empty()){
			Edge u = *(pq.begin()); pq.erase(pq.begin());
			for(Edge v : g.adj[u.target]){
				if(dist[v.target] > dist[u.target] + v.label){
					//~ if(dist[v.target] != INF) pq.erase(pq.find(v));
					dist[v.target] = dist[u.target] + v.label;
					pq.insert(Edge(v.target, dist[v.target]));
					pred[v.target] = u.target;
				}
			}
		}
	}
	
	void prnt(){
		printf("affichage du resultat de dijkstra");
		for(int i=1;i<=g.V;i++){
			int x = i;
			printf("dist[%d] = %d ; %d ",i,dist[i],x);
			while(pred[x] != -1){
				printf("%d ",pred[x]);
				x = pred[x];
			}printf("\n");
		}printf("\n\n");
	}
};
class CycleDetector{
	Graph g;
	map<int, bool> visited;
	CycleDetector(Graph g){
		this->g=g;
	}
	
	bool cycledetect(){
		for(int i=1;i<=g.V;i++){
			if(cycledetectUtil(i,-1)) return true;
		}return false;
	}
	
	bool cycledetectUtil(int u, int parent){
		visited[u] = true;
		for(Edge e: g.adj[u]){
			if(!visited[e.target] ){
				if(cycledetectUtil(e.target, u))
					return true;
			}
			else if (e.target != parent) return true;
		}return false;
	}
};



class Bridge{
public:
	int time = 0;
	map<int, bool>visited;
	map<int, int> disc, low,parent;
	Graph g;
	Bridge(){}
	Bridge(Graph g){
		this->g = g;
	}
	void Graph::bridgeUtil(int u){
		visited[u] = true;
		disc[u] = low[u] = ++time;
		list<int>::iterator i;
		for (Edge e:g.adj[u]){
			int v = e.target;
			if (!visited[v]){
				parent[v] = u;
				bridgeUtil(v);
				low[u]  = min(low[u], low[v]);
				if (low[v] > disc[u])
					cout << u <<" " << v << endl;
			}
			else if (v != parent[u])
				low[u]  = min(low[u], disc[v]);
		}
	}
	void Graph::bridge(){
		for (int i = 0; i < V; i++)parent[i] = NIL;
		for (int i = 0; i < V; i++)if (visited[i] == false)bridgeUtil(i, visited, disc, low, parent);
	}
}

class ArticulationPoint{
public:
	int time;
	map<int, bool>visited, isAP;
	map<int, int> disc, low;
	Graph g;
	ArticulationPoint(){}
	ArticulationPoint(Graph g){
		this->g = g;
	}
	void APUtil(int u, parent){
		int children = 0;
		visited[u] = true;
		disc[u] = low[u] = ++time;
		for (auto v : adj[u]) {
			if (!visited[v]) {
				children++;
				APUtil(v, u);
				low[u] = min(low[u], low[v]);
				if (parent != -1 && low[v] >= disc[u])
					isAP[u] = true;
				}
			else if (v != parent)
			low[u] = min(low[u], disc[v]);
		}
		if (parent == -1 && children > 1)isAP[u] = true;
	}

	void AP(vector<int> adj[], int V){
		int disc[V] = { 0 };
		int low[V];
		bool visited[V] = { false };
		bool isAP[V] = { false };
		int time = 0, parent = -1;
		for (int u = 0; u < V; u++)
			if (!visited[u])
				APUtil(u, parent);
		for (int u = 0; u < V; u++) if (isAP[u] == true)
		cout << u << " ";
	}	
}

class Biconnectivity{
public:
	map<int, bool> visited;
	map<int, bool> disc, low, parent;
	Graph g;
	Biconnectivity(){}
	Biconnectivity(Graph g){
		this->g = g;
	}
	bool isBCUtil(int u){
		static int time = 0;
		int children = 0;
		visited[u] = true;
		disc[u] = low[u] = ++time;
		list<int>::iterator i;
		for (Edge e:g.adj[u){
			int v = e.target;
			if (!visited[v]){
				children++;
				parent[v] = u;
				if (isBCUtil(v))
					return true;
				low[u]  = min(low[u], low[v]);
				if (parent[u] == NIL && children > 1)
					return true;
				if (parent[u] != NIL && low[v] >= disc[u])
					return true;
			}
			else if (v != parent[u])
			low[u]  = min(low[u], disc[v]);
		}
		return false;
	}
	bool isBC(){
		for (int i = 0; i < g.V; i++){
			parent[i] = NIL;
			visited[i] = false;
		}
		if (isBCUtil(0) == true) return false;
		for (int i = 0; i < V; i++)if (visited[i] == false) return false;
		return true;
	}
}

int main(){
	

	return 0;
}

