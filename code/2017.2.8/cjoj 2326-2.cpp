#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
 
#define ll long long
 
const int maxsize=100001;
const long long inf=2147483647;
 
class SORT_DATA
{
public:
    int k,p;
    void A(int a,int b)
    {
        k=a;
        p=b;
	}
};
 
int n;
int A[maxsize];
int Left[maxsize];
int Right[maxsize];
SORT_DATA Sort[maxsize];
 
bool cmp(SORT_DATA a,SORT_DATA b);
 
int main()
{
    int i,j,k;
    int a,b,c;
    ll ans=0;
    
    cin>>n;
    
    for (i=1;i<=n;i++)
    {
        cin>>A[i];
        Left[i]=i-1;
        Right[i]=i+1;
        Sort[i].A(A[i],i);
	}
	Left[1]=n;
	Right[n]=1;
	
	sort(&Sort[1],&Sort[n+1],cmp);
	
	for (i=1;i<n;i++)
	{
	    b=Sort[i].p;
	    a=Left[b];
	    c=Right[b];
	    if (A[a]<A[c])
	    {
	        ans+=A[a]-A[b];
		}
		else
		    ans+=A[c]-A[b];
		Right[a]=c;
		Left[c]=a;
	}
	
	cout<<ans<<endl;
	
	return 0;
}
 
bool cmp(SORT_DATA a,SORT_DATA b)
{
    return a.k<b.k;
}
