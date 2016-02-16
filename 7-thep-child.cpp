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


int ttime[500];
void solve() {
	int n;
	cin >> n;
	vector<int> v(n,0);
	for(int i = 0 ; i < n ; ++ i ) cin >> v[i];
	for(int i = 0 ; i < n ; ++ i ) {
		for(int k = 1 ; ; k ++ ) {
			if(i+k>=n)break;
			bool ok =true;
			for(int j = i + k ; j < n ; ++ j ) {
				if(v[j]!= v[i+ ( (j-i)%k)])ok=false;
			}
			if(ok && (  ( n - i + 1) / k >=2 ) ){
				cout <<"yes"<<endl;
				return;
			}
		}
	}
	cout <<"no"<<endl;
}

int main() {
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
