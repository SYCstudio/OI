#include<bits/stdc++.h>
using namespace std;

const int maxN=1100;
const int maxM=5050;

int n,m;
int U[maxM],V[maxM];
vector<int> T1[maxN],T2[maxN],G[maxN];
int M1[maxN],M2[maxN];

void dfs1(int u);
void dfs2(int u);
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
	scanf("%d%d",&U[i],&V[i]);
	T1[U[i]].pb(V[i]);T2[U[i]].pb(V[i]);
    }
    dfs1(1);dfs2(n);
}
void dfs1(int u){
    M1[u]=1;for (int i=0;i<T1[u].size();i++) if (!M1[T1[u][i]]) dfs1(T1[u][i]);
    return;
}
void dfs2(int u){
    M2[u]=1;for (int i=0;i<T2[u].size();i++) if (!M2[T2[u][i]]) dfs2(T2[u][i]);
    return;
}
