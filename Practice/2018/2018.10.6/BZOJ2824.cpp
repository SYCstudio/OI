#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=55;
const int inf=2147483647;

int n;
int W[maxN],tot=0;
pair<int,int> Sorter[maxN];

bool dfs(int d);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Sorter[i].first),Sorter[i].second=i;
	sort(&Sorter[1],&Sorter[n+1]);
	for (int i=1;i<=n;i++) W[Sorter[i].second]=i;
	for (int i=1;i<n;i++) tot+=(abs(W[i]-W[i+1])>1);
	for (int i=0;;i++)
		if (dfs(i)){
			printf("%d\n",i);break;
		}
	return 0;
}

bool dfs(int d){
	if (tot+(W[n]!=n)>d) return 0;
	if ((tot==0)&&(W[1]==1)) return 1;
	for (int i=n;i>=1;i--)
		if ((i==n)||(abs(W[i]-W[i+1])>1)){
			if (i!=n) tot-=(abs(W[i]-W[i+1])>1);
			for (int p=1,q=i;p<q;p++,q--) swap(W[p],W[q]);
			if (i!=n) tot+=(abs(W[i]-W[i+1])>1);
			if (dfs(d-1)) return 1;
			if (i!=n) tot-=(abs(W[i]-W[i+1])>1);
			for (int p=1,q=i;p<q;p++,q--) swap(W[p],W[q]);
			if (i!=n) tot+=(abs(W[i]-W[i+1])>1);
		}
	return 0;
}
