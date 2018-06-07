#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510;
const int maxAlpha=510;
const int maxTrie=510;
const int inf=2147483647;

class TrieData
{
public:
	int end,fail;
	int son[maxAlpha];
};

int n,l,m,nodecnt;
TrieData T[maxTrie];
ld Gl[maxAlpha];
char Input[maxN];
int Id[maxN],Queue[maxTrie];

class Matrix
{
public:
	ld M[maxTrie][maxTrie];
	Matrix(){mem(M,0);}
	Matrix(ld arr[maxTrie][maxTrie]){
		for (int i=0;i<maxTrie;i++)
			for (int j=0;j<maxTrie;j++)
				M[i][j]=arr[i][j];
	}
};

Matrix Ret;

void Insert(char *str,int id);
void GetFail();
void Mul1();
void Mul2();

int main()
{
	//ios::sync_with_stdio(false);
	
	scanf("%d%d%d",&n,&l,&m);
	for (int i=1;i<=m;i++)
	{
		int p,q;scanf("%d%d",&p,&q);
		Gl[i-1]=(ld)p/(ld)q;
	}

	for (int i=1;i<=n;i++)
	{
		scanf("%s",Input+1);
		Insert(Input,i);
	}
	GetFail();
	for (int i=0;i<=nodecnt;i++)
	{
		if (T[i].end) Ret.M[i][i]=1/*,cout<<"1:"<<i<<endl*/;
		else for (int j=0;j<m;j++) Ret.M[i][T[i].son[j]]+=Gl[j]/*,cout<<i<<" "<<T[i].son[j]<<" "<<Gl[j]<<endl*/;
	}
	//Ans.M[0][0]=1;
	for(int i=100;i>=0;i--){
	    Mul2();
		//for (int j=0;j<=nodecnt;j++) cout<<Ans.M[0][j]<<" ";cout<<endl;
	}
	for (int i=1;i<=n;i++) printf("%.2lf\n",Ret.M[0][Id[i]]);
	return 0;
}

void Insert(char *str,int id)
{
	//int len=strlen(str+1);
	int now=0;
	for (int i=1;i<=l;i++)
	{
		if (T[now].son[str[i]-'A']==0) T[now].son[str[i]-'A']=++nodecnt;
		now=T[now].son[str[i]-'A'];
	}
	Id[id]=now;T[now].end=1;return;
}

void GetFail()
{
	int h=0,t=0;
	for (int i=0;i<m;i++) if (T[0].son[i]) Queue[++h]=T[0].son[i];
	while (h!=t)
	{
		int u=Queue[++t];
		for (int i=0;i<m;i++)
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

ld Backup[maxTrie][maxTrie];

/*
void Mul1()
{
	for (int i=0;i<=nodecnt;i++) Backup[0][i]=Ans.M[0][i],Ans.M[0][i]=0;
	for (int i=0;i<=nodecnt;i++)
		for (int j=0;j<=nodecnt;j++)
			Ans.M[0][i]=Ans.M[0][i]+Backup[0][j]*Ret.M[j][i];
	return;
}
//*/

void Mul2()
{
	for (int i=0;i<=nodecnt;i++) for (int j=0;j<=nodecnt;j++) Backup[i][j]=Ret.M[i][j],Ret.M[i][j]=0;
	for (int i=0;i<=nodecnt;i++)
		for (int j=0;j<=nodecnt;j++)
			for (int k=0;k<=nodecnt;k++)
				Ret.M[i][j]=Ret.M[i][j]+Backup[i][k]*Backup[k][j];
	return;
}
