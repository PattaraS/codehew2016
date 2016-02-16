#include <bits/stdc++.h>

using namespace std;

int ttime[500];
void solve() {
	int n;
	cin >> n;
	for(int i = 0 ; i < 500 ; ++ i )ttime[i]=0;
	for(int i = 0 ; i < n ; ++ i ){
		int a,b;
		cin>> a >> b;
		for(int x=a;x<=b;++x){
			ttime[x]++;
		}
	}
	int ans =0;
	for(int i = 0 ; i < 100 ; ++ i ){
		ans=max(ans,ttime[i]);
	}
	cout << ans << endl;
}

int main() {
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
