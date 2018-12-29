#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxT=3030000;
const int maxAlpha=26;

int n,nodecnt=1,root=1,Ans=0;
char Input[maxT];
int son[maxT][maxAlpha],isend[maxT],cnt[maxT];

void Insert();
void dfs(int u);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%s",Input+1);Insert();
	}
	dfs(1);printf("%d\n",Ans);return 0;
}

void Insert(){
	int len=strlen(Input+1);
	int lst=0,now=root;
	for (int i=len;i>=1;i--){
		if (son[now][Input[i]-'a']==0) son[now][Input[i]-'a']=++nodecnt;
		now=son[now][Input[i]-'a'];
	}
	isend[now]=1;return;
}
void dfs(int u){
	Ans=max(Ans,cnt[u]);
	int tot=0;
	for (int i=0;i<maxAlpha;i++) if (son[u][i]&&isend[son[u][i]]) ++tot;
	//cout<<u<<" "<<tot<<" "<<cnt[u]<<endl;
	for (int i=0;i<maxAlpha;i++) if (son[u][i]&&isend[son[u][i]]) cnt[son[u][i]]=cnt[u]+tot;
	cnt[u]=isend[u]+tot;
	for (int i=0;i<maxAlpha;i++)
		if (son[u][i]){
			int v=son[u][i];dfs(v);
			if (isend[v]){
				Ans=max(Ans,cnt[u]+cnt[v]-1);
				cnt[u]=max(cnt[u],cnt[v]+tot-1+isend[u]);
			}
		}
	return;
}
