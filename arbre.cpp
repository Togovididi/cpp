#include <bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

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

class EulerWalk{
public:
}


class LCA_LOG{
public:	
#define MAXN 100000
#define level 18
 
vector <int> tree[MAXN];
int depth[MAXN];
int parent[MAXN][level];
void dfs(int cur, int prev)
{
    depth[cur] = depth[prev] + 1;
    parent[cur][0] = prev;
    for (int i=0; i<tree[cur].size(); i++)
    {
        if (tree[cur][i] != prev)
            dfs(tree[cur][i], cur);
    }
}
void precomputeSparseMatrix(int n)
{
    for (int i=1; i<level; i++)
    {
        for (int node = 1; node <= n; node++)
        {
            if (parent[node][i-1] != -1)
                parent[node][i] =
                    parent[parent[node][i-1]][i-1];
        }
    }
}
int lca(int u, int v)
{
    if (depth[v] < depth[u])
        swap(u, v);
    int diff = depth[v] - depth[u];
    for (int i=0; i<level; i++)
        if ((diff>>i)&1)
            v = parent[v][i];
    if (u == v)
        return u;
    for (int i=level-1; i>=0; i--)
        if (parent[u][i] != parent[v][i])
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    return parent[u][0];
}
}

class LCA_CONST{
public:
#define sz 101
vector < int > adj[sz];    // stores the tree
vector < int > euler;      // tracks the eulerwalk
vector < int > depthArr;   // depth for each node corresponding
// to eulerwal
int FAI[sz];     // stores first appearance index of every node
int level[sz];   // stores depth for all nodes in the tree
int ptr;         // pointer to euler walk
int dp[sz][18];  // sparse table
int logn[sz];    // stores log values
int p2[20];      // stores power of 2

void buildSparseTable(int n)
{
memset(dp,-1,sizeof(dp));
for (int i=1; i<n; i++)
dp[i-1][0] = (depthArr[i]>depthArr[i-1])?i-1:i;
for (int l=1; l<15; l++)
for (int i=0; i<n; i++)
if (dp[i][l-1]!=-1 and dp[i+p2[l-1]][l-1]!=-1)
dp[i][l] =
(depthArr[dp[i][l-1]]>depthArr[dp[i+p2[l-1]][l-1]])?
dp[i+p2[l-1]][l-1] : dp[i][l-1];
else
break;
}

int query(int l,int r)
{
int d = r-l;
int dx = logn[d];
if (l==r) return l;
if (depthArr[dp[l][dx]] > depthArr[dp[r-p2[dx]][dx]])
return dp[r-p2[dx]][dx];
else
return dp[l][dx];
}

void preprocess()
{
p2[0] = 1;
for (int i=1; i<18; i++)
p2[i] = p2[i-1]*2;
int val = 1,ptr=0;
for (int i=1; i<sz; i++)
{
logn[i] = ptr-1;
if (val==i)
{
val*=2;
logn[i] = ptr;
ptr++;
}
}
}
void dfs(int cur,int prev,int dep)
{
if (FAI[cur]==-1)
FAI[cur] = ptr;

level[cur] = dep;

euler.push_back(cur);

ptr++;

for (auto x:adj[cur])
{
if (x != prev)
{
dfs(x,cur,dep+1);
euler.push_back(cur);
ptr++;
}
}
}
void makeArr()
{
for (auto x : euler)
depthArr.push_back(level[x]);
}

int LCA(int u,int v)
{
if (u==v)
return u;

if (FAI[u] > FAI[v])
swap(u,v);
return euler[query(FAI[u], FAI[v])];
}
}





int main(){

	return 0;
}
