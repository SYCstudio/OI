#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=120001;
const int inf=2147483647;

class SegmentData
{
public:
    bool edge[5];
    bool ab,ac,ad,bc,bd,cd;
    void init(){
        edge[1]=edge[2]=edge[3]=edge[4]=ab=ac=ad=bc=bd=cd=0;
        return;
    }
};

int n;
SegmentData S[maxN<<3];
int Pos,Type,Opt;

SegmentData operator + (SegmentData A,SegmentData B);
void Modify(int now,int l,int r);
SegmentData Query(int now,int l,int r,int ql,int qr);

int main()
{
    scanf("%d",&n);n--;
    char input[30];
    while (1)
    {
        scanf("%s",input);
        if (input[0]=='E') break;
        int r1,c1,r2,c2;
        scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
        if (c1>c2) swap(r1,r2),swap(c1,c2);
        //cout<<r1<<" "<<c1<<" "<<r2<<" "<<c2<<endl;
        if (input[0]=='C')
        {
            if (r1==r2)
            {
                if (r1==1) Pos=c1,Type=1,Opt=0,Modify(1,1,n);
                if (r1==2) Pos=c1,Type=3,Opt=0,Modify(1,1,n);
            }
            else
            {
                if (c1!=1) Pos=c1-1,Type=4,Opt=0,Modify(1,1,n);
                if (c1<=n) Pos=c1,Type=2,Opt=0,Modify(1,1,n);
            }
        }
        if (input[0]=='O')
        {
            if (r1==r2)
            {
                if (r1==1) Pos=c1,Type=1,Opt=1,Modify(1,1,n);
                if (r1==2) Pos=c1,Type=3,Opt=1,Modify(1,1,n);
            }
            else
            {
                if (c1!=1) Pos=c1-1,Type=4,Opt=1,Modify(1,1,n);
                if (c1<=n) Pos=c1,Type=2,Opt=1,Modify(1,1,n);
            }
        }
        if (input[0]=='A')
        {
            SegmentData mid,left,right;mid.init();left.init();right.init();
            if (c1==c2)
            {
				c1=min(c1,n);
                mid=Query(1,1,n,c1,c1);
                if (c1!=1) left=Query(1,1,n,1,c1-1);
                if (c1<=n) right=Query(1,1,n,c1,n);
                if (r1==r2) printf("Y\n");
                else
                {
                    if ((mid.ac)||(left.bd)||(mid.ab&&right.ac&&mid.cd)||(mid.ad&&right.ac&&mid.bc)) printf("Y\n");
                    else printf("N\n");
                }
            }
            else
            {
                mid=Query(1,1,n,c1,c2-1);
                if (c1!=1) left=Query(1,1,n,1,c1-1);
                if (c2<=n) right=Query(1,1,n,c2,n);
                if ((r1==1)&&(r2==1))
                {
                    if ((mid.ab)||(left.bd&&mid.cd&&right.ac)) printf("Y\n");
                    else printf("N\n");
                }
                else if ((r1==1)&&(r2==2))
                {
                    if ((mid.ad)||(left.bd&&mid.cd)||(right.ac&&mid.ab)) printf("Y\n");
                    else printf("N\n");
                }
                else if ((r1==2)&&(r2==1))
                {
                    if ((mid.bc)||(left.bd&&mid.ab)||(right.ac&&mid.cd)) printf("Y\n");
                    else printf("N\n");
                }
                else if ((r1==2)&&(r2==2))
                {
                    if ((mid.cd)||(left.bd&&mid.ab&&right.ac)) printf("Y\n");
                    else printf("N\n");
                }
            }
        }
    }
    return 0;
}

SegmentData operator + (SegmentData A,SegmentData B)
{
    SegmentData Ret;
    Ret.ab=(A.ab&&B.ab)||(A.ad&&B.bc);
    Ret.ac=(A.ac)||(A.ab&&B.ac&&A.cd);
    Ret.ad=(A.ab&&B.ad)||(A.ad&&B.cd);
    Ret.bc=(A.bc&&B.ab)||(A.cd&&B.bc);
    Ret.bd=(B.bd)||(B.ab&&A.bd&&B.cd);
    Ret.cd=(A.cd&&B.cd)||(A.bc&&B.ad);
    return Ret;
}

void Modify(int now,int l,int r)
{
    if (l==r)
    {
        S[now].edge[Type]=Opt;
        S[now].ab=(S[now].edge[1])||(S[now].edge[2]&&S[now].edge[3]&&S[now].edge[4]);
        S[now].ac=(S[now].edge[2])||(S[now].edge[1]&&S[now].edge[4]&&S[now].edge[3]);
        S[now].ad=(S[now].edge[1]&&S[now].edge[4])||(S[now].edge[2]&&S[now].edge[3]);
        S[now].bc=(S[now].edge[1]&&S[now].edge[2])||(S[now].edge[4]&&S[now].edge[3]);
        S[now].bd=(S[now].edge[4])||(S[now].edge[1]&&S[now].edge[2]&&S[now].edge[3]);
        S[now].cd=(S[now].edge[3])||(S[now].edge[1]&&S[now].edge[2]&&S[now].edge[4]);
        return;
    }
    int mid=(l+r)>>1;
    if (Pos<=mid) Modify(lson,l,mid);
    else Modify(rson,mid+1,r);
    S[now]=S[lson]+S[rson];
    return;
}

SegmentData Query(int now,int l,int r,int ql,int qr)
{
    if ((l==ql)&&(r==qr)) return S[now];
    int mid=(l+r)>>1;
    if (qr<=mid) return Query(lson,l,mid,ql,qr);
    else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
    else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}
