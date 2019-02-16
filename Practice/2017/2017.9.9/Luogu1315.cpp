#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=2000;
const int maxM=20000;
const int inf=2147483647;

int n,m,K;
int Dist[maxN];
int EndSum[maxN];//EndSum[i]表示在i号位置下车的人的数量
int Rangel[maxM];
int Ranger[maxM];
int PeopleTime[maxM];
int LastTime[maxN];//最后到达的人的时间
int LeaveTime[maxN];//离开的时间
int LastInfluence[maxN];

void init();

int main()
{
	memset(LastTime,0,sizeof(LastTime));
	memset(EndSum,0,sizeof(EndSum));
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<n;i++)
		scanf("%d",&Dist[i]);
	Dist[n]=0;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&PeopleTime[i],&Rangel[i],&Ranger[i]);
		EndSum[Ranger[i]]++;
		LastTime[Rangel[i]]=max(LastTime[Rangel[i]],PeopleTime[i]);
	}
	int Ans=0;
	for (int i=1;i<=n;i++)
		EndSum[i]+=EndSum[i-1];
	init();
	/*
	GetTime[1]=0;
	LeaveTime[1]=LastTime[1];
	for (int i=2;i<=n;i++)
	{
		GetTime[i]=LeaveTime[i-1]+Dist[i-1];
		LeaveTime[i]=max(GetTime[i],LastTime[i]);
	}
	//*/
	for (int i=1;i<=m;i++)
		Ans+=LeaveTime[Ranger[i]]-PeopleTime[i];
	/*
	cout<<Ans<<endl;
	for (int i=1;i<=n;i++)
		cout<<LeaveTime[i]<<" ";
	cout<<endl;
	for (int i=1;i<=n;i++)
		cout<<GetTime[i]<<" ";
	cout<<endl;
	for (int i=1;i<=n;i++)
		cout<<LastTime[i]<<" ";
	cout<<endl;
	//*/
	while (K--)
	{
		LastInfluence[n]=LastInfluence[n-1]=n;
		for (int i=n-2;i>=1;i--)
			LastInfluence[i]=(LeaveTime[i+1]<LastTime[i+1])?i+1:LastInfluence[i+1];
		int nowmax=0,id;
		/*
		for (int i=1;i<=n;i++)
			cout<<LastInfluence[i]<<" ";
		cout<<endl;
		for (int i=1;i<=n;i++)
			cout<<EndSum[i]<<" ";
		cout<<endl;
		//*/
		for (int i=1;i<n;i++)
			if ((EndSum[LastInfluence[i]]-EndSum[i]>nowmax)&&(Dist[i]!=0))
			{
				nowmax=EndSum[LastInfluence[i]]-EndSum[i];
				id=i;
			}
		Dist[id]--;
		Ans-=nowmax;
		init();
		/*
		for (int i=2;i<=n;i++)
			LeaveTime[i]=max(LeaveTime[i-1],GetTime[i-1])+Dist[i-1];
		//*/
	}
	printf("%d\n",Ans);
	return 0;
}

void init()
{
	LeaveTime[1]=LastTime[1];
	for (int i=2;i<=n;i++)
		LeaveTime[i]=max(LastTime[i-1],LeaveTime[i-1])+Dist[i-1];
	return;
}
