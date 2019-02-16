#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210;
const int maxAlpha=26;
const int maxBit=48;
const int inf=2147483647;
const ll INF=1e16;

int n;
ll L;
int nodecnt=0,root=0;
int son[maxAlpha][maxN],fail[maxN],sum[maxN];
ll Mat[maxBit][maxN][maxN],Ans[maxN][maxN],Bp[maxN][maxN];
int Val[maxN];
char Input[maxN];
queue<int> Q;

void GetFail();
void Mul(int b);

int main(){
	scanf("%d%lld",&n,&L);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]);
	for (int i=1;i<=n;i++){
		scanf("%s",Input+1);
		int now=root,len=strlen(Input+1);
		for (int j=1;j<=len;j++){
			if (son[Input[j]-'a'][now]==0) son[Input[j]-'a'][now]=++nodecnt;
			now=son[Input[j]-'a'][now];
		}
		sum[now]+=Val[i];
	}

	/*
	for (int i=0;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (son[j][i]) cout<<i<<"->"<<son[j][i]<<" ["<<(char)(j+'a')<<"]"<<endl;
	cout<<endl;
	//*/

	GetFail();

	/*
	for (int i=0;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			cout<<i<<"->"<<son[j][i]<<" ["<<(char)(j+'a')<<"]"<<endl;
	cout<<endl;
	//*/
	
	for (int k=0;k<maxBit;k++) for (int i=0;i<=nodecnt;i++) for (int j=0;j<=nodecnt;j++) Mat[k][i][j]=-INF;

	for (int i=0;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++){
			if (Mat[0][i][son[j][i]]==-INF) Mat[0][i][son[j][i]]=0;
			Mat[0][i][son[j][i]]+=sum[son[j][i]];
			//cout<<i<<"->"<<son[j][i]<<" "<<Mat[0][i][son[j][i]]<<endl;
		}

	/*
	for (int i=0;i<=nodecnt;i++){
		for (int j=0;j<=nodecnt;j++)
			//if (Mat[0][i][j]==-INF) printf(" -INF");
			printf("%5lld",Mat[0][i][j]);
		printf("\n");
	}
	//*/

	for (int i=0;i<=nodecnt;i++) for (int j=0;j<=nodecnt;j++) Ans[i][j]=Mat[0][i][j];

	for (int b=1;b<maxBit;b++)
		for (int k=0;k<=nodecnt;k++)
			for (int i=0;i<=nodecnt;i++)
				for (int j=0;j<=nodecnt;j++){
					Mat[b][i][j]=max(Mat[b][i][j],Mat[b-1][i][k]+Mat[b-1][k][j]);
					//cout<<"b:"<<b<<" "<<i<<"->"<<k<<"->"<<j<<" "<<Mat[b-1][i][k]<<" "<<Mat[b-1][k][j]<<endl;

					}
	/*
	for (int b=0;b<=3;b++)
	{
		for (int i=0;i<=nodecnt;i++){
			for (int j=0;j<=nodecnt;j++)
				if (Mat[b][i][j]==-INF) printf("-INF");
				else printf("%5lld",Mat[b][i][j]);
			printf("\n");
		}
		printf("\n");
	}
	//*/
	L--;
	for (int i=maxBit-1;i>=0;i--)
		if ((1ll<<i)&L) Mul(i);

	ll ans=-INF;
	for (int i=0;i<=nodecnt;i++) ans=max(ans,Ans[0][i]);

	printf("%lld\n",ans);

	return 0;
}

void GetFail(){
	for (int i=0;i<maxAlpha;i++) if (son[i][0]) Q.push(son[i][0]);
	while (!Q.empty()){
		int u=Q.front();Q.pop();
		for (int i=0;i<maxAlpha;i++)
			if (son[i][u]){
				fail[son[i][u]]=son[i][fail[u]];
				sum[son[i][u]]+=sum[fail[son[i][u]]];
				Q.push(son[i][u]);
			}
			else son[i][u]=son[i][fail[u]];
	}
	return;
}

void Mul(int b){
	//cout<<"Mul:"<<b<<endl;
	for (int i=0;i<=nodecnt;i++) for (int j=0;j<=nodecnt;j++) Bp[i][j]=Ans[i][j],Ans[i][j]=-INF;
	for (int k=0;k<=nodecnt;k++)
		for (int i=0;i<=nodecnt;i++)
			for (int j=0;j<=nodecnt;j++)
				Ans[i][j]=max(Ans[i][j],Bp[i][k]+Mat[b][k][j]);
	return;
}
