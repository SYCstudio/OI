#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30010;
const int maxAlpha=2;
const int maxTrie=3000010;
const int inf=2147483647;

class Trie_Data
{
public:
    int end,fail;
    bool dange;
    int son[maxAlpha];
    Trie_Data()
    {
		end=dange=0;mem(son,0);
		return;
    }
};

int n;
char str[maxTrie];
int triecnt=0;
Trie_Data T[maxTrie];
queue<int> Queue;
bool vis[maxN],instack[maxN];

void Insert(char * str);
void GetFail();
void dfs(int now);

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
		scanf("%s",str+1);
		Insert(str);
    }
    GetFail();
    dfs(0);
    printf("NIE\n");
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
    T[now].end=T[now].dange=1;
    return;
}

void GetFail()
{
    for (int i=0;i<maxAlpha;i++)
		if (T[0].son[i]) Queue.push(T[0].son[i]);
    do
    {
		int u=Queue.front();Queue.pop();
		for (int i=0;i<maxAlpha;i++)
			if (T[u].son[i])
			{
				Queue.push(T[u].son[i]);
				T[T[u].son[i]].fail=T[T[u].fail].son[i];
				if (T[T[T[u].fail].son[i]].dange)
					T[T[u].son[i]].dange=1;
			}
			else T[u].son[i]=T[T[u].fail].son[i];
    }
    while (!Queue.empty());
    return;
}

void dfs(int u)
{
    vis[u]=1;instack[u]=1;
    for (int i=0;i<maxAlpha;i++)
		if (instack[T[u].son[i]])
		{
			printf("TAK\n");
			exit(0);
		}
		else if ((vis[T[u].son[i]]==0)&(T[T[u].son[i]].dange==0))
			dfs(T[u].son[i]);
    instack[u]=0;
    return;
}
