#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

const int maxsize=30;
const int inf=2147483647;

int n,k1,k2;
int Cnt;
int Next[maxsize];
int Last[maxsize];
bool vis[maxsize];

inline void Out(int x,int y);

int main()
{
	while (cin>>n>>k1>>k2) {
		if ((n==0)&&(k1==0)&&(k2==0))
			break;
		memset(vis,0,sizeof(vis));
		for (int i=0; i<=n; i++) {
			Last[i]=i-1;
			Next[i]=i+1;
		}
		Last[1]=n;
		Next[n]=1;
		Cnt=n;
		int t1=1,t2=n;
		k1--;
		k2--;
		while (Cnt!=0) {
			//k1=(k1+Cnt)%Cnt;
			//k2=(k2+Cnt)%Cnt;
			for (int i=1; i<=k1; i++)
				t1=Next[t1];
			for (int i=1; i<=k2; i++)
				t2=Last[t2];
			if (t1==t2) {
				//cout<<"case1"<<endl;
				Last[Next[t1]]=Last[t1];
				Next[Last[t1]]=Next[t1];
				//Cnt--;
				Out(t1,-1);
				t1=Next[t1];
				t2=Last[t2];
				vis[t1]=1;
				//cout<<t1<<endl;
				//cout<<k1<<" "<<k2<<endl;
				Cnt--;
			} else if (t1==Last[t2]) {
				//cout<<"case2"<<endl;
				Next[Last[t1]]=Next[t2];
				Last[Next[t2]]=Last[t1];
				//Cnt=Cnt-2;
				Out(t1,t2);
				t1=Next[t2];
				t2=Last[t1];
				vis[t1]=vis[t2]=1;
				//cout<<t1<<" "<<t2<<endl;
				//cout<<k1<<" "<<k2<<endl;
				Cnt--;
				Cnt--;
			} else if (t1==Next[t2]) {
				//cout<<"case3"<<endl;
				Next[Last[t2]]=Next[t1];
				Last[Next[t1]]=Last[t2];
				//Cnt=Cnt-2;
				Out(t1,t2);
				t1=Next[t1];
				t2=Last[t2];
				vis[t1]=vis[t2]=1;
				//cout<<t1<<" "<<t2<<endl;
				//cout<<k1<<" "<<k2<<endl;
				Cnt--;
				Cnt--;
			} else {
				//cout<<"case4"<<endl;
				Last[Next[t1]]=Last[t1];
				Next[Last[t1]]=Next[t1];
				Last[Next[t2]]=Last[t2];
				Next[Last[t2]]=Next[t2];
				//Cnt=Cnt-2;
				Out(t1,t2);
				t1=Next[t1];
				t2=Last[t2];
				vis[t1]=vis[t2]=1;
				//cout<<t1<<" "<<t2<<endl;
				//cout<<k1<<" "<<k2<<endl;
				Cnt--;
				Cnt--;
			}
			/*for (int i=1;i<=n;i++)
			    cout<<i<<' ';
			cout<<endl;
			for (int i=1;i<=n;i++)
			    cout<<vis[i]<<' ';
			cout<<endl;
			for (int i=1;i<=n;i++)
			    cout<<Next[i]<<' ';
			cout<<endl;
			for (int i=1;i<=n;i++)
			    cout<<Last[i]<<' ';
			cout<<endl;
			cout<<endl;*/
		}
		cout<<endl;
	}
	return 0;
}

inline void Out(int x,int y)
{
	if (Cnt!=n)
		cout<<',';
	if (y==-1) {
		cout<<" ";
		if (x<10)
			cout<<" ";
		cout<<x;
	} else {
		cout<<' ';
		if (x<10)
			cout<<' ';
		cout<<x;
		cout<<' ';
		if (y<10)
			cout<<' ';
		cout<<y;
	}
	//cout<<endl;
	return;
}
