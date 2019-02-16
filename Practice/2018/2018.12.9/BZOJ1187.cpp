#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxM=6;
const int inf=2147483647;

int n,m;
int C[maxN+10][maxM+10],P[10];
int now,F[2][3000],Seq[2][3000],scnt[2],Pos[3000],tim,Tim[3000];

void Add(int S,int key);

int main(){
	P[0]=1;for (int i=1;i<10;i++) P[i]=P[i-1]*3;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&C[i][j]);
	for (int i=1;i<3000;i++) F[0][i]=F[1][i]=-inf;
	now=0;F[now][1]=0;Seq[now][1]=0;scnt[now]=1;
	int Ans=-inf;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			now^=1;scnt[now]=0;++tim;
			for (int l=1;l<=scnt[now^1];l++){
				int S=Seq[now^1][l],x=S%3,y=S/P[j]%3,key=F[now^1][l];F[now^1][l]=-inf;
				if (x==0){
					if (y==0){
						Add(S,key);
						if ((i<n)&&(j<m)) Add(S+P[j]+2,key+C[i][j]);
					}
					if (y==1){
						if (i<n) Add(S,key+C[i][j]);
						if (j<m) Add(S-P[j]+1,key+C[i][j]);
					}
					if (y==2){
						if (i<n) Add(S,key+C[i][j]);
						if (j<m) Add(S-P[j]*2+2,key+C[i][j]);
					}
				}
				if (x==1){
					if (y==0){
						if (i<n) Add(S-1+P[j],key+C[i][j]);
						if (j<m) Add(S,key+C[i][j]);
					}
					if (y==1){
						int cnt=0,p=j+1;
						while ((p<=m)&&((cnt)||(S/P[p]%3!=2))){
							if (S/P[p]%3==1) ++cnt;
							if (S/P[p]%3==2) --cnt;
							++p;
						}
						if (p<=m) Add(S-1-P[j]-P[p],key+C[i][j]);
					}
					if (y==2){
						bool flag=1;
						for (int p=1;(p<=m)&&(flag);p++)
							if ((p!=j)&&(S/P[p]%3!=0)) flag=0;
						if (flag) Ans=max(Ans,key+C[i][j]);
					}
				}
				if (x==2){
					if (y==0){
						if (i<n) Add(S-2+P[j]*2,key+C[i][j]);
						if (j<m) Add(S,key+C[i][j]);
					}
					if (y==1) Add(S-2-P[j],key+C[i][j]);
					if (y==2){
						int cnt=0,p=j-1;
						while ((p>=1)&&((cnt)||(S/P[p]%3!=1))){
							if (S/P[p]%3==1) --cnt;
							if (S/P[p]%3==2) ++cnt;
							--p;
						}
						if (p>=1) Add(S-2-P[j]*2+P[p],key+C[i][j]);
					}
				}
			}
			/*
			cout<<"("<<i<<" "<<j<<")"<<endl;
			for (int l=1;l<=scnt[now];l++){
				cout<<Seq[now][l]<<" "<<Seq[now][l]%3<<"|";
				for (int k=1;k<=m;k++) cout<<Seq[now][l]/P[k]%3;
				cout<<" "<<F[now][l]<<endl;
			}
			//*/
		}
	printf("%d\n",Ans);return 0;
}

void Add(int S,int key){
	if (Tim[S]!=tim){
		Pos[Seq[now][++scnt[now]]=S]=scnt[now];Tim[S]=tim;
		F[now][scnt[now]]=key;
	}
	else F[now][Pos[S]]=max(F[now][Pos[S]],key);
}
