#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;

#define ll int
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const ll maxN=500010;
const ll inf=0x3f3f3f3f;

int outpcnt=0;

class Splay_Data
{
public:
    ll key;
    ll ch[2],fa;
    ll size,sum;
    ll presum,sufsum,arrsum;
    ll set,rev;//是否覆盖，是否翻折
    Splay_Data()
	{
	    ch[0]=ch[1]=fa=size=sum=presum=sufsum=arrsum=0;
	    set=rev=0;
	    return;
	}
    void clear()//回收
	{
	    ch[0]=ch[1]=fa=size=sum=presum=sufsum=0;
	    arrsum=-inf;
	    set=rev=0;
	    return;
	}
};

class SplayTree
{
public:
    ll cnt,root;
    Splay_Data S[maxN];
    stack<ll> Stack;
    ll Input[maxN];
    SplayTree()
	{
	    cnt=root=0;
	    while (!Stack.empty()) Stack.pop();
	    return;
	}
    ll New()//申请一个新地址
	{
	    if (!Stack.empty())
	    {
		ll u=Stack.top();Stack.pop();return u;
	    }
	    cnt++;return cnt;
	}
    void PushDown(ll x)//下放操作
	{
	    ll lson=S[x].ch[0],rson=S[x].ch[1];
	    if (S[x].set!=0)//当所选区间有覆盖操作时，不论是否有翻转操作都是无意义的
	    {
		ll key=S[x].key;
		S[x].set=S[x].rev=0;
		if (lson)//下放信息
		{ S[lson].key=key; S[lson].set=1; S[lson].sum=S[lson].size*key;}
		if (rson)
		{ S[rson].key=key; S[rson].set=1; S[rson].sum=S[rson].size*key;}
		//接下来是更新区间最值
		if (key>=0)//当key是大于0的时候直接更新
		{
		    if (lson) S[lson].presum=S[lson].sufsum=S[lson].arrsum=S[lson].sum;
		    if (rson) S[rson].presum=S[rson].sufsum=S[rson].arrsum=S[rson].sum;
		}
		else//否则前缀最大和后缀最大都为0，但因为区间最大字段和要求至少存在一个数，所以arrsum就为key
		{
		    if (lson)
		    {
			S[lson].presum=S[lson].sufsum=0;
			S[lson].arrsum=key;
		    }
		    if (rson)
		    {
			S[rson].presum=S[rson].sufsum=0;
			S[rson].arrsum=key;
		    }
		}
	    }
	    if (S[x].rev)
	    {
		S[x].rev=0;
		if (lson) S[lson].rev^=1;
		if (rson) S[rson].rev^=1;
		swap(S[lson].presum,S[lson].sufsum);//交换前后缀和
		swap(S[rson].presum,S[rson].sufsum);
		swap(S[lson].ch[0],S[lson].ch[1]);//交换左右子树
		swap(S[rson].ch[0],S[rson].ch[1]);
	    }
	    return;
	}
    void Update(ll x)
	{
	    ll lson=S[x].ch[0],rson=S[x].ch[1];
	    S[x].size=S[lson].size+S[rson].size+1;
	    S[x].sum=S[lson].sum+S[rson].sum+S[x].key;
	    S[x].presum=max(S[lson].presum,S[lson].sum+S[x].key+S[rson].presum);
	    S[x].sufsum=max(S[rson].sufsum,S[lson].sufsum+S[x].key+S[rson].sum);
	    S[x].arrsum=max(max(S[lson].arrsum,S[rson].arrsum),S[lson].sufsum+S[x].key+S[rson].presum);
	    return;
        
	}
    void Rotate(ll x)
	{
	    ll y=S[x].fa;ll z=S[y].fa;
	    bool sx=(x==S[y].ch[1]);
	    bool sy=(y==S[z].ch[1]);
	    S[x].fa=z;S[z].ch[sy]=x;
	    S[S[x].ch[sx^1]].fa=y;S[y].ch[sx]=S[x].ch[sx^1];
	    S[y].fa=x;S[x].ch[sx^1]=y;
	    Update(y);Update(x);
	    return;
	}
    void Splay(ll x,ll goal)
	{
	    while (S[x].fa!=goal)
	    {
		ll y=S[x].fa;ll z=S[y].fa;
		if (z!=goal)
		    ((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	    }
	    if (goal==0) root=x;
	    return;
	}
    ll Rank(ll kth)
	{
	    ll now=root;
	    while (now)
	    {
		PushDown(now);
		ll lson=S[now].ch[0];
		if (S[lson].size+1==kth) return now;
		if (S[lson].size+1<kth)
		{
		    kth=kth-S[lson].size-1;
		    now=S[now].ch[1];
		}
		else now=lson;
	    }
	}
    void BuildTree(ll l,ll r,ll father,ll opt)//按照中序遍历构建一棵完美的平衡树
	{
	    //cout<<"Build: l:"<<l<<" r:"<<r<<" fa:"<<father<<" opt:"<<opt<<" num:"<<Input[(l+r)/2]<<" mid:"<<(l+r)/2<<endl;
	    if (l>r) return;
	    ll mid=(l+r)/2,now=New();
	    S[now].clear();
	    if (l==r)
	    {
		S[now].size=1;
		S[now].sum=S[now].arrsum=Input[mid];
		S[now].presum=S[now].sufsum=max(0,Input[mid]);
		S[now].set=S[now].rev=0;
	    }
	    S[now].key=Input[mid];
	    //cout<<"now:"<<now<<" mid:"<<mid<<" num:"<<Input[mid]<<endl;
	    S[now].fa=father;
	    if (father!=0) S[father].ch[opt]=now;
	    if (l<mid) BuildTree(l,mid-1,now,0);
	    if (mid<r) BuildTree(mid+1,r,now,1);
	    Update(now);
	    //cout<<mid<<" "<<now<<" "<<S[now].ch[0]<<" "<<S[now].ch[1]<<endl;
	    return;
	}
    void Insert()
	{
	    ll pos,tot;scanf("%d%d",&pos,&tot);
	    for (ll i=1;i<=tot;i++) scanf("%d",&Input[i]);
	    if (tot==0) return;
	    //cout<<"Insert:"<<pos<<" "<<tot<<":";
	    //for (ll i=1;i<=tot;i++) cout<<Input[i]<<" ";
	    //cout<<endl;
	    ll l=Rank(pos+1),r=Rank(pos+2);//找到实际在Splay中的位置
	    Splay(l,0);Splay(r,l);//旋转端点，得到区间
	    //ll nowroot=S[l].ch[1];
	    BuildTree(1,tot,r,0);
	    Update(r);Update(l);
	    return;
	}
    void Recover(ll x)//回收被删除的点
	{
	    if (x==0) return;
	    if (S[x].ch[0]) Recover(S[x].ch[0]);
	    if (S[x].ch[1]) Recover(S[x].ch[1]);
	    S[x].clear();
	    Stack.push(x);
	    return;
	}
    void Delete()
	{
	    ll pos,tot;scanf("%d%d",&pos,&tot);
	    if (tot==0) return;
	    //cout<<"Delete:"<<pos<<" "<<tot<<endl;
	    ll l=Rank(pos),r=Rank(pos+tot+1);
	    Splay(l,0);Splay(r,l);
	    //before__outp();
	    //_outp(root);
	    Recover(S[r].ch[0]);
	    S[r].ch[0]=0;
	    Update(r);Update(l);
	    //_outp(root);
	    return;
	}
    void Set()
	{
	    ll pos,tot,num;scanf("%d%d%d",&pos,&tot,&num);
	    //cout<<"Set:"<<pos<<" "<<tot<<" "<<num<<endl;
	    ll l=Rank(pos),r=Rank(pos+tot+1);
	    Splay(l,0);Splay(r,l);
	    ll x=S[r].ch[0];
	    S[x].key=num;
	    S[x].sum=S[x].size*num;
	    if (num>=0) S[x].presum=S[x].sufsum=S[x].arrsum=S[x].sum;
	    else S[x].presum=S[x].sufsum=0,S[x].arrsum=num;
	    S[x].set=1;
	    Update(r);Update(l);
	    //__outp(root);
	    return;
	}
    void Reverse()
	{
	    ll pos,tot;scanf("%d%d",&pos,&tot);
	    //cout<<"Reverse:"<<pos<<" "<<tot<<endl;
	    //cout<<pos<<" "<<tot<<endl;
            ll l=Rank(pos),r=Rank(pos+tot+1);
	    Splay(l,0);Splay(r,l);
	    ll now=S[S[l].ch[1]].ch[0];
	    if (S[now].set==0)
	    {
		S[now].rev^=1;
		swap(S[now].ch[0],S[now].ch[1]);
		swap(S[now].presum,S[now].sufsum);
		Update(r);Update(l);
	    }
	    return;
	}
    void Sum()
	{
	    ll pos,tot;scanf("%d%d",&pos,&tot);
	    //cout<<"Sum:"<<pos<<" "<<tot<<endl;
	    ll l=Rank(pos),r=Rank(pos+tot+1);
	    Splay(l,0);Splay(r,l);
	    ll now=S[r].ch[0];
	    printf("%d\n",S[now].sum);
	    //Splay(now,0);
	    return;
	}
    void SumArr()
	{
	    //PushDown(root);
	    //cout<<"SumArr ";
	    printf("%d\n",S[root].arrsum);
	    /*
	      ll pos,tot;scanf("%d%d",&pos,&tot);
	      ll l=Rank(pos+1),r=Rank(pos+tot+2);
	      Splay(l,0);Splay(r,l);
	      ll now=S[S[l].ch[1]].ch[0];
	      printf("%d\n",S[now].arrsum);
	      Splay(now,0);
	    //*/
	    return;
	}
    void _outp(ll now)
	{
	    PushDown(now);
	    //printf("%2lld %11lld %11lld %11lld %11lld %11lld %11lld %11lld %11lld %11lld %11lld %11lld\n",now,S[now].key,S[now].fa,S[now].ch[0],S[now].ch[1],S[now].size,S[now].sum,S[now].presum,S[now].sufsum,S[now].arrsum,S[now].set,S[now].rev);
	    //cout<<"["<<now<<"] "<<S[now].key<<"   "<<S[now].fa<<"  "<<S[now].ch[0]<<"  "<<S[now].ch[1]<<"   "<<S[now].size<<"   "<<S[now].sum<<"   "<<S[now].presum<<"   "<<S[now].sufsum<<"   "<<S[now].arrsum<<"   "<<S[now].set<<"   "<<S[now].rev<<endl;
	    if (S[now].ch[0]) _outp(S[now].ch[0]);
	    if (S[now].ch[1]) _outp(S[now].ch[1]);
	    return;
	}
    void __outp(ll now)
	{
	    PushDown(now);
	    if (S[now].ch[0]) __outp(S[now].ch[0]);
	    if (S[now].key!=-inf) cout<<S[now].key<<" ";
	    if (S[now].ch[1]) __outp(S[now].ch[1]);
	    return;
	}
    void before__outp()
	{
	    cout<<"id         key          fa          ls          rs         siz         sum         pre         suf         arr         set         rev"<<endl;
	}
    void Outp()
	{
	    //cout<<"Root:"<<root<<endl;
	    //cout<<"id         key          fa          ls          rs         siz         sum         pre         suf         arr         set         rev"<<endl;
	    //_outp(root);
	    __outp(root);cout<<endl;
	    return;
	}
};

ll n,m;
SplayTree S;
char Opt[20]="";

int main()
{
    scanf("%d%d",&n,&m);
    S.Input[1]=S.Input[n+2]=-inf;
    for (ll i=1;i<=n;i++) scanf("%d",&S.Input[i+1]);
    //for (ll i=1;i<=n;i++) cout<<S.Input[i]<<" ";
    //cout<<endl;
    S.root=0;
    S.BuildTree(1,n+2,0,0);
    S.root=1;
    //S.__outp(S.root);cout<<endl;
    int mi=1;
    S.S[0].clear();
    while (m--)
    {
	//cout<<mi<<":";
	scanf("%s",Opt+1);
	if (Opt[1]=='I') S.Insert();
	if (Opt[1]=='D') S.Delete();
	if (Opt[3]=='K') S.Set();
	if (Opt[1]=='R') S.Reverse();
	if (Opt[1]=='G') S.Sum();
	if (Opt[3]=='X') S.SumArr();
	//if (outpcnt==44)
	//{
	//    cout<<"A "<<mi<<endl;
	//}
	//S.Outp();
	//S.__outp(S.root);cout<<endl;
	//mi++;
    }
    return 0;
}
