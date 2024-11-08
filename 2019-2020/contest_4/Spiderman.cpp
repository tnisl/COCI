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
const int nmax=3e5;
const int maxa=1e6;
const int base=311;
//
int n, k;
vector<int> d[maxa+1];
int cnt[maxa+1];
int h[nmax+1];
int ma0=0;
int sz=0;
void sieve(){
  
  for(int i=k+1;i<=maxa;++i){
    if(cnt[i])
      for(int j=i;j+k<=maxa;j+=i)
         if(cnt[j + k]) d[j].push_back(i);
  }
}

void solve(){
  cin>>n>>k;
  int cnt0=0;
  for(int i=1;i<=n;++i) cin>>h[i], ++cnt[h[i]], cnt0+=(h[i]>k);
  sieve();
  int ans[n+1];
  
  for(int i=n;i>=1;--i){
    ans[i]=0;
    if(k > h[i]) continue;
    if(k==h[i]){
      ans[i]=cnt0;
      continue;
    }
    for(auto &x:d[h[i]-k])
       ans[i]+=cnt[x];
    if(k==0) --ans[i];
  }
  for(int i=1;i<=n;++i)
    cout<<ans[i]<<" ";
}


int32_t main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0),cout.tie(0);
  #ifndef ONLINE_JUDGE
  freopen(".inp", "r", stdin);
  freopen(".out", "w", stdout);
  #endif

  solve();
  return 0;
}