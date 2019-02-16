#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=25;
const int Shunzi[4]={0,5,3,2};//i顺子至少需要多少张牌
const int inf=2147483647;

int n;
int Card[maxN];
int F[maxN][maxN][maxN][maxN];
int Ans;

void init();
void dfs(int step);
int now_step(int x1,int x2,int x3,int x4);

int main()
{
    int T;
    scanf("%d%d",&T,&n);
    init();
    while (T--)
    {
        memset(Card,0,sizeof(Card));
        Ans=n;
        for (int i=1;i<=n;i++)//输入
        {
            int a,b;
            scanf("%d%d",&a,&b);
            if (a==0)//0是王
                Card[0]++;
            else
                if (a==1)
                    Card[14]++;
                else
                    Card[a]++;
        }
        dfs(0);
        printf("%d\n",Ans);
    }
    return 0;
}

void init()
{
    F[0][0][0][0]=0;
    for (int i=0;i<=n;i++)
        for (int j=0;j<=n;j++)
            for (int k=0;k<=n;k++)
                for (int l=0;l<=n;l++)
                {
                    F[i][j][k][l]=i+j+k+l;
                    if (4*i+3*j+2*k+l<=n)
                    {
                        if (l!=0)//一张牌
                            F[i][j][k][l]=min(F[i][j][k][l],F[i][j][k][l-1]+1);//打出一个单牌
                        if (k!=0)//双牌
                            F[i][j][k][l]=min(F[i][j][k][l],F[i][j][k-1][l]+1);//打出一个对子
                        if (j!=0)//三张牌
                        {
                            F[i][j][k][l]=min(F[i][j][k][l],F[i][j-1][k][l]+1);//打出三张牌
                            if (l!=0)
                                F[i][j][k][l]=min(F[i][j][k][l],F[i][j-1][k][l-1]+1);//打出三带一
                            if (k!=0)
                                F[i][j][k][l]=min(F[i][j][k][l],F[i][j-1][k-1][l]+1);//打出三带二
							if (j>=1)
								F[i][j][k][l]=min(F[i][j][k][l],F[i][j-1][k+1][l+1]);//三个拆成一对和一个
                        }
                        if (i!=0)//四张牌
                        {
                            F[i][j][k][l]=min(F[i][j][k][l],F[i-1][j][k][l]+1);//打出四张牌
                            if (l>=2)
                                F[i][j][k][l]=min(F[i][j][k][l],F[i-1][j][k][l-2]+1);//打出四带两张单牌
                            if (k>=2)
                                F[i][j][k][l]=min(F[i][j][k][l],F[i-1][j][k-2][l]+1);//打出四带两对牌
							if (i>=1)
								F[i][j][k][l]=min(F[i][j][k][l],F[i-1][j+1][k][l+1]);//四个拆成三个和一个
							if (i>=2)
								F[i][j][k][l]=min(F[i][j][k][l],F[i-2][j][k][l]+1);//两个四拆成一个四带两对
							if (k>=1)
								F[i][j][k][l]=min(F[i][j][k][l],F[i-1][j][k-1][l]+1);//四带一对
                        }
                        //printf("(%d,%d,%d,%d) %d\n",i,j,k,l,F[i][j][k][l]);
                    }
                }
    return;
}

void dfs(int step)
{
    if (step>Ans)
        return;
    int Cnt[maxN];
    memset(Cnt,0,sizeof(Cnt));
    for (int i=2;i<=14;i++)
        Cnt[Card[i]]++;
    Ans=min(Ans,step+now_step(Cnt[1],Cnt[2],Cnt[3],Cnt[4]));
    //cout<<Ans<<endl;
    for (int k=1;k<=3;k++)
    {
        for (int i=3;i<=14;i++)
        {
            int pos;
            for (pos=i;(pos<=14)&&(Card[pos]>=k);pos++)
            {
                Card[pos]=Card[pos]-k;
                if (pos-i+1>=Shunzi[k])
                    dfs(step+1);
            }
            for (pos=pos-1;pos>=i;pos--)
                Card[pos]=Card[pos]+k;
        }
    }
    return;
}

int now_step(int x1,int x2,int x3,int x4)
{
    if (Card[0]==0)
        return F[x4][x3][x2][x1];//没有王
    if (Card[0]==1)
        return F[x4][x3][x2][x1+1];//只有一个王
    if (Card[0]==2)
        return min(F[x4][x3][x2][x1+2],F[x4][x3][x2][x1]+1);//将两张王看作两张单牌or一对牌
}
