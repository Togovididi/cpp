#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	printf("entre n : "); scanf("%d",&n);
	vector<int> v(n);
	printf("la taille du vecteur est %d\n",(int)v.size());
	for(int i=0;i<(int)v.size();i++){
		printf("%d ",v[i]);
	}
	return 0;
}
