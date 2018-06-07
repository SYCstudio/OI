#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson S[now].ls
#define rson S[now].rs
#define find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=200010;
const int inf=2147483647;

class SegmentData
{
public:
	int sum;
	int ls,rs;
	void init(){
		sum=rs=ls=0;return;
	}
};

int n,m;
int nodecnt,root[maxN];
int Arr[maxN];
int numcnt=0,Num[maxN];
int Lastpos[maxN];
SegmentData S[maxN*100];

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int pos,int key);
int Query(int now,int l,int r,int ql,int qr);

int main()
{
	int T;scanf("%d",&T);
	for (int ti=1;ti<=T;ti++)
	{
		nodecnt=numcnt=0;mem(root,0);mem(Lastpos,0);
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&Arr[i]);
			Num[++numcnt]=Arr[i];
		}
		sort(&Num[1],&Num[numcnt+1]);
		numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;

		Build(root[n+1],1,n);
		for (int i=n;i>=1;i--)
		{
			root[i]=root[i+1];
			int k=find(Arr[i]);
			if (Lastpos[k]!=0) Modify(root[i],1,n,Lastpos[k],-1);
			Modify(root[i],1,n,i,1);
			Lastpos[k]=i;
		}
        /*
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++) cout<<Query(root[i],1,n,j,j)<<" ";
			cout<<endl;
		}
		cout<<endl;
        //*/
		int lastans=0;
		printf("Case #%d:",ti);
		while (m--)
		{
			int ql,qr;scanf("%d%d",&ql,&qr);
			ql=(ql+lastans)%n+1;qr=(qr+lastans)%n+1;
			if (ql>qr) swap(ql,qr);
			//cout<<ql<<" "<<qr<<endl;
			int cnt=Query(root[ql],1,n,ql,qr);
			int kth=(cnt+1)/2;
			//cout<<"cnt:"<<cnt<<endl;
			int L=1,R=n,now=root[ql];
			while (L!=R)
			{
				//cout<<"["<<L<<","<<R<<"]"<<endl;
				int lsum=S[lson].sum;
				int mid=(L+R)>>1;
				if (lsum>=kth) now=lson,R=mid;
				else now=rson,L=mid+1,kth-=lsum;
			}
			printf(" %d",lastans=L);
		}
		printf("\n");
	}
	return 0;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;S[now].init();
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	if (l==r){
		S[now].sum+=key;return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	S[now].sum=S[lson].sum+S[rson].sum;
	return;
}

int Query(int now,int l,int r,int ql,int qr)
{
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return S[now].sum;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}
