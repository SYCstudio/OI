#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1510;
const int maxM=maxN*maxN;
const int inf=2147483647;

class Data
{
public:
	ll mx,my,x,y,d;
};

int n,m;
int X[maxN],Y[maxN];
Data D[maxM];

bool cmp(Data A,Data B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&X[i],&Y[i]);
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++){
			m++;
			D[m]=((Data){X[i]+X[j],Y[i]+Y[j],X[i],Y[i],1ll*(X[i]-X[j])*(X[i]-X[j])+1ll*(Y[i]-Y[j])*(Y[i]-Y[j])});
		}
	sort(&D[1],&D[m+1],cmp);

	for (int i=1,j;i<=n;i=j+1){
		j=i;
		
	}
}

bool cmp(Data A,Data B){
	if (A.mx!=B.mx) return A.mx<B.mx;
	if (A.my!=B.my) return A.my<B.my;
	if (A.d!=B.d) return A.d<B.d;
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}
