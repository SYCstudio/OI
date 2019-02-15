#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int inf=2147483647;

int n;
ll Num[maxN];
bool Empty[maxN];
int St[maxN];
ll Sorter[maxN];

int main(){
	ll sum=0,res=0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&Num[i]),sum+=Num[i],Empty[i]=(Num[i]==0);

	int top=0,scnt=0;
	int p1,p2;
	for (p1=1;Empty[p1]==0;p1++){
		St[++top]=p1;
		while ((top>=3)&&(Num[St[top]]<=Num[St[top-1]])&&(Num[St[top-2]]<=Num[St[top-1]])){
			Num[St[top-2]]=Num[St[top-2]]+Num[St[top]]-Num[St[top-1]];
			top-=2;
		}
	}
	
	while ((top>=1)&&((top==1)||(Num[St[top]]>=Num[St[top-1]]))){
		Sorter[++scnt]=Num[St[top]];top--;
	}
	if (top&1) Sorter[++scnt]=Num[St[top--]];
	for (int i=1;i<=top;i+=2) res=res+Num[St[i+1]]-Num[St[i]];

	top=0;
	for (p2=n;Empty[p2]==0;p2--){
		St[++top]=p2;
		while ((top>=3)&&(Num[St[top]]<=Num[St[top-1]])&&(Num[St[top-2]]<=Num[St[top-1]])){
			Num[St[top-2]]=Num[St[top-2]]+Num[St[top]]-Num[St[top-1]];
			top-=2;
		}
	}
	while ((top>=1)&&((top==1)||(Num[St[top]]>=Num[St[top-1]]))){
		Sorter[++scnt]=Num[St[top]];top--;
	}
	if (top&1) Sorter[++scnt]=Num[St[top--]];
	for (int i=1;i<=top;i+=2) res=res+Num[St[i+1]]-Num[St[i]];

	top=0;
	for (int i=p1;i<=p2;i++)
		if (Empty[i]==0){
			St[++top]=i;
			while ((top>=3)&&(Num[St[top]]<=Num[St[top-1]])&&(Num[St[top-2]]<=Num[St[top-1]])){
				Num[St[top-2]]=Num[St[top-2]]+Num[St[top]]-Num[St[top-1]];
				top-=2;
			}
		}
		else while (top) Sorter[++scnt]=Num[St[top--]];

	sort(&Sorter[1],&Sorter[scnt+1]);
	reverse(&Sorter[1],&Sorter[scnt+1]);

	if (scnt&1) res=-res;

	for (int i=1;i<=scnt;i++)
		if (i&1) res=res+Sorter[i];
		else res=res-Sorter[i];

	printf("%lld %lld\n",(sum+res)/2,(sum-res)/2);

	return 0;
}
