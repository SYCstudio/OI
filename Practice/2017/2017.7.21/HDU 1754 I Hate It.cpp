#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=2000001;
const int inf=2147483647;

class SegmentTree
{
public:
    int maxnum;
};

int n;
SegmentTree T[maxN*4];

void init(int l,int r,int now);
int read();
int Query(int l0,int r0,int l,int r,int now);
void Updata(int id,int val,int l,int r,int now);

int main()
{
    int m;
    while (cin>>n>>m)
    {
        init(1,n,1);
        for (int i=1;i<=m;i++)
        {
            char ch;
            int a,b;
            cin>>ch>>a>>b;
            if (ch=='Q')
                cout<<Query(a,b,1,n,1)<<endl;
            else
                Updata(a,b,1,n,1);
        }
    }
}

int read()
{
    int x=0;
    int k=1;
    char ch=getchar();
    while (((ch<'0')||(ch>'9'))&&(ch!='-'))
        ch=getchar();
    if (ch=='-')
    {
        k=-1;
        ch=getchar();
    }
    while ((ch<='9')&&(ch>='0'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*k;
}

void init(int l,int r,int now)
{
    if (l==r)
    {
        T[now].maxnum=read();
        return;
    }
    int mid=(l+r)/2;
    init(l,mid,now*2);
    init(mid+1,r,now*2+1);
    T[now].maxnum=max(T[now*2].maxnum,T[now*2+1].maxnum);
    return;
}

int Query(int l0,int r0,int l,int r,int now)
{
    //cout<<l0<<' '<<r0<<' '<<l<<' '<<r<<endl;
    //system("pause");
    if ((l0==l)&&(r0==r))
    {
        return T[now].maxnum;
    }
    //if (l==r)
    //    return T[now].maxnum;
    int mid=(l+r)/2;
    if (r0<=mid)
        return Query(l0,r0,l,mid,now*2);
    else
    if (l0>=mid+1)
        return Query(l0,r0,mid+1,r,now*2+1);
    else
        return max(Query(l0,mid,l,mid,now*2),Query(mid+1,r0,mid+1,r,now*2+1));
}

void Updata(int id,int val,int l,int r,int now)
{
    if (l==r)
    {
        T[now].maxnum=val;
        return;
    }
    int mid=(l+r)/2;
    if (id<=mid)
        Updata(id,val,l,mid,now*2);
    else
        Updata(id,val,mid+1,r,now*2+1);
    T[now].maxnum=max(T[now*2].maxnum,T[now*2+1].maxnum);
    return;
}
