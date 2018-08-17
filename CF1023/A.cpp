#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210000;
const int inf=2147483647;

int n,m;
char S[maxN],T[maxN];

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",S+1);scanf("%s",T+1);
	int pos=-1;
	for (int i=1;i<=n;i++) if (S[i]=='*') pos=i;
	if (pos==-1){
		if (n!=m){
			printf("NO\n");return 0;
		}
		for (int i=1;i<=n;i++)
			if (S[i]!=T[i]){
				printf("NO\n");return 0;
			}
		printf("YES\n");return 0;
	}
	int j1=0,j2=m+1;
	for (int i=1;i<pos;i++){
		j1++;
		if (j1>m){
			printf("NO\n");return 0;
		}
		if (S[i]!=T[j1]){
			printf("NO\n");return 0;
		}
	}
	for (int i=n;i>pos;i--){
		j2--;
		if (j2<=0){
			printf("NO\n");return 0;
		}
		if (S[i]!=T[j2]){
			printf("NO\n");return 0;
		}
	}
	//cout<<j1<<" "<<j2<<endl;
	if (j1<=j2) printf("YES\n");
	else printf("NO\n");
	return 0;
}
