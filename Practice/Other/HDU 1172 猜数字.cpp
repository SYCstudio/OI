#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

class Data
{
public:
	int num,rp,rc;
	//number,right_place,right_count
};

const int maxsize=101;
const int inf=2147483647;

int n;
Data T[maxsize];

bool Check(int x);
bool Check_(int x,int p);

int main()
{
	int ans;
	bool flag;

	while (cin>>n) {
		if (n==0)
			break;
		flag=0;
		for (int i=1; i<=n; i++) {
			cin>>T[i].num>>T[i].rc>>T[i].rp;
		}
		for (int i=1000; i<=9999; i++) {
			if (Check(i)==1) {
				if (flag) {
					flag=0;
					break;
				}
				flag=1;
				ans=i;
			}
		}
		//cout<<ans<<endl;
		if(flag)
			cout<<ans<<endl;
		else
			cout<<"Not sure"<<endl;
	}
}

bool Check(int x)
{
	bool flag=1;
	for (int i=1; i<=n; i++) {
		if (Check_(x,i)==0) {
			flag=0;
			break;
		}
	}
	return flag;
}

bool Check_(int x,int p)
{
	int Gn[10];//Guess number
	int Tn[10];//This number(p->number)
	int pnum=T[p].num;
	int prc=T[p].rc;
	int prp=T[p].rp;
	int Right_cnt=0;
	int Right_pos=0;
	for (int i=4; i>=1; i--) {
		Gn[i]=x%10;
		Tn[i]=pnum%10;
		x=x/10;
		pnum=pnum/10;
	}
	for (int i=1; i<=4; i++)
		if (Gn[i]==Tn[i])
			Right_pos++;
	for (int i=1; i<=4; i++)
		for (int j=1; j<=4; j++)
			if(Gn[i]==Tn[j]) {
				Right_cnt++;
				Tn[j]=-1;
				Gn[i]=-1;
				break;
			}
	//cout<<Right_cnt<<" "<<Right_pos<<endl;
	return (Right_cnt==prc)&&(Right_pos==prp);
}
