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


class SparseTable{
public:
	int n;
	int lg;
	vector<vector<int> > lookup;
	SparseTable(){}
	SparseTable(int n){
		this->n = n;
		lg = (int)log2(n) + 1;
		for(int 0;i<=n;i++) lookup.push_back(vector<int> v(lg));
	}
	void preProcess(vector<int> v){
		for(int i=0;i<n;i++) lookup[i][O] = v[i];
		for(int j=1;(1<<j)<=n;j++){//j<lg;
			for(int i=0;(i+(1<<j)-1)<n;i++){
				if (v[lookup[i][j-1]]< v[lookup[i + (1 << (j - 1))][j - 1]])
					lookup[i][j] = lookup[i][j - 1];
				else lookup[i][j] = lookup[i + (1<<(j-1))][j-1];
			}
		}
	}
}

class RQM{
public:
	SparseTable table;
	vector<int> arr;
	vector<vector<int> > lookup;
	RQM(){}
	RQM(vector<int> v, int n){
		table = SparseTable(n);
		arr = v;
		this->lookup = table.lookup;
	}
	void preprocess(){
		for(int i=0;i<n;i++) lookup[i][O] = arr[i];
		for(int j=1;(1<<j)<=n;j++){//j<lg;
			for(int i=0;(i+(1<<j)-1)<n;i++){
				if (arr[lookup[i][j-1]]< arr[lookup[i + (1 << (j - 1))][j - 1]])
					lookup[i][j] = lookup[i][j - 1];
				else lookup[i][j] = lookup[i + (1<<(j-1))][j-1];
			}
		}
	}
	int query(int L, int R){
		int j = (int)log2(R - L + 1);
		if (arr[lookup[L][j]]<= arr[lookup[R - (1 << j) + 1][j]])
			return arr[lookup[L][j]];
		else return arr[lookup[R - (1 << j) + 1][j]];
	}
}

class SqrtDecomp{
public:
	int arr[MAXN];               // original array
	int block[SQRSIZE];          // decomposed array
	int blk_sz;                      // block size

	void update(int idx, int val){
		int blockNumber = idx / blk_sz;
		block[blockNumber] += val - arr[idx];
		arr[idx] = val;
	}
	int query(int l, int r){
		int sum = 0;
		while (l<r and l%blk_sz!=0 and l!=0){
			sum += arr[l];
			l++;
		}
		while (l+blk_sz <= r){
			sum += block[l/blk_sz];
			l += blk_sz;
		}
		while (l<=r){
			sum += arr[l];
			l++;
		}
		return sum;
	}
	void preprocess(int input[], int n){
		int blk_idx = -1;
		blk_sz = sqrt(n);
		for (int i=0; i<n; i++){
			arr[i] = input[i];
			if (i%blk_sz == 0){
				blk_idx++;
			}
			block[blk_idx] += arr[i];
		}
	}
}

class SegTree{
public:
}

class FenwickTree{
public:
}

class DiffArr{
public:
vector<int> initializeDiffArray(vector<int>& A)
{
int n = A.size();
vector<int> D(n + 1);

D[0] = A[0], D[n] = 0;
for (int i = 1; i < n; i++)
D[i] = A[i] - A[i - 1];
return D;
}
void update(vector<int>& D, int l, int r, int x)
{
D[l] += x;
D[r + 1] -= x;
}
int printArray(vector<int>& A, vector<int>& D)
{
for (int i = 0; i < A.size(); i++) {
if (i == 0)
A[i] = D[i];
else
A[i] = D[i] + A[i - 1];

cout << A[i] << " ";
}
cout << endl;
}
}

class PrefSum{
public:
void fillPrefixSum(int arr[], int n, int prefixSum[])
{
prefixSum[0] = arr[0];
for (int i = 1; i < n; i++)
prefixSum[i] = prefixSum[i - 1] + arr[i];
}
int main()
{
int arr[] = { 10, 4, 16, 20 };
int n = sizeof(arr) / sizeof(arr[0]);
int prefixSum[n];

fillPrefixSum(arr, n, prefixSum);
for (int i = 0; i < n; i++)
cout << prefixSum[i] << " ";
}
}

class SuffixTree{
public:
}








