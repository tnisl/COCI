#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
#define inp(x) freopen(x".inp", "r", stdin);
#define out(x) freopen(x".out", "w", stdout);
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define endl '\n'
#define bit(i,x) (x>>i)&1
#define fou(i, a, b) for(int i=(a);i<=(b);++i)
#define fod(i, a, b) for(int i=(a);i>=(b);--i)
const ll e=1e9+7;
const ll inf=1e18;
const int nmax=2e5;
const int base=311;
#define TIME (1.0*clock()/CLOCKS_PER_SEC)

struct info{
    ll left[2], right[2], full[2][2], ans;
} st[nmax*4+1];
ll a[nmax+1];
int n, q;
ll lazy[nmax*4+1];

void push(int id){
   ll val=lazy[id];
   st[id].left[0]+=val;
   st[id].left[1]-=val;
   st[id].right[0]+=val;
   st[id].right[1]-=val;

   st[id].full[0][0]+=val*2;
   st[id].full[1][1]-=val*2;
}


void get_true(int id, int l, int r){
    push(id);
    if(l!=r){
        lazy[id<<1]+=lazy[id];
        lazy[id<<1|1]+=lazy[id];
    }
    lazy[id]=0;
}

info merge(info x, info y){
    info ans;

    ans.left[0]=max({x.left[0], y.left[0],  x.ans + y.left[0], x.left[1] + y.full[0][0], 
                    x.left[0]+ y.full[1][0]});

    ans.left[1]=max({x.left[1], y.left[1],  x.ans + y.left[1], x.left[1] + y.full[0][1], 
                    x.left[0] + y.full[1][1]});
    
    ans.right[0]=max({x.right[0], y.right[0],  x.right[0] + y.ans, x.full[0][0] + y.right[1], 
                    x.full[0][1] + y.right[0]});
    
    ans.right[1]=max({x.right[1], y.right[1],  x.right[1] + y.ans, x.full[1][0] + y.right[1], 
                    x.full[1][1] + y.right[0]});
    
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j){
            ans.full[i][j]=max({x.full[i][j], y.full[i][j], 
                            x.full[i][0] + y.full[1][j], x.full[i][1]+ y.full[0][j], x.right[i] + y.left[j]});
        }

    ans.ans=max({x.ans, y.ans, x.ans+y.ans,  x.left[0] + y.right[1], x.left[1] + y.right[0]});
    return ans;
    
}



void build(int id, int l, int r){
    if(l==r){
        st[id]={{a[l], -a[l]}, {a[r], -a[r]}, {{-inf, -inf}, {-inf, -inf}}, -inf};
        return;
    }
    int m=l+r>>1;
    build(id<<1, l, m);
    build(id<<1|1,m+1,r);
    st[id]=merge(st[id<<1], st[id<<1|1]);
}

void update(int id, int l, int r, int u, int v, int val){
    get_true(id, l, r);
    if(r < u || v < l) return;
    if(u<=l && r<=v){
        lazy[id]+=val;
        get_true(id, l, r);
        return;
    }
    int m=l+r>>1;
    update(id<<1, l, m, u, v, val);
    update(id<<1|1,m+1,r,u,v,val);
    st[id]=merge(st[id<<1], st[id<<1|1]);
}

void solve(){
    cin>>n>>q;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    build(1,1,n);

    // while(p<n) p<<=1;
    // for(int i=1;i<=n;++i)
    //     cout<<st[i+p-1].left[0]<<" ";
  
    while(q--){
        int l, r, x;
        cin>>l>>r>>x;
        update(1,1,n,l,r,x);
        cout<<st[1].ans<<endl;
    }

}


int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    //  inp("");
    //  out("");
  
    solve();

    return 0;
}
