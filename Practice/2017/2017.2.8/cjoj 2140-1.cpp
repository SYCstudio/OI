#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;
 
#define ll long long
 
const int maxsize=21;
const ll inf=2147483647;
 
int n,m;
int F[1<<maxsize];//�������� 
int R[maxsize];//״ѹÿһ���в��ܷ��õĸ��� 
 
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
        cnt=0;//ͳ��i��1�ĸ�����������ȷ����ǰ�ǵڼ��� 
        for (j=i;j>0;j=j-(j&-j)) cnt++;
        for (j=i&R[cnt];j>0;j=j-(j&-j))//j&-j����ȡj�Ķ����ƴӵ�λ���λ�ĵ�һ��1����������״�����lowbit
		    F[i]+=F[i^(j&-j)];
	}
	
	//for (i=1;i<(1<<n);i++)
	//    cout<<F[i]<<" ";
	//cout<<endl;
	
	cout<<F[(1<<n)-1]<<endl;
	
	return 0;
}