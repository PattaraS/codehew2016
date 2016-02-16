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



void solve() {
	int n,w,h;
	cin >> n >> w >> h;
	vector<pair<int,int>> shop;
	for(int i = 0 ; i < n ; ++ i ){
		int a,b;
		cin >> a  >> b;
		shop.push_back({a,b});
	}
	int q;
	cin >> q;
	int ans = 0 ;
	for(int i = 0 ; i < q ; ++ i ){
		int a,b,c,d;
		cin >> a >> b >> c >> d;
		int x1,y1,x2,y2;
		x1=a;y1=b-d+1;
		x2=a+c-1;y2=b;
		for(auto x : shop ) {
			if(x.first >=x1&&x.first<=x2&&x.second>=y1&&x.second<=y2) ans++;
		}
	}
	cout << ans << endl;
}

int main() {
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
