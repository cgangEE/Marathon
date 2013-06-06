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
typedef vector<string> vs; 
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
#define clr(a, b) memset(a, b, sizeof(a))
#define pb push_back
#define sz(a) ((int)(a).size())
#define all(a) a.begin(), a.end()
#define mid(x, y) ((x+y)/2)
#define vp vector<P>

const int N = 50;

struct e_t {int to, cap, rev, cost;}; 

// -------------------------Minimal Cost Maximal Flow        ------------------------------------------------------------------------
template <int N>
class MCMF{           
public:          
vector<e_t> a[N*5+10]; 
int f[N*5+10], c[N*5+10];
bool inQ[N*5+10];
e_t *e[N*5+10];
int s, t;

void clear(){ rep(i, t+1) a[i].clear(); }

void add(int i, int j, int c, int cost){ 
        a[i].pb((e_t){j, c, sz(a[j]), cost}); 
        a[j].pb((e_t){i, 0, sz(a[i])-1, -cost}); 
} 

bool bellmanFord(int &flow, int &cost){
    queue<int> q; 
    clr(f, 0), clr(c, 0x7f), clr(inQ, 0);
    
    q.push(s), f[s]=INF, c[s]=0, inQ[s]=1;
    while (!q.empty()){
        int i=q.front(); q.pop(); inQ[i]=0;
        rep(k, sz(a[i])){
            e_t & ei = a[i][k];
            if (ei.cap && c[ei.to]>c[i]+ei.cost){
                f[ei.to]=min(f[i], ei.cap);
                c[ei.to]=c[i]+ei.cost;
                e[ei.to]=&ei;                
                if (!inQ[ei.to]) inQ[ei.to]=true, q.push(ei.to);
            }
            
        }
    }
    if (c[t]==0x7f7f7f7f) return false;
    flow+=f[t], cost+=c[t]*f[t];
    int i=t;
    while (i!=s){
        e[i]->cap-=f[t];
        a[i][e[i]->rev].cap+=f[t];
        i=a[i][e[i]->rev].to;
    }
    return true;
}

void minCost(int &flow, int &cost){
    while (bellmanFord(flow, cost));    
}

};

// ----------------------------------------------------------------------------------------------------------------------------------
MCMF<N*100> mcmf;


int i,j,k,m,n,l;
int pay, fine;
struct P{
    int x, y, d, t;
    P(){ d=t=0; }
	P(int x, int y):x(x),y(y){ d=t=0; }
    P operator +(const P&p){ return P(x+p.x, y+p.y); }
    P operator -(const P&p){ return P(x-p.x, y-p.y); }    
    bool ok(){ return (x>=0 && y>=0 && x<n && y<n); }
    int mht(P &p){ return abs(x-p.x)+abs(y-p.y); }
    void out(){cerr<<x<<' '<<y<<endl; }
};

vp work, snow;
vs ret;
bool SNOW[N+10][N+10], WORK[N+10][N+10];
P d[]={P(-1,0),P(1,0),P(0,-1),P(0,1),P(-2,0),P(2,0),P(0,-2),P(0,2),P(-1,1),P(1,-1),P(-1,-1),P(1,1)}; //up down left right
char c[5]="UDLR";
int x, y;
double Snf, day, snf;
int w2s[N*N+10], s2w[N*N+10];


