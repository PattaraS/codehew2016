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
}

vector<int> v[2000000];

int main() {
	int a,b,c;
	while(scanf("%d,%d,%d",&a,&b,&c)>0){
		v[b].push_back(c);
	}
	double maxsd=0;
	int maxid = 0;
	for(int i = 0 ; i < 2000000 ; ++ i ) {
		if(v[i].size()>=10) {
			double sum = 0 ;
			for(auto x : v[i]) sum+=x;
			sum/=v[i].size();
			double rmq = 0;
			for(auto x : v[i]) {
				rmq+= (x-sum)*(x-sum);
			}
			rmq/=(v[i].size());
			rmq=sqrt(rmq);	
			if(rmq>maxsd) {
				maxsd=rmq;
				maxid=i;
			}
		}
	}
	cout << maxid << endl << maxsd << endl;
	return 0;
}
