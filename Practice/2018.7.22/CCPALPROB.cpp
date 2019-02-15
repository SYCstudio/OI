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
const int maxBit=16;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fail,len;
	ll cnt,num;
};

char str[maxN];
int last,nodecnt;
Node S[maxN];
int Fa[maxBit][maxN];

void Insert(int pos,int c);

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		scanf("%s",str+1);
		int len=strlen(str+1);
		last=0;nodecnt=1;mem(S,0);
		S[1].fail=S[0].fail=1;
		S[1].len=-1;S[0].len=0;
		for (int i=1;i<=len;i++){
			Insert(i,str[i]-'a');
			//cout<<last<<" ";
		}
		//cout<<endl;

		for (int i=2;i<=nodecnt;i++) Fa[0][i]=S[i].fail;
		for (int i=nodecnt;i>=2;i--) S[S[i].fail].cnt+=S[i].cnt;

		for (int i=1;i<maxBit;i++)
			for (int j=2;j<=nodecnt;j++)
				Fa[i][j]=Fa[i-1][Fa[i-1][j]];

		ll Ans=0;
		for (int i=2;i<=nodecnt;i++)
			if (S[i].len==1)
			{
				S[i].num=1;
				Ans+=1ll*S[i].cnt;
			}
			else
			{
				int l=S[i].len/2,now=i;
				for (int j=maxBit-1;j>=0;j--) if ((Fa[j][now])&&(S[Fa[j][now]].len>=l)) now=Fa[j][now];
				if (S[now].len==l) S[i].num=S[now].num+1;
				else S[i].num=1;
				Ans+=1ll*S[i].num*S[i].cnt;
			}

		//for (int i=1;i<=nodecnt;i++) cout<<S[i].len<<" ";cout<<endl;
		//for (int i=1;i<=nodecnt;i++) cout<<S[i].cnt<<" ";cout<<endl;
		//for (int i=1;i<=nodecnt;i++) cout<<S[i].num<<" ";cout<<endl;

		printf("%lld\n",Ans);
	}

	return 0;
}

void Insert(int pos,int c)
{
	int p=last;
	while (str[pos-1-S[p].len]!=str[pos]) p=S[p].fail;
	if (S[p].son[c]==0)
	{
		int np=++nodecnt,q=S[p].fail;
		while (str[pos-1-S[q].len]!=str[pos]) q=S[q].fail;
		S[np].len=S[p].len+2;S[np].fail=S[q].son[c];
		S[p].son[c]=np;
	}
	last=S[p].son[c];
	S[last].cnt++;
	return;
}
/*
2
zxqfd
aba
//*/
