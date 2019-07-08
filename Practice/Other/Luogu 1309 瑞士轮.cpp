#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

class PEOPLE
{
public:
	int point,w,num;
};

bool operator < (PEOPLE a,PEOPLE b)
{
	if (a.point==b.point)
		return a.num<b.num;
	else
		return a.point>b.point;
}

const int maxN=1000001;
const int inf=2147483647;

int n,R,Q;
PEOPLE A[maxN*2];
PEOPLE K1[maxN*2];
PEOPLE K2[maxN*2];

int main()
{
	cin>>n>>R>>Q;
	for (int i=1; i<=n*2; i++)
		cin>>A[i].point;
	for (int i=1; i<=n*2; i++)
		cin>>A[i].w;
	for (int i=1; i<=n*2; i++)
		A[i].num=i;
	sort(&A[1],&A[2*n+1]);
	for (int i=1; i<=R; i++) {
		for (int j=1; j<=2*n; j=j+2) {
			if (A[j].w>A[j+1].w) {
				K1[j/2+1]=A[j];
				K2[j/2+1]=A[j+1];
				K1[j/2+1].point++;
			} else {
				K1[j/2+1]=A[j+1];
				K2[j/2+1]=A[j];
				K1[j/2+1].point++;
			}
		}
		int j1=1,j2=1;
		for (int j=1; j<=2*n; j++)
			if ((j2>n)|| ((j1<=n)&&((K1[j1].point>K2[j2].point)||((K1[j1].point==K2[j2].point)&&(K1[j1].num<K2[j2].num))) )     ) {
				A[j]=K1[j1];
				j1++;
			} else {
				A[j]=K2[j2];
				j2++;
			}
	}
	cout<<A[Q].num<<endl;
	return 0;
}
