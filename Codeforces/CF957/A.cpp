#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200;
const int inf=2147483647;

int L;
char str[maxN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>L;
	cin>>(str+1);
	bool wenhao=0,flag=0;
	char col=0;str[0]=str[L+1]=0;
	for (int i=1;i<=L+1;i++)
	{
		//cout<<i<<endl;
		if (str[i]=='?') wenhao=1;
		if ((str[i]!='?')&&(str[i-1]!='?')&&(str[i]!=0)&&(str[i-1]!=0)&&(str[i]==str[i-1])){
			flag=0;break;
		}
		if ((str[i]=='?')&&(str[i-1]!='?')){
			//cout<<"C1:"<<i<<endl;
			col=str[i-1];continue;
		}
		if ((str[i]!='?')&&(str[i-1]=='?')){
			//cout<<"C2:"<<i<<endl;
			if ((col==str[i])||(col==0)||(str[i]==0)){
				flag=1;
			}
		}
	}
	if (wenhao==0) cout<<"No"<<endl;
	else if (flag==0) cout<<"No"<<endl;
	else cout<<"Yes"<<endl;
	return 0;
}
