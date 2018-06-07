#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=200101;
const int maxColor=60;
const int inf=2147483647;

int n,K,P;
int F1[maxColor];
int F2[maxColor];

int main()
{
	memset(F1,0,sizeof(F1));
	memset(F2,0,sizeof(F2));
	int Ans=0;
	scanf("%d%d%d",&n,&K,&P);
	for (int i=1;i<=n;i++)
	{
		int col,val;
		scanf("%d%d",&col,&val);
		col++;
		if (val<=P)
		{
			for (int j=1;j<=K;j++)
			{
				F1[j]=F1[j]+F2[j];
				F2[j]=0;
			}
			
			//cout<<"cas1"<<endl;
			Ans=Ans+F1[col];
			F1[col]++;
		}
		else
		{
			//cout<<"cas2"<<endl;
			//cout<<Ans<<" "<<F1[col]<<endl;
			Ans=Ans+F1[col];
			//cout<<Ans<<endl;
			F2[col]++;
		}
		/*
		for (int i=1;i<=K;i++)
			printf("%d,%d ",F1[i],F2[i]);
		cout<<endl;
		cout<<Ans<<endl<<endl;
		//*/
	}
	printf("%d\n",Ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
