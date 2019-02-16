#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=501000;
const int inf=2147483647;

int n,m;
map<int,pair<int,int> > E[maxN];
int Ans[maxN],Cnt[maxN];

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		char opt;scanf(" %c",&opt);
		if (opt=='!'){
			int id;scanf("%d",&id);++Cnt[id];
		}
		if (opt=='+'){
			int u,v;scanf("%d%d",&u,&v);if (u>v) swap(u,v);
			E[u].insert(make_pair(v,make_pair(Cnt[u],Cnt[v])));
		}
		if (opt=='-'){
			int u,v;scanf("%d%d",&u,&v);if (u>v) swap(u,v);
			int c1=E[u][v].first,c2=E[u][v].second;E[u].erase(v);
			Ans[u]+=Cnt[v]-c2;Ans[v]+=Cnt[u]-c1;
		}
	}
	for (int u=1;u<=n;u++){
		for (map<int,pair<int,int> >::iterator it=E[u].begin();it!=E[u].end();it++){
			int v=(*it).first,c1=(*it).second.first,c2=(*it).second.second;
			Ans[u]+=Cnt[v]-c2;Ans[v]+=Cnt[u]-c1;
		}
	}
	for (int i=1;i<=n;i++){
		printf("%d",Ans[i]);
		if (i!=n) printf(" ");
	}
	return 0;
}

