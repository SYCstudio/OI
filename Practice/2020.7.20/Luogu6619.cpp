#include<bits/stdc++.h>
using namespace std;

const int maxN = 2000010;
const int inf = 2100000010;

#define lson (x<<1)
#define rson (lson|1)

class InputData{
    public:
    int a, b, c, d;
};

int n, Q, ncnt = 0, Num[maxN], S0[maxN*4], S1[maxN*4], Bucket[maxN];
InputData In[maxN];
int Ans,tpr;

void Modify(int x, int l, int r, int p, int key,int opt);
void Query(int x, int l, int r, int lsum, int rsum);
bool QueryT(int x, int l, int r);

int main() {
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        scanf("%d", &In[i].a);
        if (In[i].a == 1) {
            scanf("%d%d%d", &In[i].b, &In[i].c, &In[i].d);
            Num[++ncnt] = In[i].c;
        }
        else scanf("%d", &In[i].b);
    }
    sort(&Num[1], &Num[ncnt+1]);
    ncnt = unique(&Num[1], &Num[ncnt+1])-Num-1;

    //for (int i = 1; i <= ncnt; i++) cout<<Num[i]<<" ";cout<<endl;

    for (int i = 1; i <= Q; i++)
        if (In[i].a == 1) In[i].c = lower_bound(&Num[1], &Num[ncnt+1], In[i].c)-Num;
    
    int cnt[2];
    cnt[0] = cnt[1] = 0;
    for (int i = 1; i <= Q; i++) {
        if (In[i].a == 1) {
            ++cnt[In[i].b];
            if (In[i].b == 1) Bucket[In[i].c] += In[i].d;
            Modify(1,1,ncnt,In[i].c,In[i].d,In[i].b);
        }
        else{
            int id = In[i].b;
            --cnt[In[id].b];
            if (In[id].b == 1) Bucket[In[id].c] -= In[id].d;
            Modify(1,1,ncnt,In[id].c,-In[id].d,In[id].b);
        }
        if ((cnt[0] == 0) || (cnt[1] == 0)) printf("Peace\n");
        else{
            tpr = inf;Query(1, 1, ncnt, 0, 0);
            if (Ans != 0) {
                //while (Bucket[tpr] == 0) ++tpr;
                //QueryT(1,1,ncnt);
                printf("%d %lld\n", Num[tpr], 1ll * Ans * 2);
            }
            else printf("Peace\n");
        }
    }
    return 0;
}

void Modify(int x, int l, int r, int p, int key, int opt) {
    if (opt == 0) S0[x] += key;
    else S1[x] += key;
    if (l == r) return;
    int mid = (l+r)>>1;
    if (p <= mid) Modify(lson, l, mid, p, key, opt);
    else Modify(rson, mid+1, r, p, key, opt);
    return;
}

void Query(int x, int l, int r, int lsum, int rsum) {
    //cout<<"Q:"<<x<<" "<<l<<" "<<r<<" "<<lsum<<" "<<rsum<<" "<<S0[x]<<" "<<S1[x]<<endl;
    if (l == r){
        Ans = min(lsum + S0[x], rsum + S1[x]);
        tpr = l;
        return;
    }
    int mid = (l+r)>>1;
    //cout<<"Q:"<<x<<" ["<<Num[l]<<","<<Num[r]<<"] "<<lsum+S0[lson]<<" "<<rsum+S1[rson]<<" "<<Num[mid]<<" "<<S0[x]<<" "<<S1[x]<<endl;
    if (lsum + S0[lson] <= rsum + S1[rson]) Query(rson, mid+1, r, lsum + S0[lson], rsum);
    else Query(lson, l, mid, lsum, rsum + S1[rson]);
    return;
}

bool QueryT(int x,int l,int r){
    if (l == r) {
        if (S1[x] == 0) return 0;
        else {
            tpr = l;
            return 1;
        }
    }
    int mid = (l+r)>>1;
    if (mid < tpr) return QueryT(rson, mid+1, r);
    else {
        int opt = QueryT(lson, l, mid);
        if (opt == 1) return 1;
        if (S1[rson] == 0) return 0;
        QueryT(rson, mid+1, r);
        return 1;
    }
}