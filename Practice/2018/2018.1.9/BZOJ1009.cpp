#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxstr=25;
const int maxAlpha=10;
const int inf=2147483647;

int n,m,Mod;

class Matrix
{
public:
    int M[maxstr][maxstr];
    Matrix()
    {
	mem(M,0);
	return;
    }
};

Matrix operator * (Matrix A,Matrix B)
{
    Matrix Ans;
    for (int i=0;i<maxstr;i++)
	for (int k=0;k<maxstr;k++)
	    for (int j=0;j<maxstr;j++)
		Ans.M[i][j]=(Ans.M[i][j]+A.M[i][k]*B.M[k][j]%Mod)%Mod;
    return Ans;
}

class Trie_Data
{
public:
    int end,fail;
    int son[maxAlpha];
    Trie_Data()
    {
	end=fail=0;mem(son,0);
	return;
    }
};

int triecnt=0;
Trie_Data T[maxstr];
queue<int> Queue;

void Insert(char * str);
void GetFail();

int main()
{
    scanf("%d%d%d",&n,&m,&Mod);
    char str[maxstr];
    scanf("%s",str+1);
    Insert(str);
    GetFail();
    Matrix Ret;
    for (int i=0;i<=triecnt;i++)
	for (int j=0;j<maxAlpha;j++)
	    if (T[T[i].son[j]].end==0)
		Ret.M[T[i].son[j]][i]++;
    /*
    for (int i=0;i<=triecnt+5;i++)
    {
	for (int j=0;j<=triecnt+5;j++)
	    cout<<Ret.M[i][j]<<" ";
	cout<<endl;
    }
    //*/
    Matrix MAns;for (int i=0;i<=triecnt;i++) MAns.M[i][i]=1;
    while (n)
    {
	if (n&1) MAns=MAns*Ret;
	Ret=Ret*Ret;
	n=n>>1;
    }
    /*
    for (int i=0;i<=triecnt;i++)
    {
	for (int j=0;j<=triecnt;j++)
	    cout<<MAns.M[i][j]<<" ";
	cout<<endl;
    }
    //*/
    ll Ans=0;
    for (int i=0;i<=triecnt;i++) Ans=(Ans+MAns.M[i][0])%Mod;
    printf("%lld\n",Ans);
    return 0;
}

void Insert(char * str)
{
    int l=strlen(str+1);
    int now=0;
    for (int i=1;i<=l;i++)
    {
	if (T[now].son[str[i]-'0']==0) T[now].son[str[i]-'0']=++triecnt;
	now=T[now].son[str[i]-'0'];
    }
    T[now].end=1;
    return;
}

void GetFail()
{
    for (int i=0;i<maxAlpha;i++) if (T[0].son[i]) Queue.push(T[0].son[i]);
    do
    {
	int u=Queue.front();Queue.pop();
	for (int i=0;i<maxAlpha;i++)
	    if (T[u].son[i])
	    {
		Queue.push(T[u].son[i]);
		T[T[u].son[i]].fail=T[T[u].fail].son[i];
		if (T[T[T[u].fail].son[i]].end!=0) T[T[u].son[i]].end=1;
	    }
	    else T[u].son[i]=T[T[u].fail].son[i];
    }
    while (!Queue.empty());
    return;
}
