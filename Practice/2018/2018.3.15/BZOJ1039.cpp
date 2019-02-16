#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1600100;
const int inf=2147483647;

int gcd(int a,int b)
{
	int t;
	while (b) t=a,a=b,b=t%b;
	return a;
}

class Point
{
public:
	int x,y;
	Point(){
		x=y=0;return;
	}
	Point(int a,int b){
		x=a;y=b;return;
	}
	int len(){
		return x*x+y*y;
	}
};

Point operator + (Point A,Point B){
	return (Point){A.x+B.x,A.y+B.y};
}

Point operator - (Point A,Point B){
	return (Point){A.x-B.x,A.y-B.y};
}

int operator * (Point A,Point B){
	return A.x*B.x+A.y*B.y;
}

int operator ^ (Point A,Point B){
	return A.x*B.y-A.y*B.x;
}

class Data
{
public:
	int len1,len2,dot,cross;
	Data(){
		len1=len2=dot=cross=0;
	}
	Data(int l1,int l2,int dt,int cs){
		//cout<<l1<<" "<<l2<<" "<<dt<<" "<<cs<<endl;
		int t=gcd(abs(l1),abs(l2));
		len1=l1/t;len2=l2/t;dot=dt;cross=cs;
		if (dt==0) cross=(cs<0)?(-1):(1);//点积为0，说明两向量垂直
		else if (cs==0) dot=(dt<0)?(-1):(1);//叉积为0，说明两向量共线
		else
		{
			t=gcd(abs(dt),abs(cs));
			dot=dt/t;cross=cs/t;
		}
		return;
	}
};

bool operator < (Data A,Data B)
{
	if (A.len1!=B.len1) return A.len1<B.len1;
	if (A.len2!=B.len2) return A.len2<B.len2;
	if (A.dot!=B.dot) return A.dot<B.dot;
	return A.cross<B.cross;
}

bool operator == (Data A,Data B){
	return ((A.len1==B.len1)&&(A.len2==B.len2)&&(A.dot==B.dot)&&(A.cross==B.cross));
}

bool operator != (Data A,Data B){
	return !(A==B);
}

ostream& operator << (ostream &os,Data A)
{
	os<<"("<<A.len1<<","<<A.len2<<","<<A.dot<<","<<A.cross<<")";
	return os;
}

class Trie
{
public:
	int fail,id;
	Data D;
	map<Data,int> Son;
};

int n,m,nodecnt,pcnt;
int Len[maxN];
Data P[maxN];
Point Input[maxN];
Trie T[maxN];
bool Same[maxN];//标记某一个是否为一根直线
int idcnt=0,Id[maxN],Queue[maxN],Cnt[maxN];

void GetFail();
void AhoCorasick();

int main()
{
	//ios::sync_with_stdio(false);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&Len[i]);
		for (int j=1;j<=Len[i];j++) scanf("%d%d",&Input[j].x,&Input[j].y);
		if (Len[i]<=2) continue;
		Same[i]=1;
		for (int j=2;j<Len[i];j++)
		{
			Point p1=Input[j]-Input[j-1],p2=Input[j+1]-Input[j];
			P[++pcnt]=Data(p1.len(),p2.len(),p1*p2,p1^p2);
			if ((p1^p2)!=0) Same[i]=0;
			//cout<<P[pcnt]<<" ";
		}
		//cout<<endl;
	}
	
	for (int i=1,p=1;i<=m;i++)
		if (Len[i]>2)
		{
			int now=0;
			for (int j=1;j<=Len[i]-2;j++,p++)
			{
				if (T[now].Son.count(P[p])==0) T[now].Son[P[p]]=++nodecnt;
				now=T[now].Son[P[p]];
			}
			if (T[now].id==0) T[now].id=++idcnt;
			Id[i]=T[now].id;
			//cout<<i<<" "<<now<<" "<<T[now].id<<endl;
		}

	//cout<<"A"<<" "<<idcnt<<endl;
	//for (int i=1;i<=m;i++) cout<<Id[i]<<" ";cout<<endl;
	
	GetFail();

	for (int i=1;i<=n;i++) scanf("%d%d",&Input[i].x,&Input[i].y);

	pcnt=0;
	for (int i=2;i<n;i++)
	{
		Point p1=Input[i]-Input[i-1],p2=Input[i+1]-Input[i];
		P[++pcnt]=Data(p1.len(),p2.len(),p1*p2,p1^p2);
		//cout<<P[pcnt]<<" ";
	}
	//cout<<endl;

	AhoCorasick();
	for (int i=1;i<=pcnt;i++) P[i].cross=-P[i].cross;
	AhoCorasick();

	for (int i=1;i<=m;i++)
		if (Len[i]<=2) printf("%d\n",n-Len[i]+1);
		else
		{
			if (Same[i]) printf("%d\n",Cnt[Id[i]]/2);
			else printf("%d\n",Cnt[Id[i]]);
		}

	return 0;
}

void GetFail()
{
	int h=0,t=0;
	for (map<Data,int>::iterator i=T[0].Son.begin();i!=T[0].Son.end();i++) Queue[++h]=i->second;
	while (t!=h)
	{
		int u=Queue[++t];
		for (map<Data,int>::iterator i=T[u].Son.begin();i!=T[u].Son.end();i++)
		{
			Data key=i->first;int id=i->second;
			int p=T[u].fail;
			while ((p)&&(T[p].Son.count(key)==0)) p=T[p].fail;
			if (T[p].Son.count(key)!=0) T[id].fail=T[p].Son[key];
			Queue[++h]=id;
		}
	}
	return;
}

void AhoCorasick()
{
	int now=0;
	for (int i=1;i<=pcnt;i++)
	{
		if (T[now].Son.count(P[i])!=0) now=T[now].Son[P[i]];
		else
		{
			while ((now)&&(T[now].Son.count(P[i])==0)) now=T[now].fail;
			if (T[now].Son.count(P[i])!=0) now=T[now].Son[P[i]];
		}
		int p=now;
		while (p)
		{
			Cnt[T[p].id]++;
			p=T[p].fail;
		}
	}
	return;
}
