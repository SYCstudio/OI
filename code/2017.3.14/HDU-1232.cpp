#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxsize=1001;
const int inf=2147483647;

int n,m;
int Kerubiel[maxsize];

int Find(int x);
void Merge(int x,int y);

int main()
{
    int i,j,k;
    int x,y;
    int cnt;
    
    while (cin>>n>>m)
    {
    	if (n==0)
    	    return 0;
        for (i=1;i<=n;i++)
            Kerubiel[i]=i;
        
        for (i=1;i<=m;i++)
        {
            cin>>x>>y;
            Merge(x,y);
		}
		
		cnt=-1;
		
		for (i=1;i<=n;i++)
		    if (Kerubiel[i]==i)
		        cnt++;
		
		cout<<cnt<<endl;
	}
    
    
    return 0;
}

int Find(int x)
{
    if (Kerubiel[x]==x)
        return x;
    return Find(Kerubiel[x]);
}

void Merge(int x,int y)
{
    int fx,fy;
    fx=Find(x);
    fy=Find(y);
    if (fx!=fy)
    {
        Kerubiel[fx]=fy;
	}
	return;
}
