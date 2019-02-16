#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=20;
const int inf=2147483647;

int n;
char Name[maxN][200];
int Deadline[maxN];
int Costtime[maxN];
int F[1<<16];
int Nowtime[1<<16];
int Path[1<<16];

void outp(int x);

int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d",&n);
        for (int i=0;i<n;i++)
            cin>>Name[i]>>Deadline[i]>>Costtime[i];
        int MAX=1<<n;
        //cout<<MAX<<endl;
        memset(F,127,sizeof(F));
        memset(Nowtime,0,sizeof(Nowtime));
        F[0]=0;
        Nowtime[0]=0;
        Path[0]=-1;
        for (int i=1;i<MAX;i++)
        {
            for (int j=n-1;j>=0;j--)
            {
                int now=1<<j;
                if ((i&now)==0)
                    continue;
                //cout<<i<<" "<<j<<endl;
                now=now^i;
                int delta=max(Nowtime[now]+Costtime[j]-Deadline[j],0);
                if (F[now]+delta<F[i])
                {
                    F[i]=F[now]+delta;
                    Nowtime[i]=Nowtime[now]+Costtime[j];
                    Path[i]=j;
                }
            }
        }
        printf("%d\n",F[MAX-1]);
        outp(MAX-1);
    }
    return 0;
}

void outp(int x)
{
    int k=Path[x];
    if (k!=-1)
        outp(x^(1<<k));
	if (k==-1)
		return;
    printf("%s\n",Name[k]);
    return;
}
