#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2000010;
const int Mod=51123987;
const int inf=2147483647;

class Node
{
public:
	int fail,len,depth;
};

int n;
char str[maxN];
int C1[maxN],C2[maxN];
int last,nodecnt;
Node S[maxN];
int edgecnt,Head[maxN],Next[maxN],V[maxN],Ch[maxN];

void Insert(int pos,int c);

int main()
{
	scanf("%d",&n);
	scanf("%s",str+1);

	last=0;nodecnt=1;mem(Head,-1);edgecnt=0;
	S[1].fail=S[0].fail=1;
	S[0].len=0;S[1].len=-1;
	S[0].depth=S[1].depth=0;
	for (int i=1;i<=n;i++){
		Insert(i,str[i]-'a');
		C1[i]=S[last].depth;
	}

	reverse(&str[1],&str[n+1]);
	mem(S,0);
	last=0;nodecnt=1;mem(Head,-1);edgecnt=0;
	S[1].fail=S[0].fail=1;
	S[0].len=0;S[1].len=-1;
	S[0].depth=S[1].depth=0;
	for (int i=1;i<=n;i++){
		Insert(i,str[i]-'a');
		C2[i]=S[last].depth;
	}
	reverse(&C2[1],&C2[n+1]);

	//for (int i=1;i<=n;i++) cout<<C1[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<C2[i]<<" ";cout<<endl;

	ll Ans=0;
	for (int i=1;i<=n;i++) Ans=(Ans+C1[i])%Mod;
	Ans=1ll*Ans*(Ans-1)/2%Mod;

	for (int i=1;i<=n;i++) C1[i]=(C1[i]+C1[i-1])%Mod;
	for (int i=1;i<n;i++) Ans=(Ans-1ll*C1[i]*C2[i+1]%Mod+Mod)%Mod;

	printf("%lld\n",Ans);

	return 0;
}

void Insert(int pos,int c)
{
	int p=last;
	while (str[pos-1-S[p].len]!=str[pos]) p=S[p].fail;
	bool flag=0;
	for (int i=Head[p];i!=-1;i=Next[i])
		if (Ch[i]==c){
			flag=1;break;
		}
	if (flag==0)
	{
		int np=++nodecnt,q=S[p].fail;
		while (str[pos-1-S[q].len]!=str[pos]) q=S[q].fail;
		S[np].len=S[p].len+2;
		S[np].depth=1;S[np].fail=0;
		for (int i=Head[q];i!=-1;i=Next[i])
			if (Ch[i]==c){
				S[np].depth=S[V[i]].depth+1;
				S[np].fail=V[i];
			}
		Next[++edgecnt]=Head[p];Head[p]=edgecnt;V[edgecnt]=np;Ch[edgecnt]=c;
	}
	for (int i=Head[p];i!=-1;i=Next[i])
		if (Ch[i]==c){
			last=V[i];break;
		}
	return;
}
