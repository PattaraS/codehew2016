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


double INF = 1e100;
double EPS = 1e-12;

struct PT { 
  double x, y; 
  PT() {}
  PT(double x, double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
ostream &operator<<(ostream &os, const PT &p) {
  os << "(" << p.x << "," << p.y << ")"; 
}

bool operator == (const PT &a, const PT &b) {
  return fabs(a.x-b.x)<1e-12 && fabs(a.y-b.y)<1e-12;
}

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p)   { return PT(-p.y,p.x); }
PT RotateCW90(PT p)    { return PT(p.y,-p.x); }
PT RotateCCW(PT p, double t) { 
  return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); 
}

// project point c onto line through a and b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
  return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}

// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
  double r = dot(b-a,b-a);
  if (fabs(r) < EPS) return a;
  r = dot(c-a, b-a)/r;
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b-a)*r;
}

// compute distance from c to segment between a and b
double DistancePointSegment(PT a, PT b, PT c) {
  return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// compute distance between point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z,
                          double a, double b, double c, double d)
{
  return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) { 
  return fabs(cross(b-a, c-d)) < EPS; 
}

bool LinesCollinear(PT a, PT b, PT c, PT d) { 
  return LinesParallel(a, b, c, d)
      && fabs(cross(a-b, a-c)) < EPS
      && fabs(cross(c-d, c-a)) < EPS; 
}

// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
  if (LinesCollinear(a, b, c, d)) {
    if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
      dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
    if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
      return false;
    return true;
  }
  if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
  if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
  return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
  b=b-a; d=c-d; c=c-a;
  assert(dot(b, b) > EPS && dot(d, d) > EPS);
  return a + b*cross(c, d)/cross(b, d);
}

// compute center of circle given three points
PT ComputeCircleCenter(PT a, PT b, PT c) {
  b=(a+b)/2;
  c=(a+c)/2;
  return ComputeLineIntersection(b, b+RotateCW90(a-b), c, c+RotateCW90(a-c));
}

// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<PT> &p, PT q) {
  bool c = 0;
  for (int i = 0; i < p.size(); i++){
    int j = (i+1)%p.size();
    if ((p[i].y <= q.y && q.y < p[j].y || 
      p[j].y <= q.y && q.y < p[i].y) &&
      q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
      c = !c;
  }
  return c;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<PT> &p, PT q) {
  for (int i = 0; i < p.size(); i++)
    if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
      return true;
    return false;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<PT> CircleLineIntersection(PT a, PT b, PT c, double r) {
  vector<PT> ret;
  b = b-a;
  a = a-c;
  double A = dot(b, b);
  double B = dot(a, b);
  double C = dot(a, a) - r*r;
  double D = B*B - A*C;
  if (D < -EPS) return ret;
  ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
  if (D > EPS)
    ret.push_back(c+a+b*(-B-sqrt(D))/A);
  return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<PT> CircleCircleIntersection(PT a, PT b, double r, double R) {
  vector<PT> ret;
  double d = sqrt(dist2(a, b));
  if (d > r+R || d+min(r, R) < max(r, R)) return ret;
  double x = (d*d-R*R+r*r)/(2*d);
  double y = sqrt(r*r-x*x);
  PT v = (b-a)/d;
  ret.push_back(a+v*x + RotateCCW90(v)*y);
  if (y > 0)
    ret.push_back(a+v*x - RotateCCW90(v)*y);
  return ret;
}

// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
double ComputeSignedArea(const vector<PT> &p) {
  double area = 0;
  for(int i = 0; i < p.size(); i++) {
    int j = (i+1) % p.size();
    area += p[i].x*p[j].y - p[j].x*p[i].y;
  }
  return area / 2.0;
}

double ComputeArea(const vector<PT> &p) {
  return fabs(ComputeSignedArea(p));
}

PT ComputeCentroid(const vector<PT> &p) {
  PT c(0,0);
  double scale = 6.0 * ComputeSignedArea(p);
  for (int i = 0; i < p.size(); i++){
    int j = (i+1) % p.size();
    c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
  }
  return c / scale;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<PT> &p) {
  for (int i = 0; i < p.size(); i++) {
    for (int k = i+1; k < p.size(); k++) {
      int j = (i+1) % p.size();
      int l = (k+1) % p.size();
      if (i == l || j == k) continue;
      if (SegmentsIntersect(p[i], p[j], p[k], p[l])) 
        return false;
    }
  }
  return true;
}

vector<PT> _merge(vector<PT> v1,vector<PT> v2) {
  map<pair<double,double>,bool> inV1,inV2;
  for(auto x : v1) inV1[{x.x,x.y}]=true;
  for(auto x : v2) inV2[{x.x,x.y}]=true;
  int st,st2;
  for(int i = 0 ; i < v1.size() ; ++ i ) {
    if(inV2[{v1[i].x,v1[i].y}]){
      st=i;
      for(int j = 0 ; j < v2.size() ; ++ j ) {
        if(v2[j]==v1[i]) {
          st2=j;
        }
      }
      break;
    }
  }
  int cur=st,cur2=st2;
  vector<PT> re1,re2;
  for(int i = cur ; i < v1.size() ; ++ i ) re1.push_back(v1[i]);
  for(int i = 0 ; i < cur ; ++ i ) re1.push_back(v1[i]);
  for(int i = cur2; i < v2.size(); ++ i ) re2.push_back(v2[i]);
  for(int i = 0 ; i < cur2 ;++ i ) re2.push_back(v2[i]);
  cur=0;
  cur2=0;
  vector<PT> ret;
  while(cur<re1.size()&&cur2<re2.size()) {
    PT from1 =re1[cur];
    PT from2 = re2[cur2];  
    if(inV2[{from1.x,from1.y}]&&inV1[{from2.x,from2.y}]) {
      ret.push_back(from1);
      cur++;cur2++;
    } else if (inV2[{from1.x,from1.y}]) {
      ret.push_back(from2);
      cur2++;
    } else {
      ret.push_back(from1);
      cur++;
    }
  }
  while(cur<re1.size()) {
    ret.push_back(re1[cur++]);
  }
  while(cur<re2.size()) {
    ret.push_back(re2[cur++]);
  }

  return ret;
}

int main() {
	vector<string> line1 = split_line_string(get_line());
	vector<string> line2 = split_line_string(get_line());
	vector<PT> polygon1,polygon2;
	for(auto x : line1) {
		PT tmp;
		sscanf(x.c_str(),"%lf,%lf",&tmp.x,&tmp.y);
		polygon1.push_back(tmp);
	}

	for(auto x : line2) {
		PT tmp;
		sscanf(x.c_str(),"%lf,%lf",&tmp.x,&tmp.y);
		polygon2.push_back(tmp);
	}

	// for(auto x : polygon1 ) {
	// 	printf("%lf %lf\n",x.x,x.y);
	// }
	
	// printf("\n\n\n\n\n\n\n");

	// for(auto x : polygon2 ) {
	// 	printf("%lf %lf\n",x.x,x.y);
	// }
	
	vector<PT> ans;
	polygon2.push_back(polygon2[0]);
	polygon1.push_back(polygon1[0]);
  PT last = polygon2[0];
  if(PointInPolygon(polygon1,last)||PointOnPolygon(polygon1,last)){
    //ans.push_back(last);
  }
  for(int i = 1 ; i < polygon2.size() ; ++ i ) {
    PT cur = polygon2[i];
		bool in = PointInPolygon(polygon1,last)||PointOnPolygon(polygon1,last);
    bool nxtIn = PointInPolygon(polygon1,cur)||PointOnPolygon(polygon1,cur);
    if(in^nxtIn) {
      if(in) {
        for(int j = 1 ; j < polygon1.size() ; ++ j ) {
          if( SegmentsIntersect(last,cur,polygon1[j-1],polygon1[j]) ) {
            PT tmp = ComputeLineIntersection(last,cur,polygon1[j-1],polygon1[j]);
            ans.push_back(tmp);
            break;
          }
        }
      } else {
        for(int j = 1 ; j < polygon1.size() ; ++ j ) {
          if( SegmentsIntersect(last,cur,polygon1[j-1],polygon1[j]) ) {
            PT tmp = ComputeLineIntersection(last,cur,polygon1[j-1],polygon1[j]);
            ans.push_back(tmp);
            ans.push_back(cur);
            break;
          }
        }
      }
    } else if( in&&nxtIn) {
      ans.push_back(cur);
    }
    last=cur;
	}

  last=polygon1[0];
  vector<PT> ans2;
  for(int i = 1 ; i < polygon1.size() ; ++ i ) {
    PT cur = polygon1[i];
    bool in = PointInPolygon(polygon2,last)||PointOnPolygon(polygon2,last);
    bool nxtIn = PointInPolygon(polygon2,cur)||PointOnPolygon(polygon2,cur);
    if(in^nxtIn) {
      if(in) {
        for(int j = 1 ; j < polygon2.size() ; ++ j ) {
          if( SegmentsIntersect(last,cur,polygon2[j-1],polygon2[j]) ) {
            PT tmp = ComputeLineIntersection(last,cur,polygon2[j-1],polygon2[j]);
            ans2.push_back(tmp);
            break;
          }
        }
      } else {
        for(int j = 1 ; j < polygon2.size() ; ++ j ) {
          if( SegmentsIntersect(last,cur,polygon2[j-1],polygon2[j]) ) {
            PT tmp = ComputeLineIntersection(last,cur,polygon2[j-1],polygon2[j]);
            ans2.push_back(tmp);
            ans2.push_back(cur);
            break;
          }
        }
      }
    } else if( in&&nxtIn) {
      ans2.push_back(cur);
    }
    last=cur;
  }

  // for(auto x : ans ) {
  //   printf("[%lf %lf]\n",x.x,x.y);
  // }

  // for(auto x : ans2 ) {
  //   printf("{%lf %lf}\n",x.x,x.y);
  // }
  vector<PT> realAns = _merge(ans,ans2);

  // for(auto x : realAns){
  //   printf("[[%lf %lf]]\n",x.x,x.y);
  // }
  int firstIdx =0 ;
  for(int i = 1 ; i < realAns.size() ; ++ i ) {
    if(dot(realAns[i],realAns[i]) < dot(realAns[firstIdx],realAns[firstIdx])) {
      firstIdx=i;
    }
  }
  cout << realAns.size() << endl;
  for(int i = 0 ; i < realAns.size() ; ++ i ) {
    int toPrint = firstIdx+i;
    toPrint%=realAns.size();
    cout << realAns[toPrint].x <<"," << realAns[toPrint].y << " " ;
  }
  cout << endl;
	return 0;
}
