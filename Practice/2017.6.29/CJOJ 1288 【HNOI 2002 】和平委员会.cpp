//����Ⱦɫ��
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
using namespace std;

#define Other(x) ((x%2==0) ? (x-1) : (x+1) )

const int maxN=16050;
const int inf=2147483647;

int n,m;
int cnt;
vector<int> E[maxN];
int color[maxN];
int Ans[maxN];

bool solve();
bool dfs(int x);

int main()
{
    //freopen("out.txt","w",stdout);
    while (cin>>n>>m)
    {
        n=n*2;
        int a,b;
        for (int i=1;i<=n;i++)
            E[i].clear();
        for (int i=1;i<=m;i++)
        {
            cin>>a>>b;
            E[a].push_back(Other(b));
            E[b].push_back(Other(a));
        }
        if (solve())
        {
            for (int i=1;i<=n;i++)
                if (color[i]==1)
                    cout<<i<<endl;
        }
        else
            cout<<"NIE"<<endl;
    }
}

bool solve()
{
    memset(color,0,sizeof(color));
    for (int i=1;i<=n;i++)
    {
        if (color[i]!=0)
            continue;
        cnt=0;
        if (!dfs(i))
        {
            for (int j=1;j<=cnt;j++)
            {
                color[Ans[j]]=0;
                color[Other(Ans[j])]=0;
            }
            if (!dfs(Other(i)))
                return 0;
        }
    }
    return 1;
}

bool dfs(int x)
{
    if (color[x]==1)
        return 1;
    if (color[x]==2)
        return 0;
    color[x]=1;
    color[Other(x)]=2;
    cnt++;
    Ans[cnt]=x;
    for (int i=0;i<E[x].size();i++)
        if (!dfs(E[x][i]))
            return 0;
    return 1;
}

/*��������ٶȸ��죬����������ֵ�����С�Ľ�
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Other(x) ((x%2==0)? (x-1) : (x+1))

const int maxN=16001;
const int inf=2147483647;

int n,m;
//Graph
vector<int> E[maxN];
vector<int> E2[maxN];//���㲢������ͼ
//Tarjan
int cnt;
int dfn[maxN];
int low[maxN];
bool instack[maxN];
stack<int> S;
int Map[maxN];//Tarjan�����±����
//LTK
int LTKcnt;
vector<int> LTK[maxN];//ÿ�������Ĵ�����е�ԭ���ĵ�ı��
int Belong_[maxN];//ԭ���ĵ����ڵ�������
int Belong[maxN];//������ת����ı��
int chosen[maxN];//ĳ�����Ƿ�ѡ��,���Ǳ���ǲ�ѡ��
//Top_sort
int In[maxN];
priority_queue<int,vector<int>,greater<int> > Q;
int Order[maxN];

void tarjan(int u,int father);
void Top_sort();

int main()
{
    int u,v;
    freopen("out.txt","w",stdout);
    while (cin>>n>>m)
    {
    n=n*2;
    for (int i=1;i<=n;i++)
    {
        E[i].clear();
        E2[i].clear();
    }
    while (!Q.empty())
        Q.pop();
    while (!S.empty())
        S.pop();
    for (int i=1;i<=m;i++)
    {
        cin>>u>>v;//��ͼ
        E[u].push_back(Other(v));
        E[v].push_back(Other(u));
    }

    //Tarjan����
    mem(dfn,0);
    mem(instack,0);
    cnt=0;
    LTKcnt=0;
    for (int i=1;i<=n;i++)
        if (dfn[i]==0)
            tarjan(i,i);
    //for (int i=1;i<=n;i++)
    //    cout<<Belong_[i]<<' ';
    //cout<<endl;

    //��ΪTarjan������ı�Ų�����ԭ2-satͼ�ĶԳ��ԣ�����Ҫ���������±��
    mem(Map,0);
    cnt=0;
    for (int i=1;i<=n;i++)
    {
        if (Map[Belong_[i]]==0)
        {
            cnt++;
            Map[Belong_[i]]=cnt;
        }
        Belong[i]=Map[Belong_[i]];
    }
    //for (int i=1;i<=n;i++)
    //    cout<<Belong[i]<<' ';
    //cout<<endl;

    //Build New Graph(������)
    for (int i=1;i<=n;i++)
    {
        for (int j=0;j<E[i].size();j++)
        {
            int v=E[i][j];
            if (Belong[i]!=Belong[v])
                E2[Belong[v]].push_back(Belong[i]);
        }
    }

    //�жϿ�����
    bool ok=1;
    for (int i=1;i<=n;i=i+2)
        if (Belong[i]==Belong[i+1])
        {
            cout<<"NIE"<<endl;
            ok=0;
            break;
        }
    if (ok==0)
        continue;
    //Top����
    mem(chosen,0);
    Top_sort();

    //���Ҫ�ĵ�ͷ���ѡ��ĵ�
    for (int i=1;i<=n;i=i+2)
    {
        if (chosen[Belong[i]]==1)
            cout<<i<<endl;
        else
            cout<<i+1<<endl;
    }
    }
    return 0;
}

void tarjan(int u,int father)
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
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
        }
        else
            if (instack[v]==1)
            {
                low[u]=min(low[u],dfn[v]);
            }
    }
    if (dfn[u]==low[u])
    {
        LTKcnt++;
        //cout<<LTKcnt<<':';
        LTK[LTKcnt].clear();
        do
        {
            v=S.top();
            //cout<<v<<' ';
            S.pop();
            instack[v]=0;
            LTK[LTKcnt].push_back(v);
            Belong_[v]=LTKcnt;
        }
        while (u!=v);
        //cout<<endl;
    }
    return;
}

void Top_sort()
{
    int cnt=0;
    memset(In,0,sizeof(In));
    for (int i=1;i<=LTKcnt;i++)
        for (int j=0;j<E2[i].size();j++)
            In[E2[i][j]]++;
    for (int i=1;i<=LTKcnt;i++)
        if (In[i]==0)
            Q.push(i);
    do
    {
        int u=Q.top();
        Q.pop();
        //cout<<u<<' ';
        cnt++;
        Order[u]=cnt;
        if (chosen[u]==0)
        {
            chosen[u]=1;
            chosen[Other(u)]=-1;
        }
        //cout<<Order[u]<<' ';
        for (int i=0;i<E2[u].size();i++)
        {
            In[E2[u][i]]--;
            if (In[E2[u][i]]==0)
                Q.push(E2[u][i]);
        }
    }
    while (!Q.empty());
    //cout<<cnt<<endl;
    //for (int i=1;i<=LTKcnt;i++)
    //    cout<<Order[i]<<' ';
    //cout<<endl;
    return;
}
*/
