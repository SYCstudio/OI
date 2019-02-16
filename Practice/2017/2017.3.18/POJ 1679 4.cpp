#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

class Edge
{
public:
    int x,y,w;
};

const int maxsize=50001;
const int inf=2147483647;

int N,M;
int Kerubiel[maxsize];
Edge E[maxsize];
bool O[maxsize];

bool cmp(Edge a,Edge b);
int Find(int x);

int main()
{
    int i,j,k;
    int T;
    int cnt;
    int MST,mst;
    int fx,fy;
    bool flag;

    cin>>T;

    while(T--)
    {
        cin>>N>>M;
        memset(O,0,sizeof(O));

        for (i=1;i<=M;i++)
            cin>>E[i].x>>E[i].y>>E[i].w;

        sort(&E[1],&E[M+1],cmp);
        for (i=1;i<=N;i++)
            Kerubiel[i]=i;

        cnt=0;i=0;
        MST=0;mst=0;

        do
        {
            i++;
            fx=Find(E[i].x);
            fy=Find(E[i].y);
            if (fx!=fy)
            {
                cnt++;
                MST+=E[i].w;
                Kerubiel[fx]=fy;
                O[i]=1;
            }
        }
        while (cnt<N-1);
        //cout<<"MST "<<MST<<endl;

        //cout<<"The min MST"<<endl;
        /*for (i=1;i<=M;i++)
            if (O[i]==1)
            {
                cout<<E[i].x<<" - "<<E[i].y<<" "<<E[i].w<<endl;
            }*/

        flag=1;

        for (i=1;i<=M;i++)
            if (O[i]==1)
            {
                //cout<<i<<endl;
                for (j=1;j<=N;j++)
                    Kerubiel[j]=j;
                mst=0;j=0;cnt=0;

                do
                {
                    j++;
                    if (i==j)
                        continue;
                    fx=Find(E[j].x);
                    fy=Find(E[j].y);
                    if (fx!=fy)
                    {
                        cnt++;
                        mst+=E[j].w;
                        Kerubiel[fx]=fy;
                    }
                }
                while ((cnt<N-1)&&(j<M));
                //cout<<"mst except "<<E[i].x<<" - "<<E[i].y<<" "<<mst<<endl;
                if ((cnt==N-1)&&(mst==MST))
                {
                    flag=0;
                    break;
                }

            }
        if(flag==0)
        {
            cout<<"Not Unique!"<<endl;
        }
        else
            cout<<MST<<endl;
    }
    return 0;
}

bool cmp(Edge a,Edge b)
{
    return a.w<b.w;
}

int Find(int x)
{
    if (Kerubiel[x]==x)
        return x;
    return Kerubiel[x]=Find(Kerubiel[x]);
    //return Kerubiel[x];
}