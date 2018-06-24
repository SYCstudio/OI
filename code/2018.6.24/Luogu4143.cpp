#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "platform"

const int maxN=401000;
const int maxBit=23;
const int inf=2147483647;

class Range
{
public:
    int l,r;
};
    
int n,m;
char str[maxN];
ll Val[maxN],SV[maxN],SS[maxN],Log2[maxN];
int SA[maxN],SSA[maxN],Rank[maxN],Height[maxBit][maxN];
int CntA[maxN],CntB[maxN],A[maxN],B[maxN];
Range Rg[maxN];

ll Calc(int l,int r);
int GetMin(int l,int r);
bool cmp (Range A,Range B);

int main()
{
    scanf("%s",str+1);n=strlen(str+1);
    for (int i=1;i<=n;i++) scanf("%lld",&Val[i]);
    for (int i=1;i<=n;i++) A[i]=str[i]-'a';

    for (int i=1;i<=n;i++) CntA[A[i]]++;
    for (int i=1;i<maxN;i++) CntA[i]+=CntA[i-1];
    for (int i=n;i>=1;i--) SA[CntA[A[i]]--]=i;
    Rank[SA[1]]=1;
    for (int i=2;i<=n;i++)
    {
        Rank[SA[i]]=Rank[SA[i-1]];
        if (A[SA[i]]!=A[SA[i-1]]) Rank[SA[i]]++;
    }
    for (int l=1;Rank[SA[n]]<n;l<<=1)
    {
        mem(CntA,0);mem(CntB,0);
        for (int i=1;i<=n;i++)
        {
            CntA[A[i]=Rank[i]]++;
            CntB[B[i]=((i+l<=n)?(Rank[i+l]):(0))]++;
        }
        for (int i=1;i<maxN;i++) CntA[i]+=CntA[i-1],CntB[i]+=CntB[i-1];
        for (int i=n;i>=1;i--) SSA[CntB[B[i]]--]=i;
        for (int i=n;i>=1;i--) SA[CntA[A[SSA[i]]]--]=SSA[i];
        Rank[SA[1]]=1;
        for (int i=2;i<=n;i++)
        {
            Rank[SA[i]]=Rank[SA[i-1]];
            if ((A[SA[i]]!=A[SA[i-1]])||(B[SA[i]]!=B[SA[i-1]])) Rank[SA[i]]++;
        }
    }
    for (int i=1,j=0;i<=n;i++)
    {
        if (j) j--;
        while (str[SA[Rank[i]-1]+j]==str[i+j]) j++;
        Height[0][Rank[i]]=j;
    }

    //for (int i=1;i<=n;i++) cout<<Rank[i]<<" ";cout<<endl;
    //for (int i=1;i<=n;i++) cout<<SA[i]<<" ";cout<<endl;
    //for (int i=1;i<=n;i++) cout<<Height[i]<<" ";cout<<endl;

    for (int i=1;i<maxBit;i++)
        for (int j=1;j<=n;j++)
            if (j+(1<<i)-1<=n)
                Height[i][j]=min(Height[i-1][j],Height[i-1][j+(1<<(i-1))+1]);
    for (int i=1;i<=n;i++) SV[i]=SV[i-1]+Val[i],SS[i]=SS[i-1]+n-SA[i]-Height[0][i]+1,Log2[i]=log2(i);

    int Ans=0;
    for (int i=1;i<=n;i++)
    {
        int L=i,R=n,ret=-1;
        do
        {
            int mid=(L+R)>>1;
            //cout<<"("<<L<<","<<R<<")"<<endl;
            if (Calc(i,mid)>=SV[mid]-SV[i-1]) ret=mid,L=mid+1;
            else R=mid-1;
        }
        while (L<=R);
        if ((ret!=-1)&&(Calc(i,ret)==SV[ret]-SV[i-1])) Rg[++Ans]=((Range){i,ret});
    }

    sort(&Rg[1],&Rg[Ans+1],cmp);
    printf("%d\n",Ans);
    for (int i=1;i<=Ans;i++) printf("%d %d\n",Rg[i].l,Rg[i].r);
    return 0;
}

ll Calc(int l,int r)
{
    //cout<<"Calc:"<<l<<" "<<r<<" "<<Height[0][Rank[l]]<<" "<<Rank[l]<<endl;
    if (Height[0][Rank[l]]<r-l+1) return SS[n]-SS[Rank[l]]+n-r+1;
    int L=1,R=Rank[l]-1,pos=Rank[l]-1;
    do
    {
        int mid=(L+R)>>1;
        //cout<<"C ("<<L<<","<<R<<")"<<endl;
        if (GetMin(mid,Rank[l])>=r-l+1) pos=mid,R=mid-1;
        else L=mid+1;
    }
    while (L<=R);
    //cout<<"pos:"<<pos<<endl;
    return Calc(SA[pos],SA[pos]+r-l);
}

int GetMin(int l,int r)
{
    int sz=Log2[r-l+1];
    return min(Height[sz][l],Height[sz][r-(1<<sz)+1]);
}

bool cmp(Range A,Range B){
    if (A.l!=B.l) return A.l<B.l;
    else return A.r<B.r;
}

