#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;

const int maxN=1000001;
const int maxM=2001;
const int inf=2147493647;

int n,m;
string A,B;
int F[maxN];

int main()
{
    cin>>A>>B;
    n=A.size();;
    m=B.size();
    //Solve_Next
    
    F[0]=-1;
    
    for (int i=1;i<m;i++)
    {
        int j=F[i-1];
        while ((B[j+1]!=B[i])&&(j>=0))
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
    
    while (i<n)
    {
        if (A[i]==B[j])
        {
            i++;
            j++;
            if (j==m)
            {
                printf("%d\n",i-m+1);
                j=F[j-1]+1;
            }
        }
        else
        {
            if (j==0)
                i++;
            else
                j=F[j-1]+1;
        }
    }
    
    for (int i=0;i<m;i++)
        cout<<F[i]+1<<' ';//注意这里要＋１
    cout<<endl;
    return 0;
}