class SnowCleaning{
public:
    string dtoi(int n){
        vi v; string ret;
        if (!n) v.pb(0);
        while (n) v.pb(n%10), n/=10;
        repd(i, sz(v)-1, 0) ret+=v[i]+'0';        
        return ret;
    }
    int drct(int i, int j){
        P p=snow[j]-work[i];
        if (p.x==0 && p.y==0) return -1;
        if (p.x!=0){
            p.x/=abs(p.x);
            rep(k, 4) if (d[k].x==p.x) return k;
        }
        if (p.y!=0){
            p.y/=abs(p.y);
            rep(k, 4) if (d[k].y==p.y) return k;
        }
    }
    char gao(int i){
		if (work[i].t && (d[work[i].d]+work[i]).ok()){
			work[i].t--;
			return work[i].d;
		}
		while(1){
			int ret=rand()%4;
			if ((d[ret]+work[i]).ok()) {
				work[i].d=ret, work[i].t=5;
				return ret;
			}
		}
    }    
    void move(int i, int k){
        if (k!=-1){
            work[i]=work[i]+d[k];
            ret.pb("M "+dtoi(i)+' '+c[k]);
        }
        SNOW[work[i].x][work[i].y]=0;
    }
    int init (int n, int pay, int fine){
        ::n=n, ::pay=pay, ::fine=fine; 
        work.clear(), clr(SNOW, 0), clr(WORK, 0);
        srand(time(NULL));
        Snf=day= snf=0;
    }

	int bcc[N+10][N+10];
	bool v[N*N+10];
	int cnt;
	void dfs(P p){
		bcc[p.x][p.y]=cnt;
		rep(k, 4){
			P q=p+d[k];
			if (q.ok() && !bcc[q.x][q.y] && SNOW[q.x][q.y]) dfs(q);
		}
	}

    vs nextDay(vi s){
        snow.clear(), ret.clear();
        
        rep(i, sz(s)/2) SNOW[s[i*2]][s[i*2+1]]=1;
        rep(i, n) rep(j, n) if (SNOW[i][j]) snow.pb(P(i,j));

		clr(v, 0), clr(bcc, 0),  cnt=0;
		rep(i, n) rep(j, n) if (!bcc[i][j] && SNOW[i][j]) ++cnt, dfs(P(i, j));
        
        mcmf.s=sz(work)+sz(snow), mcmf.t=mcmf.s+1;
        mcmf.clear();

        rep(i, sz(work)) rep(j, sz(snow)) mcmf.add(i, sz(work)+j, 1, work[i].mht(snow[j]));
        rep(i, sz(work)) mcmf.add(mcmf.s, i, 1, 0);
        rep(i, sz(snow)) mcmf.add(i+sz(work), mcmf.t, 1, 0);
        int flow, cost;
        mcmf.minCost(flow, cost);
        

        clr(w2s, -1), clr(s2w, -1);
        rep(i, sz(work)) rep(j, sz(mcmf.a[i])){
            e_t e=mcmf.a[i][j];
            int j=e.to-sz(work);
            if (e.cap==0 && j>=0 && j<sz(snow))
                w2s[i]=j, s2w[j]=i;
        }
        rep(i, sz(work))
            if (w2s[i]!=-1)
                move(i, drct(i, w2s[i])), v[bcc[snow[j].x][snow[j].y]]=1;
            else
                move(i, gao(i));
				
        Snf+=sz(s), day++;
        snf=max(4, (int)min(snf+n/4, Snf/day-n/4));
        int mw=min(100, (int)(sqrt(snf * fine / pay) * n / 4));
        
        snow.clear(); 
        rep(i, n) rep(j, n) if (SNOW[i][j]) snow.pb(P(i,j));
        rep(i, sz(snow)) if (sz(work)<mw && s2w[i]==-1 && v[bcc[snow[i].x][snow[i].y]]==0){
            work.pb(snow[i]), ret.pb("H "+dtoi(snow[i].x)+' '+dtoi(snow[i].y));
            SNOW[snow[i].x][snow[i].y]=0;
        }

        return ret;
    }

};

int main(){
    int i,j,k,m,n,l;
    SnowCleaning sc;
    cin>>i>>j>>k;
    sc.init(i,j,k);
    
    rep(i, 2000){
        cin>>n;
        vi v;
        rep(j, n*2) cin>>k, v.pb(k);
        vector<string> vs=sc.nextDay(v);
        cout<<sz(vs)<<endl;
        rep(j, sz(vs)) cout<<vs[j]<<endl;
        cout.flush();
    }
}
