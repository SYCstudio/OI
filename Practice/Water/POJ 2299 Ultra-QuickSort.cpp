#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

const int maxsize=510000;

int N;
int cnt;
int A[maxsize];
int T[maxsize];

void Sort(int l,int r);

int main()
{
	while (cin>>N) {
		for (int i=1; i<=N; i++)
			cin>>A[i];
		cnt=0;
		Sort(1,N);
		cout<<cnt<<endl;
	}
	return 0;
}

void Sort(int l,int r)
{
	if (l==r) {
		return;
	}
	if (l+1==r) {
		if (A[l]>A[r]) {
			cnt++;
			swap(A[l],A[r]);
		}
		return;
	}
	int mid=(l+r)/2;
	Sort(l,mid);
	Sort(mid+1,r);
	memcpy(T+l,A+l,sizeof(int)*(l-r+1));
	int i=l,j=mid+1;


}
