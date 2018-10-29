#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll int
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=1010000;
const int Mod=19940417;
const int Pri[2]={7,2848631};
const int inf=2147483647;

int n,K;
int Fc[2][2910000],Fi[2][2910000],pi[2];
pair<int,int> P[maxN];

IL int Input();
IL int QPow(RG int x,RG int cnt,RG int p);
IL int C(RG int n,RG int m);
IL int Lucas(RG int n,RG int m,RG int id);

int main(){
	RG int i,j;
	for (i=0;i<=1;++i){
		Fc[i][0]=Fi[i][0]=1;pi[i]=QPow(Mod/Pri[i],Pri[i]-2,Pri[i]);
		for (j=1;j<Pri[i];++j) Fc[i][j]=1ll*Fc[i][j-1]*j%Pri[i];
		Fi[i][Pri[i]-1]=QPow(Fc[i][Pri[i]-1],Pri[i]-2,Pri[i]);
		for (j=Pri[i]-2;j>=1;--j) Fi[i][j]=1ll*Fi[i][j+1]*(j+1)%Pri[i];
	}
	n=Input();K=Input();
	//scanf("%d%d",&n,&K);
	for (i=1;i<=K;++i) P[i].first=Input(),P[i].second=Input();//scanf("%d%d",&P[i].first,&P[i].second);
	P[++K]=make_pair(0,0);P[++K]=make_pair(n,0);

	sort(&P[1],&P[K+1]);K=unique(&P[1],&P[K+1])-P-1;
	//cout<<"P:"<<endl;
	//for (int i=1;i<=K;i++) cout<<"("<<P[i].first<<","<<P[i].second<<")"<<endl;

	RG int Ans1=1,Ans2=0,x1,y1,x2,y2,b,d,ret;
	for (i=2;i<=K;++i){
		x1=P[i-1].first;y1=P[i-1].second;x2=P[i].first;y2=P[i].second;
		b=(x2+y2-x1+y1)/2;Ans2=max(Ans2,b);
		d=y1+y2-b;
		//cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
		ret=C(x2-x1,b-y1);
		//cout<<"r1:"<<C(x2-x1,a-x1)<<endl;
		if (d<0) ret=(ret-C(x2-x1,-d-1)+Mod)%Mod;
		//cout<<i<<" "<<ret<<endl;
		Ans1=1ll*Ans1*ret%Mod;
	}
	printf("%d %d\n",Ans1,Ans2);return 0;
}

IL int Input(){
	RG int x=0;RG char ch=getchar();
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=x*10+ch-48,ch=getchar();
	return x;
}

IL int QPow(RG int x,RG int cnt,RG int p){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%p;
		x=1ll*x*x%p;cnt>>=1;
	}
	return ret;
}

IL int C(RG int n,RG int m){
	//cout<<"GetC:"<<n<<" "<<m<<endl;
	RG int ret=0;
	for (RG int i=0;i<=1;++i) ret=(ret+1ll*Lucas(n,m,i)*pi[i]%Mod*(Mod/Pri[i])%Mod)%Mod;
	//cout<<ret<<endl;
	return ret;
}

IL int Lucas(RG int n,RG int m,RG int id){
	if ((n<m)||(n<0)||(m<0)) return 0;
	if (n<Pri[id]) return 1ll*Fc[id][n]*Fi[id][m]%Pri[id]*Fi[id][n-m]%Pri[id];
	return 1ll*Lucas(n%Pri[id],m%Pri[id],id)*Lucas(n/Pri[id],m/Pri[id],id)%Pri[id];
}
