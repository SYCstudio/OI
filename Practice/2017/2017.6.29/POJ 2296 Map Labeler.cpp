#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<stack>
#include<cmath>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500;
const int inf=2147483647;

int n;
int Readx[maxN];
int Ready[maxN];
vector<int> E[maxN];
//tajan
int cnt;
int dfn[maxN];
int low[maxN];
bool instack[maxN];
stack<int> S;
//LTK
int LTKcnt;
int Belong[maxN];

void init();
void Graph_init(int Diff);
void Link(int u,int v);
bool check();
void tarjan(int u);

int main()
{
    int T;
    cin>>T;
    for (int ti=1;ti<=T;ti++)
    {
        cin>>n;
        init();
        for (int i=1;i<=n;i++)
            scanf("%d%d",&Readx[i],&Ready[i]);
        int l=0,r=20000;
        int Ans;
        do
        {
            init();
            int mid=(l+r)/2;
            Graph_init(mid);
            if (check())
            {
                Ans=mid;
                l=mid+1;
            }
            else
                r=mid;
        }
        while (l<r);
        cout<<Ans<<endl;
    }
    return 0;
}

void init()
{
    cnt=LTKcnt=0;
    mem(dfn,0);
    mem(instack,0);
    for (int i=0;i<=n*2;i++)
        E[i].clear();
    while (!S.empty())
        S.pop();
    return;
}
void Graph_init(int Diff)
{
    for (int i=1;i<=n;i++)
        for (int j=i+1;j<=n;j++)
            if (abs(Readx[i]-Readx[j])<Diff)//i��ʾ���ϣ�i+n��ʾ����
            {
                int maxy,miny;
                if (Ready[i]>Ready[j])
                {
                    maxy=i;
                    miny=j;
                }
                else
                {
                    maxy=j;
                    miny=i;
                }
                if (Ready[maxy]==Ready[miny])//��������ͬʱ������һ��һ��
                {
                    Link(miny,maxy+n);//���С�����ϣ���ı�������
                    Link(maxy,miny+n);//���������ϣ�С�ı�������
                    Link(miny+n,maxy);
                    Link(maxy+n,miny);
                    continue;
                }
                if ((Ready[maxy]-Ready[miny]<2*Diff)&&(Ready[maxy]-Ready[miny]>=Diff))
                {
                    Link(miny,maxy);//���С�����ϣ���ı�������
                    Link(maxy+n,miny+n);//���������£�С�ı�������
                    continue;
                }
                if ((Ready[maxy]-Ready[miny]<Diff))
                {
                    Link(miny,miny+n);//С�ı�������
                    Link(maxy+n,maxy);//��ı�������
                    Link(miny+n,maxy);
                    Link(maxy,miny+n);
                }
            }
    return;
}

void Link(int u,int v)
{
    E[u].push_back(v);
    return;
}

bool check()
{
    for (int i=1;i<=2*n;i++)
        if (dfn[i]==0)
        {
            tarjan(i);
        }
    for (int i=1;i<=n;i++)
        if (Belong[i]==Belong[i+n])
            return 0;
    return 1;
}

void tarjan(int u)
{
    int v;

    cnt++;
    dfn[u]=low[u]=cnt;
    instack[u]=1;
    S.push(u);

    for (int i=0;i<E[u].size();i++)
    {
        v=E[u][i];
        if (dfn[v]==0)
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            if (instack[v]==1)
                low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u])
    {
        LTKcnt++;
        do
        {
            v=S.top();
            S.pop();
            instack[v]=0;
            Belong[v]=LTKcnt;
        }
        while (u!=v);
    }
    return;
}
