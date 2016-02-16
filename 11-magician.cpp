#include <bits/stdc++.h>

using namespace std;

struct SuffixArray {
  const int L;
  string s;
  vector<vector<int> > P;
  vector<pair<pair<int,int>,int> > M;

  SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L) {
    for (int i = 0; i < L; i++) P[0][i] = int(s[i]);
    for (int skip = 1, level = 1; skip < L; skip *= 2, level++) {
      P.push_back(vector<int>(L, 0));
      for (int i = 0; i < L; i++) 
	M[i] = make_pair(make_pair(P[level-1][i], i + skip < L ? P[level-1][i + skip] : -1000), i);
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++) 
	P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
    }    
  }

  vector<int> GetSuffixArray() { return P.back(); }

  // returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
  int LongestCommonPrefix(int i, int j) {
    int len = 0;
    if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
      if (P[k][i] == P[k][j]) {
	i += 1 << k;
	j += 1 << k;
	len += 1 << k;
      }
    }
    return len;
  }
};

char buff[101000];

int main() {
	int t;
	cin >> t;
	vector<string> v;
	for(int i = 0 ; i < t ; ++ i ) {
		scanf("%[^$]$",buff);
		v.push_back(string(buff));
	}

	//for(auto x : v ) cout << x << "\n\n\n\n\n\n\n\n\n\n\n\n" << endl;

	for(auto x : v ) {
		SuffixArray sa(x);
		int ans = 0 ;
		vector<int> vv = sa.GetSuffixArray();
		for(int i = 0 ; i < x.size() ; ++ i ){
			for(int j = 0 ; j < x.size() ; ++ j ) {
				if(i!=j){
					int z = sa.LongestCommonPrefix(i,j);
					if(sa.LongestCommonPrefix(i,j) > ans ) {
						printf("[%d,%d]\n",i,j);
						cout << x.substr(i,z) << "::" << endl;
						cout << x.substr(j,z) << "::" << endl;

					}
					ans=max(ans,sa.LongestCommonPrefix(i,j));
				}
			}
		}
		cout << ans << endl;
	}
	
	return 0;
}
