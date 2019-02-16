#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001000;
const int maxAlpha=11;
const int Mod=1e9+7;
const int inf=2147483647;

class SAM
{
public:
	int ch[maxAlpha];
	int fa,len;
};

int n;
char str[maxN];
int root=1,last=1,nodecnt=1;
SAM S[maxN<<1];
ll F[maxN<<1],Cnt[maxN<<1];
int Queue[maxN<<1],Degree[maxN<<1];

void Insert(int key);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		int l=strlen(str+1);
		for (int j=1;j<=l;j++) Insert(str[j]-'0');
		if (i!=n) Insert(10);
	}

	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S[i].ch[j])
				cout<<i<<"->"<<S[i].ch[j]<<" "<<(char)(j+'0')<<endl;
	//*/

	F[1]=0;Cnt[1]=1;
	for (int i=1;i<=nodecnt;i++) for (int j=0;j<maxAlpha;j++) if (S[i].ch[j]) Degree[S[i].ch[j]]++;
	int h=1,t=0;Queue[1]=1;
	do
	{
		int u=Queue[++t];
		//cout<<u<<" ";
		for (int i=0;i<maxAlpha;i++)
			if (S[u].ch[i])
			{
				Degree[S[u].ch[i]]--;
				if (Degree[S[u].ch[i]]==0) Queue[++h]=S[u].ch[i];
				if (i==maxAlpha-1) continue;
				F[S[u].ch[i]]=(F[S[u].ch[i]]+(F[u]*(ll)10%Mod+(ll)i*Cnt[u]%Mod)%Mod)%Mod;
				Cnt[S[u].ch[i]]=(Cnt[S[u].ch[i]]+Cnt[u])%Mod;
			}
	}
	while (t!=h);
	//cout<<endl;
	ll Ans=0;
	//for (int i=1;i<=nodecnt;i++) cout<<F[i]<<" "<<Cnt[i]<<endl;
	for (int i=1;i<=nodecnt;i++) Ans=(Ans+F[i])%Mod;
	printf("%lld\n",Ans);
	return 0;
}

void Insert(int key)
{
	//cout<<"Insert:"<<key<<endl;
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;
	while ((p!=0)&&(S[p].ch[key]==0)) S[p].ch[key]=np,p=S[p].fa;
	if (p==0) S[np].fa=root;
	else
	{
		int q=S[p].ch[key];
		if (S[p].len+1==S[q].len) S[np].fa=q;
		else
		{
			int nq=++nodecnt;
			S[nq]=S[q];S[nq].len=S[p].len+1;
			S[q].fa=S[np].fa=nq;
			while ((p!=0)&&(S[p].ch[key]==q)) S[p].ch[key]=nq,p=S[p].fa;
		}
	}
	return;
}
