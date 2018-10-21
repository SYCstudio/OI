#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=10001;
const int inf=2147483647;

int n;
priority_queue<int,vector<int>,greater<int> > Q;

int read();

int main()
{
    n=read();
    for (int i=1;i<=n;i++)
        Q.push(read());
    int Ans=0;
    for (int i=1;i<n;i++)
    {
        int x=Q.top();
        Q.pop();
        int y=Q.top();
        Q.pop();
        Ans+=x+y;
        Q.push(x+y);
    }
    cout<<Ans<<endl;
    return 0;
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
    while ((ch>='0')&&(ch<='9'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*k;
}
