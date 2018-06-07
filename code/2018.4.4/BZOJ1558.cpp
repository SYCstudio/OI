#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)
#define MIN(a,b,c) min(a,min(b,c))

const int maxN=101000;
const int inf=2147483647;

class Data
{
public:
	int f00,f01,f10,f11;
	int left,right;
	int lazy;
	Data(){
		lazy=0;
	}
};

int n,m;
int Arr[maxN];
Data S[maxN<<2];

Data operator + (Data A,Data B);
void PushDown(int now);
void Build(int now,int l,int r);
void Modify(int now,int l,int r,int ql,int qr,int key);
Data Query(int now,int l,int r,int ql,int qr);
void OutpNum(int now,int l,int r);

int main()
{
	//ios::sync_with_stdio(false);

	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Arr[i]);//cin>>Arr[i];
	for (int i=n;i>=1;i--) Arr[i]=Arr[i]-Arr[i-1];
	//for (int i=1;i<=n;i++) cout<<Arr[i]<<" ";cout<<endl;
	Build(1,1,n);

	//OutpNum(1,1,n);
	cin>>m;
	while (m--)
	{
		char opt;//cin>>opt;
		opt=getchar();
		while ((opt!='A')&&(opt!='B')) opt=getchar();
		if (opt=='A')
		{
			int s,t,a,b;scanf("%d%d%d%d",&s,&t,&a,&b);//cin>>s>>t>>a>>b;
			Modify(1,1,n,s,s,a);
			if (s<t) Modify(1,1,n,s+1,t,b);
			if (t<n) Modify(1,1,n,t+1,t+1,-(t-s)*b-a);
		}
		if (opt=='B')
		{
			int s,t;scanf("%d%d",&s,&t);//cin>>s>>t;
			Data G=Query(1,1,n,s,t);
			//cout<<G.f00<<" "<<G.f10<<" "<<G.f01<<" "<<G.f11<<endl;
			//cout<<min(G.f11,G.f01)<<endl;
			printf("%d\n",min(G.f11,G.f01));
		}
		//OutpNum(1,1,n);cout<<endl;
	}
	return 0;
}

Data operator + (Data A,Data B)
{
	Data Ret;
	Ret.left=A.left;Ret.right=B.right;
	Ret.f00=MIN(A.f01+B.f10-(A.right==B.left),A.f00+B.f10,A.f01+B.f00);
	Ret.f01=MIN(A.f01+B.f11-(A.right==B.left),A.f00+B.f11,A.f01+B.f01);
	Ret.f10=MIN(A.f11+B.f10-(A.right==B.left),A.f10+B.f10,A.f11+B.f00);
	Ret.f11=MIN(A.f11+B.f11-(A.right==B.left),A.f10+B.f11,A.f11+B.f01);
	return Ret;
}

void PushDown(int now)
{
	if (S[now].lazy)
	{
		int lz=S[now].lazy;
		S[lson].left+=lz;S[lson].right+=lz;S[lson].lazy+=lz;
		S[rson].left+=lz;S[rson].right+=lz;S[rson].lazy+=lz;
		S[now].lazy=0;
	}
	return;
}

void Build(int now,int l,int r)
{
	if (l==r)
	{
		S[now].f00=0;S[now].f10=S[now].f01=1;S[now].f11=1;
		S[now].left=S[now].right=Arr[l];//cout<<now<<":"<<Arr[l]<<endl;
		//cout<<l<<" "<<r<<" "<<S[now].left<<" "<<S[now].right<<endl;
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	S[now]=S[lson]+S[rson];
	//cout<<l<<" "<<r<<" "<<S[now].left<<" "<<S[now].right<<endl;
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int key)
{
	if ((l==ql)&&(r==qr))
	{
		S[now].left+=key;S[now].right+=key;S[now].lazy+=key;
		return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,key);
	else
	{
		Modify(lson,l,mid,ql,mid,key);
		Modify(rson,mid+1,r,mid+1,qr,key);
	}
	S[now]=S[lson]+S[rson];
	return;
}

Data Query(int now,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return S[now];
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}

void OutpNum(int now,int l,int r)
{
	cout<<"["<<l<<","<<r<<"]"<<S[now].f00<<" "<<S[now].f10<<" "<<S[now].f01<<" "<<S[now].f11<<" "<<S[now].left<<" "<<S[now].right<<endl;
	if (l==r) return;
	PushDown(now);
	int mid=(l+r)>>1;
	OutpNum(lson,l,mid);OutpNum(rson,mid+1,r);
	return;
}
