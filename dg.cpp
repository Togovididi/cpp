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


class Edge{
public:
	int id, src, target, label;
	Edge(int target, int label=0, int src=-1, int id=-1){
		this->target = target;
		this->label = label;
		this->src = src;
		this->id = id;
	}
	bool operator <(const Edge& e) const{ //sort using id,
		return (this->label < e.label);
	}
};
bool compareEdge(Edge a, Edge b){return a.label < b.label;}
class Graph {
public:
	map<int, vector<Edge> > adj;
	int V;
	
	Graph(){}
	Graph(int V){this->V = V;}
		
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
	}
};
class BFS{
public:	
	map<int, bool> visited;
	Graph g;
	BFS(Graph g){
		this->g = g;
	}
	
	void bfs(int s)
	{
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
class CycleDetector{
public:
	Graph g;
	map<int, bool> visited;
	map<int, bool> rstack;
	CycleDetector(Graph g){
		this->g=g;
	}
	
	bool cycledetect(){
		for(int i=1;i<=g.V;i++){
			if(cycledetectUtil(i)) return true;
		}return false;
	}
	
	bool cycledetectUtil(int u){
		if(!visited[u]){
			visited[u] = true; rstack[u] = true;
			for(Edge e: g.adj[u]){
				if((!visited[e.target] && cycledetectUtil(e.target)) || rstack[e.target]){
					return true;
				}
			}
		}
		return rstack[u] = false;
	}
};
class TopologicalSorter{
public:
	bool isCyclic=false;
	Graph g;
	map<int, bool> visited;
	vector<int> ans;
	TopologicalSorter(Graph g){
		this->g = g;
	}
	void tsort(){
		for(int i=1;i<=g.V;i++){
			if(!visited[i]){
				tsortUtil(i);
			}
		}
		map<int, int> pos;
		for(int i=0;i<(int)ans.size();i++) pos[ans[i]] = i;
		for(int i=1;i<=g.V;i++)
			for(Edge e:g.adj[i])
				if(pos[i] < pos[e.target]) isCyclic = true;
		reverse(ans.begin(),ans.end());
	}
	void tsortUtil(int u){
		visited[u] = true;
		for(Edge e: g.adj[u]){
			if(!visited[e.target]) tsortUtil(e.target);
		}
		ans.push_back(u);
	}	
	void prnt(){
		//~ printf("affichage du resultat\n");
		for(int i=0;i<(int)ans.size();i++){
			printf("%d ",ans[i]);
		}printf("\n");
	}
	map<int, int> indegree;	
	void allts(){
		for(int i=1;i<=g.V;i++){
			for(Edge e: g.adj[i]){
				indegree[e.target]++;
			}
		}
		alltsUtil();
	}
	void alltsUtil(){
		bool flag = false;
		for(int i=1;i<=g.V;i++){
			if(indegree[i] == 0 && !visited[i]){
				for(Edge e: g.adj[i]){
					indegree[e.target]--;
				}
				ans.push_back(i);
				visited[i] = true;
				alltsUtil();
				visited[i] = false;
				ans.pop_back();
				for(Edge e: g.adj[i]){
					indegree[e.target]++;
				}
				flag = true;
			}
		}
		if(!flag){
			for(int x: ans){
				printf("%d ",x);
			}printf("\n");
		}
	}
};


int main(){
	
	return 0;
}
