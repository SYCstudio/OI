#include<bits/stdc++.h>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
char str[maxN];
stack<int> St;
int del[maxN],vis[maxN],ink[maxN];

void Add_Edge(int u,int v);
bool check(int u);

int main(){
	mem(Head,-1);
	cin>>n>>m;
	cin>>(str+1);
	for (int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		Add_Edge(u,v);Add_Edge(v,u);
	}
	for (int i=1;i<=n;i++)
		if (check(i)==0){
			St.push(i);
			do{
				int u=St.top();St.pop();
				if (del[u]==1) continue;
				del[u]=1;
				for (int j=Head[u];j!=-1;j=Next[j])
					if ((del[V[j]]==0)&&(check(V[j])==0)) St.push(V[j]);
			}
			while (!St.empty());
		}

	bool flag=0;
	for (int i=1;i<=n;i++) if (del[i]==0) flag=1;
	if (flag) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

bool check(int u){
	bool fa=0,fb=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (del[V[i]]==0){
			if (str[V[i]]=='A') fa=1;
			if (str[V[i]]=='B') fb=1;
		}
	return fa&fb;
}
