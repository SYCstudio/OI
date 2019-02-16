#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200010;
const int inf=2147483647;

class Pos
{
public:
	int x,y;
};

int n;
ll Ans;
Pos P[maxN],Backup[maxN];
int Queue1[maxN],Queue2[maxN];

bool cmp(Pos A,Pos B);
void Solve(int l,int r);

int main()
{
	ios::sync_with_stdio(false);

	cin>>n;
	for (int i=1;i<=n;i++) cin>>P[i].x>>P[i].y;
	sort(&P[1],&P[n+1],cmp);

	Solve(1,n);

	cout<<Ans<<endl;
	return 0;
}

bool cmp(Pos A,Pos B)
{
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}

void Solve(int L,int R)
{
	if (L==R) return;
	int mid=(L+R)>>1;
	Solve(L,mid);Solve(mid+1,R);

	//cout<<"["<<L<<","<<R<<"] "<<mid<<endl;
	//for (int i=L;i<=R;i++) cout<<"("<<P[i].x<<","<<P[i].y<<") ";cout<<endl;
	int h1=0,h2=0;
	int nowans=0;
	for (int i=L,j=mid+1;i<=mid;i++)
	{
		while ((h1!=0)&&(P[Queue1[h1]].x<P[i].x)) h1--;
		Queue1[++h1]=i;
		while ((j<=R)&&(P[j].y>P[i].y))
		{
			while ((h2!=0)&&(P[Queue2[h2]].x>P[j].x)) h2--;
			Queue2[++h2]=j;j++;
		}
		if (h2==0) continue;
		//if ((h2!=0)&&(P[Queue1[h1]].x==Queue2[1])) continue;
		//cout<<"Q1:";for (int k=1;k<=h1;k++) cout<<"("<<P[Queue1[k]].x<<","<<P[Queue1[k]].y<<") ";cout<<endl;
		//cout<<"Q2:";for (int k=1;k<=h2;k++) cout<<"("<<P[Queue2[k]].x<<","<<P[Queue2[k]].y<<") ";cout<<endl;
		int p1,p2;
		int l=0,r=h2;
		//cout<<"y:"<<P[i].y<<endl;
		P[0].y=inf;
		while (l<=r)
		{
			int mid=(l+r)>>1;
			if (P[Queue2[mid]].y>P[i].y){
				p1=mid;l=mid+1;
			}
			else r=mid-1;
		}
		if (h1==1) p2=1;
		else
		{
			l=1,r=h2+1;P[0].y=0;Queue2[h2+1]=0;P[0].x=-10;
			while (l<=r)
			{
				int mid=(l+r)>>1;
				if (P[Queue2[mid]].y<=P[Queue1[h1-1]].y){
					p2=mid;r=mid-1;
				}
				else l=mid+1;
				//cout<<"["<<l<<","<<r<<"]"<<endl;
			}
		}
		//while (P[Queue2[p2]].x==P[i].x) p2++;
		//cout<<p1<<" "<<p2<<endl;
		if (p1>=p2) nowans+=(p1-p2+1),Ans+=(p1-p2+1);
	}
	//cout<<"nowAns:"<<nowans<<endl<<endl;
	int p1=L,p2=mid+1;
	for (int i=L;i<=R;i++)
		if ((p1<=mid)&&((p2>R)||(P[p1].y>P[p2].y)))
			Backup[i]=P[p1++];
		else Backup[i]=P[p2++];
	for (int i=L;i<=R;i++) P[i]=Backup[i];
	return;
}
