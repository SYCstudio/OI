#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxsize=50;
const int inf=2147483647;

int N,M;
int Ans;
int R;//当前能拼出的最大值，同时也是搜索右边界 
int Stamp[maxsize];

void dfs(int x);//枚举邮票面值 
int DP_solve(int x);//计算当前能贴出的最大面值 

int main()
{
    int i,j,k;
    
    cin>>N>>M;
    
    Ans=0;
    R=M;
    Stamp[1]=1;//第一张一定为1,否则就会出错 
    
    dfs(2);
    
    cout<<Ans<<endl;
    return 0;
}

void dfs(int x)
{
    if (x==N+1)
    {
        Ans=max(Ans,R);
        return;
	}
	
	int i;
	
	for (i=Stamp[x-1]+1;i<=R+1;i++)
	{
	    Stamp[x]=i;
	    R=DP_solve(x);
	    dfs(x+1);
	}
	return;
}

int DP_solve(int x)
{
    int i,j,k;
    int F[1000];
    
    mem(F,127);
    
    i=0;
    F[0]=0;
    
    while (1)
    {
        i++;
        for (j=1;j<=x;j++)
            if (i>=Stamp[j])
                F[i]=min(F[i],F[i-Stamp[j]]+1);
        if (F[i]>M)
            return i-1;
	}
	
	return 0;
    
}
