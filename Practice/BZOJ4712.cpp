#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=201000;
const int maxM=maxN<<1;

class Matrix{
    public:
    int M[2][2];
};

int n;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];