#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=111;
const int maxTwo=11;
const int inf=2147483647;

int n,m;
int Bycnt;
int Binary[70];
int Cnt[70];
int Map[maxN];
int F[2][1<<maxTwo][1<<maxTwo];
char str[20];

void Two(int x);

int main()
{
	scanf("%d%d",&n,&m);
	Bycnt=1;
	Binary[1]=0;
	Cnt[1]=0;
	for (int i=1;i<=(1<<(m+1))-1;i++)
		if ((i&1)||((i<<1)&i)||((i<<2)&i)||((i>>1)&i)||((i>>2)&i))
			continue;
		else
		{
			Bycnt++;
			Binary[Bycnt]=i;
			Cnt[Bycnt]=0;
			int x=i;
			while (x)
			{
				x-=(x)&(-x);
				Cnt[Bycnt]++;
			}
			//cout<<Cnt[Bycnt]<<" ";
			//Two(i);
			//cout<<endl;
		}
	//cout<<Bycnt<<endl;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		for (int j=1;j<=m;j++)
			if (str[j]=='H')
				Map[i]=Map[i]|(1<<(m-j+1));
		//Two(Map[i]);
	}
	//cout<<endl;
	int now=1;
	for (int i=1;i<=Bycnt;i++)
		if ((Binary[i]&Map[1])==0)
			for (int j=1;j<=Bycnt;j++)
				if (((Binary[i]&Binary[j])==0)&&((Binary[j]&Map[2])==0))
				{
					F[0][j][i]=Cnt[i]+Cnt[j];
					/*
					Two(Binary[i]);
					Two(Binary[j]);
					cout<<F[0][i][j]<<endl;
					//*/
				}
	/*
	for (int i=1;i<=Bycnt;i++)
		for (int j=1;j<=Bycnt;j++)
		{
			Two(Binary[i]);
			Two(Binary[j]);
			cout<<(((Binary[i]&Map[1])==0)&&(((Binary[i]&Binary[j])==0)&&((Binary[j]&Map[2])==0)))<<" "<<F[0][i][j]<<endl;
		}
	//*/
	int Ans=0;
	for (int i=3;i<=n;i++)
	{
		memset(F[now],0,sizeof(F[now]));
		for (int S1=1;S1<=Bycnt;S1++)
			if ((Binary[S1]&Map[i])==0)
				for (int j=1;j<=Bycnt;j++)
					if (((Binary[S1]&Binary[j])==0)&&((Binary[j]&Map[i-1])==0))
					{
						for (int k=1;k<=Bycnt;k++)
							if (((Binary[S1]&Binary[k])==0)&&((Binary[j]&Binary[k])==0)&&((Binary[k]&Map[i-2])==0))
								F[now][S1][j]=max(F[now][S1][j],F[now^1][j][k]+Cnt[S1]);
						//Two(Binary[j]);
						//Two(Binary[S1]);
						//cout<<F[now][S1][j]<<endl;
						Ans=max(Ans,F[now][S1][j]);
					}
		now=now^1;
	}
	printf("%d\n",Ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}

void Two(int x)
{
	int x2=x;
	int cnt=0;
	for (int i=m;i>=1;i--)
		if (x&(1<<i))
			cout<<1;
		else
			cout<<0;
	cout<<endl;
	return;
}
