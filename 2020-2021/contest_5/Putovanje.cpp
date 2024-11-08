#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define fou(i,a,b) for(int i=(a);i<=(b);++i)
#define fod(i,a,b) for(int i=(a);i>=(b);--i)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<ll,int> lli;

const int nmax=2e5;
const ll inf=1e18;
const ll e=1e9+7;

vector<ii> a[nmax+1];
int par[nmax+1][18];
int n, c1[nmax+1], c2[nmax+1], h[nmax+1];
int cnt[nmax+1], pre[nmax+1];



void input(){
    cin>>n;
    fou(i,1,n-1){
        int x, y;
        cin>>x>>y>>c1[i]>>c2[i];
        a[x].pb({i,y});
        a[y].pb({i,x});
    }
}

void dfs(int u, int pre){
    par[u][0]=pre;
    h[u]=h[pre]+1;
    for(ii &x:a[u])
        if(x.se!=pre) dfs(x.se,u);
}

void build(){
    fou(i,1,17)
        fou(u,1,n)
            par[u][i]=par[par[u][i-1]][i-1];
}

int lca(int u, int v){
    if(h[u] > h[v]) swap(u,v);
    fod(i,17,0)
        if(h[u]<=h[par[v][i]])
            v=par[v][i];
    fod(i,17,0)
        if(par[u][i]!=par[v][i])
            u=par[u][i],
            v=par[v][i];
    if(u!=v) return par[u][0];
    return u;
}

void upd(int u, int p){
    for(ii &x:a[u]){
        int v=x.se, id=x.fi;
        if(v==p) continue;
        upd(v,u);
        cnt[id]+=pre[v];
        pre[u]+=pre[v];
    }
}

void solve(){
    input();
    dfs(1,0);
    build();
    fou(i,1,n-1){
        int p=lca(i,i+1);
        ++pre[i];
        ++pre[i+1];
        pre[p]-=2;
    }
    upd(1,0);
    ll ans=0;
    fou(i,1,n-1)
        ans+=min(1ll*c1[i]*cnt[i], 1ll*c2[i]);
    cout<<ans;

}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 //   freopen(".inp", "r", stdin);
  //  freopen(".out", "w", stdout);
    solve();
    return 0;
}
