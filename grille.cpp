#include <bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define pb push_back
#define vi vector<int>
#define vvi vector<vector<int> >
#define vll vector<ll>
#define sz(x) (int)(x).size()
#define all(x) x.begin(),x.end()
#define MOD 1000000007
typedef long long int ll;

const int szmax = 1005;

template<typename T>T ind_min(vector<T>& v, T val){int ans = lower_bound(v.begin(), v.end(), val) - v.begin();if(ans==0 && v[0]!=val) ans = -1;return ans;}
template<typename T>T ind_max(vector<T>& v, T val){int ans = upper_bound(v.begin(), v.end(), val) - v.begin();if(ans==(int)v.size()-1 && v[(int)v.size()-1]!=val) ans=(int)v.size();return ans;}
template<typename T>T suporeq(vector<T>& v, T val){return v.end() - lower_bound(v.begin(), v.end(), val);}
template<typename T>T supstrict(vector<T>& v, T val){return v.end() - upper_bound(v.begin(), v.end(), val);}
int h, w;
string grid[szmax];
vvi dp(szmax);
int solve(int i, int j){
	if(grid[i][j]=='#') return dp[i][j] = 0;
	if(dp[i][j]!=-1) return dp[i][j];
	if(i==0 && j==0) return dp[i][j] = 1;
	if(i==0)return dp[i][j] = solve(i,j-1);
	if(j==0)return dp[i][j] = solve(i-1,j);
	return dp[i][j] = (solve(i,j-1) + solve(i-1,j))%MOD;
}

int main(){
	cin>>h>>w;
	for(int i=0;i<h;i++) {
		cin>>grid[i];
		vi v(w,-1);
		dp[i] = v;
	}
	ll ans = solve(h-1, w-1);
	cout<<ans;
	return 0;
}
