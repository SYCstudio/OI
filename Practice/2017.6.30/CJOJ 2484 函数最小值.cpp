#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

class Function
{
public:
    long long a,b,c;
};

class Value
{
public:
    long long data,num,x;
};

bool operator < (Value a,Value b)
{
    return a.data>b.data;
}

const int maxN=500000;

int n,m;
priority_queue<Value> Q;
Function F[maxN];

long long solve(long long num,long long x);

int main()
{
    cin>>n>>m;
    for (int i=1;i<=n;i++)
    {
        cin>>F[i].a>>F[i].b>>F[i].c;
        Q.push((Value){solve(i,1),i,1});
    }
    for (int i=1;i<=m;i++)
    {
        Value x=Q.top();
        Q.pop();
        cout<<x.data<<' ';
        Q.push((Value){solve(x.num,x.x+1),x.num,x.x+1});
    }
    return 0;
}

long long solve(long long num,long long x)
{
    return F[num].a*x*x+F[num].b*x+F[num].c;
}
