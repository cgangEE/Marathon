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
int sgn(double d){ return d<-eps?-1:d>eps; }


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


int i,j,k,m,n,l;
vector<C> c;
vector<P> p;

void move(C &c, C &c2, double  d){
	P v=c.p-c2.p;
	c.p=c.p+v*(5*d/v.len());
}

void spread(){
		bool flag=true;
		while (flag){
			flag=false;
			rep(i, n) repf(j, i+1, n-1){
				double d=c[i].p.dis(c[j].p);
				if (d>c[i].r+c[j].r+eps) continue;
			//	cerr<<d<<endl;
				if (c[i].m<c[j].m) move(c[i], c[j], c[i].r+c[j].r-d);
				else move(c[j], c[i], c[i].r+c[j].r-d);

				/*

				double x=c[j].m/(c[i].m+c[j].m)*(c[i].r+c[j].r-d);
				double y=c[i].m/(c[i].m+c[j].m)*(c[i].r+c[j].r-d);
				P v=c[i].p-c[j].p;
				c[i].p=c[i].p+v*((1+0.90)*x/v.len());
				c[j].p=c[j].p-v*((1+0.90)*y/v.len());
				*/
				flag=true;
			}
		}
}

void gather(){
	for (double etha=0.9; etha>=0.1; etha-=0.1)
		rep(i, n){// rep(j, 360){
			P pp=p[i]+(c[i].p-p[i])*etha;
			bool cross=false;
			rep(k, n) if (i!=k){
				double d=pp.dis(c[k].p);
				if (d<=c[i].r+c[k].r+eps){
				   cross=true; break;
				}
			}
			if (!cross){
				c[i].p=pp; break;
			}
		}
}

class CirclesSeparation{
public:
	vd minimumWork(vd x, vd y, vd r, vd m){
		n=sz(x), c.clear(), p.clear();
		rep(i, n) p.pb(P(x[i], y[i]));
		rep(i, n) c.pb(C(x[i], y[i], r[i], m[i]));

		
		spread();
		gather();


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
	ret=xxx.minimumWork(x, y, r, m);

	rep(i, 2*n) printf("%lf\n", ret[i]);
	cout.flush();
	return 0;
}

