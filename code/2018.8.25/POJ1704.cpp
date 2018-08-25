#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int inf=2147483647;

int Seq[maxN];

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int n;scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);Seq[0]=0;
		sort(&Seq[1],&Seq[n+1]);
		int sum=0;
		for (int i=n,opt=1;i>=1;i--,opt^=1){
			sum^=(opt*(Seq[i]-Seq[i-1]-1));
			//cout<<opt*(Seq[i]-Seq[i-1])-1<<" ";
		}
		//cout<<endl;
		if (sum==0) printf("Bob will win\n");
		else printf("Georgia will win\n");
	}

	return 0;
}
