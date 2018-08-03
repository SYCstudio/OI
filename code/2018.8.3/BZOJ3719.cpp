#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000*3;
const int maxNum=1000000;
const int inf=2147483647;

class Rtg
{
public:
	int x1,x2,y1,y2;
};

class SegmentData{
public:
	vector<int> A,B;
};

int n;
Rtg R[maxN],A[maxN];
vector<int> St;
SegmentData S[maxNum<<2];
bool vis[maxN];

bool cmp1(Rtg A,Rtg B);
bool cmp2(Rtg A,Rtg B);
void Query(int now,int l,int r,int ql,int qr,int id);
void Modify(int now,int l,int r,int ql,int qr,int id);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d%d%d",&R[i].x1,&R[i].x2,&R[i].y1,&R[i].y2);
	int ncnt=0,acnt=0;
	for (int i=1;i<=n;i++)
		if ((R[i].x1==R[i].x2)||(R[i].y1==R[i].y2)) A[++acnt]=R[i];
		else R[++ncnt]=R[i];
	n=ncnt;

	sort(&R[1],&R[n+1],cmp1);
	for (int i=1;i<=n;i++) R[i].x2--;
	for (int i=1;i<=acnt;i++) A[i].x2--;
	int nnn=n;
	for (int i=1;i<=nnn;i++){
		int now=i;
		//cout<<"i:"<<i<<endl;
		do{
			St.clear();
			//cout<<"Query:"<<R[now].x1<<" "<<R[now].x2<<" "<<R[now].y1<<" "<<R[now].y2<<endl;
			Query(1,0,maxNum,R[now].x1,R[now].x2,now);
			if (St.empty()) break;
			//cout<<"continue..."<<endl;
			//cout<<"Get:"<<endl;
			int sz=St.size();
			//for (int j=0;j<sz;j++) cout<<R[St[j]].x1<<" "<<R[St[j]].x2<<" "<<R[St[j]].y1<<" "<<R[St[j]].y2<<endl;
			//cout<<endl;
			R[++n]=R[now];vis[now]=1;
			for (int j=0;j<sz;j++){
				vis[St[j]]=1;
				R[n].x1=min(R[n].x1,R[St[j]].x1);
				R[n].x2=max(R[n].x2,R[St[j]].x2);
				R[n].y1=min(R[n].y1,R[St[j]].y1);
				R[n].y2=max(R[n].y2,R[St[j]].y2);
			}
			now=n;
			//cout<<R[now].x1<<" "<<R[now].x2<<" "<<R[now].y1<<" "<<R[now].y2<<endl;
			St.clear();
		}
		while (1);
		//cout<<"Add:"<<R[now].x1<<" "<<R[now].x2<<" "<<R[now].y1<<" "<<R[now].y2<<endl;
		Modify(1,0,maxNum,R[now].x1,R[now].x2,now);
	}

	for (int i=1;i<=n;i++) if (vis[i]==0) A[++acnt]=R[i];
	sort(&A[1],&A[acnt+1],cmp2);

	printf("%d\n",acnt);
	for (int i=1;i<=acnt;i++) printf("%d %d %d %d\n",A[i].x1,A[i].x2+1,A[i].y1,A[i].y2);

	return 0;
}

bool cmp1(Rtg A,Rtg B){
	return A.y2<B.y2;
}

bool cmp2(Rtg A,Rtg B){
	if (A.x1==B.x1){
		if (A.x2==B.x2){
			if (A.y1==B.y1)
				return A.y2<B.y2;
			else return A.y1<B.y1;
		}
		else return A.x2<B.x2;
	}
	else return A.x1<B.x1;
}

void Query(int now,int l,int r,int ql,int qr,int id){
	//cout<<"Query:"<<now<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<id<<endl;
	int sz,p;
	while ((sz=S[now].A.size())&&(vis[S[now].A[sz-1]])) S[now].A.pop_back();
	while ((sz=S[now].B.size())&&(vis[S[now].B[sz-1]])) S[now].B.pop_back();
	//cout<<"A:";for (int i=0;i<S[now].A.size();i++) cout<<S[now].A[i]<<" ";cout<<endl;
	//cout<<"B:";for (int i=0;i<S[now].B.size();i++) cout<<S[now].B[i]<<" ";cout<<endl;
	
	if ((l==ql)&&(r==qr)){
		while (sz=S[now].B.size()){
			if (vis[S[now].B[sz-1]]){
				S[now].B.pop_back();continue;
			}
			//cout<<"Q:[B]"<<S[now].B[sz-1]<<" "<<R[S[now].B[sz-1]].y2<<" "<<R[id].y1<<endl;
			if (R[p=S[now].B[sz-1]].y2>R[id].y1){
				St.push_back(p);S[now].B.pop_back();vis[p]=1;
			}
			else break;
		}
		return;
	}

	while (sz=S[now].A.size()){
		if (vis[S[now].A[sz-1]]){
			S[now].A.pop_back();continue;
		}
		//cout<<"Q:[A]"<<S[now].A[sz-1]<<" "<<R[S[now].A[sz-1]].y2<<" "<<R[id].y1<<endl;
		if (R[p=S[now].A[sz-1]].y2>R[id].y1){
			St.push_back(p);S[now].A.pop_back();vis[p]=1;
		}
		else break;
	}

	int mid=(l+r)>>1;
	if (qr<=mid) Query(lson,l,mid,ql,qr,id);
	else if (ql>=mid+1) Query(rson,mid+1,r,ql,qr,id);
	else{
		Query(lson,l,mid,ql,mid,id);Query(rson,mid+1,r,mid+1,qr,id);
	}
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int id){
	int sz;
	//cout<<"Modify:"<<now<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<id<<endl;
	while ((sz=S[now].A.size())&&(vis[S[now].A[sz-1]])) S[now].A.pop_back();
	while ((sz=S[now].B.size())&&(vis[S[now].B[sz-1]])) S[now].B.pop_back();
	S[now].B.push_back(id);
	if ((l==ql)&&(r==qr)){
		S[now].A.push_back(id);
		return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,id);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,id);
	else{
		Modify(lson,l,mid,ql,mid,id);Modify(rson,mid+1,r,mid+1,qr,id);
	}
	return;
}

/*
5
7 8 1 4
1 5 2 3
4 5 2 7
2 3 5 9
4 6 8 9

5
12 20 22 33
12 20 22 33
12 20 22 33
12 20 22 33
12 20 22 33

42
4 9 4 9
16 17 300 303
6 9 306 307
0 5 14 16
20 30 20 30
0 5 0 5
40 50 40 50
2 5 90 91
948 972 815 818
820 836 931 997
10 11 306 309
29 30 29 30
0 10 100 110
70 80 72 78
4 7 304 305
12 13 304 307
2 5 302 303
5 10 115 125
14 17 314 315
0 1 90 93
0 5 10 20
2 3 312 315
8 11 308 309
0 3 94 95
6 7 308 311
12 15 312 313
10 20 110 120
100 200 100 200
4 5 310 313
110 111 189 190
29 30 20 21
900 950 800 820
10 13 310 311
33 35 66 68
810 893 930 932
49 59 40 50
32 36 62 66
20 21 20 21
14 15 302 305
20 21 29 30
4 5 92 95
72 78 70 80
//*/

