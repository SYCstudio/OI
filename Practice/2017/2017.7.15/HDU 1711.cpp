#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1000001;
const int inf=2147483647;

int n,m;
int A[maxN];
int B[maxN];
int F[maxN];

int read();

int main()
{
    int TT=read();
    for (int ti=1;ti<=TT;ti++)
    {
        n=read();
        m=read();
        for (int i=0;i<n;i++)
            A[i]=read();
        for (int i=0;i<m;i++)
            B[i]=read();
        F[0]=-1;
        for (int i=1;i<m;i++)
        {
            int j=F[i-1];
            while ((B[j+1]!=B[i])&&(j!=-1))
                j=F[j];
            if (B[j+1]==B[i])
                F[i]=j+1;
            else
                F[i]=-1;
        }
        //for (int i=0;i<m;i++)
        //    cout<<F[i]<<' ';
        //cout<<endl;
        int i=0,j=0;
        bool flag=0;
        while (i<n)
        {
            if (A[i]==B[j])
            {
                i++;
                j++;
                if (j==m)
                {
                    cout<<i-j+1<<endl;
                    flag=1;
                    break;
                }
            }
            else
            if (j==0)
                i++;
            else
                j=F[j-1]+1;
        }
        if (flag==0)
            cout<<-1<<endl;
    }
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
    while ((ch<='9')&&(ch>='0'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*k;
}