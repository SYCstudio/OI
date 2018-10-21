#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=21;
const int maxAlpha=26;
const int inf=2147483647;

class Trie_Data
{
public:
    int end,depth,fail;
    int son[maxAlpha];
    Trie_Data()
    {
	end=depth=0;
	mem(son,0);
	return;
    }
};

int n,m;
char str[2000010];
int triecnt=0;
Trie_Data T[100000];
queue<int> Queue;
bool Explain[2000010];

void Insert(char * str);
void GetFail();
int AhoCorasick(char * str);

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {
	scanf("%s",str+1);
	Insert(str);
    }
    GetFail();
    for (int i=1;i<=m;i++)
    {
	scanf("%s",str+1);
	printf("%d\n",AhoCorasick(str));
    }
    return 0;
}

void Insert(char * str)
{
    int l=strlen(str+1);
    int now=0;
    for (int i=1;i<=l;i++)
    {
	if (T[now].son[str[i]-'a']==0) T[now].son[str[i]-'a']=++triecnt,T[triecnt].depth=T[now].depth+1;
	now=T[now].son[str[i]-'a'];
    }
    T[now].end=1;
    return;
}

void GetFail()
{
    for (int i=0;i<maxAlpha;i++)
	if (T[0].son[i]) Queue.push(T[0].son[i]),T[T[0].son[i]].fail=0;
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

int AhoCorasick(char * str)
{
    mem(Explain,0);
    Explain[0]=1;
    int l=strlen(str+1);
    int now=0;
    for (int i=1;i<=l;i++)
    {
	now=T[now].son[str[i]-'a'];
	for (int j=now;j!=0;j=T[j].fail)
	    if ((T[j].end)&&(Explain[i-T[j].depth]==1))
	    {
		Explain[i]=1;
		break;
	    }
    }
    //for (int i=1;i<=l;i++) cout<<Explain[i];cout<<endl;
    for (int i=l;i>=0;i--) if (Explain[i]) return i;
}
