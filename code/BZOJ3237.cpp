#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int maxM=101000;
const int maxQ=101000;
const int inf=2147483647;

class Edge
{
public:
	int u,v;
};

int n,m,Q;
int tim,Tim[maxN];
Edge E[maxM];
int UFS[maxN],Size[maxN];
int top=0,St1[maxN],St2[maxN],St3[maxN];
vector<int> Qn[maxQ];
int Ans[maxN];

void Divide(int l,int r);
int Find(int x);
void Union(int u,int v);
void Undo();

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) UFS[i]=i,Size[i]=1;
	for (int i=1;i<=m;i++) scanf("%d%d",&E[i].u,&E[i].v);
	scanf("%d",&Q);
	for (int i=1;i<=Q;i++){
		int c;scanf("%d",&c);
		for (int j=1;j<=c;j++){
			int id;scanf("%d",&id);
			Tim[id]=tim;Qn[i].push_back(id);
		}
	}

	for (int i=1;i<=m;i++) if (Tim[i]!=tim) UFS[Find(E[i].u)]=Find(E[i].v);

	Divide(1,Q);
}

void Divide(int l,int r){
	int now=top;
	if (l==r){
		bool flag=1;
		for (int sz=Qn[l].size(),i=0;i<sz;i++)
			if (Find(E[Qn[l][i]].u)!=Find(E[Qn[l][i]].v)){
				flag=0;break;
			}
		Ans[l]=flag;return;
	}

	tim++;int mid=(l+r)>>1;
	for (int i=l;i<=mid;i++) for (int sz=Qn[i].size(),j=0;j<sz;j++) Tim[Qn[i][j]]=tim;
	for (int i=mid+1;i<=r;i++) for (int sz=Qn[i].size(),j=0;j<sz;j++) if (Tim[Qn[i][j]]!=tim) Union(E[Qn[i][j]].u,E[Qn[i][j]].v);

	Divide(l,mid);
	while (top!=now) Undo();
	tim++;
	for (int i=mid+1;i<=r;i++) for (int sz=Qn[i].size(),j=0;j<sz;j++) 
}

int Find(int x){
	if (UFS[x]!=x) return Find(UFS[x]);
	return UFS[x];
}

void Union(int u,int v){
	if (Find(u)!=Find(v)){
		top++;u=Find(u);v=Find(v);
		if (Size[u]>Size[v]) swap(u,v);
		St1[top]=u;St2[top]=UFS[u];St3[top]=Size[u];
		UFS[u]=v;
	}
	return;
}

void Undo(){
	int u=St1[top],f=St2[top],sz=St3[top];top--;
	UFS[u]=f;Size[u]=sz;return;
}
