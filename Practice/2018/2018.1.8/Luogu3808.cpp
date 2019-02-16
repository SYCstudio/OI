#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxAlpha=26;
const int maxN=1000010;
const int inf=2147483647;

class Trie_Data
{
public:
    int end,fail;
    int son[maxAlpha];
    Trie_Data()
		{
			end=fail=0;
			mem(son,0);
		}
};

int n;
int triecnt=0;
char str[1000010];
Trie_Data T[1000010];
queue<int> Queue;

void Insert(char * str);
void GetFail();
int AhoCorasick(char *str);

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
		scanf("%s",str+1);
		Insert(str);
    }
    T[0].fail=0;
    GetFail();
    scanf("%s",str+1);
    printf("%d\n",AhoCorasick(str));
    return 0;
}

void Insert(char * str)
{
    int l=strlen(str+1);
    int now=0;
    for (int i=1;i<=l;i++)
    {
		if (T[now].son[str[i]-'a']) now=T[now].son[str[i]-'a'];
		else now=T[now].son[str[i]-'a']=++triecnt;
    }
    T[now].end++;
    return;
}

void GetFail()
{
    for (int i=0;i<maxAlpha;i++)
		if (T[0].son[i])
		{
			Queue.push(T[0].son[i]);
			T[T[0].son[i]].fail=0;
		}
    do
    {
		int u=Queue.front();Queue.pop();
		for (int i=0;i<maxAlpha;i++)
			if (T[u].son[i])//存在此节点
			{
				Queue.push(T[u].son[i]);
				T[T[u].son[i]].fail=T[T[u].fail].son[i];
			}
			else T[u].son[i]=T[T[u].fail].son[i];//不存在此节点
    }
    while (!Queue.empty());
    return;
}

int AhoCorasick(char * str)
{
    int ret=0;
    int now=0;
    int l=strlen(str+1);
    for (int i=1;i<=l;i++)
    {
		now=T[now].son[str[i]-'a'];
		for (int j=now;(j!=0)&&(T[j].end!=-1);j=T[j].fail)
		{
			ret+=T[j].end;T[j].end=-1;//标记这个已经走过了
		}
    }
    return ret;
}
