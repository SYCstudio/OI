#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000*2;
const int inf=2147483647;

class SegmentData
{
public:
	int ls,rs,sum;
};

int n;
int nodecnt,Ls[maxN],Rs[maxN],Key[maxN];
int segcnt,root[maxN];
SegmentData S[maxN*30];
ll sum1,sum2,Ans;

void Input(int u);
void Calc(int u);
void Modify(int &now,int l,int r,int pos,int key);
int Merge(int r1,int r2);

int main()
{
	scanf("%d",&n);nodecnt++;
	Input(1);
	Calc(1);
	printf("%lld\n",Ans);
	return 0;
}

void Input(int u)
{
	int key;scanf("%d",&key);
	if (key==0){
		Ls[u]=++nodecnt;Rs[u]=++nodecnt;
		Input(Ls[u]);Input(Rs[u]);
	}
	else Key[u]=key;
	return;
}

void Calc(int u)
{
	//cout<<u<<" "<<Ls[u]<<" "<<Rs[u]<<endl;
	if (Key[u]!=0){
		Modify(root[u],1,n,Key[u],1);return;
	}
	Calc(Ls[u]);Calc(Rs[u]);
	sum1=0;sum2=0;
	root[u]=Merge(root[Ls[u]],root[Rs[u]]);
	Ans=Ans+min(sum1,sum2);
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++segcnt]=S[now];now=segcnt;
	S[now].sum+=key;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[now].ls,l,mid,pos,key);
	else Modify(S[now].rs,mid+1,r,pos,key);
}

int Merge(int r1,int r2)
{
	if (r1==0) return r2;
	if (r2==0) return r1;
	int now=++segcnt;
	sum1=sum1+1ll*S[S[r1].ls].sum*S[S[r2].rs].sum;
	sum2=sum2+1ll*S[S[r1].rs].sum*S[S[r2].ls].sum;
	S[now].sum=S[r1].sum+S[r2].sum;
	S[now].ls=Merge(S[r1].ls,S[r2].ls);
	S[now].rs=Merge(S[r1].rs,S[r2].rs);
	return now;
}
