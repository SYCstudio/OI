#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=100;
const int inf=147483647;

int n;
int M[maxN][maxN];
int Dist[maxN];
bool solve[maxN];

int read();

int main()
{
	int T;
	cin>>T;
	for (int ti=1;ti<=T;ti++)
	{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		M[i][i]=0;
		for (int j=1;j<i;j++)
		{
			M[i][j]=M[j][i]=read();
		}
	}
	/*for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		    cout<<M[i][j]<<' ';
		cout<<endl;
	}*/
	for (int i=1;i<=n;i++)
	    Dist[i]=M[1][i];
	memset(solve,0,sizeof(solve));
	for (int i=1;i<n;i++)
	{
		int id,mi=inf;
		for (int j=1;j<=n;j++)
		    if ((solve[j]==0)&&(Dist[j]<mi))
		    {
		    	mi=Dist[j];
		    	id=j;
			}
		solve[id]=1;
		for (int j=1;j<=n;j++)
		    if ((solve[j]==0)&&(Dist[id]+M[id][j]<Dist[j]))
		    {
		    	Dist[j]=Dist[id]+M[id][j];
			}
	}
	int Ans=0;
	for (int i=1;i<=n;i++)
	    Ans=max(Ans,Dist[i]);
	cout<<Ans<<endl;
	if (ti!=T)
	    cout<<endl;
}
	return 0;
}

int read()
{
	int x=0;
	int k=1;
	char ch=getchar();
	while (((ch>'9')||(ch<'0'))&&(ch!='-')&&(ch!='x'))
	    ch=getchar();
	if (ch=='x')
	    return inf;
	if (ch=='-')
	{
		k=-1;
		ch=getchar();
	}
	while ((ch>='0')&&(ch<='9'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*k;
}
