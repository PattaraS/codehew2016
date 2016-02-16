#include <bits/stdc++.h>

using namespace std;

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
