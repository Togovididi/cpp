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


class FordFulkersonFlow{
public:
bool bfs(int rGraph[V][V], int s, int t, int parent[]){
    bool visited[V];
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}
int fordFulkerson(int graph[V][V], int s, int t){
    int u, v;
    int rGraph[V]
              [V]; 
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];
 
    int parent[V];
 
    int max_flow = 0;
    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}
int main(){
    int graph[V][V]
        = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 },
            { 0, 4, 0, 0, 14, 0 },  { 0, 0, 9, 0, 0, 20 },
            { 0, 0, 0, 7, 0, 4 },   { 0, 0, 0, 0, 0, 0 } };
 
    cout << "The maximum possible flow is "
         << fordFulkerson(graph, 0, 5);
 
    return 0;
}	
}


class MininmumSTCutFLow{
public:
int bfs(int rGraph[V][V], int s, int t, int parent[]){
bool visited[V];
memset(visited, 0, sizeof(visited));
queue <int> q;
q.push(s);
visited[s] = true;
parent[s] = -1;
while (!q.empty())
{
int u = q.front();
q.pop();

for (int v=0; v<V; v++)
{
if (visited[v]==false && rGraph[u][v] > 0)
{
q.push(v);
parent[v] = u;
visited[v] = true;
}
}
}
return (visited[t] == true);
}
void dfs(int rGraph[V][V], int s, bool visited[])
{
visited[s] = true;
for (int i = 0; i < V; i++)
if (rGraph[s][i] && !visited[i])
dfs(rGraph, i, visited);
}
void minCut(int graph[V][V], int s, int t)
{
int u, v;
int rGraph[V][V]; // rGraph[i][j] indicates residual capacity of edge i-j
for (u = 0; u < V; u++)
for (v = 0; v < V; v++)
rGraph[u][v] = graph[u][v];

int parent[V];
while (bfs(rGraph, s, t, parent)){
int path_flow = INT_MAX;
for (v=t; v!=s; v=parent[v])
{
u = parent[v];
path_flow = min(path_flow, rGraph[u][v]);
}
for (v=t; v != s; v=parent[v])
{
u = parent[v];
rGraph[u][v] -= path_flow;
rGraph[v][u] += path_flow;
}
}
bool visited[V];
memset(visited, false, sizeof(visited));
dfs(rGraph, s, visited);
for (int i = 0; i < V; i++)
for (int j = 0; j < V; j++)
if (visited[i] && !visited[j] && graph[i][j])
cout << i << " - " << j << endl;

return;
}
}



class MaxNumberOfEdgeDisjointPahts{
public:
	Graph g;
	Bridge(){}
	Bridge(Graph g){
		this->g = g;
	}
	bool bfs(int rGraph[V][V], int s, int t, int parent[]){
		bool visited[V];
		memset(visited, 0, sizeof(visited));
		queue <int> q;
		q.push(s);
		visited[s] = true;
		parent[s] = -1;
		while (!q.empty()){
			int u = q.front();
			q.pop();

			for (int v=0; v<V; v++){
				if (visited[v]==false && rGraph[u][v] > 0){
						q.push(v);
						parent[v] = u;
						visited[v] = true;
				}
			}
		}
		return (visited[t] == true);
	}
	int findDisjointPaths(int graph[V][V], int s, int t){
		int u, v;
		int rGraph[V][V];
		for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
		rGraph[u][v] = graph[u][v];
		int parent[V]; // This array is filled by BFS and to store path
		int max_flow = 0; // There is no flow initially
		while (bfs(rGraph, s, t, parent)){
			int path_flow = INT_MAX;
			for (v=t; v!=s; v=parent[v]){
				u = parent[v];
				path_flow = min(path_flow, rGraph[u][v]);
			}
			for (v=t; v != s; v=parent[v])
			{
				u = parent[v];
				rGraph[u][v] -= path_flow;
				rGraph[v][u] += path_flow;
			}
			max_flow += path_flow;
		}
		return max_flow;
	}
}
