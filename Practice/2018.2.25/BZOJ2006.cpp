#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500010;
const int inf=2147483647;

class Segment
{
public:
	int size;
	int ls,rs;
};

class Queue_Data
{
public:
	ll key;
	int r,kth;
};

bool operator < (Queue_Data A,Queue_Data B)
{
	return A.key<B.key;
}

int n,K,L,R;
int nodecnt=0,numcnt=0,Num[maxN];
int A[maxN],root[maxN];
Segment S[maxN*30];
priority_queue<Queue_Data> Q;

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int pos,int key);
int Query(int r1,int r2,int l,int r,int kth);

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>K>>L>>R;
	for (int i=1;i<=n;i++) cin>>A[i+1];
	for (int i=2;i<=n+1;i++) A[i]=A[i-1]+A[i],Num[i]=A[i];
	//for (int i=1;i<=n+1;i++) cout<<A[i]<<" ";cout<<endl;
	sort(&Num[1],&Num[n+2]);
	numcnt=unique(&Num[1],&Num[n+2])-Num-1;
	//for (int i=1;i<=numcnt;i++) cout<<Num[i]<<" ";cout<<endl;
	Build(root[0],1,n);
	for (int i=1;i<=n+1;i++)
	{
		root[i]=root[i-1];
		//cout<<"Modify:"<<i<<" "<<lower_bound(&Num[1],&Num[numcnt+1],A[i])-Num<<endl;
		Modify(root[i],1,numcnt,lower_bound(&Num[1],&Num[numcnt+1],A[i])-Num,1);
	}
	for (int i=L+1;i<=n+1;i++)
	{
		//cout<<"Q:"<<max(0,i-R)<<" "<<i-L<<endl;
		int pos=Query(root[max(0,i-R-1)],root[i-L],1,numcnt,1);
		Q.push((Queue_Data){A[i]-Num[pos],i,1});
		//cout<<i<<" "<<pos<<" "<<Num[pos]<<" "<<A[i]-Num[pos]<<endl;
	}
	ll Ans=0;
	int cnt=0;
	for (int tt=1;tt<=K;tt++)
	{
		Queue_Data u=Q.top();Q.pop();
		Ans+=u.key;//cout<<u.key<<endl;
		int r=u.r,kth=u.kth;
		if (kth<(r-L)-max(0,r-R-1))
		{
			int pos=Query(root[max(0,r-R-1)],root[r-L],1,numcnt,kth+1);
			Q.push((Queue_Data){A[r]-Num[pos],r,kth+1});
		}
	}
	printf("%lld\n",Ans);
	return 0;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);
	Build(S[now].rs,mid+1,r);
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	if (l==r){
		S[now].size++;return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[now].ls,l,mid,pos,key);
	else Modify(S[now].rs,mid+1,r,pos,key);
	S[now].size=S[S[now].ls].size+S[S[now].rs].size;
	return;
}

int Query(int r1,int r2,int l,int r,int kth)
{
	if (l==r) return l;
	int mid=(l+r)>>1;
	int lsize=S[S[r2].ls].size-S[S[r1].ls].size;
	if (lsize>=kth) Query(S[r1].ls,S[r2].ls,l,mid,kth);
	else return Query(S[r1].rs,S[r2].rs,mid+1,r,kth-lsize);
}
