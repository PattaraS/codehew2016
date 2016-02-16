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



map<int,int> users;
vector<int> reviews[3000000];
char buff[101000];
map<int,bool> isFake;
int main() {
	FILE *f = fopen("users.csv","r");
	int a,b;
	while(fscanf(f,"%d,%d",&a,&b)>0) {
		users[a]=b;
	}

	for(auto x : users ) {
		cout << x.first << " " << x.second << endl;
	}
	
	FILE *f2 = fopen("reviews.csv","r");
	int c;
	while(fscanf(f2,"%d,%d,%d,%[^\r]\n",&a,&b,&c,buff) > 0) {
		int len = strlen(buff);
		reviews[b].push_back(a);
		if(c==5 && users[b] < 100 && strlen(buff) <= 100 ) {isFake[a]=true;
		cout << a << " " << b << " " << c << " " << string(buff) << endl;
		cout << "\n\n\n\n\n\n\n\__________________\n\n\n\n\n\n\n\n\n" ;
		}
	}
	vector<int> ans;
	for(int i = 0 ; i < 3000000 ; ++ i ) {
		if(reviews[i].size()) {
			sort(reviews[i].begin(),reviews[i].end());
			if(isFake[reviews[i][0]]) {
				ans.push_back(reviews[i][0]);
			}
		}
	}
	sort(ans.begin(),ans.end());
	for(auto x : ans ) {
		cout << x << endl;
	}
	return 0;
}
