#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;

int n,m;
map<string,int> Mp;
int Nxt[maxN],vis[maxN],D[maxN];
queue<int> Qu;

int main(){
    ios::sync_with_stdio(false);
    cin>>m;
    while (m--){
	string a,b;cin>>a>>b;
	if (Mp.count(a)==0) Mp[a]=++n;if (Mp.count(b)==0) Mp[b]=++n;
	if (Nxt[Mp[a]]){
	    puts("-1");return 0;
	}
	Nxt[Mp[a]]=Mp[b];
    }
    if (n&1){
	puts("-1");return 0;
    }
    for (int i=1;i<=n;i++)
	if (Nxt[i]==0){
	    puts("-1");return 0;
	}
	else if (Nxt[i]==i) Nxt[i]=0;
    for (int i=1;i<=n;i++) ++D[Nxt[i]];
    int Ans=0;vis[0]=1;
    for (int i=1;i<=n;i++) if (Nxt[Nxt[i]]==i&&vis[i]==0) vis[i]=vis[Nxt[i]]=1;
    for (int i=1;i<=n;i++) if (!vis[i]&&!D[i]) Qu.push(i);
    while (!Qu.empty()){
	int u=Qu.front();Qu.pop();
	if (!vis[Nxt[u]]){
	    ++Ans;vis[u]=vis[Nxt[u]]=1;
	    int v=Nxt[Nxt[u]];
	    if (!vis[v]&&(--D[v])==0) Qu.push(v);
	}
    }
    for (int i=1;i<=n;i++)
	if (!vis[i]){
	    if (vis[Nxt[i]]) ++Ans,vis[i]=1;
	    else{
		int now=i,cnt=0;
		while (vis[now]==0) vis[now]=1,++cnt,now=Nxt[now];
		Ans+=(cnt+1)/2;
	    }
	}
    printf("%d\n",Ans);return 0;
}
