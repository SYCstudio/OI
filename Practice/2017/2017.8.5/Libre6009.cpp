#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=300;
const int maxM=maxN*maxN*2;
const int inf=2147483647;

int n,m;
unsigned int B1[maxN];
unsigned int B2[maxN];
unsigned int F1[maxN];
unsigned int F2[maxN];
int Cost[maxN];
int Q[(1<<25)];
int Dist[(1<<25)];
bool inqueue[(1<<25)];

void Add_Edge(int u,int v,int cost);
void Outp(int x)
{
	if (x!=0)
		Outp(x/2);
	cout<<x%2;
}

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		char str[maxN];
		scanf("%d%s",&Cost[i],str);
		for (int j=0;j<n;j++)
			if (str[j]=='+')
				B1[i]=B1[i]|(1<<(j));
			else
				if (str[j]=='-')
					B2[i]=B2[i]|(1<<j);
		scanf("%s",str);
		for (int j=0;j<n;j++)
			if (str[j]=='+')
				F1[i]=F1[i]|(1<<j);
			else
				if (str[j]=='-')
					F2[i]=F2[i]|(1<<j);
		/*Outp(B1[i]);
		cout<<" ";
		Outp(B2[i]);
		cout<<" ";
		Outp(F1[i]);
		cout<<" ";
		Outp(F2[i]);
		cout<<endl;
		*/
	}
	for (int i=0;i<=(1<<n)-1;i++)
		Dist[i]=inf;
	int h=1,t=0;
	Q[1]=(1<<n)-1;
	Dist[(1<<n)-1]=0;
	inqueue[(1<<n)-1]=1;
	do
	{
		t++;
		int u=Q[t];
		//Outp(u);
		//cout<<endl;
		inqueue[u]=0;
		for (int i=1;i<=m;i++)
		{
			unsigned int now=u;
			if (((now&B1[i])==B1[i]) && (((~now)&B2[i])==B2[i]))
			{
				//cout<<"in!"<<i<<endl;
				now=now&(~F2[i]);
				//cout<<"~F: "<<(~F1[i])<<" ";
				//Outp(~F1[i]);
				//cout<<endl;
				now=now|F1[i];
				//Outp(now);
				//cout<<endl;
				if (Dist[now]>Dist[u]+Cost[i])
				{
					Dist[now]=Dist[u]+Cost[i];
					if (inqueue[now]==0)
					{
						h++;
						Q[h]=now;
						inqueue[now]=1;
					}
				}
			}
		}
	}
	while (h!=t);
	if (Dist[0]==inf)
		cout<<0<<endl;
	else
		cout<<Dist[0]<<endl;
	return 0;
}
