#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=12;
const int inf=2147483647;

int n,m;
char Mp[maxN+5][maxN+5];
ll F[2][1594323+10],P[20];

//void dfs(int d,int S,int cnt);

int main(){
	P[0]=1;for (int i=1;i<=15;i++) P[i]=P[i-1]*3;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%s",Mp[i]+1);
	//dfs(1,0,0);cout<<scnt<<endl;
	//for (int i=1;i<=scnt;i++) cout<<Seq[i]<<" "<<T[Seq[i]]<<endl;
	int lstx=0,lsty=0;
	for (int i=n;(i>=1)&&(lstx==0);i--) for (int j=m;(j>=1)&&(lstx==0);j--) if (Mp[i][j]=='.') lstx=i,lsty=j;
	//cout<<lstx<<" "<<lsty<<endl;
	int now=0,up=P[m+1];F[now][0]=1;ll Ans=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			now^=1;mem(F[now],0);
			for (int k=0;k<=up;k++)
				if (F[now^1][k]){
					int x=k%3,y=k/P[j]%3;ll key=F[now^1][k];
					//cout<<k<<" "<<x<<" "<<y<<" "<<key<<endl;
					if (Mp[i][j]=='*'){
						if ((x==0)&&(y==0)) F[now][k]+=key;
						continue;
					}
					if (x==0){
						if (y==0)
							if ((i<n)&&(j<m)&&(Mp[i+1][j]=='.')&&(Mp[i][j+1]=='.')) F[now][k+2+P[j]]+=key;
						if (y==1){
							if ((i<n)&&(Mp[i+1][j]=='.')) F[now][k]+=key;
							if ((j<m)&&(Mp[i][j+1]=='.')) F[now][k-P[j]+1]+=key;
						}
						if (y==2){
							if ((i<n)&&(Mp[i+1][j]=='.')) F[now][k]+=key;
							if ((j<m)&&(Mp[i][j+1]=='.')) F[now][k-P[j]*2+2]+=key;
						}
					}
					if (x==1){
						if (y==0){
							if ((i<n)&&(Mp[i+1][j]=='.')) F[now][k-1+P[j]]+=key;
							if ((j<m)&&(Mp[i][j+1]=='.')) F[now][k]+=key;
						}
						if (y==1){
							int cnt=0,p=j+1;
							while ((p<=m)&&((cnt!=0)||(k/P[p]%3!=2))){
								if (k/P[p]%3==1) ++cnt;
								if (k/P[p]%3==2) --cnt;
								++p;
							}
							if (p<=m) F[now][k-1-P[j]-P[p]]+=key;
						}
						if (y==2)
							if ((i==lstx)&&(j==lsty)) Ans+=key;
					}
					if (x==2){
						if (y==0){
							if ((i<n)&&(Mp[i+1][j]=='.')) F[now][k-2+P[j]*2]+=key;
							if ((j<m)&&(Mp[i][j+1]=='.')) F[now][k]+=key;
						}
						if (y==1) F[now][k-2-P[j]]+=key;
						if (y==2){
							int cnt=0,p=j-1;
							while ((p>=1)&&((cnt!=0)||(k/P[p]%3!=1))){
								if (k/P[p]%3==1) --cnt;
								if (k/P[p]%3==2) ++cnt;
								--p;
							}
							if (p>=1) F[now][k-2-P[j]*2+P[p]]+=key;
						}
					}
				}
			/*
			if ((i==lstx)&&(j==lsty)){
				printf("%lld\n",Ans);return 0;
			}
			//*/
			/*
			cout<<"("<<i<<","<<j<<")"<<endl;
			for (int k=0;k<=up;k++)
				if (F[now][k]){
					cout<<k<<" ";
					cout<<k%3<<"|";
					for (int l=1;l<=m;l++) cout<<k/P[l]%3;
					cout<<" "<<F[now][k]<<endl;
				}
			//*/
		}
	printf("%lld\n",Ans);return 0;
}

/*
void dfs(int d,int S,int cnt){
	//cout<<"dfs:"<<d<<" "<<S<<" "<<cnt<<" "<<scnt<<endl;
	if (d==m+1){
		if (cnt) return;
		T[Seq[++scnt]=S*3]=scnt;T[Seq[++scnt]=S*3+1]=scnt;T[Seq[++scnt]=S*3+2]=scnt;
		return;
	}
	dfs(d+1,S*3,cnt);
	dfs(d+1,S*3+2,cnt+1);
	if (cnt>1) dfs(d+1,S*3+1,cnt-1);
	return;
}
//*/
