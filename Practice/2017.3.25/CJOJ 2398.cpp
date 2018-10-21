#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class Array
{
public:
    int a,f,g;
    Array()
    {
        f=0;g=0;
    }
    void operator =(Array b)
    {
        a=b.a;
        f=b.f;
        g=b.g;
    }
    bool operator <(Array b)
    {
        return a<b.a;
    }
};

const int maxsize=50050;
const int inf=2147483647;

int n;
Array A[maxsize];
Array T[maxsize];

void Sort(int l,int r);

int main()
{

    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>A[i].a;

    Sort(1,n);

    //for (int i=1;i<=n;i++)
    //    cout<<A[i].a<<" "<<A[i].f<<" "<<A[i].g<<endl;
    //cout<<endl;

    long long Ans=0;

    for (int i=1;i<=n;i++)
        Ans=Ans+((long long)A[i].f)*((long long)A[i].g);
    cout<<Ans-10<<endl;

    return 0;
}

void Sort(int l,int r)
{
    if (l==r)
    {
        return;
    }
    if (l+1==r)
    {
        if (A[l].a==A[r].a)
            return;
        if (A[l].a>A[r].a)
        {
            A[l].g++;
            swap(A[l],A[r]);
        }
        else
        {
            A[r].f++;
        }
        return;
    }
    int mid=(l+r)/2;
    Sort(l,mid);
    Sort(mid+1,r);
    //cout<<"sort "<<l<<" "<<r<<endl;
    //for (int i=l;i<=r;i++)
    //    cout<<A[i].a<<" "<<A[i].f<<" "<<A[i].g<<endl;
    //cout<<endl;
    memcpy(T+l,A+l,sizeof(Array)*(r-l+2));
    int i=l,j=mid+1;
    int ci=0,cj=0;
    int ai=-1,aj=-1;
    for (int k=l;k<=r;k++)
    {
        /*cout<<"k"<<k<<" i"<<i<<" j"<<j<<endl;
        for (int ii=l;ii<=r;ii++)
            cout<<A[ii].a<<" "<<A[ii].f<<" "<<A[ii].g<<endl;
        cout<<endl;
        for (int ii=l;ii<=r;ii++)
            cout<<T[ii].a<<" "<<T[ii].f<<" "<<T[ii].g<<endl;*/
        if (((T[i]<T[j])&&(i<=mid))||(j>r))
        {
            A[k]=T[i];
            if (A[k].a==ai)
            {
                ci++;
            }
            else
            {
                ci=1;
                ai=A[k].a;
            }
            A[k].g=A[k].g+j-mid-1;
            if (A[k].a==aj)
                A[k].g=A[k].g-cj;
            i++;
        }
        else
        {
            A[k]=T[j];
            if (A[k].a==aj)
            {
                cj++;
            }
            else
            {
                cj=1;
                aj=A[k].a;
            }
            A[k].f=A[k].f+i-l;
            if (A[k].a==ai)
                A[k].f=A[k].f-ci;
            j++;
        }
    }
    //for (int i=l;i<=r;i++)
    //    cout<<A[i].a<<" "<<A[i].f<<" "<<A[i].g<<endl;
    //cout<<endl;
}
