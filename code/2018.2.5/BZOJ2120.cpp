#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=5001000;
const int inf=2147483647;

class Question
{
public:
	int l,r,tim,id;
};

class Modify
{
public:
	int pos,before,col;
};

int n,m,nowans=0;
int L,R,Tim;
int Col[maxN],InitCol[maxN],Sum[maxN],Belong[maxN];
Question Q[maxN];
Modify M[maxN];
int Ans[maxN];

bool cmp(Question A,Question B);
void TimeMove(int pos,int col);
void PosMove(int col,int opt);

int main()
{
	scanf("%d%d",&n,&m);
	int size=pow(n,0.66666666);
	for (int i=1;i<=n;i++) Belong[i]=(i-1)/size+1;
	for (int i=1;i<=n;i++) scanf("%d",&Col[i]),InitCol[i]=Col[i];
	int mcnt=0,qcnt=0;
	for (int i=1;i<=m;i++)
	{
		char opt;cin>>opt;
		if (opt=='Q')
		{
			int l,r;scanf("%d%d",&l,&r);
			Q[++qcnt]=(Question){l,r,mcnt,qcnt};
		}
		else
		{
			int pos,col;scanf("%d%d",&pos,&col);
			M[++mcnt]=(Modify){pos,Col[pos],col};
			Col[pos]=col;
		}
	}
	for (int i=1;i<=n;i++) Col[i]=InitCol[i];
	L=1,R=0;Tim=0;
	sort(&Q[1],&Q[qcnt+1],cmp);
	for (int i=1;i<=qcnt;i++)
	{
		while (Tim<Q[i].tim) TimeMove(M[Tim+1].pos,M[Tim+1].col),Tim++;
		while (Tim>Q[i].tim) TimeMove(M[Tim].pos,M[Tim].before),Tim--;
		while (L<Q[i].l) PosMove(Col[L],-1),L++;
		while (L>Q[i].l) PosMove(Col[L-1],1),L--;
		while (R>Q[i].r) PosMove(Col[R],-1),R--;
		while (R<Q[i].r) PosMove(Col[R+1],1),R++;
		Ans[Q[i].id]=nowans;
	}
	for (int i=1;i<=qcnt;i++) printf("%d\n",Ans[i]);
	return 0;
}

bool cmp(Question A,Question B)
{
	return (Belong[A.l]!=Belong[B.l])?(A.l<B.l):((Belong[A.r]!=Belong[B.r])?(A.r<B.r):(A.tim<B.tim));
}

void TimeMove(int pos,int col)
{
	if ((pos>=L)&&(pos<=R)) PosMove(Col[pos],-1),PosMove(col,1);
	Col[pos]=col;
	return;
}

void PosMove(int col,int opt)
{
	nowans-=(Sum[col]>0);
	Sum[col]+=opt;
	nowans+=(Sum[col]>0);
	return;
}
