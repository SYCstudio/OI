#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=401;
const int inf=2147483647;

int n,m;
int Cnt[maxN],Tot[maxN];

bool Check();

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=3*m+1;i++){
		int key;scanf("%d",&key);Cnt[key]++;
	}

	int getans=0;
	for (int i=1;i<=n;i++){
		Cnt[i]++;
		if (Check()){
			printf("%d ",i);getans=1;
		}
		Cnt[i]--;
	}

	if (getans==0) printf("NO\n");

	return 0;
}

bool Check()
{
	for (int i=1;i<=n;i++)
		if (Cnt[i]>=2){
			bool flag=1;
			Cnt[i]-=2;

			for (int j=1;j<=n;j++) Tot[j]=Cnt[j];
			for (int j=1;j<=n;j++){
				Tot[j]%=3;
				int k=Tot[j];
				if ((Tot[j+1]<k)||(Tot[j+2]<k)){
					flag=0;break;
				}
				Tot[j+1]-=k;Tot[j+2]-=k;
			}
			
			Cnt[i]+=2;

			if (flag) return 1;
		}
	return 0;
}
