#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=61;
const int maxText=110;
const int Mod=10007;
const int maxAlpha=26;
const int inf=2147483647;

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

int n,m;
char str[maxText];
int triecnt=0;
Trie_Data T[100000];
int F[maxText][100000];
queue<int> Queue;

void Insert(char * str);
void GetFail();
ll Pow(ll x,ll cnt);

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {
	scanf("%s",str+1);
	Insert(str);
    }
    GetFail();
    F[0][0]=1;
    for (int i=0;i<m;i++)
	for (int j=0;j<=triecnt;j++)
	    if ((F[i][j])&&(T[j].end==0))
		for (int k=0;k<maxAlpha;k++)
		    if (T[T[j].son[k]].end==0)
			F[i+1][T[j].son[k]]=(F[i+1][T[j].son[k]]+F[i][j])%Mod;
    int Ans=0;
    for (int i=0;i<=triecnt;i++) if (T[i].end==0) Ans=(Ans+F[m][i])%Mod;
    int Tot=Pow(26,m)%Mod;//总方案
    printf("%d\n",(Tot-Ans+Mod)%Mod);
    return 0;
}

void Insert(char * str)
{
    int now=0;
    int l=strlen(str+1);
    for (int i=1;i<=l;i++)
    {
	if (T[now].son[str[i]-'A']==0) T[now].son[str[i]-'A']=++triecnt;
	now=T[now].son[str[i]-'A'];
    }
    T[now].end=1;
    return;
}

void GetFail()
{
    for (int i=0;i<maxAlpha;i++) if (T[0].son[i]) Queue.push(T[0].son[i]),T[T[0].son[i]].fail=0;
    do
    {
	int u=Queue.front();Queue.pop();
	for (int i=0;i<maxAlpha;i++)
	    if (T[u].son[i])
	    {
		Queue.push(T[u].son[i]);
		T[T[u].son[i]].fail=T[T[u].fail].son[i];
		if (T[T[T[u].fail].son[i]].end) T[T[u].son[i]].end=1;//注意这里单词结尾的标记也要传递
	    }
	    else T[u].son[i]=T[T[u].fail].son[i];
    }
    while (!Queue.empty());
    return;
}

ll Pow(ll x,ll cnt)
{
    ll ret=1;
    while (cnt)
    {
	if (cnt&1) ret=ret*x%Mod;
	x=x*x%Mod;
	cnt=cnt>>1;
    }
    return ret;
}
