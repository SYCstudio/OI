#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;
 
#define ll long long
 
const int maxsize=21;
const ll inf=2147483647;
 
int n,m;
int F[1<<maxsize];//递推数组 
int R[maxsize];//状压每一行中不能放置的格子 
 
int main()
{
    int i,j,k;
    int x,y;
    int cnt;
    
    memset(F,0,sizeof(F));
    
    cin>>n>>m;
    
    for (i=1;i<=n;i++)
        R[i]=(1<<(n))-1;
    
    //cout<<R[1]<<endl;
    
    for (i=1;i<=m;i++)
    {
        cin>>x>>y;
        R[x]=R[x]&(~(1<<(y-1)));
	}
    
    //for (i=1;i<=n;i++)
    //    cout<<R[i]<<" ";
    //cout<<endl;
    
    F[0]=1;
    
    for (i=1;i<(1<<n);i++)
    {
        //j=i&R[i];
        cnt=0;//统计i中1的个数，即可以确定当前是第几行 
        for (j=i;j>0;j=j-(j&-j)) cnt++;
        for (j=i&R[cnt];j>0;j=j-(j&-j))//j&-j就是取j的二进制从低位向高位的第一个1，类似于树状数组的lowbit
		    F[i]+=F[i^(j&-j)];
	}
	
	//for (i=1;i<(1<<n);i++)
	//    cout<<F[i]<<" ";
	//cout<<endl;
	
	cout<<F[(1<<n)-1]<<endl;
	
	return 0;
}