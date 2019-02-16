#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
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
ll X[maxN],Y[maxN];
Data D[maxM];

bool cmp(Data A,Data B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&X[i],&Y[i]);
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++){
			m++;
			D[m]=((Data){X[i]+X[j],Y[i]+Y[j],X[i],Y[i],1ll*(X[i]-X[j])*(X[i]-X[j])+1ll*(Y[i]-Y[j])*(Y[i]-Y[j])});
			//cout<<i<<" "<<j<<":"<<D[m].mx<<" "<<D[m].my<<" "<<D[m].d<<","<<X[i]<<" "<<Y[i]<<" "<<X[j]<<" "<<Y[j]<<endl;
		}
	//cout<<endl;
	sort(&D[1],&D[m+1],cmp);
	//for (int i=1;i<=m;i++) cout<<D[i].mx<<" "<<D[i].my<<" "<<D[i].d<<endl;

	ll Ans=0;
	for (int i=1,j;i<=m;i=j+1){
		j=i;
		while ((j<m)&&(D[j+1].mx==D[i].mx)&&(D[j+1].my==D[i].my)&&(D[j+1].d==D[i].d)) j++;
		//cout<<i<<" "<<j<<endl;
		for (int p=i;p<=j;p++)
			for (int q=i+1;q<=j;q++){
				ll x1=D[p].x,y1=D[p].y,x2=D[p].mx-D[p].x,y2=D[p].my-D[p].y;
				ll x3=D[q].x,y3=D[q].y,x4=D[q].mx-D[q].x,y4=D[q].my-D[q].y;
				ll a=x4-x1,b=y4-y1,c=x3-x1,d=y3-y1;
				Ans=max(Ans,abs(a*d-b*c));
			}
	}
	printf("%lld\n",Ans);
	return 0;
}

bool cmp(Data A,Data B){
	if (A.mx!=B.mx) return A.mx<B.mx;
	if (A.my!=B.my) return A.my<B.my;
	if (A.d!=B.d) return A.d<B.d;
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}
