#include<bits/stdc++.h>
using namespace std;

const int maxN=120;
const int maxM=200;

int n,m,Fa[maxN];
vector<int> T[maxN];
bool vis[maxN];
queue<int> Q;
int To[]={100,80,98,56,37,36,50,40,54,13,7,1};

int main(){
	freopen("oldcomputer3.in","r",stdin);
	freopen("oldcomputer3.out","w",stdout);
	cout<<"node 1"<<endl;
	cout<<"read 0 a"<<endl;
	cout<<"write a 7"<<endl;
	for (int i=10;i>=1;i--){
		cout<<"node "<<To[i]<<endl;
		cout<<"read "<<To[i+1]<<" a"<<endl;
		cout<<"write a "<<To[i-1]<<endl;
	}
	cout<<"node 100"<<endl;
	cout<<"read 80 a"<<endl;
	cout<<"write a 0"<<endl;
	/*
	scanf("%d%d%d",&n,&n,&m);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		T[u].push_back(v);T[v].push_back(u);
	}
	Q.push(1);vis[1]=1;
	while (!Q.empty()){
		int u=Q.front();Q.pop();
		for (int i=0,sz=T[u].size();i<sz;i++)
			if (vis[T[u][i]]==0){
				Q.push(T[u][i]);vis[T[u][i]]=1;
				Fa[T[u][i]]=u;
			}
	}
	int now=n;
	while (now!=1){
		cout<<now<<" ";now=Fa[now];
	}
	//*/
	return 0;
}
