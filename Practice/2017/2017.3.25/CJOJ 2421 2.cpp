#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=400;
const int inf=1000000;

int N;
int Matr[maxN][maxN];
int Sum[maxN][maxN]={0};

int main()
{

    cin>>N;
    long long Ans=0;
    for (int i=1;i<=N;i++)
    {
        for (int j=1;j<=N;j++)
        {
            cin>>Matr[i][j];
            if(Matr[i][j]==0)
                Matr[i][j]=-inf;
            Sum[i][j]=Sum[i][j-1]+Matr[i][j];
        }
    }
    /*for (int i=1;i<=N;i++)
    {
        for (int j=1;j<=N;j++)
            cout<<Sum[i][j]<<" ";
        cout<<endl;
    }*/

    for (int x1=1;x1<=N;x1++)
        for (int x2=x1;x2<=N;x2++)
        {
            long long cnt=0;
            for (int i=1;i<=N;i++)
            {
                //cout<<x1<<" "<<x2<<" "<<i<<endl;
                cnt+=Sum[i][x2]-Sum[i][x1-1];
                Ans=max(Ans,cnt);
                if (cnt<0)
                    cnt=0;
            }
            //cout<<cnt<<endl;
            Ans=max(Ans,cnt);
        }
    if (Ans-10<=0)
        cout<<0<<endl;
    else
        cout<<Ans-10<<endl;

    fclose(stdin);
    fclose(stdout);
    return 0;
}
