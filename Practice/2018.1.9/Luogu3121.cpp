#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200000;
const int maxAlpha=26;
const int inf=2147483647;

class Trie_Data
{
public:
    int depth,end,fail;
    int son[maxAlpha];
    Trie_Data()
    {
	depth=end=0;mem(son,0);
	return;
    }
};

int n,m;
int triecnt=0;
Trie_Data T[maxN];
char Text[maxN];
char str[maxN];
queue<int> Queue;
int Stack[maxN],Stacknow[maxN];

void Insert(char * str);
void GetFail();
void AhoCorasick(char * str);

int main()
{
    scanf("%s",Text+1);
    int L=strlen(Text+1);
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
	scanf("%s",str+1);
	Insert(str);
    }
    GetFail();
    AhoCorasick(Text);
    return 0;
}

void Insert(char * str)
{
    int now=0;
    int l=strlen(str+1);
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
    int now=0;
    for (int i=0;i<maxAlpha;i++) if (T[0].son[i]) Queue.push(T[0].son[i]),T[0].fail=0;
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
    int stacktop=0;
    for (int i=1;i<=l;i++)
    {
	stacktop++;Stack[stacktop]=str[i];Stacknow[stacktop]=now;
	now=T[now].son[str[i]-'a'];
	//这里不需要for循环，因为题目保证了不会有字符串是其它的前缀
	if (T[now].end)
	    stacktop=stacktop-T[now].depth,now=Stacknow[stacktop+1];
    }
    for (int i=1;i<=stacktop;i++) printf("%c",Stack[i]);
    printf("\n");
    return;
}
