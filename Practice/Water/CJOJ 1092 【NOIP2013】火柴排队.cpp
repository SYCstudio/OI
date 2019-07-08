#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

class Height
{
public:
	int height,position;
};

const int maxsize=100001;
const int P=99999997;
const int inf=2147483647;

int n;
long long Ans=0;
Height A[maxsize],B[maxsize];
int C[maxsize];
int D[maxsize];

bool cmp(Height a,Height b);
void Sort(int l,int r);

int main()
{
	cin>>n;
	for (int i=1; i<=n; i++) {
		cin>>A[i].height;
		A[i].position=i;
	}
	for (int i=1; i<=n; i++) {
		cin>>B[i].height;
		B[i].position=i;
	}
	sort(&A[1],&A[n+1],cmp);
	sort(&B[1],&B[n+1],cmp);
	for (int i=1; i<=n; i++)
		C[A[i].position]=B[i].position;
	Sort(1,n);
	cout<<Ans<<endl;
}

bool cmp(Height a,Height b)
{
	return a.height<b.height;
}

void Sort(int l,int r)
{
	if (l==r)
		return;
	int mid=(l+r)/2;
	Sort(l,mid);
	Sort(mid+1,r);
	int pos1=l;
	int pos2=mid+1;
	for (int i=l; i<=r; i++) {
		if (((C[pos1]<=C[pos2])&&(pos1<=mid)) || ((pos2>r))) {
			D[i]=C[pos1];
			pos1++;
		} else {
			D[i]=C[pos2];
			pos2++;
			Ans=Ans+(mid+1)-pos1;
			Ans=Ans%P;
			//cout<<pos1<<' '<<mid<<' '<<Ans<<endl;
		}
	}
	for (int i=l; i<=r; i++)
		C[i]=D[i];
	return;
}
