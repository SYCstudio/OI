#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int inf=2147483647;

int main()
{
    int T,ti;
    int n,pos,L;
    cin>>T;
    for (ti=1;ti<=T;ti++)
    {
        int Min=0,Max=0;
        scanf("%d%d",&L,&n);
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&pos);
            Min=max(Min,min(pos,L-pos));
            Max=max(Max,max(pos,L-pos));
        }
        printf("%d %d\n",Min,Max);
    }
    return 0;
}
