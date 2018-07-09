#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)
#define lowbit(x) ((x)&(-x))

const int maxN=41010;
const int inf=2147483647;

class SegmentData
{
public:
	int cnt;
	int ls,rs;
};

int n,m;
int H[maxN];
int numcnt,Num[maxN];
int nodecnt,root[maxN];
SegmentData S[maxN*200];

void Build(int &now,int l,int r);
void Modify(int pos,int key,int opt);
int Query(int l,int r,int nl,int nr);
void SModify(int &now,int l,int r,int pos,int key);
int SQuery(int now,int l,int r,int ql,int qr);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&H[i]);
		Num[++numcnt]=H[i];
	}
	sort(&Num[1],&Num[numcnt+1]);numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;

	Build(root[0],0,numcnt);
	for (int i=1;i<=n;i++) Modify(i,Find(H[i]),1);

	int Ans=0;
	for (int i=1;i<=n;i++) Ans+=Query(1,i,Find(H[i])+1,numcnt);
	//for (int i=1;i<=n;i++) cout<<Query(1,i,Find(H[i])+1,numcnt)<<" ";cout<<endl;

	printf("%d\n",Ans);

	scanf("%d",&m);
	
	for (int i=1;i<=m;i++)
	{
		int p1,p2;scanf("%d%d",&p1,&p2);
		if (p1>p2) swap(p1,p2);
		if (p1==p2){
			printf("%d\n",Ans);continue;
		}
		Ans=Ans-Query(p1+1,p2-1,Find(H[p2])+1,numcnt)+Query(p1+1,p2-1,Find(H[p1])+1,numcnt)-Query(p1+1,p2-1,0,Find(H[p1])-1)+Query(p1+1,p2-1,0,Find(H[p2])-1);
		if (H[p1]>H[p2]) Ans--;
		else if (H[p1]<H[p2]) Ans++;

		Modify(p1,Find(H[p1]),-1);Modify(p2,Find(H[p2]),-1);
		swap(H[p1],H[p2]);
		Modify(p1,Find(H[p1]),1);Modify(p2,Find(H[p2]),1);
		printf("%d\n",Ans);
	}

	return 0;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);Build(S[now].rs,mid+1,r);
	return;
}

void Modify(int pos,int key,int opt)
{
	while (pos<=n)
	{
		SModify(root[pos],0,numcnt,key,opt);
		pos+=lowbit(pos);
	}
	return;
}

int Query(int l,int r,int nl,int nr)
{
	if ((l>r)||(nl>nr)) return 0;
	int Ret=0;
	while (r)
	{
		Ret+=SQuery(root[r],0,numcnt,nl,nr);
		r-=lowbit(r);
	}
	l--;
	while (l)
	{
		Ret-=SQuery(root[l],0,numcnt,nl,nr);
		l-=lowbit(l);
	}
	return Ret;
}

void SModify(int &now,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	S[now].cnt+=key;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) SModify(S[now].ls,l,mid,pos,key);
	else SModify(S[now].rs,mid+1,r,pos,key);
	return;
}

int SQuery(int now,int l,int r,int ql,int qr)
{
	if (ql>qr) return 0;
	if ((l==ql)&&(r==qr)) return S[now].cnt;
	int mid=(l+r)>>1;
	if (qr<=mid) return SQuery(S[now].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return SQuery(S[now].rs,mid+1,r,ql,qr);
	else return SQuery(S[now].ls,l,mid,ql,mid)+SQuery(S[now].rs,mid+1,r,mid+1,qr);
}
