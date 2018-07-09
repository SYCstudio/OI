#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=100005;
const int blocksize=320;
const int inf=2147483647;

class Option
{
public:
	int opt;
	int l,r,c,p;
};

int n,m;
int Val[maxN];
int L[maxN],R[maxN],Belong[maxN];
int numcnt,Num[maxN*4],Cnt[blocksize][maxN];
Option O[maxN];

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]),Num[++numcnt]=Val[i];
	for (int i=1;i<=m;i++)
	{
		char ch;scanf(" %c",&ch);
		if (ch=='Q'){
			O[i].opt=1;
			scanf("%d%d%d",&O[i].l,&O[i].r,&O[i].c);
			Num[++numcnt]=O[i].c;
		}
		if (ch=='C'){
			O[i].opt=2;
			scanf("%d%d",&O[i].p,&O[i].c);
			Num[++numcnt]=O[i].c;
		}
	}

	sort(&Num[1],&Num[numcnt+1]);numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;

	for (int i=1;i<=n;i++)
	{
		Belong[i]=i/blocksize+1;
		if (L[Belong[i]]==0) L[Belong[i]]=i;
		R[Belong[i]]=i;
	}

	for (int i=1;i<=n;i++) Cnt[Belong[i]][Val[i]=Find(Val[i])]++;

	for (int i=1;i<=m;i++)
	{
		if (O[i].opt==1)
		{
			int c=Find(O[i].c),Ans=0;
			if (Belong[O[i].l]==Belong[O[i].r]){
				for (int j=O[i].l;j<=O[i].r;j++) if (Val[j]==c) Ans++;
			}
			else{
				for (int j=Belong[O[i].l]+1;j<=Belong[O[i].r]-1;j++) Ans+=Cnt[j][c];
				for (int j=O[i].l;j<=R[Belong[O[i].l]];j++) if (Val[j]==c) Ans++;
				for (int j=L[Belong[O[i].r]];j<=O[i].r;j++) if (Val[j]==c) Ans++;
			}
			printf("%d\n",Ans);
		}
		if (O[i].opt==2)
		{
			int c=Find(O[i].c);
			Cnt[Belong[O[i].p]][Val[O[i].p]]--;
			Cnt[Belong[O[i].p]][Val[O[i].p]=c]++;
		}
	}
	return 0;
}
