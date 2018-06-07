#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxN=20;
const int inf=2147483647;
const double eps=1e-6;

int n,m;
int shootcnt=0;
double px[maxN];
double py[maxN];
int Shoot[maxN*maxN];
int F[1<<maxN];

int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        shootcnt=0;
        memset(Shoot,0,sizeof(Shoot));
        memset(F,127,sizeof(F));
        scanf("%d%d",&n,&m);
        for (int i=0;i<n;i++)
            scanf("%lf%lf",&px[i],&py[i]);
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
            {
                if (i>j)
                    continue;
                if (i==j)
                {
                    shootcnt++;
                    Shoot[shootcnt]=(1<<i);
                    continue;
                }
                double x1=px[i],x2=px[j],y1=py[i],y2=py[j];
                if ((x2*y1-x1*y2)==0)
                    continue;
                double a=(x2*y1-x1*y2)/(x1*x2*(x1-x2));
                if (a>=0)
                    continue;
                double b=(y1-a*x1*x1)/x1;
                //cout<<a<<" "<<b<<" "<<a*px[i]*px[i]+b*px[i]-py[i]<<" "<<a*px[j]*px[j]+b*px[j]-py[j]<<endl;
                //cout<<"("<<i<<","<<j<<") "<<a<<" "<<b<<endl;
                //Shoot[i][j]=Shoot[i][j]|(1<<i)|(1<<j);
                shootcnt++;
                for (int k=0;k<n;k++)
                    if (fabs(a*px[k]*px[k]+b*px[k]-py[k])<=eps)
                        Shoot[shootcnt]=Shoot[shootcnt]|(1<<k);
            }
        /*
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
                cout<<Shoot[i][j]<<" ";
            cout<<endl;
        }
        //*/
        F[0]=0;
        for (int i=0;i<n;i++)
            F[1<<i]=1;
        for (int i=1;i<=shootcnt;i++)
        {
            for (int j=0;j<=(1<<n)-1;j++)
                F[j|Shoot[i]]=min(F[j|Shoot[i]],F[j]+1);
        }
        printf("%d\n",F[(1<<n)-1]);
    }
    return 0;
}
