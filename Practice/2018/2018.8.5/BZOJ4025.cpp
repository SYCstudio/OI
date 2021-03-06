#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int maxM=201000;
const int maxBit=20;
const int inf=2147483647;

class Edge
{
public:
	int u,v;
};

int n,m,T;
Edge E[maxM];
vector<int> S[maxN<<2];
int UFS[maxN],Rev[maxN],Size[maxN],flag=1;
int top,St1[maxN],St2[maxN],St3[maxN],St4[maxN];
int Ans[maxN];

void Modify(int now,int l,int r,int ql,int qr,int id);
void Query(int now,int l,int r,int depth);
int Find(int x);
int GetRev(int x);

int main(){
	scanf("%d%d%d",&n,&m,&T);
	for (int i=1;i<=m;i++){
		int s,t;scanf("%d%d%d%d",&E[i].u,&E[i].v,&s,&t);
		if (s==t) continue;
		Modify(1,1,T,s+1,t,i);
	}

	for (int i=1;i<=n;i++) UFS[i]=i,Rev[i]=0,Size[i]=1;

	Query(1,1,T,1);

	for (int i=1;i<=T;i++)
		if (Ans[i]) printf("Yes\n");
		else printf("No\n");

	return 0;
}

void Modify(int now,int l,int r,int ql,int qr,int id){
	if ((l==ql)&&(r==qr)){
		S[now].push_back(id);return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,id);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,id);
	else{
		Modify(lson,l,mid,ql,mid,id);Modify(rson,mid+1,r,mid+1,qr,id);
	}
	return;
}

void Query(int now,int l,int r,int depth){
	bool nowflag=flag;int nowtop=top;
	if (flag)
		for (int sz=S[now].size(),i=0;i<sz;i++){
			int u=E[S[now][i]].u,v=E[S[now][i]].v;
			//cout<<"Add_Edge:"<<u<<" "<<v<<endl;
			int c1=GetRev(u),c2=GetRev(v);
			if (Find(u)!=Find(v)){
				u=Find(u);v=Find(v);
				if (Size[u]>Size[v]) swap(u,v);
				top++;St1[top]=u;St2[top]=v;St3[top]=Size[v];St4[top]=Rev[u];
				if ( ((c1==c2)&&(Rev[v]==0)) || ((c1!=c2)&&(Rev[v]==1)) ) Rev[u]^=1;
				UFS[u]=v;Size[v]+=Size[u];
			}
			else{
				if (c1==c2){
					flag=0;break;
				}
			}
		}
	//cout<<"Divide:"<<now<<" "<<l<<" "<<r<<" "<<depth<<endl;
	//cout<<flag<<endl;
	//for (int i=1;i<=n;i++) cout<<UFS[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Rev[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Size[i]<<" ";cout<<endl;
	if (l==r) Ans[l]=flag;
	else{
		int mid=(l+r)>>1;
		Query(lson,l,mid,depth+1);Query(rson,mid+1,r,depth+1);
	}
	flag=nowflag;
	while (top!=nowtop){
		int u=St1[top],v=St2[top],sz=St3[top],re=St4[top];top--;
		UFS[u]=u;Size[v]=sz;Rev[u]=re;
	}
	return;
}

int Find(int x){
	if (UFS[x]!=x) return Find(UFS[x]);
	return x;
}

int GetRev(int x){
	if (UFS[x]==x) return Rev[x];
	return GetRev(UFS[x])^Rev[x];
}
/*
3 3 3
1 2 0 2
2 3 0 3
1 3 1 2

4 6 5
1 2 0 3
2 3 1 4
2 4 0 5
1 3 2 4
1 4 3 5
3 4 0 3
//*/
