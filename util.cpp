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
