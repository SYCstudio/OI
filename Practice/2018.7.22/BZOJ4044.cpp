#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fail,len,fa;
	void clear(){
		fail=len=fa=0;mem(son,0);return;
	}
};

char str[maxN];
int nodecnt,last;
Node S[maxN];
int Pos[maxN],F[maxN];

void Insert(int pos,int c);

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		mem(str,-1);
		scanf("%s",str+1);
		int len=strlen(str+1);
		for (int i=1;i<=len;i++)
			if (str[i]=='A') str[i]=0;
			else if (str[i]=='T') str[i]=1;
			else if (str[i]=='G') str[i]=2;
			else str[i]=3;

		last=0;nodecnt=1;Pos[0]=Pos[1]=0;S[0].clear();S[1].clear();
		S[0].fail=S[1].fail=1;
		S[0].len=0;S[1].len=-1;
		for (int i=1;i<=len;i++) Insert(i,str[i]);

		for (int i=2;i<=nodecnt;i++) F[i]=S[i].len;

		int Ans=len;F[0]=1;
		for (int i=2;i<=nodecnt;i++)
			if ((S[i].len&1)==0)
			{
				int l=S[i].len/2,now=Pos[i];
				F[i]=S[i].len;
				F[i]=min(F[i],F[S[i].fa]+1);
				if (S[now].len>l) continue;
				F[i]=min(F[i],F[now]+l-S[now].len+1);
			}

		for (int i=2;i<=nodecnt;i++) Ans=min(Ans,len-S[i].len+F[i]);

		printf("%d\n",Ans);
	}
	return 0;
}

void Insert(int pos,int c)
{
	int p=last;
	while (str[pos-1-S[p].len]!=str[pos]) p=S[p].fail;
	if (S[p].son[c]==0)
	{
		int np=++nodecnt,q=S[p].fail;S[np].clear();Pos[np]=0;
		while (str[pos-1-S[q].len]!=str[pos]) q=S[q].fail;
		S[np].fail=S[q].son[c];
		S[p].son[c]=np;S[np].len=S[p].len+2;
		S[np].fa=p;
		if (S[np].len<=2){
			Pos[np]=S[np].fail;
		}
		else{
			int now=Pos[p];
			while ((str[pos-1-S[now].len]!=str[pos])||(S[now].len*2+4>S[np].len)) now=S[now].fail;
			Pos[np]=S[now].son[c];
		}
	}
	last=S[p].son[c];
	return;
}
