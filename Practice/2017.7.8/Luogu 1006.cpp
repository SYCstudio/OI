#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int n,m;
int f[51][51][51][51]={0};
int map[100][100]={0};

int max(int a,int b,int c,int d);

int main()
{
    //freopen("fgqs.in","r",stdin);
    //freopen("fgqs.out","w",stdout);
    int i,j,k,l;
    int a,b,c;
    cin>>n>>m;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            cin>>map[i][j];
    f[1][1][1][1]=map[1][1];
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            for (k=1;k<=n;k++)
                for (l=1;l<=m;l++)
                {
                    a=max(f[i-1][j][k-1][l],f[i-1][j][k][l-1],f[i][j-1][k-1][l],f[i][j-1][k][l-1]);
                    if ((i==k)&&(j==l))
                        f[i][j][k][l]=map[i][j]+a;
                    else
                        f[i][j][k][l]=a+map[i][j]+map[k][l];
                }
    cout<<f[n][m][n][m]<<endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

int max(int a,int b,int c,int d)
{
    if ((a>=b)&&(a>=c)&&(a>=d))
        return a;
    else if ((b>=a)&&(b>=c)&&(b>=d))
        return b;
    else if ((c>=a)&&(c>=b)&&(c>=d))
        return c;
    else
        return d;
}