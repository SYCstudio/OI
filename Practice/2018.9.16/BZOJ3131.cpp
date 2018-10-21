#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=501000;
const int Mod=1000000007;
const int inf=2147483647;

class HData
{
public:
	ll key;
	int id;
};

int len,N[20];
ll F[2][20][maxN];
ll numcnt,Num[maxN];
ll Sum[maxN],Lst[maxN],Id[maxN];
priority_queue<HData> H;

void dfs(int lst,int cnt,ll mul);
bool operator < (HData A,HData B);

int main(){
	ll n,K;scanf("%lld%lld",&n,&K);
	while (n){
		N[++len]=n%10;
		n/=10;
	}

	dfs(1,0,1);Num[++numcnt]=0;
	sort(&Num[1],&Num[numcnt+1]);numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;

	//for (int i=1;i<=len;i++) cout<<N[i]<<" ";cout<<endl;

	F[0][0][Find(1)]=1;
	for (int i=0;i<len;i++)
		for (int j=1;j<=numcnt;j++)
			for (int k=0;k<=1;k++)
				if (F[k][i][j]){
					for (int p=(i==0)?0:1;p<=9;p++)
						F[k+p>N[i+1]][i+1][Find(Num[j]*p)]+=F[k][i][j];
				}

	for (int i=1;i<=numcnt;i++){
		for (int j=1;j<len;j++) Sum[i]+=F[0][j][i]+F[1][j][i];
		Sum[i]+=F[0][len][i];
	}

	/*
	for (int i=1;i<=10;i++){
		cout<<Num[i]<<" "<<Sum[i]<<endl;
		for (int j=1;j<=len;j++) cout<<F[0][j][i]<<" "<<F[1][j][i]<<endl;
		cout<<endl;
	}

	cout<<numcnt<<endl;
	//for (int i=1;i<=numcnt;i++) cout<<Num[i]<<" "<<Sum[i]<<endl;
	//*/
	Sum[Find(0)]=0;

	sort(&Sum[1],&Sum[numcnt+1]);
	reverse(&Sum[1],&Sum[numcnt+1]);

	for (int i=1;i<=numcnt;i++) H.push((HData){Sum[1]*Sum[i],i}),Lst[i]=1;

	ll Ans=0;
	while (!H.empty()&&(K--)){
		HData h=H.top();H.pop();
		Ans=(Ans+h.key)%Mod;
		//cout<<h.key<<endl;
		if (Lst[h.id]!=numcnt){
			H.push((HData){Sum[h.id]*Sum[Lst[h.id]+1],h.id});
			Lst[h.id]++;
		}
	}

	printf("%lld\n",Ans%Mod);
	return 0;
}

void dfs(int lst,int cnt,ll mul){
	if (cnt==len+1){
		Num[++numcnt]=mul;return;
	}
	for (int i=lst;i<=9;i++)
		dfs(i,cnt+1,mul*i);
	return;
}

bool operator < (HData A,HData B){
	return A.key<B.key;
}

