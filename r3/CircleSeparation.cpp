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

struct P{
	double x, y;
	P(){}
	P(double x, double y):x(x),y(y){}
	P operator +(const P &p)const{ return P(x+p.x, y+p.y); }
	P operator -(const P &p)const{ return P(x-p.x, y-p.y); }
	P operator *(double k)const{ return P(x*k, y*k); }
	P operator /(double k)const{ return P(x/k, y/k); }
	P rl(double ang)const{
		double c=cos(ang), s=sin(ang);
		return P(x*c-y*s, y*c+x*s);
	}
	P rr(double ang)const{
		double c=cos(ang), s=sin(ang);
		return P(x*c+y*s, y*c-x*s);
	}
	double dis(P &p){ return sqrt(SQR(x-p.x)+SQR(y-p.y));}
	double len(){ return sqrt(SQR(x)+SQR(y)); }
};

struct C{
	int i;
	P p; double r, m;
	C(){}
	C(int i, P p, double r, double m):i(i),p(p),r(r),m(m){}
};


int i,j,k,m,n,l;
vector<C> c;
vector<P> p;

bool cmpM(const C &a, const C &b){return a.m*b.r>b.m*a.r; }
bool cmpI(const C &a, const C &b){return a.i<b.i; }

inline void gao(int i){
    for (double d=0; d<=9; d+=0.01) for (double ang=0; ang<3.14*2; ang+=0.01){
        P v=P(cos(ang), sin(ang))*d+c[i].p;
        bool flag=true;
        repf(j, 0, i-1) if (SQR(v.x-c[j].p.x)+SQR(v.y-c[j].p.y)<SQR(c[i].r+c[j].r+eps)){
            flag=false; break;
        }
        if (flag){
            c[i].p=v; return;
        }
    }
}

class CirclesSeparation{
public:
	vd minimumWork(vd x, vd y, vd r, vd m){
		n=sz(x), c.clear(), p.clear();
		rep(i, n) p.pb(P(x[i], y[i])), c.pb(C(i, p[i], r[i], m[i]));
		sort(all(c), cmpM);
		rep(i, n) gao(i);

		sort(all(c), cmpI);
		vd ret;
		rep(i, n) ret.pb(c[i].p.x), ret.pb(c[i].p.y);
		return ret;
	}
};

int main(){
	int n;
	vd x, y, r, m, ret;
	double k;

	scanf("%d", &n);
	rep(i, n) scanf("%lf", &k), x.pb(k);
	rep(i, n) scanf("%lf", &k), y.pb(k);
	rep(i, n) scanf("%lf", &k), r.pb(k);
	rep(i, n) scanf("%lf", &k), m.pb(k);

	CirclesSeparation xxx;
	ret=xxx.minimumWork(x, y, r, m);

	rep(i, 2*n) printf("%.12lf\n", ret[i]);
	cout.flush();
	return 0;
}

