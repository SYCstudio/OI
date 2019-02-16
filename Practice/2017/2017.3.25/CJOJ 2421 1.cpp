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
    int Ans=0;
    for (int i=1;i<=N;i++)
    {
        for (int j=1;j<=N;j++)
        {
            cin>>Matr[i][j];
            if(Matr[i][j]==0)
                Matr[i][j]=-inf;
            Sum[i][j]=Sum[i-1][j]+Sum[i][j-1]-Sum[i-1][j-1]+Matr[i][j];
        }
    }
 
    for (int x1=0;x1<=N;x1++)
        for (int y1=0;y1<=N;y1++)
            for (int x2=x1+1;x2<=N;x2++)
                for (int y2=y1+1;y2<=N;y2++)
                    Ans=max(Ans,Sum[x2][y2]-Sum[x1][y1]);
 
    if (Ans-10<=0)
        cout<<0<<endl;
    else
        cout<<Ans<<endl;
 
    fclose(stdin);
    fclose(stdout);
    return 0;
}
