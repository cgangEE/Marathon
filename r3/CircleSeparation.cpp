#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <cctype>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <stack>
using namespace std;
typedef vector<int> vi;
typedef map<int,int> mii;
typedef long long ll;
template <class T> void checkmax(T &t, T x){if (x > t) t = x;}
template <class T> void checkmin(T &t, T x){if (x < t) t = x;}
template <class T> void _checkmax(T &t, T x){if (t == -1 || x > t) t = x;}
template <class T> void _checkmin(T &t, T x){if (t == -1 || x < t) t = x;}
#define INF (INT_MAX/10)
#define SQR(x) ((x)*(x))
#define rep(i, n) for (int i=0; i<(n); ++i)
#define repf(i, a, b) for (int i=(a); i<=(b); ++i)
#define repd(i, a, b) for (int i=(a); i>=(b); --i)
#define iter(v) __typeof((v).begin())
#define foreach(it, v) for (iter(v) it = (v).begin(); it != (v).end(); it++)
#define fill(a, b) memset(a, b, sizeof(a))
#define pb push_back
#define sz(a) ((int)(a).size())
#define all(a) a.begin(), a.end()
#define mid(x, y) ((x+y)/2)
#define vp vector<P>
#define itr iterator
typedef vector<double> vd;

const double eps=1e-9;
int sgn(double d){ return d<-eps?-1:d>eps; }

int i,j,k,m,n,l;

struct P{
	double x, y;
	P(){}
	P(double x, double y):x(x),y(y){}
	P operator +(const P &p)const{ return P(x+p.x, y+p.y); }
	P operator -(const P &p)const{ return P(x-p.x, y-p.y); }
	P operator *(double k)const{ return P(x*k, y*k); }
	P operator /(double k)const{ return P(x/k, y/k); }
	double dis(P &p){ return sqrt(SQR(x-p.x)+SQR(y-p.y));}
	double len(){ return sqrt(SQR(x)+SQR(y)); }
};

struct C{
	P p; double r, m;
	C(){}
	C(double x, double y, double r, double m):p(P(x,y)), r(r), m(m){}
};

class CirclesSeparation{
public:
	vd minimunWork(vd x, vd y, vd r, vd m){
		n=sz(x);
		vector<C> c;
		rep(i, n) c.pb(C(x[i], y[i], r[i], m[i]));
		bool flag=true;
		while (flag){
			flag=false;
			rep(i, n) repf(j, i+1, n-1){
				double d=c[i].p.dis(c[j].p);
				if (sgn(c[i].r+c[j].r-d)<0) continue;
				double x=c[j].m/(c[i].m+c[j].m)*(c[i].r+c[j].r-d);
				double y=c[i].m/(c[i].m+c[j].m)*(c[i].r+c[j].r-d);
				P v=c[i].p-c[j].p;
				c[i].p=c[i].p+v*((1+0.9)*x/v.len());
				c[j].p=c[j].p-v*((1+0.9)*y/v.len());
		//		if (i==j-1) cerr<<i<<' '<<j<<' '<<c[i].r+c[j].r-d<<endl;
				flag=true;
			}
		}
		vd ret;
		rep(i, n) ret.pb(c[i].p.x), ret.pb(c[i].p.y);
		return ret;
	}
};

int main(){
	cerr<<"ft"<<endl;
	int n;
	vd x, y, r, m, ret;
	double k;

	scanf("%d", &n);
	rep(i, n) scanf("%lf", &k), x.pb(k);
	rep(i, n) scanf("%lf", &k), y.pb(k);
	rep(i, n) scanf("%lf", &k), r.pb(k);
	rep(i, n) scanf("%lf", &k), m.pb(k);

	CirclesSeparation xxx;
	ret=xxx.minimunWork(x, y, r, m);

	rep(i, 2*n) printf("%lf\n", ret[i]);
	cout.flush();
	return 0;
}

