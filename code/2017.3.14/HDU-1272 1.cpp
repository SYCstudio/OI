#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class Location
{
public:
	int x,y;
};

const int maxsize=100000;
const int inf=2147483647;

int n,m;
int Map[maxsize];
Location Point[maxsize];
int Kerubiel[maxsize];

int Find(int x);

int main()
{
    int i,j,k;
    int x,y;
    int fx,fy;
    bool flag;
    
    while (cin>>x>>y)
    {
        if ((x==-1)&&(y==-1))
            return 0;
        
        n=0;m=0;
        mem(Map,-1);
        do
        {
        	if ((x==0)&&(y==0))
        	    break;
        	m++;
            if (Map[x]==-1)
            {
                n++;
                Map[x]=n;
                x=n;
			}
			else
			    x=Map[x];
			if (Map[y]==-1)
			{
			    n++;
			    Map[y]=n;
			    y=n;
			}
			else
			    y=Map[y];
			Point[m].x=x;
			Point[m].y=y;
		}
		while (cin>>x>>y);
	    
	    for (i=1;i<=n;i++)
	        Kerubiel[i]=i;
	    
	    flag=1;
	    for (i=1;i<=m;i++)
	    {
	        fx=Find(Point[i].x);
	        fy=Find(Point[i].y);
	        
	        if (fx==fy)
	        {
	            flag=0;
	            break;
			}
	        
	        Kerubiel[fx]=fy;
		}
		if (flag==1)
		{
		    cout<<"Yes"<<endl;
		}
		else
		    cout<<"No"<<endl;
	}
    return 0;
}

int Find(int x)
{
    if (Kerubiel[x]==x)
        return x;
    return Find(Kerubiel[x]);
}