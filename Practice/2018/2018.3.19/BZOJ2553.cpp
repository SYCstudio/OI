#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10;
const int maxLen=20;
const int maxNode=maxN*maxLen;
const int maxAlpha=27;
const int inf=2147483647;

class Trie
{
public:
	int end,fail;
	int son[maxAlpha];
};

class Matrix
{
public:
	ld M[maxNode][maxNode];
};

int n,len,alpha,nodecnt;
char str[maxLen];
Trie T[maxNode];
int Queue[maxNode];
Matrix Ans,Ret;

void Insert(char *str);
void GetFail();
void Mul1();
void Mul2();

int main()
{
	scanf("%d%d%d",&n,&len,&alpha);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		Insert(str);
	}
	GetFail();
	ld dx=(ld)1/(ld)alpha;
	for (int i=0;i<=nodecnt;i++)
	{
		if (T[i].end) for (int j=0;j<alpha;j++) T[i].son[j]=0;
		if (T[i].end) continue;
		for (int j=0;j<alpha;j++)
			//if (T[i].son[j])
			{
				if (T[T[i].son[j]].end) Ret.M[i][0]+=dx,Ret.M[i][nodecnt+1]+=dx;
				else Ret.M[i][T[i].son[j]]+=dx;
			}
	}
	Ret.M[nodecnt+1][nodecnt+1]=1;
	/*
	for (int i=0;i<=nodecnt+1;i++)
	{
		for (int j=0;j<=nodecnt+1;j++)
			printf("%.6LF ",Ret.M[i][j]);
		printf("\n");
	}
	printf("\n");
	//*/
	Ans.M[0][0]=1;
    /*
	while (len--)
	{
		Mul1();
		for (int i=0;i<=nodecnt+1;i++)
		{
			for (int j=0;j<=nodecnt+1;j++)
				printf("%.6LF ",Ans.M[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	//*/
    
	while (len)
	{
		if (len&1) Mul1();
		Mul2();
		len=len>>1;
	}
	//*/
	printf("%.10lf\n",(double)Ans.M[0][nodecnt+1]);
	return 0;
}

void Insert(char *str)
{
	int len=strlen(str+1);
	int now=0;
	for (int i=1;i<=len;i++)
	{
		if (T[now].son[str[i]-'a']==0) T[now].son[str[i]-'a']=++nodecnt;
		now=T[now].son[str[i]-'a'];
		if (T[now].end) break;
	}
	T[now].end=1;
	return;
}

void GetFail()
{
	int h=0,t=0;
	for (int i=0;i<alpha;i++) if (T[0].son[i]) Queue[++h]=T[0].son[i];
	while (t!=h)
	{
		int u=Queue[++t];
		for (int i=0;i<alpha;i++)
			if (T[u].son[i])
			{
				T[T[u].son[i]].fail=T[T[u].fail].son[i];
				Queue[++h]=T[u].son[i];
				T[T[u].son[i]].end|=T[T[T[u].fail].son[i]].end;
			}
			else T[u].son[i]=T[T[u].fail].son[i];
	}
	return;
}

ld Baup[maxNode][maxNode];

void Mul1()
{
	int sz=nodecnt+1;
	for (int i=0;i<=sz;i++) Baup[0][i]=Ans.M[0][i],Ans.M[0][i]=0;
	for (int j=0;j<=sz;j++)
		for (int k=0;k<=sz;k++)
			Ans.M[0][j]=Ans.M[0][j]+Baup[0][k]*Ret.M[k][j];
	return;
}

void Mul2()
{
	int sz=nodecnt+1;
	for (int i=0;i<=sz;i++) for (int j=0;j<=sz;j++) Baup[i][j]=Ret.M[i][j],Ret.M[i][j]=0;
	for (int i=0;i<=sz;i++)
		for (int j=0;j<=sz;j++)
			for (int k=0;k<=sz;k++)
				Ret.M[i][j]=Ret.M[i][j]+Baup[i][k]*Baup[k][j];
	return;
}
