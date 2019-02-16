#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1001;
const int inf=2147483647;

int n,m;
char A[maxN];
char B[maxN];
int F[maxN];

int main()
{
    while (1)
    {
        scanf("%s",A);
        if ((strlen(A)==1)&&(A[0]=='#'))
            break;
        scanf("%s",B);
        n=strlen(A);
        m=strlen(B);
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
        int i=0,j=0;
        int Ans=0;
        while (i<n)
        {
            if (A[i]==B[j])
            {
                i++;
                j++;
                if (j==m)
                {
                    Ans++;
                    j=0;//注意这里j为０，而KMP算法中这里是j=F[j-1]+1，因为一块花纹不能重复出现在多条小饰条上。
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