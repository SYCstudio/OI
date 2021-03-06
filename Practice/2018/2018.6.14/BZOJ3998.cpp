#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=501000;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fa,len;
};

int n,nodecnt=1,root=1,last=1;
int opt,K;
char str[maxN];
Node S[maxN<<1];
int Endpos[maxN<<1],Sum[maxN<<1],A[maxN<<1];
int Q[maxN<<1];

void Insert(int key);
void outp(int u,int K);

int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	for (int i=1;i<=n;i++) Insert(str[i]-'a');

	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S[i].son[j])
				cout<<i<<" -> "<<S[i].son[j]<<" ["<<(char)(j+'a')<<"]"<<endl;
	cout<<endl;
	for (int i=1;i<=nodecnt;i++) cout<<S[i].len<<" ";cout<<endl;
	//*/
	
	scanf("%d%d",&opt,&K);

	for (int i=1;i<=nodecnt;i++) A[S[i].len]++;
	//cout<<"A:";for (int i=1;i<=n;i++) cout<<A[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) A[i]+=A[i-1];
	for (int i=nodecnt;i>=1;i--) Q[A[S[i].len]--]=i;

	//cout<<"Q:";for (int i=1;i<=nodecnt;i++) cout<<Q[i]<<" ";cout<<endl;

	for (int i=nodecnt;i>=1;i--)
	{
		if (opt==1) Endpos[S[Q[i]].fa]+=Endpos[Q[i]];
		else Endpos[Q[i]]=1;
	}
	Endpos[1]=0;

	for (int i=nodecnt;i>=1;i--)
	{
		Sum[Q[i]]=Endpos[Q[i]];
		for (int j=0;j<maxAlpha;j++)
			if (S[Q[i]].son[j]) Sum[Q[i]]+=Sum[S[Q[i]].son[j]];
	}

	//for (int i=1;i<=nodecnt;i++) cout<<Sum[i]<<" ";cout<<endl;
	
	if (Sum[1]<K){
		printf("-1\n");return 0;
	}
	outp(1,K);printf("\n");
	return 0;
}

void Insert(int key)
{
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;Endpos[np]=1;
	while ((p!=0)&&(S[p].son[key]==0)) S[p].son[key]=np,p=S[p].fa;
	if (p==0) S[np].fa=root;
	else
	{
		int q=S[p].son[key];
		if (S[p].len+1==S[q].len) S[np].fa=q;
		else
		{
			int nq=++nodecnt;
			S[nq]=S[q];S[nq].len=S[p].len+1;
			S[q].fa=S[np].fa=nq;
			while ((p!=0)&&(S[p].son[key]==q)) S[p].son[key]=nq,p=S[p].fa;
		}
	}
	return;
}

void outp(int u,int K)
{
	//cout<<"now:"<<u<<" "<<K<<" "<<Endpos[u]<<endl;
	if (Endpos[u]>=K) return;
	K-=Endpos[u];
	for (int i=0;i<maxAlpha;i++)
		if (S[u].son[i])
		{
			if (K<=Sum[S[u].son[i]])
			{
				printf("%c",(char)(i+'a'));
				outp(S[u].son[i],K);
				return;
			}
			K-=Sum[S[u].son[i]];
		}
	return;
}
