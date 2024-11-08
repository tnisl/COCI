#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define endl '\n'
#define Bit(i,x) ((x>>i)&1)
#define Flip(i,msk) (msk^(1<<i))
#define TIME (1.0*clock()/CLOCKS_PER_SEC)

//const
const ll e=1e9+7;
const ll inf=1e18;
const int nmax=1e3+20;
const int base=311;
//
int m, n;
vector<int> adj[nmax];
int d[nmax];
ll dp1[nmax][nmax]; //not choose u 
ll dp2[nmax][nmax]; //must choose u;
ll dp3[nmax][nmax]; //can choose u or not

int sz[nmax];
void cal_sz(int u, int pre){
    sz[u]=1;
    for(int &v:adj[u]){
      if(v==pre) continue;
      cal_sz(v,u);
      sz[u]+=sz[v];
    }
} 

void dfs(int u, int pre){
   dp1[u][0]=0;
   dp3[u][0]=0;
   int cur_size = 1; 
    for(int &v:adj[u]){
      if(v==pre) continue;
      dfs(v,u);
      for(int d1=cur_size;d1>=0;--d1)
        for(int d2=sz[v];d2>=0;--d2){
          
            dp1[u][d1+d2]=min(dp1[u][d1+d2], dp1[u][d1] + dp3[v][d2]); 
            dp3[u][d1+d2]=min(dp3[u][d1+d2], dp1[u][d1+d2]);

            if(u!=0){
              dp2[u][d1+d2+2]=min(dp2[u][d1+d2+2],dp1[u][d1] + d[u] + d[v] + dp1[v][d2]);

             dp2[u][d1+d2]=min(dp2[u][d1+d2], dp2[u][d1] + dp3[v][d2]);
            dp2[u][d1+d2+1]=min(dp2[u][d1+d2+1], dp2[u][d1] + d[v] + dp1[v][d2]);
            dp2[u][d1+d2+1]=min(dp2[u][d1+d2+1], dp1[u][d1] + d[u] + dp2[v][d2]);
            }


            dp3[u][d1+d2]=min(dp3[u][d1+d2], dp2[u][d1+d2]);
             dp3[u][d1+d2+1]=min(dp3[u][d1+d2+1], dp2[u][d1+d2+1]);
             dp3[u][d1+d2+2]=min(dp3[u][d1+d2+2], dp2[u][d1+d2+2]);
             

        }
      cur_size+=sz[v];
    }
}
void init(){

  cin>>n>>m;
  for(int i=1;i<=n;++i)
    cin>>d[i];

 
  for(int i=1;i<=m;++i){
    int x, y;
    cin>>x>>y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

memset(dp1,0x3f, sizeof(dp1));
memset(dp2, 0x3f, sizeof(dp2));
memset(dp3, 0x3f, sizeof(dp3));
  for(int i=1;i<=n;++i){
    if(sz[i]==0){
      cal_sz(i,0);
      adj[i].push_back(0);
      adj[0].push_back(i);
    }
  }
  sz[0]=n+1;

}

void solve(){
    init();
    dfs(0,0);
    vector<int> c;
    vector<ll> S;


  for(int i=2;i<=n;++i){
      c.push_back(i);
      S.push_back(dp3[0][i]);
  }

  stable_sort(c.begin(),c.end(), [&](int x, int y)->bool{
    return dp3[0][x] <=dp3[0][y];
  });
  sort(S.begin(),S.end());

  for(int i=1;i<c.size();++i)
    c[i]=max(c[i], c[i-1]);
   int q;
   cin>>q;
   while(q--){
      ll s;
      cin>>s;
      if(c.size()==0 || s < S[0]) {cout<<0<<endl;continue;}
      int k=upper_bound(S.begin(), S.end(), s) -S.begin();
      cout<<c[k-1]<<endl;
   }
  
}

int32_t main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0),cout.tie(0);
  #ifndef ONLINE_JUDGE
 freopen(".inp", "r", stdin);
 freopen(".out", "w", stdout);
  #endif
 // cout<<"hello";
  solve();
  return 0;
}
