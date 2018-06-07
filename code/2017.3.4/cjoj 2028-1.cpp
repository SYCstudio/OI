#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
 
#define mem(ARR,x) memset(ARR,x,sizeof(ARR))
 
const int maxsize=1000;
const int inf=2147483647;
 
int N,M,K;
int cnt;
int Ans;
int Head[maxsize];
int Last[maxsize];
int Next[maxsize];
int E[maxsize];
int Cvis[maxsize][maxsize];//表示第i个点周围的第j中颜色使用次数 
//bool Cvis[maxsize][maxsize];//必须用int，因为要存次数，而不仅仅是存是否使用过该颜色，因为存在周围一种颜色用两次的情况 
bool vis[maxsize];
 
void Add_Edge(int u,int v);
void dfs(int u);
 
int main()
{
    int i,j,k;
    int u,v;
    
    while (cin>>N>>M>>K)
    {
        mem(Head,-1);
        mem(Next,-1);
        mem(Last,-1);
        mem(vis,0);
        cnt=0;
        Ans=0;
        for (i=1;i<=M;i++)
        {
            cin>>u>>v;
            Add_Edge(u,v);
            Add_Edge(v,u);
		}
		
		vis[1]=1;
		
		dfs(1);
		
		cout<<Ans<<endl;
		
	}
	return 0;
}
 
void Add_Edge(int u,int v)
{
    cnt++;
    E[cnt]=v;
    if (Head[u]==-1)
    {
        Head[u]=cnt;
        Last[u]=cnt;
	}
	else
	{
	    Next[Last[u]]=cnt;
	    Last[u]=cnt;
	}
	return;
}
 
void dfs(int u)
{
	int i,j,k;
	
    if (u==N+1)
    {
        Ans++;
        return;
	}
	for (i=1;i<=K;i++)
	{
	    if (Cvis[u][i]==0)
	    {
	        for (j=Head[u];j!=-1;j=Next[j])
	        {
	            Cvis[E[j]][i]++;
			}
			
			dfs(u+1);
			
			for (j=Head[u];j!=-1;j=Next[j])
			{
			    Cvis[E[j]][i]--;
			}
		}
	}
	return;
}
