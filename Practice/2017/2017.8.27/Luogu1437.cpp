#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=60;
const int maxM=4000;
const int inf=2147483647;

int n,m;
int Arr[maxN][maxN];
int Sum[maxN][maxN];
int F[maxN][maxN][maxM];

int read();
void outp();

int main()
{
    n=read();
    m=read();
    for (int j=1;j<=n;j++)//输入，同时转置矩阵
        for(int i=j;i<=n;i++)
            Arr[i][j]=read();
    for (int i=1;i<=n;i++)//计算前缀和
        for (int j=1;j<=i;j++)
            Sum[i][j]=Sum[i][j-1]+Arr[i][j];
    mem(F,-1);//置为-1，标记为不行
    for (int i=1;i<=n;i++)//动态转移初始值
    {
        F[i][0][0]=0;
        F[i][1][1]=Arr[1][i];
    }
    int Ans=0;
    for (int i=1;i<=n;i++)
        for (int j=0;j<=i;j++)
            for (int k=0;k<=m;k++)
            {
                if (j<=k)//只用j<k的时候才能推
                    for (int p=max(j-1,0);p<=i-1;p++)//注意这里的取max，因为j为0的时候j-1是负数
                        if (F[i-1][p][k-j]!=-1)
                            F[i][j][k]=max(F[i][j][k],F[i-1][p][k-j]+Sum[i][j]);
                Ans=max(Ans,F[i][j][k]);//取最大值
            }
    printf("%d\n",Ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}

int read()
{
    int x=0;
    int k=1;
    char ch=getchar();
    while (((ch>'9')||(ch<'0'))&&(ch!='-'))
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