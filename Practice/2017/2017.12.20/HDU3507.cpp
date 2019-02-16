#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))
#define GetY(a,b) (F[a]+sqr(Sum[a])-F[b]-sqr(Sum[b]))
#define GetX(a,b) (2*(Sum[a]-Sum[b]))

const int maxN=500010;
const int inf=2147483647;

int n,m;
ll Sum[maxN];
ll F[maxN];
ll Q[maxN];

int read();

int main()
{
    while (scanf("%d%d",&n,&m)!=EOF)
    {
	Sum[0]=0;
	for (int i=1;i<=n;i++) Sum[i]=Sum[i-1]+(ll)(read());
	int h=1,t=0;
	Q[0]=0;
	Q[1]=0;
	for (int i=1;i<=n;i++)
	{
	    while ((t<h)&&(GetY(Q[t+1],Q[t])<=GetX(Q[t+1],Q[t])*Sum[i])) t++;//注意这里的等号
	    F[i]=F[Q[t]]+sqr(Sum[i]-Sum[Q[t]])+m;
	    //cout<<i<<" "<<Q[t]<<endl;
	    while ((t<h)&&(GetY(i,Q[h])*GetX(Q[h],Q[h-1])<=GetY(Q[h],Q[h-1])*GetX(i,Q[h]))) h--;//注意这里的等号
	    h++;Q[h]=i;
	}
	//for (int i=1;i<=n;i++) cout<<F[i]<<" ";
	//cout<<endl;
	printf("%lld\n",F[n]);
    }
    return 0;
}

int read()
{
    char ch=getchar();int k=1,x=0;
    while (((ch>'9')||(ch<'0'))&&(ch!='-')) ch=getchar();
    if (ch=='-')
    {
	k=-1;ch=getchar();
    }
    while ((ch>='0')&&(ch<='9'))
    {
	x=x*10+ch-48;ch=getchar();
    }
    return x*k;
}
