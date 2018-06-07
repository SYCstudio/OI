#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110001;
const int maxTwo=20;
const ll inf=1e15;

class Edge
{
public:
    ll u,v,w;
};

class sort_data
{
public:
    ll pos,resttime;
};

bool operator < (sort_data A,sort_data B)
{
    return A.resttime<B.resttime;
}

class Destination
{
public:
    ll pos,tim;
};

bool operator < (Destination A,Destination B)
{
    return A.tim<B.tim;
}

ll n,m;
int cnt;
ll Ans;
int Head[maxN];
Edge E[maxN];
int Next[maxN];
ll Armypos[maxN];
ll Skip[25][maxN];
ll Skip_path[25][maxN];
ll Getpos[maxN];
bool get_top[maxN];
ll rest_time[maxN];
bool is_cover[maxN];

ll read();
void Add_Edge(int u,int v,int w);
void Skip_dfs(int u,int father);
bool check(int mid);
void check_dfs(int u,int father);

int main()
{
    
    n=read();
    cnt=0;
    mem(Head,-1);
    for (int i=1;i<n;i++)
    {
        int u=read(),v=read(),w=read();
        Add_Edge(u,v,w);
    }

    mem(Skip,-1);
    mem(Skip_path,0);
    Skip_dfs(1,1);
    
    for (int i=1;i<=maxTwo;i++)
        for (int j=1;j<=n;j++)
            if (Skip[i-1][j]!=-1)
            {
                Skip[i][j]=Skip[i-1][Skip[i-1][j]];
                Skip_path[i][j]=Skip_path[i-1][j]+Skip_path[i-1][Skip[i-1][j]];
            }
    /*
    for (int i=1;i<=n;i++)
    {
        for (int j=0;j<=maxTwo;j++)
            cout<<Skip[j][i]<<" ";
        cout<<endl;
    }
    //*/
    
    m=read();
    for (int i=1;i<=m;i++)
        Armypos[i]=read();

    int l=0,r=1000000;
    Ans=inf;
    do
    {
        int mid=(l+r)/2;
        //cout<<l<<" "<<r<<endl;
        if (check(mid))
        {
            Ans=min(Ans,(ll)(mid));
            r=mid-1;
        }
        else
            l=mid+1;
    }
    while (l<=r);
    //*/
    cout<<Ans<<endl;
    return 0;
}

ll read()
{
    ll x=0;
    char ch=getchar();
    while ((ch>'9')||(ch<'0'))
        ch=getchar();
    while ((ch>='0')&&(ch<='9'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x;
}

void Add_Edge(int u,int v,int w)
{
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    E[cnt].u=u;
    E[cnt].v=v;
    E[cnt].w=w;

    cnt++;
    Next[cnt]=Head[v];
    Head[v]=cnt;
    E[cnt].u=v;
    E[cnt].v=u;
    E[cnt].w=w;
    return;
}

void Skip_dfs(int u,int father)
{
    for (int i=Head[u];i!=-1;i=Next[i])
    {
        int v=E[i].v;
        if (v==father)
            continue;
        if (Skip[0][v]==-1)
        {
            Skip[0][v]=u;
            Skip_path[0][v]=E[i].w;
            Skip_dfs(v,u);
        }
    }
    return;
}

bool check(int mid)
{
    //cout<<"check:"<<mid<<endl;
    mem(get_top,0);
    mem(is_cover,0);
    for (int i=1;i<=m;i++)
    {
        Getpos[i]=Armypos[i];
        ll timecnt=0;
        for (int j=maxTwo;j>=0;j--)
            if ((Skip[j][Getpos[i]]>1)&&(timecnt+Skip_path[j][Getpos[i]]<=mid))
            {
                timecnt=timecnt+Skip_path[j][Getpos[i]];
                Getpos[i]=Skip[j][Getpos[i]];
            }
        if ((Skip[0][Getpos[i]]==1)&&(Skip_path[0][Getpos[i]]+timecnt<=mid))
        {
            get_top[i]=1;
            rest_time[i]=mid-timecnt;
        }
        else
            is_cover[Getpos[i]]=1;
    }

    /*
    for (int i=1;i<=m;i++)
        cout<<i<<" "<<Getpos[i]<<" "<<rest_time[i]<<endl;
    cout<<endl;
    //*/
    
    check_dfs(1,1);

    /*
    for (int i=1;i<=n;i++)
        cout<<is_cover[i]<<" ";
    cout<<endl;
    //*/
    
    vector<sort_data> V2;
    V2.clear();
    for (int i=1;i<=m;i++)
        if (get_top[i]==1)
            V2.push_back((sort_data){Getpos[i],rest_time[i]});
    sort(V2.begin(),V2.end());

    /*
    for (int i=0;i<V.size();i++)
        cout<<V[i].pos<<" "<<V[i].resttime<<endl;
    cout<<endl;
    //*/

    vector<sort_data> V;
    V.clear();
    for (int i=0;i<V2.size();i++)
    {
        if (is_cover[V2[i].pos]==0)
            is_cover[V2[i].pos]=1;
        else
            V.push_back((sort_data){V2[i].pos,V2[i].resttime-Skip_path[0][V2[i].pos]});
    }

    sort(V.begin(),V.end());
    
    /*
    for (int i=0;i<V.size();i++)
        cout<<V[i].pos<<" "<<V[i].resttime<<endl;
    cout<<endl;
    for (int i=1;i<=n;i++)
        cout<<is_cover[i]<<" ";
    cout<<endl<<endl;
    //*/
    
    vector<Destination> D;
    D.clear();
    for (int i=Head[1];i!=-1;i=Next[i])
    {
        int v=E[i].v;
        if (is_cover[v]==0)
            D.push_back((Destination){v,E[i].w});
    }
    sort(D.begin(),D.end());
    /*
    for (int i=0;i<D.size();i++)
        cout<<D[i].pos<<" "<<D[i].tim<<endl;
    cout<<endl;
    //*/
    if (D.size()>V.size())
        return 0;
    int j=0;
    if (D.size()==0)
        return 1;
    for (int i=0;i<V.size();i++)
    {
        if (V[i].resttime>=D[j].tim)
            j++;
        if (j==D.size())
            return 1;
    }
    return 0;
}

void check_dfs(int u,int father)
{
    if (is_cover[u]==1)
        return;
    bool is_all=1;
    bool has_son=0;
    for (int i=Head[u];i!=-1;i=Next[i])
    {
        int v=E[i].v;
        if (v==father)
            continue;
        has_son=1;
        check_dfs(v,u);
        if (is_cover[v]==0)
            is_all=0;
    }
    if (has_son==0)
        is_all=0;
    if (is_all==1)
        is_cover[u]=1;
    return;
}
