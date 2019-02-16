#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500005;
const int maxBit=18;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fail,len;
};

char Input[maxN];
int nodecnt,last;
Node S[maxN];
int Fa[maxBit][maxN];

void Insert(int pos,int c);

int main()
{
	int len;scanf("%d",&len);
	scanf("%s",Input+1);

	last=0;nodecnt=1;
	S[1].fail=S[0].fail=1;S[0].len=0;S[1].len=-1;
	for (int i=1;i<=len;i++) Insert(i,Input[i]-'a');

	for (int i=0;i<=nodecnt;i++) if (i!=1) Fa[0][i]=S[i].fail;
	for (int i=1;i<maxBit;i++)
		for (int j=0;j<=nodecnt;j++)
			Fa[i][j]=Fa[i-1][Fa[i-1][j]];

	int Ans=0;
	for (int i=1;i<=nodecnt;i++)
		if ((S[i].len>=4)&&(S[i].len%4==0))
		{
			int u=i;
			for (int j=maxBit-1;j>=0;j--) if ((Fa[j][u])&&(S[Fa[j][u]].len>=S[i].len/2)) u=Fa[j][u];
			//cout<<i<<" ["<<S[i].len<<"] "<<u<<" ["<<S[u].len<<"]"<<endl;
			if ((S[u].len%2==0)&&(S[u].len==S[i].len/2)) Ans=max(Ans,S[i].len);
		}

	printf("%d\n",Ans);
	return 0;
}

void Insert(int pos,int c){
	int p=last;
	while (Input[pos-1-S[p].len]!=Input[pos]) p=S[p].fail;
	if (S[p].son[c]==0)
	{
		int np=++nodecnt,q=S[p].fail;
		while (Input[pos-1-S[q].len]!=Input[pos]) q=S[q].fail;
		S[np].fail=S[q].son[c];S[np].len=S[p].len+2;S[p].son[c]=np;
	}
	last=S[p].son[c];
	//cout<<"["<<last<<","<<S[last].len<<","<<S[last].fail<<"] ";
	return;
}
