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


int board[20][20];
int ans = 0;
int n,m;

bool _set(int x,int y,int style,int toSet) {
	vector<int> dx,dy;
	dx=vector<int>(4,0);
	dy=vector<int>(4,0);
	if(style == 0 ) {
		dx[0]=0;
		dx[1]=0;
		dx[2]=1;
		dx[3]=2;
		dy[0]=0;
		dy[1]=1;
		dy[2]=1;
		dy[3]=1;
	}

	if(style == 1 ) {
		dx[0]=0;
		dx[1]=1;
		dx[2]=2;
		dx[3]=2;
		dy[0]=0;
		dy[1]=0;
		dy[2]=0;
		dy[3]=1;
	}
	if(style == 2 ) {
		dx[0]=0;
		dx[1]=0;
		dx[2]=0;
		dx[3]=-1;
		dy[0]=0;
		dy[1]=1;
		dy[2]=2;
		dy[3]=2;
	}
	if(style == 3 ) {
		dx[0]=0;
		dx[1]=0;
		dx[2]=0;
		dx[3]=1;
		dy[0]=0;
		dy[1]=1;
		dy[2]=2;
		dy[3]=0;
	}
		// x y x y+1 x+1 y+1 x+2 y+1 
		for(int i = 0 ; i < 4 ; ++ i ) {
			if( x+dx[i]<0 ||x+dx[i] >= n || y + dy[i] < 0 || y+dy[i]>=m)return false;
			if( board[x+dx[i]][y+dy[i]]>0 ) return false;
		}
		for(int i = 0 ; i < 4 ; ++ i ) {
			board[x+dx[i]][y+dy[i]]=toSet;
		}
		return true;

}

void _deset(int x,int y,int style) {
	vector<int> dx,dy;
	dx=vector<int>(4,0);
	dy=vector<int>(4,0);
	if(style == 0 ) {
		dx[0]=0;
		dx[1]=0;
		dx[2]=1;
		dx[3]=2;
		dy[0]=0;
		dy[1]=1;
		dy[2]=1;
		dy[3]=1;
	}

	if(style == 1 ) {
		dx[0]=0;
		dx[1]=1;
		dx[2]=2;
		dx[3]=2;
		dy[0]=0;
		dy[1]=0;
		dy[2]=0;
		dy[3]=1;
	}
	if(style == 2 ) {
		dx[0]=0;
		dx[1]=0;
		dx[2]=0;
		dx[3]=-1;
		dy[0]=0;
		dy[1]=1;
		dy[2]=2;
		dy[3]=2;
	}
	if(style == 3 ) {
		dx[0]=0;
		dx[1]=0;
		dx[2]=0;
		dx[3]=1;
		dy[0]=0;
		dy[1]=1;
		dy[2]=2;
		dy[3]=0;
	}

		for(int i = 0 ; i < 4 ; ++ i ) {
			board[x+dx[i]][y+dy[i]]=0;
		}
}

void print() {

		for(int i = 0 ; i < n ; ++ i ){
			for(int j = 0 ; j < m ; ++ j ) {
				cout << board[i][j];
			}
			cout << endl;
		}
		cout <<"_________________" << endl;
}

void dfs(int cur,int bound) {
	if(cur==bound) {
		ans++;
		return;
	}
	for(int i = 0 ; i < n ; ++ i ){
		for(int j = 0 ; j < m ; ++ j ){
			for(int k = 0 ; k < 4 ; ++ k ) {
				if(_set(i,j,k,cur+1)) {
					dfs(cur+1,bound);
					_deset(i,j,k);
				}
			}
		}
	}
}

void solve() {
	ans=0;
	cin >> n >> m ;
	int area = n*m/4;
	if(( (n*m)%4) !=0 ) {
		cout << 0 << endl;
		return;
	}
	dfs(0,area);
	cout << ans << endl;
}

int main() {
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
