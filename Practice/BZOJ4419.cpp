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
vector<int> Apr[maxN];
map<int,int> E[maxN];
int Ans[maxN];

int Binary(int id,int key);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		char opt;scanf(" %c",&opt);
		if (opt=='!'){
			int id;scanf("%d",&id);Apr[id].push_back(i);
		}
		if (opt=='+'){
			int u,v;scanf("%d%d",&u,&v);if (u>v) swap(u,v);
			E[u].insert(make_pair(v,i));
		}
		if (opt=='-'){
			int u,v;scanf("%d%d",&u,&v);if (u>v) swap(u,v);
			int tim=E[u][v];E[u].erase(v);
			Ans[u]+=Binary(v,tim);Ans[v]+=Binary(u,tim);
		}
	}
	for (int i=1;i<=n;i++){
		for (map<int,int>::iterator it=E[i].begin();it!=E[i].end();it++){
			int u=i,v=(*it).first,tim=(*it).second;
			Ans[u]+=Binary(v,tim);Ans[v]+=Binary(u,tim);
		}
	}
	for (int i=1;i<=n;i++){
		printf("%d",Ans[i]);
		if (i!=n) printf(" ");
	}
	return 0;
}

int Binary(int id,int key){
	if (Apr[id].empty()) return 0;
	int l=0,r=Apr[id].size()-1,pos=r;
	do{
		int mid=(l+r)>>1;
		if (Apr[id][mid]>=key) pos=mid,r=mid-1;
		else l=mid+1;
	}
	while (l<=r);
	cout<<"B:"<<id<<" "<<key<<" "<<pos<<endl;
	return Apr[id].size()-pos;
}
