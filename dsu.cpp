#include <bits/stdc++.h>
using namespace std;

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


#define nmax 500005


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

int main(){
	int n,m; scanf("%d %d",&n,&m);
	vector<int> ans;
	ans.push_back(0);
	vector<int>adj[n+1];
	for(int i=0;i<m;i++){
		int a, b; scanf("%d %d",&a,&b);
		adj[a].push_back(b);
	}
	
	UnionFind dsu(n);
	int nb=0;
	
	for(int i=n;i>0;i--){
		nb++;
		for(int v: adj[i]){
			dsu.unite(i,v) ? nb--: nb+=0;
		}
		ans.push_back(nb);
	}
	reverse(ans.begin(), ans.end());
	for(int i=1;i<(int)ans.size();i++){
		printf("%d\n",ans[i]);
	}
	
}
