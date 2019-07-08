#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class Stick
{
public:
	int l,w;
};

const int maxsize=10000;
const int inf=2147483647l;

int n;
int Used[maxsize];
Stick S[maxsize];

bool cmp(Stick a,Stick b);

int main()
{
	int T;
	cin>>T;
	while (T--) {
		cin>>n;
		for (int i=1; i<=n; i++)
			cin>>S[i].l>>S[i].w;
		sort(&S[1],&S[n+1],cmp);
		mem(Used,0);
		int cnt=0;
		for (int i=1; i<=n; i++)
			if (Used[i]==0) {
				cnt++;
				Used[i]=cnt;
				int k=i;
				for (int j=i+1; j<=n; j++)
					if((Used[j]==0)&&(S[j].l>=S[k].l)&&(S[j].w>=S[k].w)) {
						Used[j]=cnt;
						k=j;
					}
			}
		cout<<cnt<<endl;
	}
	return 0;
}

bool cmp(Stick a,Stick b)
{
	if (a.l==b.l)
		return a.w<b.w;
	return a.l<b.l;
}
