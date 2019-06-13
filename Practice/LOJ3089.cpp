#include<bits/stdc++.h>
using namespace std;

const int maxN=1510;
const int Alpha=10;
const double eps=1e-9;
const double inf=1e18;

int n,m;
int son[maxN][Alpha],fail[maxN];
int tcnt=1,Fr[maxN][maxN],cnt[maxN];
char str[maxN],in[maxN];
double F[maxN][maxN],Key[maxN];

void Calc(double val);
void Outp(int d,int u);
int main(){
    scanf("%d%d",&n,&m);scanf("%s",str+1);
    while (m--){
	scanf("%s",in+1);int len=strlen(in+1),now=1,key;scanf("%d",&key);
	for (int i=1;i<=len;i++){
	    if (son[now][in[i]-'0']==0) son[now][in[i]-'0']=++tcnt;
	    now=son[now][in[i]-'0'];
	}
	Key[now]+=log(key);++cnt[now];
    }
    queue<int> Qu;
    for (int i=0;i<Alpha;i++) if (son[1][i]) Qu.push(son[1][i]);else son[1][i]=1;
    while (!Qu.empty()){
	int u=Qu.front();Qu.pop();
	for (int i=0;i<Alpha;i++)
	    if (son[u][i]){
		fail[son[u][i]]=son[fail[u]][i];Key[son[u][i]]+=Key[son[fail[u]][i]];cnt[son[u][i]]+=cnt[son[fail[u]][i]];
		Qu.push(son[u][i]);
	    }
	    else son[u][i]=son[fail[u]][i];
    }
    for (int i=1;i<=tcnt;i++) cout<<Key[i]<<" ";cout<<endl;
    for (int i=1;i<=tcnt;i++) cout<<cnt[i]<<" ";cout<<endl;
    double l=0,r=1e18,Ans;
    while (l+eps<r){
	double mid=(l+r)/2;
	Calc(mid);double mx=-inf;
	for (int i=1;i<=tcnt;i++) mx=max(mx,F[n][i]);
	//cout<<l<<" "<<r<<":"<<mx<<endl;
	if (mx>=0) Ans=mid,r=mid-eps;else l=mid+eps;
    }
    cout<<"Ans:"<<Ans<<endl;
    Calc(Ans);int ansu=1;for (int i=1;i<=tcnt;i++) if (F[n][ansu]<F[n][i]) ansu=i;
    Outp(n,ansu);
    return 0;
}
void Calc(double val){
    for (int i=1;i<=n;i++) for (int j=1;j<=tcnt;j++) F[i][j]=-inf,Fr[i][j]=0;
    F[0][1]=0;Fr[0][1]=0;
    for (int i=1;i<=n;i++){
	for (int j=1;j<=tcnt;j++)
	    if (str[i]=='.')
		for (int k=0;k<Alpha;k++){
		    int v=son[j][k];
		    if (F[i][v]<F[i-1][j]+Key[v]-val*cnt[v]){
			cout<<i-1<<" "<<j<<"->"<<i<<" "<<v<<":"<<F[i-1][j]<<" "<<Key[v]<<" "<<-val*cnt[v]<<endl;
			F[i][v]=F[i-1][j]+Key[v]-val*cnt[v];
			Fr[i][v]=j;
		    }
		}
	    else{
		int v=son[j][str[i]-'0'];
		if (F[i][v]<F[i-1][j]+Key[v]-val*cnt[v]){
		    F[i][v]=F[i-1][j]+Key[v]-val*cnt[v];
		    Fr[i][v]=j;
		}
	    }
    }
    cout<<"Calc at:"<<val<<endl;
    for (int i=1;i<=n;i++){
	for (int j=1;j<=tcnt;j++) cout<<F[i][j]<<" ";
	cout<<endl;
    }
    return;
}
void Outp(int d,int u){
    if (d==0) return;
    Outp(d-1,Fr[d][u]);
    for (int i=0;i<Alpha;i++)
	if (son[Fr[d][u]][i]==u){
	    printf("%d",i);return;
	}
    return;
}
