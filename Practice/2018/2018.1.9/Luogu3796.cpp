#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=160;
const int maxstr=80;
const int maxT=1000010;
const int maxAlpha=26;
const int maxTrie=10000000;
const int inf=2147483647;

class Trie_Data
{
public:
    int id,fail;
    int son[maxAlpha];
    Trie_Data()
    {
	id=fail=0;mem(son,0);
	return;
    }
    void clear()
    {
	id=fail=0;mem(son,0);
	return;
    }
};

int n,triecnt=0;
Trie_Data T[1000000];
char str[1000010];
char Text[151][100];
queue<int> Queue;
int Tot[160];

void Insert(char * str,int id);
void GetFail();
void AhoCorasick(char *str);

int main()
{
    while (scanf("%d",&n)!=EOF)
    {
	if (n==0) break;
	T[0].clear();mem(Tot,0);triecnt=0;
	for (int i=1;i<=n;i++)
	{
	    scanf("%s",Text[i]+1);
	    Insert(Text[i],i);
	}
	GetFail();
	scanf("%s",str+1);
	AhoCorasick(str);
	int mxcnt=0;
	//for (int i=1;i<=n;i++) printf("%d %d\n",i,Tot[i]);
	for (int i=1;i<=n;i++) mxcnt=max(mxcnt,Tot[i]);
	printf("%d\n",mxcnt);
	for (int i=1;i<=n;i++) if (Tot[i]==mxcnt) printf("%s\n",Text[i]+1);
    }
    return 0;
}

void Insert(char * str,int id)
{
    int l=strlen(str+1);
    int now=0;
    for (int i=1;i<=l;i++)
    {
	if (T[now].son[str[i]-'a']==0)
	    T[now].son[str[i]-'a']=++triecnt,T[triecnt].clear();
	now=T[now].son[str[i]-'a'];
    }
    T[now].id=id;
    return;
}

void GetFail()
{
    for (int i=0;i<maxAlpha;i++) if (T[0].son[i])
				 {
				     Queue.push(T[0].son[i]);
				     T[T[0].son[i]].fail=0;
				 }
    do
    {
	int u=Queue.front();Queue.pop();
	for (int i=0;i<maxAlpha;i++)
	    if (T[u].son[i])
	    {
		Queue.push(T[u].son[i]);
		T[T[u].son[i]].fail=T[T[u].fail].son[i];
	    }
	    else T[u].son[i]=T[T[u].fail].son[i];
    }
    while (!Queue.empty());
    return;
}

void AhoCorasick(char * str)
{
    int l=strlen(str+1);
    int now=0;
    for (int i=1;i<=l;i++)
    {
	now=T[now].son[str[i]-'a'];
	for (int j=now;j!=0;j=T[j].fail)
	    if (T[j].id) Tot[T[j].id]++;
    }
    return;
}
