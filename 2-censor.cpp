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

map<string,string> mp;


void solve() {
}

int main() {

	mp["ควย"]="#]!";
	mp["เหี้ย"]="#]!(&";
	mp["ห้วดอ"]="#]!(&";
	mp["หมาไม่แดก"]="#]!(&@%?#";
	mp["ส้นตีน"]="#]!(&@";
	mp["อีโง่"]="#]!(&";
	mp["ไอ้โง่"]="#]!(&@";
	mp["เย็ดแม่"]="#]!(&@%";
	mp["แม่ตาย"]="#]!(&@";
	mp["โคตรพ่อโคตรแม่"]="#]!(&@%?#]!(&@";
	mp["จัญไร"]="#]!(&";
		
	for(auto x : mp ) {
		if(x.first.size() != x.second.size() )
		cout << x.first << " " << x.second << endl;
	}
	for (int i = 801 ; i <= 991 ; ++ i ){
		char tmp[20];
		sprintf(tmp,"review/%d.txt",i);
		string in(tmp);
		sprintf(tmp,"ans/censored-%d.txt",i);
		string out(tmp);
		cout << in << endl;
		char c;
		FILE *fin = fopen(in.c_str(),"r");
		string fcon;
		while(true){
			if(fscanf(fin,"%c",&c)>0)
				fcon.push_back(c);
			else break;
		}
		cout <<"________\n\n\n\n\n\n" << fcon << "_________\n\n\n\n\n\n";
		string fcout;
		int cur = 0 ;
		while(cur<fcon.size()) {
			bool found=false;
			string daword;
			for(auto x : mp ) {
				bool yes=true;
				for(int i = 0 ; i < x.first.size() ; ++ i) {
					if(cur+i>=fcon.size() || x.first[i]!=fcon[cur+i]) {
						yes=false;
					}
				}
				if(yes){
					found=true;
					daword = x.first;
					break;
				}
			}
			if(found) {
				fcout.append(mp[daword]);
				cur+=daword.size();
			} else {
				fcout.push_back(fcon[cur++]);
			}
		}
		if(fcon!=fcout){
			FILE *fout = fopen(out.c_str(),"w");
			fprintf(fout,"%s",fcout.c_str());
		}
	}
	return 0;
}
