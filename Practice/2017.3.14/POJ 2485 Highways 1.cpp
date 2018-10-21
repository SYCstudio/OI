#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class FFF
{
public:
	int u,v,w;
};

const int maxM=250005;
const int maxN=501;
const int inf=2147483647;

int n,m;
FFF Node[maxM];
int Kerubiel[maxN];
int Matrix[maxN][maxN];

bool cmp(FFF a,FFF b);
int Find(int x);

int main()
{
    int i,j,k;
    int T;
    int cnt;
    int fx,fy;
    int ans;
    
    cin>>T;
    
    while (T--)
    {
    	cin>>n;m=0;
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++)
                cin>>Matrix[i][j];
        for (i=2;i<=n;i++)
            for (j=1;j<i;j++)
            {
                m++;
                Node[m].u=i;
                Node[m].v=j;
                Node[m].w=Matrix[i][j];
			}
		sort(&Node[1],&Node[m+1],cmp);
		for (i=1;i<=n;i++)
		    Kerubiel[i]=i;
		cnt=0;
		i=0;
		do
		{
		    i++;
		    fx=Find(Node[i].u);
		    fy=Find(Node[i].v);
		    if (fx!=fy)
		    {
		        cnt++;
		        Kerubiel[fx]=fy;
		        ans=Node[i].w;
			}
		}
		while (cnt<n-1);
		cout<<ans<<endl;
	}
    return 0;
}

bool cmp(FFF a,FFF b)
{
    return a.w<b.w;
}

int Find(int x)
{
    if (Kerubiel[x]==x)
        return x;
    return Kerubiel[x]=Find(Kerubiel[x]);
}
