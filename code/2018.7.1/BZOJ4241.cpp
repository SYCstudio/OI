#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxB=410;
const int inf=2147483647;

int n,Q;
int Val[maxN];
int numcnt,Num[maxN];
ll Ans[maxB][maxB];
int Cnt[maxB][maxN];
int Belong[maxN],BL[maxN],BR[maxN];
int S[maxN],Tot[maxN];

int main()
{
	scanf("%d%d",&n,&Q);int size=max(1,(int)sqrt(n));
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]),Num[++numcnt]=Val[i];
	sort(&Num[1],&Num[n+1]);numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;

	for (int i=1;i<=n;i++) Val[i]=lower_bound(&Num[1],&Num[numcnt+1],Val[i])-Num;

	for (int i=1;i<=n;i++)
	{
		Belong[i]=i/size+1;
		if (BL[Belong[i]]==0) BL[Belong[i]]=i;
		BR[Belong[i]]=i;
	}

	int sizetop=n/size+1;

	for (int i=1;i<=n;i++) Cnt[Belong[i]][Val[i]]++;
	for (int i=1;i<=sizetop;i++) for (int j=1;j<=numcnt;j++) Cnt[i][j]+=Cnt[i-1][j];

	for (int i=1;i<=sizetop;i++)
	{
		ll nowans=0;int top=0;
		for (int j=BL[i];j<=n;j++)
		{
			if (Tot[Val[j]]==0) S[++top]=Val[j];
			Tot[Val[j]]++;
			nowans=max(nowans,1ll*Tot[Val[j]]*Num[Val[j]]);
			Ans[i][Belong[j]]=max(Ans[i][Belong[j]],nowans);
		}
		while (top) Tot[S[top--]]=0;
	}

	/*
	cout<<"size:"<<size<<endl;
	//for (int i=1;i<=n;i++) cout<<Belong[i]<<" ";cout<<endl;
	for (int i=1;i<=sizetop;i++)
	{
		for (int j=i;j<=sizetop;j++)
			cout<<Ans[i][j]<<" ";
		cout<<endl;
	}
	for (int i=1;i<=sizetop;i++) cout<<BL[i]<<" ";cout<<endl;
	for (int i=1;i<=sizetop;i++) cout<<BR[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<Belong[i]<<" ";cout<<endl;
	//*/

	while (Q--)
	{
		int l,r;scanf("%d%d",&l,&r);
		//cout<<"("<<Belong[l]<<","<<Belong[r]<<")"<<endl;
		if (Belong[l]==Belong[r])
		{
			//cout<<"cas1"<<endl;
			int top=0;ll nowans=0;
			for (int i=l;i<=r;i++)
			{
				if (Tot[Val[i]]==0) S[++top]=Val[i];
				Tot[Val[i]]++;
				nowans=max(nowans,1ll*Tot[Val[i]]*Num[Val[i]]);
			}
			while (top) Tot[S[top--]]=0;
			printf("%lld\n",nowans);
		}
		else
		{
			//cout<<"cas2"<<" "<<Ans[Belong[l]+1][Belong[r]-1]<<endl;
			ll nowans=Ans[Belong[l]+1][Belong[r]-1];
			int top=0;
			for (int i=l;i<=BR[Belong[l]];i++) if (Tot[Val[i]]==0) S[++top]=Val[i],Tot[Val[i]]=Cnt[Belong[r]-1][Val[i]]-Cnt[Belong[l]][Val[i]];
			for (int i=BL[Belong[r]];i<=r;i++) if (Tot[Val[i]]==0) S[++top]=Val[i],Tot[Val[i]]=Cnt[Belong[r]-1][Val[i]]-Cnt[Belong[l]][Val[i]];
			for (int i=l;i<=BR[Belong[l]];i++) Tot[Val[i]]++;
			for (int i=BL[Belong[r]];i<=r;i++) Tot[Val[i]]++;
			//for (int i=1;i<=top;i++) cout<<S[i]<<" ";cout<<endl;
			//for (int i=1;i<=top;i++) cout<<Tot[S[i]]<<" ";cout<<endl;
			//for (int i=1;i<=top;i++) cout<<Num[S[i]]<<" ";cout<<endl;
			while (top){
				nowans=max(nowans,1ll*Tot[S[top]]*Num[S[top]]);
				Tot[S[top--]]=0;
			}
			printf("%lld\n",nowans);
		}
	}
	return 0;
}
