#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int inf=2147483647;

int n,m;

int Input();

/*
namespace St1
{
	const int maxN=110000;
	const int maxM=10100;

	bitset<maxM> B[maxN];

	int main();
}
//*/

namespace St2
{
#define ld long double
	const int maxN=1110000;
	const int maxM=101000;
	const int maxSize=50;
	const int maxRange=1000000007;

	int Fr[maxN][2];
	ld Ans[maxN];
	int Key[maxN][maxSize+5];
	
	int main();
	int Random();
	void Work();
}

int main(){
	//freopen("2.in","r",stdin);freopen("out","w",stdout);
	n=Input();m=Input();
	//if ((n<=100000)&&(m<=10000)) St1::main();
	St2::main();
}

int Input(){
	int x=0;char ch=getchar();
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=x*10+ch-48,ch=getchar();
	return x;
}
/*
namespace St1
{
	int main(){
		for (int i=1;i<=m;i++) B[i][i]=1;
		for (int i=m+1;i<=n;i++){
			int u=Input(),v=Input();
			B[i]=B[u]|B[v];
			printf("%d\n",(int)B[i].count());
		}
		return 0;
	}
}
//*/
namespace St2
{
	int main(){
		for (int i=m+1;i<=n;i++) Fr[i][0]=Input(),Fr[i][1]=Input();
		ld starttime=(ld)clock();//cout<<starttime<<" "<<CLOCKS_PER_SEC<<endl;
		//Work();//for (int i=m+1;i<=n;i++) Ans[i]=(ld)maxSize*(ld)maxRange/(ld)Key[i][Key[i][0]];
		int tcnt=0;
		//Work();return 0;
		while (1){
			//cout<<(ld)clock()-starttime<<endl;
			if (clock()-starttime>=1.7*CLOCKS_PER_SEC) break;
			Work();++tcnt;
		}
		for (int i=m+1;i<=n;i++) Ans[i]=Ans[i]/(ld)tcnt;
		for (int i=m+1;i<=n;i++) printf("%d\n",(int)(Ans[i]+0.5));
		return 0;
	}

	
	int Random(){
		ld dou=1.0*rand()/RAND_MAX;
		return dou*(maxRange)+1;
	}
	//*/

	void Work(){
		//cout<<"Work:"<<endl;
		for (int i=1;i<=m;i++) Key[i][0]=1,Key[i][1]=Random();
		for (int i=m+1;i<=n;i++){
			//cout<<i<<endl;
			int j1=1,j2=1,p=1;
			while ( ((j1<=Key[Fr[i][0]][0])||(j2<=Key[Fr[i][1]][0])) && (p<=maxSize)){
				if ((j2>Key[Fr[i][1]][0])||((j1<=Key[Fr[i][0]][0])&&(Key[Fr[i][0]][j1]<=Key[Fr[i][1]][j2]))){
					if ((j2<=Key[Fr[i][1]][0])&&(Key[Fr[i][0]][j1]==Key[Fr[i][1]][j2])) ++j2;
					Key[i][p++]=Key[Fr[i][0]][j1++];
				}
				else Key[i][p++]=Key[Fr[i][1]][j2++];
			}
			Key[i][0]=p-1;
		}
		/*
		for (int i=m+1;i<=n;i++){
			cout<<Key[i][0]<<":";for (int j=1;j<=Key[i][0];j++) cout<<Key[i][j]<<" ";cout<<endl;
		}
		//*/
		for (int i=m+1;i<=n;i++) //Ans[i]+=((ld)Key[i][0]*(ld)maxRange/(ld)Key[i][Key[i][0]]);
			Ans[i]+=(Key[i][0]==maxSize)?((ld)maxSize/(ld)(Key[i][Key[i][0]])*(ld)maxRange):(Key[i][0]);
		return;
	}
}
