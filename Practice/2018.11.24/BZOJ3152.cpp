#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010000;
const int inf=2147483647;

int n;
int A[maxN];
priority_queue<int> H;

int Input();

int main(){
	int TTT=Input();
	while (TTT--){
		n=Input();for (int i=1;i<=n;i++) A[i]=Input();
		if (n==1){
			if (A[1]) printf("0\n");
			else printf("-1\n");
			continue;
		}
		if (A[1]==1){
			printf("-1\n");continue;
		}
		while (!H.empty()) H.pop();
		int k=A[1]-1,Ans=1;
		for (int i=2;i<=n;i++){
			if (k) --k;
			else{
				if ((H.empty())||(H.top()<=1)){
					Ans=-1;break;
				}
				k+=H.top()-2;H.pop();++Ans;
			}
			H.push(A[i]);
		}
		printf("%d\n",Ans);
	}
	return 0;
}

int Input(){
	char ch=getchar();int x=0;
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=x*10+ch-48,ch=getchar();
	return x;
}
