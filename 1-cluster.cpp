#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll mod = 1e9 + 7;

ll add_mod(ll a,ll b) {
	return ( (a%mod) + (b%mod) )%mod;
}

ll mul_mod(ll a,ll b) {
	return ( (a%mod) * (b%mod) ) %mod;
}

ll pow_mod(ll a,ll p) {
	if(p==0) return 1;
	if(p==1) return a%p;
	ll ret = pow_mod(a,p>>1);
	ret = mul_mod(ret,ret);
	if(p&1) ret = mul_mod(ret, a);
	return ret;
}

vector<int> gen_prime(int bound) {
	vector<bool> is_prime(bound+1,true);
	vector<int> ret;
	for(int i = 2 ; i <= bound ; ++i) {
		if(is_prime[i]) {
			ret.push_back(i);
			for(int j = i+i ; j <= bound ; j += i) {
				is_prime[j]=false;
			}
		}
	}
	return ret;
}

string get_line() {
	char buff[50100];
	cin.getline(buff, 50000);
	return string(buff);
}

vector<string> split_line_string(string in) {
	stringstream ss;
	ss << in;
	vector<string> ret;
	string buff = "";
	while(ss >> buff) {
		ret.push_back(buff);
	}
	return ret;
}

vector<int> split_line_int(string in) {
	stringstream ss;
	ss << in;
	vector<int> ret;
	int buff = -1;
	while(ss >> buff) {
		ret.push_back(buff);
	}
	return ret;
}

int dfs(int x,int y,vector<vector<int>> &a) {
	if(a[x][y]==0)return 0;
	int ret = 1; 
	a[x][y]=0;
	for(int i = -1 ; i <= 1 ; ++ i ){
		for(int j = -1 ; j<= 1 ; ++ j ) {
			if(i!=0&&j!=0)continue;
			if(x+i>=0&&x+i<a.size()&& y+j >=0 && y+j<=a[0].size() ) {
				if(a[x+i][y+j]) {
					ret+=dfs(x+i,y+j,a);
				}
			}
		}
	}
	return ret;
}

void solve() {
	int m,n;
	cin >> m >> n ;
	int r;
	cin >> r;
	vector<vector<int> >  a (m+10,vector<int>(n+10,0));
	for(int i = 0 ; i < r;  ++ i ) {
		int x,y;
		cin >> x >> y;
		a[x][y]=1;
	}
	int ans = 0 ;
	for(int i = 0; i < m ; ++ i ){
		for(int j = 0 ; j < n ; ++ j ){
			if(a[i][j]) {
				ans=max(ans,dfs(i,j,a));
			}
		}
	}
	cout << ans << endl;
}

int main() {
	int t;
	cin >> t;
	while(t--)solve();
	return 0;
}
