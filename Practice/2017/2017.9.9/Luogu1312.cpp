#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
 
const int maxN=9;
const int N=7;
const int M=5;
const int inf=2147483647;
 
int Step;
int Mat[maxN][maxN];
int Outp[15][5];
//int Ans[10][maxN][maxN];
 
void dfs(int step);
void Clear();
void OutpMat();
 
int main()
{
   	memset(Mat,0,sizeof(Mat));	
   	scanf("%d",&Step);
   	for (int i=1;i<=5;i++)
   	{
   		int j=1;
   		int x;
   		while ((scanf("%d",&x)!=EOF)&&(x!=0))
   		{
   			Mat[j][i]=x;
   			j++;
   		}
   	}
   	//OutpMat();
   	dfs(1);
   	cout<<-1<<endl;
   	//*/
   	/*
   	for (int i=1;i<=7;i++)
   		for (int j=1;j<=5;j++)
   			scanf("%d",&Mat[i][j]);
   	OutpMat();
   	Clear();
   	//*/
   	return 0;
}
    
void dfs(int step)
{
   	if (step==Step+1)
   	{
		//cout<<"step!"<<endl;
   		Clear();
   		for (int i=1;i<=7;i++)
   			for (int j=1;j<=5;j++)
   				if (Mat[i][j]!=0)
   					return;
   		for (int i=1;i<=Step;i++)
		{
   			printf("%d %d %d\n",Outp[i][1]-1,Outp[i][2]-1,Outp[i][3]);
			/*
			for (int j=1;j<=7;j++)
			{
				for (int k=1;k<=5;k++)
					cout<<Ans[i][j][k]<<" ";
				cout<<endl;
			}
			cout<<endl;
			//*/
		}
   		exit(0);
   	}
   	int nowMat[maxN][maxN];
	int Colorcnt[11];
	memset(Colorcnt,0,sizeof(Colorcnt));
	for (int i=1;i<=7;i++)
		for (int j=1;j<=5;j++)
			Colorcnt[Mat[i][j]]++;
	for (int i=1;i<=10;i++)
		if ((Colorcnt[i]==1)||(Colorcnt[i]==2))
			return;
   	memcpy(nowMat,Mat,sizeof(Mat));
   	for (int j=1;j<=5;j++)
   		for (int i=1;i<=7;i++)
   			if (nowMat[i][j]!=0)
   			{
				//cout<<"Yes"<<endl;
   				if ((j!=5)&&(nowMat[i][j]!=nowMat[i][j+1]))
   				{
   					memcpy(Mat,nowMat,sizeof(Mat));
					//cout<<"Swap "<<i<<" "<<j<<endl;
					//OutpMat();
   					swap(Mat[i][j],Mat[i][j+1]);
   					//cout<<"A "<<step<<" "<<i<<" "<<j<<endl;
   					Clear();
					//OutpMat();
					//cout<<"------------------------"<<endl;
   					Outp[step][1]=j;
   					Outp[step][2]=i;
   					Outp[step][3]=1;
					//memcpy(Ans[step],Mat,sizeof(Mat));
   					//getchar();
   					dfs(step+1);
   				}
   				if ((j!=1)&&(nowMat[i][j-1]==0)&&(nowMat[i][j]!=nowMat[i][j-1]))
   				{
   					memcpy(Mat,nowMat,sizeof(Mat));
					//cout<<"swap2 "<<i<<" "<<j<<endl;
					//OutpMat();
   					swap(Mat[i][j],Mat[i][j-1]);
   					//cout<<"B "<<step<<" "<<i<<" "<<j<<endl;
   					Clear();
					//OutpMat();
					//cout<<"-----------------------"<<endl;
   					Outp[step][1]=j;
   					Outp[step][2]=i;
   					Outp[step][3]=-1;
				    //memcpy(Ans[step],Mat,sizeof(Mat));
   					//getchar();
   					dfs(step+1);
   				}
   			}
	return;
}

void Clear()
{
    bool cls[maxN][maxN];
   	//cout<<"------------------------------"<<endl;
   	//OutpMat();
   	while (1)
   	{
   		for (int i=2;i<=7;i++)
   			for (int j=1;j<=5;j++)
   				if ((Mat[i][j]!=0)&&(Mat[i-1][j]==0))
   				{
					int k=i;
					//cout<<"("<<i<<","<<j<<")"<<endl;
					//OutpMat();
					while ((k>=2)&&(Mat[k][j]!=0)&&(Mat[k-1][j]==0))
					{
						//cout<<k<<" "<<j<<" "<<Mat[k-1][j]<<" "<<Mat[k][j]<<endl;
						Mat[k-1][j]=Mat[k][j];
						Mat[k][j]=0;
						k--;
					}
					//cout<<"("<<i<<","<<j<<")"<<endl;
					//OutpMat();
   				}
   		//OutpMat();
   		memset(cls,0,sizeof(cls));
   		bool is_cls=0;
   		for (int i=1;i<=7;i++)
   			for (int j=1;j<=5;j++)
   			{
   				if ((Mat[i][j]!=0)&&(Mat[i][j]==Mat[i][j-1])&&(Mat[i][j]==Mat[i][j+1]))
   				{
   					is_cls=1;
   					cls[i][j]=cls[i][j-1]=cls[i][j+1]=1;
   				}
   				if ((Mat[i][j]!=0)&&(Mat[i][j]==Mat[i+1][j])&&(Mat[i][j]==Mat[i-1][j]))
   				{
   					is_cls=1;
   					cls[i][j]=cls[i+1][j]=cls[i-1][j]=1;
   				}
   			}
   		if (is_cls==0)
   			break;
   		for (int i=1;i<=7;i++)
   			for (int j=1;j<=5;j++)
   				if (cls[i][j]==1)
   					Mat[i][j]=0;
   	}
   	//OutpMat();
   	//cout<<"------------------------------"<<endl;
}
    
void OutpMat()
{
   	for (int i=1;i<=7;i++)
   	{
   		for (int j=1;j<=5;j++)
   			cout<<Mat[i][j]<<" ";
   		cout<<endl;
   	}
   	cout<<endl;
   	return;
}
