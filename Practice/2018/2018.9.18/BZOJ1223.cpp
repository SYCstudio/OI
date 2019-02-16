#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510;
const int inf=2147483647;

class Bigint
{
public:
	int num[maxN],len;
	Bigint(){
		mem(num,0);len=1;return;
	}

	Bigint(char *s){
		len=strlen(s);for (int i=0;i<len;i++) num[len-i]=s[i]-'0';
		return;
	}
	
	void MainTain(){
		for (int i=1;i<len;i++) num[i+1]+=num[i]/10,num[i]%=10;
		while (num[len]>=10) num[len+1]+=num[len]/10,num[len]%=10,len++;
		return;
	}
	
	Bigint & operator = (int A){
		mem(num,0);num[len=1]=A;MainTain();
		return *this;
	}
	
	Bigint & operator = (Bigint A){
		mem(num,0);
		len=A.len;for (int i=1;i<=len;i++) num[i]=A.num[i];
		return *this;
	}

	Bigint & operator = (char *s){
		mem(num,0);
		len=strlen(s);for (int i=0;i<len;i++) num[len-i]=s[i]-'0';
		return *this;
	}

	int low(){
		return num[1]&1;
	}

	void Right(){
		for (int i=len;i>1;i--) num[i-1]+=(num[i]&1)*10,num[i]>>=1;
		num[1]>>=1;
		while ((num[len]==0)&&(len>1)) len--;
		return;
	}

	void Left(){
		for (int i=1;i<=len;i++) num[i]<<=1;
		MainTain();return;
	}

	void Outp(){
		for (int i=len;i>=1;i--) printf("%d",num[i]);
		printf("\n");
		return;
	}
};

char Input[maxN];
Bigint B;
int bn=0,Bt[maxN*maxN];

Bigint operator + (Bigint A,Bigint B);
Bigint operator + (Bigint A,int B);
Bigint operator - (Bigint A,int B);

int main(){
	/*
	Bigint SA,SB;SA=0;SB=0;
	scanf("%s",Input);
	SA=Input;
	scanf("%s",Input);
	SB=Input;
	SA=SA+SB;SA.Outp();
	SA.Right();SA.Outp();
	//*/
	
	scanf("%s",Input);
	B=Input;
	while ((B.num[1])||(B.len>1)){
		Bt[++bn]=B.low();B.Right();
	}
	//for (int i=1;i<=bn;i++) cout<<Bt[i];cout<<endl;
	if (bn<=1){
		printf("%d\n",bn);return 0;
	}

	int mid=(bn+1)>>1;
	Bigint Ans,Tot;Ans=0;Tot=1;
	for (int i=1;i<bn;i++){
		Ans=Ans+Tot;
		if ((i&1)==0) Tot.Left();
	}
	//cout<<"less than "<<bn<<":";Ans.Outp();

	Tot=0;
	for (int i=bn-1;i>=bn-mid+1;i--) Tot.Left(),Tot=Tot+Bt[i];
	//cout<<bn-1<<" "<<bn-mid+1<<endl;
	//cout<<"after tot left:";Tot.Outp();
	bool flag=1;
	for (int i=mid;i>=1;i--)
		if (Bt[i]!=Bt[bn-i+1]){
			flag=Bt[bn-i+1]<Bt[i];break;
		}
	if (flag) Tot=Tot+1;
	//cout<<"flag:"<<flag<<endl;
	Ans=Ans+Tot;

	Ans.Outp();return 0;
}

Bigint operator + (Bigint A,Bigint B){
	Bigint ret;
	ret.len=max(A.len,B.len);
	for (int i=1;i<=ret.len;i++) ret.num[i]=A.num[i]+B.num[i];
	ret.MainTain();return ret;
}

Bigint operator + (Bigint A,int B){
	A.num[1]+=B;A.MainTain();
	return A;
}

Bigint operator - (Bigint A,int B){
	A.num[1]-=B;
	int p=1;
	while (A.num[p]<0) A.num[p]+=10,A.num[p+1]--,p++;
	A.MainTain();return A;
}
