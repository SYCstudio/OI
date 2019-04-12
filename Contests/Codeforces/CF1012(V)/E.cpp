#include<bits/stdc++.h>
using namespace std;

const int maxN=202000;

int n,S,ufs[maxN],Id[maxN],vis[maxN];
pair<int,int> A[maxN];
vector<int> Ring[maxN];

int find(int x);
void dfs(int rcnt,int u);
int main(){
    scanf("%d%d",&n,&S);for (int i=1;i<=n;i++) scanf("%d",&A[i].first),A[i].second=ufs[i]=i;
    sort(&A[1],&A[n+1]);for (int i=1;i<=n;i++) Id[A[i].second]=i;
    for (int i=1;i<=n;i++)
	if (A[i].first==A[Id[i]].first&&i!=Id[i]){
	    int x=A[i].second,y=Id[i];
	    A[y].second=x;Id[x]=y;Id[i]=A[i].second=i;
	}
    int sum=0,rcnt=0;
    for (int i=1;i<=n;i++) ufs[find(i)]=find(Id[i]);
    for (int i=1,lst=0;i<=n;i++)
	if (Id[i]!=i){
	    ++sum;
	    if (lst&&A[lst].first==A[i].first&&find(A[lst].second)!=find(A[i].second)){
		ufs[find(A[lst].second)]=find(A[i].second);swap(Id[A[lst].second],Id[A[i].second]);
	    }
	    lst=i;
	}
    for (int i=1;i<=n;i++) if (Id[i]!=i&&!vis[i]) dfs(++rcnt,i);

    if (sum>S){
	puts("-1");return 0;
    }
    int trn=min(S-sum,rcnt);
    if (trn<=2){
	printf("%d\n",rcnt);
	for (int i=1,sz;i<=rcnt;i++){
	    printf("%d\n",sz=Ring[i].size());for (int j=0;j<sz;j++) printf("%d ",Ring[i][j]);printf("\n");
	}
    }
    else{
	printf("%d\n",rcnt-(trn-2));
	for (int i=1,sz;i<=rcnt-trn;i++){
	    printf("%d\n",sz=Ring[i].size());for (int j=0;j<sz;j++) printf("%d ",Ring[i][j]);printf("\n");
	}
	int sum=0;for (int i=rcnt-trn+1;i<=rcnt;i++) sum+=Ring[i].size();
	printf("%d\n",sum);
	for (int i=rcnt-trn+1;i<=rcnt;i++) for (int j=0,sz=Ring[i].size();j<sz;j++) printf("%d ",Ring[i][j]);printf("\n");
	printf("%d\n",trn);
	for (int i=rcnt;i>=rcnt-trn+1;i--) printf("%d ",Ring[i][0]);printf("\n");
    }
    return 0;
}
int find(int x){
    if (ufs[x]!=x) ufs[x]=find(ufs[x]);
    return ufs[x];
}
void dfs(int rcnt,int u){
    if (vis[u]) return;
    Ring[rcnt].push_back(u);vis[u]=1;
    dfs(rcnt,Id[u]);return;
}
