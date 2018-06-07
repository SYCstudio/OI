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
int R;//��ǰ��ƴ�������ֵ��ͬʱҲ�������ұ߽� 
int Stamp[maxsize];

void dfs(int x);//ö����Ʊ��ֵ 
int DP_solve(int x);//���㵱ǰ�������������ֵ 

int main()
{
    int i,j,k;
    
    cin>>N>>M;
    
    Ans=0;
    R=M;
    Stamp[1]=1;//��һ��һ��Ϊ1,����ͻ���� 
    
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
