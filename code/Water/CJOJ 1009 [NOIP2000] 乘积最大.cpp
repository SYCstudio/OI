#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

int num[100][100]={0};
long long f[100][100]={0};
int N,K;

int main()
{
    int i,j,k,l;
    char str[100];
    cin>>N>>K;
    cin>>str;
    for (i=0;i<N;i++)
        num[i+1][i+1]=str[i]-48;
    for (i=1;i<=N;i++)
        for (j=i+1;j<=N;j++)
            if (i!=j)
            {
                num[i][j]=num[i][j-1]*10+str[j-1]-48;
            }
    /*for (i=1;i<=N;i++)
    {
        for (j=1;j<=N;j++)
            cout<<num[i][j]<<" ";
        cout<<endl;
    }*/
    for (i=1;i<=N;i++)
        f[i][0]=num[1][i];
    /*for (i=2;i<=N;i++)
        for (j=1;j<=K;j++)
            for (l=1;l<i;l++)
                f[i][j]=max(f[i][j],f[l][j-1]*num[l+1][i]);*/
    for (j=1;j<=K;j++)
        for (i=2;i<=N;i++)
            for (l=1;l<i;l++)
            {
                f[i][j]=max(f[i][j],f[l][j-1]*num[l+1][i]);
            }
    cout<<f[N][K]<<endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
