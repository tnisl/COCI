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
const int nmax=4e4;
const int base=311;
const int maxa=1e9;
//
int n, k;
string s[2002];
long long C[2002][2002];

void build(){
  C[0][0]=1;
  for(int i=1;i<=2000;++i)
    C[0][i]=1;
  
  for(int i=1;i<=2000;++i)
    for(int j=i;j<=2000;++j){
      C[i][j]=C[i][j-1] + C[i-1][j-1];
      if(C[i][j]>=e) C[i][j]-=e;
    }
}


void solve(){
  build();
cin>>n>>k;
for(int i=1;i<=n;++i)
  cin>>s[i], sort(s[i].begin(),s[i].end());

sort(s+1,s+1+n);
s[n+1]="#";
vector<int> S;
S.push_back(0);
for(int i=2, c=1;i<=n+1;++i){
    if(s[i]!=s[i-1]) S.push_back(c), c=1;
    else ++c;
}

 

int sz=S.size()-1;

ll dp[sz+1][k+1];

dp[0][0]=1;
for(int i=1;i<=sz;++i)
    dp[0][i]=0;
for(int i=1;i<=sz;++i)
  for(int j=0;j<=k;++j){
      dp[i][j]=0;
    for(int c=0;c<=S[i] && c*(c-1)/2 <=j;++c){
      dp[i][j]+=dp[i-1][j-c*(c-1)/2] * C[c][S[i]]%e;
      if(dp[i][j]>=e) dp[i][j]-=e;
    }
  }
  cout<<dp[sz][k];

  
}



int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0),cout.tie(0);
  #ifndef ONLINE_JUDGE
  // freopen(".inp", "r", stdin);
  // freopen(".out", "w", stdout);
  #endif

  solve();
  return 0;
}