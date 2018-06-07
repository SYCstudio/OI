#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

const int maxsize=50001;
const int inf=2147483647;

int n,m;
int Mayuri[maxsize*3];

int Find(int x);
bool Same(int x,int y);
void Union(int x,int y);

int main()
{
    int Ans=0;

    cin>>n>>m;

    for (int i=1;i<=n*3;i++)
        Mayuri[i]=i;

    for (int i=1;i<=m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        if ((b>n)||(c>n))
        {
            Ans++;
            //cout<<1<<' '<<i<<endl;
            continue;
        }
        if (a==1)
        {
            if (Same(b,c+n)||(Same(b,c+n*2)))
            {
                Ans++;
                //cout<<2<<' '<<i<<endl;
                continue;
            }
            else
            {
                Union(b,c);
                Union(b+n,c+n);
                Union(b+n*2,c+n*2);
            }
        }
        else
        {
            if ((Same(b,c+2*n))||(Same(b,c)))
            {
                Ans++;
                //cout<<3<<' '<<i<<endl;
                continue;
            }
            else
            {
                Union(b,c+n);
                Union(b+n,c+n*2);
                Union(b+n*2,c);
            }
        }
    }
    cout<<Ans<<endl;
    return 0;
}

int Find(int x)
{
    return Mayuri[x]==x ? x : Mayuri[x]=Find(Mayuri[x]);
}

bool Same(int x,int y)
{
    return Find(x)==Find(y);
}

void Union(int x,int y)
{
    int fx=Find(x);
    int fy=Find(y);
    if (fx!=fy)
    {
        Mayuri[fy]=fx;
    }
    return;
}
