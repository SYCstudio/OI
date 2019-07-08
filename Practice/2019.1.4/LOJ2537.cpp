#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=303000;
const int Mod=998244353;

class SegmentData
{
public:
	int ls,rs,sum,mul;
	SegmentData()
	{
		mul=1;
		return;
	}
};

int n;
int Son[maxN][2],Val[maxN],num,Num[maxN],Ans;
int nodecnt,rt[maxN];
SegmentData S[maxN*15];

int QPow(int x,int cnt);
void dfs(int x);
void Mul(int x,int mul);
void PushDown(int x);
void Update(int x);
int Merge(int x,int y,int P,int mul1,int mul2);
void Modify(int &x,int l,int r,int pos);
void Calc(int x,int l,int r);
void outp(int x,int l,int r);

int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		int fa;
		scanf("%d",&fa);
		if (!fa) continue;
		if (Son[fa][0]) Son[fa][1]=i;
		else Son[fa][0]=i;
	}
	int inv=QPow(10000,Mod-2);
	for (int i=1; i<=n; i++) {
		scanf("%d",&Val[i]);
		if (Son[i][0]==0) Num[++num]=Val[i];
		else Val[i]=1ll*Val[i]*inv%Mod;
	}
	sort(&Num[1],&Num[num+1]);
	num=unique(&Num[1],&Num[num+1])-Num-1;
	for (int i=1; i<=n; i++) if (Son[i][0]==0) Val[i]=lower_bound(&Num[1],&Num[num+1],Val[i])-Num;
	dfs(1);
	Calc(rt[1],1,num);
	printf("%d\n",Ans);
	return 0;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
void dfs(int x)
{
	if (Son[x][0]==0) Modify(rt[x],1,num,Val[x]);
	else if (Son[x][1]==0) dfs(Son[x][0]),rt[x]=rt[Son[x][0]];
	else {
		dfs(Son[x][0]);
		dfs(Son[x][1]);
		//PreMerge(rt[Son[x][0]],rt[Son[x][1]],Val[x],1,1);
		rt[x]=Merge(rt[Son[x][0]],rt[Son[x][1]],Val[x],0,0);
	}
	//cout<<x<<" : ["<<Val[x]<<"]";outp(rt[x],1,num);cout<<endl;
	return;
}
void Mul(int x,int mul)
{
	S[x].sum=1ll*S[x].sum*mul%Mod;
	S[x].mul=1ll*S[x].mul*mul%Mod;
	return;
}
void PushDown(int x)
{
	if (S[x].mul!=1) {
		if (S[x].ls) Mul(S[x].ls,S[x].mul);
		if (S[x].rs) Mul(S[x].rs,S[x].mul);
		S[x].mul=1;
	}
	return;
}
void Update(int x)
{
	S[x].sum=0;
	if (S[x].ls) S[x].sum=(S[x].sum+S[S[x].ls].sum)%Mod;
	if (S[x].rs) S[x].sum=(S[x].sum+S[S[x].rs].sum)%Mod;
	return;
}
void Modify(int &x,int l,int r,int pos)
{
	if (x==0) x=++nodecnt;
	if (l==r) {
		S[x].sum=1;
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[x].ls,l,mid,pos);
	else Modify(S[x].rs,mid+1,r,pos);
	Update(x);
	//cout<<x<<" "<<l<<" "<<r<<" "<<S[x].sum<<endl;
	return;
}
int Merge(int x,int y,int P,int mul1,int mul2)
{
	//cout<<"Merge:"<<x<<" "<<y<<" "<<mul1<<" "<<mul2<<endl;
	if ((!x)||(!y)) {
		if (x) Mul(x,mul1);
		if (y) Mul(y,mul2);
		return x+y;
	}
	PushDown(x);
	PushDown(y);
	int mll,mlr,mrl,mrr;
	mll=mlr=mul1;
	mrl=mrr=mul2;
	if (S[x].ls&&S[y].rs) {
		int k1=S[S[x].ls].sum,k2=S[S[y].rs].sum;
		mrr=(1ll*k1*P%Mod+mrr)%Mod;
		mll=(1ll*k2*(1-P+Mod)%Mod+mll)%Mod;
	}
	if (S[x].rs&&S[y].ls) {
		int k1=S[S[x].rs].sum,k2=S[S[y].ls].sum;
		mlr=(1ll*k2*P%Mod+mlr)%Mod;
		mrl=(1ll*k1*(1-P+Mod)%Mod+mrl)%Mod;
	}
	S[x].ls=Merge(S[x].ls,S[y].ls,P,mll,mrl);
	S[x].rs=Merge(S[x].rs,S[y].rs,P,mlr,mrr);
	Update(x);
	return x;
}
void Calc(int x,int l,int r)
{
	if (l==r) {
		//cout<<l<<" "<<S[x].sum<<endl;
		Ans=(Ans+1ll*l*Num[l]%Mod*S[x].sum%Mod*S[x].sum%Mod)%Mod;
		return;
	}
	int mid=(l+r)>>1;
	PushDown(x);
	Calc(S[x].ls,l,mid);
	Calc(S[x].rs,mid+1,r);
	return;
}
void outp(int x,int l,int r)
{
	if (l==r) {
		cout<<l<<":"<<S[x].sum<<" ";
		return;
	}
	PushDown(x);
	int mid=(l+r)>>1;
	if (S[x].ls) outp(S[x].ls,l,mid);
	if (S[x].rs) outp(S[x].rs,mid+1,r);
}