class Query{
public:
    int L, R, id, result, blocksize;
    Query(){}
    Query(int l, int r, int id){
		this->L=l;
		this->R=r;
		this->id=id;
	}
	bool operator <(const Query& q) const{
		return (this->L/blocksize != q.L/blocksize && this->L/blocksize < q.L/blocksize) || (this->R < q.R);
	}
};
bool byId(Query q1, Query q2){
	return q1.id < q2.id;
}
class MOsAlgo{
public:
	int block, n;
	vi a;
	MOsAlgo(){}
	MOsAlgo(vector<int>& v){
		a = v;
		n = sz(a);
		block = (int)sqrt(n);
	}
	void process(vector<Query>& q){
		for(Query& Q: q){Q.blocksize = block;}
		int m = sz(q);
		sort(q.begin(),q.end());
	 
		int currL = 0, currR = 0;
		int currSum = 0;
	 
		for (int i=0; i<m; i++){
			int L = q[i].L, R = q[i].R;
			while (currL < L){
				currSum -= a[currL];
				currL++;
			}
			while (currL > L){
				currSum += a[currL-1];
				currL--;
			}
			while (currR <= R){
				currSum += a[currR];
				currR++;
			}
			while (currR > R+1){
				currSum -= a[currR-1];
				currR--;
			}
			//~ printf("%d %d %d\n",q[i].L,q[i].R,currSum);
			q[i].result = currSum;
		}
		sort(all(q), byId);
	}
};


//diffretnts elements

class Query{
public:
    int L, R, id, result, blocksize;
    Query(){}
    Query(int l, int r, int id){
		this->L=l;
		this->R=r;
		this->id=id;
	}
	bool operator <(const Query& q) const{
		return (this->L/blocksize != q.L/blocksize && this->L/blocksize < q.L/blocksize) || (this->R < q.R);
	}
};

bool byId(Query q1, Query q2){
	return q1.id < q2.id;
}

class MOsAlgo{
public:
	int block, n;
	vi a;
	MOsAlgo(){}
	MOsAlgo(vector<int>& v){
		a = v;
		n = sz(a);
		block = (int)sqrt(n);
	}
	void process(vector<Query>& q){
		for(Query& Q: q){Q.blocksize = block;}
		int m = sz(q);
		int freq[szmax] = { 0 };
		sort(q.begin(),q.end());
		int currL = 0, currR = 0;
		int curr_Diff_elements = 0;
		for (int i = 0; i < m; i++) {
			int L = q[i].L, R = q[i].R;
			while (currL < L) {
				freq[a[currL]]--;
				if (freq[a[currL]] == 0) 
					curr_Diff_elements--;
				currL++;
			}
				while (currL > L) {
				freq[a[currL - 1]]++;
				if (freq[a[currL - 1]] == 1) 
					curr_Diff_elements++;
				currL--;
			}
			while (currR <= R) {
				freq[a[currR]]++;
				if (freq[a[currR]] == 1) 
					curr_Diff_elements++;
				currR++;
			}
			while (currR > R + 1) {
				freq[a[currR - 1]]--;
				if (freq[a[currR - 1]] == 0) 
					curr_Diff_elements--;
				currR--;
			}
			q[i].result = curr_Diff_elements;
		}
		sort(all(q), byId);
	}
};
		





class ZAlgo{
public:
void getZarr(string str, int Z[]);
void search(string text, string pattern)
{
string concat = pattern + "$" + text;
int l = concat.length();
int Z[l];
getZarr(concat, Z);
for (int i = 0; i < l; ++i)
{
if (Z[i] == pattern.length())
cout << "Pattern found at index "
<< i - pattern.length() -1 << endl;
}
}
void getZarr(string str, int Z[])
{
int n = str.length();
int L, R, k;
L = R = 0;
for (int i = 1; i < n; ++i)
{
if (i > R)
{
L = R = i;
while (R<n && str[R-L] == str[R])
R++;
Z[i] = R-L;
R--;
}
else
{
k = i-L;
if (Z[k] < R-i+1)
Z[i] = Z[k];
else
{
L = i;
while (R<n && str[R-L] == str[R])
R++;
Z[i] = R-L;
R--;
}
}
}
}
}


class D2PrefSum{
public:
void prefixSum2D(int a[][C])
{
    int psa[R][C];
    psa[0][0] = a[0][0];
    for (int i = 1; i < C; i++)
        psa[0][i] = psa[0][i - 1] + a[0][i];
    for (int i = 1; i < R; i++)
        psa[i][0] = psa[i - 1][0] + a[i][0];
    for (int i = 1; i < R; i++) {
        for (int j = 1; j < C; j++)
            psa[i][j] = psa[i - 1][j] + psa[i][j - 1]
                        - psa[i - 1][j - 1] + a[i][j];
    }
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++)
            cout << psa[i][j] << " ";
        cout << "\n";
    }
}
}
