#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1000005;
const int maxAlpha=26;
const int Mod=19930726;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fail,len,cnt;
};

int n;
ll K;
char str[maxN];
int last,nodecnt;
Node S[maxN];

void Insert(int pos,int c);
ll Calc(int limit);
ll QPow(ll x,ll cnt);

int main()
{
	scanf("%d%lld",&n,&K);
	scanf("%s",str+1);

	last=0;nodecnt=1;
	S[0].fail=S[1].fail=1;S[0].len=0;S[1].len=-1;
	for (int i=1;i<=n;i++) Insert(i,str[i]-'a');
	//cout<<endl;
	for (int i=nodecnt;i>=0;i--) if (i!=1) S[S[i].fail].cnt+=S[i].cnt;

	int L=0,R=0;
	for (int i=2;i<=nodecnt;i++) R=max(R,S[i].len);

	int tot=-1;
	do
	{
		int mid=(L+R)>>1;
		if (Calc(mid)>=K) tot=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);

	if (tot==-1) printf("-1\n");
	else
	{
		ll cnt=0,Ans=1;
		for (int i=2;i<=nodecnt;i++)
			if ((S[i].len&1)&&(S[i].len>tot)) Ans=1ll*Ans*QPow(S[i].len,S[i].cnt)%Mod,cnt+=S[i].cnt;
		Ans=1ll*Ans*QPow(tot,K-cnt)%Mod;

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
		S[np].len=S[p].len+2;S[np].fail=S[q].son[c];S[p].son[c]=np;
	}
	last=S[p].son[c];
	S[last].cnt++;
	//cout<<S[last].len<<" ";
	return;
}

ll Calc(int limit)
{
	ll ret=0;
	for (int i=2;i<=nodecnt;i++)
		if ((S[i].len&1)&&(S[i].len>=limit)) ret+=S[i].cnt;
	return ret;
}

ll QPow(ll x,ll cnt){
	ll ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}
