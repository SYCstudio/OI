#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=11;
const int inf=2147483647;

int N1[maxN],N2[maxN];
int Ten[maxN];

int main(){
	Ten[0]=1;for (int i=1;i<maxN;i++) Ten[i]=Ten[i-1]*10;
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int L,R;scanf("%d%d",&L,&R);
		int cnt1=0,cnt2=0;
		for (int key=L;key;key/=10) N1[++cnt1]=key%10;
		for (int key=R;key;key/=10) N2[++cnt2]=key%10;

		int Ans=inf,cnt=inf;
		if (cnt1==cnt2){
			int p=cnt1;
			for (p;p!=0;p--) if (N1[p]!=N2[p]) break;
			//cout<<"p:"<<p<<endl;
			if (p==0) Ans=L;
			else{
				int pre=0;
				//cout<<N1[p]<<" "<<N2[p]<<endl;
				for (int i=cnt1;i>=0;i--){
					for (int j=N1[i];j<=N2[i];j++)
						if ((pre+j*Ten[i-1]>=L)&&(pre+j*Ten[i-1]<=R)){
							if ((cnt1-i+1)*2-(j==5)<=cnt){
								if ((cnt1-i+1)*2-(j==5)==cnt) Ans=min(Ans,pre+j*Ten[i-1]);
								else Ans=pre+j*Ten[i-1];
								cnt=(cnt1-i+1)*2-(j==5);
							}
						}
					pre=pre+N1[i]*Ten[i-1];
				}
			}
		}
		else{
			for (int i=cnt1;i<=cnt2;i++)
				for (int j=0;j<=9;j++)
					if ((j*Ten[i-1]>=L)&&(j*Ten[i-1]<=R))
						if (2-(j==5)<=cnt){
							if (2-(j==5)==cnt) Ans=min(Ans,j*Ten[i-1]);
							else Ans=j*Ten[i-1];
							cnt=2-(j==5);
						}
		}
		printf("%d\n",Ans);
	}
	return 0;
}
