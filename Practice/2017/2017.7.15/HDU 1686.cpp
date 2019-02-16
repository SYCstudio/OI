#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=10001;
const int maxM=1000001;
const int inf=2147483647;

int n,m;
char W[maxN];
char T[maxM];
int F[maxN];

int main()
{
    int TT;
    cin>>TT;
    for (int ti=1;ti<=TT;ti++)
    {
        scanf("%s",W);
        scanf("%s",T);
        n=strlen(W);
        m=strlen(T);
        F[0]=-1;
        for (int i=1;i<n;i++)
        {
            int j=F[i-1];
            while ((W[j+1]!=W[i])&&(j!=-1))
                j=F[j];
            if (W[j+1]==W[i])
                F[i]=j+1;
            else
                F[i]=-1;
        }
        int i=0,j=0;
        int Ans=0;
        while (i<m)
        {
            if (W[j]==T[i])
            {
                i++;
                j++;
                if (j==n)
                {
                    Ans++;
                    j=F[j-1]+1;
                }
            }
            else
            if (j==0)
                i++;
            else
                j=F[j-1]+1;
        }
        cout<<Ans<<endl;
    }
    return 0;
}