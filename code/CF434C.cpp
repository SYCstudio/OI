#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210;
const int maxAlpha=20;
const int maxK=510;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m,K;
int nodecnt=0,root=0;
int son[maxAlpha][maxN],fail[maxN],Val[maxN];
int Llen,L[maxN],Rlen,R[maxN],Seq[maxN];
int F[2][maxN][maxN][maxK];
queue<int> Q;

void Insert(int len);
void GetFail();
void Add(int &x,int y);
int Calc(int len,int *Up);

int main(){
	scanf("%d%d%d",&n,&m,&K);
	scanf("%d",&Llen);
	for (int i=1;i<=Llen;i++) scanf("%d",&L[i]);
	scanf("%d",&Rlen);
	for (int i=1;i<=Rlen;i++) scanf("%d",&R[i]);

	for (int i=1;i<=n;i++){
		int len;scanf("%d",&len);
		for (int j=1;j<=len;j++) scanf("%d",&Seq[j]);
		Insert(len);
	}
	GetFail();

	/*
	for (int i=0;i<=nodecnt;i++)
		for (int j=0;j<m;j++)
			cout<<i<<"->"<<son[j][i]<<" ["<<j<<"]"<<endl;
	for (int i=0;i<=nodecnt;i++) cout<<Val[i]<<" ";cout<<endl;
	//*/

	int nowlen=Llen;
	while (L[nowlen]==0) L[nowlen--]=m-1;
	L[nowlen]--;
	if (L[1]==0){
		for (int i=1;i<Llen;i++) L[i]=L[i+1];Llen--;
	}

	//cout<<Calc(Rlen,R)<<" "<<Calc(Llen,L)<<endl;

	printf("%d\n",(Calc(Rlen,R)+Mod-Calc(Llen,L))%Mod);

	return 0;
}

void Insert(int len){
	//cout<<"Insert:";for (int i=1;i<=len;i++) cout<<Seq[i];cout<<endl;
	int now=root;
	for (int i=1;i<=len;i++){
		if (son[Seq[i]][now]==0) son[Seq[i]][now]=++nodecnt;
		now=son[Seq[i]][now];
	}
	int val;scanf("%d",&val);
	Val[now]+=val;return;
}

void GetFail(){
	while (!Q.empty()) Q.pop();
	for (int i=0;i<m;i++) if (son[i][0]) Q.push(son[i][0]);
	while (!Q.empty()){
		int u=Q.front();Q.pop();
		for (int i=0;i<m;i++)
			if (son[i][u]){
				fail[son[i][u]]=son[i][fail[u]];
				Val[son[i][u]]+=Val[fail[son[i][u]]];
				Q.push(son[i][u]);
			}
			else son[i][u]=son[i][fail[u]];
	}
	return;
}

void Add(int &x,int y){
	x=(x+y)%Mod;return;
}

int Calc(int len,int Up[]){
	if (len==0) return 0;
	//cout<<"Calc: "<<len<<" ";for (int i=1;i<=len;i++) cout<<Up[i]<<" ";cout<<endl;
	mem(F,0);
	for (int i=1;i<=Up[1];i++)
		if (Val[son[i][0]]<=K) Add(F[(i==Up[1])][1][son[i][0]][Val[son[i][0]]],1);
	for (int i=2;i<=len;i++)
		for (int j=1;j<m;j++)
			if (Val[son[j][0]]<=K) Add(F[0][i][son[j][0]][Val[son[j][1]]],1);
	for (int i=1;i<len;i++)
		for (int j=0;j<=nodecnt;j++)
			for (int k=0;k<=K;k++)
				if ((F[0][i][j][k])||(F[1][i][j][k]))
					for (int p=0;p<m;p++){
						int c=son[p][j];
						if (k+Val[c]>K) continue;
						Add(F[0][i+1][c][k+Val[c]],F[0][i][j][k]);
						if (p<Up[i+1]) Add(F[0][i+1][c][k+Val[c]],F[1][i][j][k]);
						if (p==Up[i+1]) Add(F[1][i+1][c][k+Val[c]],F[1][i][j][k]);
					}

	/*
	for (int i=1;i<=len;i++){
		for (int j=0;j<=nodecnt;j++){
			cout<<"("<<i<<","<<j<<")"<<endl;
			for (int k=0;k<=K;k++)
				cout<<F[0][i][j][k]<<" "<<F[1][i][j][k]<<endl;
			cout<<endl;
		}
	}
	//*/
	int ret=0;
	for (int i=0;i<=nodecnt;i++) for (int j=0;j<=K;j++) Add(ret,(F[0][len][i][j]+F[1][len][i][j])%Mod);
	return ret;
}
