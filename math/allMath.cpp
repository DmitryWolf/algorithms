#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;

namespace Math {
    const long long MOD = 1e9 + 7;


    namespace euclid {
        long long gcd(long long a, long long b) {
            return b ? gcd(b, a % b) : a;
        }
        long long lcm(long long a, long long b) {
            return a / gcd(a, b) * b;
        }
        long long gcdex(long long a, long long b, long long& x, long long& y) {
            if (!b) {
                x = 1;
                y = 0;
                return a;
            }
            long long x1, y1, d = gcdex(b, a % b, x1, y1);
            x = y1;
            y = x1 - a / b * y1;
            return d;
        }
        long long inv(long long a, long long mod = MOD) {
            long long x, y;
            return a && gcdex(a, mod, x, y) == 1 ? (x % mod + mod) % mod : 0;
        }
    };
    namespace primes {
        // O(sqrt(N))
        bool isPrime(int n) {
            if (n < 2)
                return 0;
            for (long long d = 2; d * d <= n; d++)
                if (n % d == 0)
                    return 0;
            return 1;
        }

        // O(sqrt(N))
        vector<long long> getPrimeDivisors(long long n) {
            vector<long long> primeDivisors;
            for (long long d = 2; d * d <= n; d++) {
                if (n % d == 0) {
                    primeDivisors.push_back(d);
                    while (n % d == 0)
                        n /= d;
                }
            }
            if (n != 1)
                primeDivisors.push_back(n);
            return primeDivisors;
        }

        // O(sqrt(N))
        vector<long long> factorize(long long n) {
            vector<long long> factorization;
            for (long long d = 2; d * d <= n; d++) {
                while (n % d == 0) {
                    factorization.push_back(d);
                    n /= d;
                }
            }
            if (n != 1)
                factorization.push_back(n);
            return factorization;
        }

        // O(N)
        vector<int> getPrimes(int n) {
            vector<int> minDivisor(n + 1), primes;
            for (int i = 2; i < minDivisor.size(); i++) {
                if (!minDivisor[i]) {
                    minDivisor[i] = i;
                    primes.push_back(i);
                }
                for (int j = 0; j < primes.size() && primes[j] <= minDivisor[i] && 1LL * i * primes[j] < minDivisor.size(); j++)
                    minDivisor[i * primes[j]] = primes[j];
            }
            return primes;
        }
    };

    long long binPow(long long x, long long p, long long mod = MOD) {
        if (!p)
            return 1;
        if (p % 2)
            return binPow(x, p - 1, mod) * x % mod;
        long long r = binPow(x, p / 2, mod);
        return r * r % mod;
    }

    // bigger, than LL
    // Если x и mod взаимно просты, то binPow(x, p, mod) == binPow(x, p % phi(mod), mod), где phi — функция Эйлера.
    // Если x и mod не взаимно просты, но p >= log2(mod), то binPow(x, p, mod) == binPow(x, p % phi(mod) + phi(mod), mod).
    long long phi(long long n) {
        long long res = n;
        for (long long d = 2; d * d <= n; d++) {
            if (n % d == 0) {
                while (n % d == 0)
                    n /= d;
                res -= res / d;
            }
        }
        if (n > 1)
            res -= res / n;
        return res;
    }


    namespace combinatorics {
        vector<long long> precalcFactorials() {
            vector<long long> memo(1e5);
            memo[0] = 1;
            for (int i = 1; i < memo.size(); i++)
                memo[i] = memo[i - 1] * i % MOD;
            return memo;
        }
        long long factorial(int n) {
            static vector<long long> memo = precalcFactorials();
            return memo[n];
        }
        long long invBP(long long x) {
            return binPow(x, MOD - 2, MOD);
        }
        long long c(int n, int k) {
            return factorial(n) * invBP(factorial(k)) % MOD * invBP(factorial(n - k)) % MOD;
        }
    };



    namespace matrix {
        using Matrix = vector<vector<long long>>;
        Matrix identityMatrix(int size) {
            Matrix res(size, vector<long long>(size));
            for (int i = 0; i < res.size(); i++)
                res[i][i] = 1;
            return res;
        }
        Matrix operator * (const Matrix& a, const Matrix& b) {
            Matrix res(a.size(), vector<long long>(b[0].size()));
            for (int y = 0; y < res.size(); y++)
                for (int x = 0; x < res[0].size(); x++)
                    for (int i = 0; i < a[0].size(); i++)
                        res[y][x] = (res[y][x] + a[y][i] * b[i][x] % MOD) % MOD;
            return res;
        }

        Matrix pow(const Matrix& m, long long p) {
            if (!p)
                return identityMatrix(m.size());
            if (p % 2)
                return pow(m, p - 1) * m;
            Matrix r = pow(m, p / 2);
            return r * r;
        }
        // just in case
        Matrix mult(Matrix& a, Matrix& b) {
            return a * b;
        }
    };


    class ModInt {
        long long value;
        static long long gcdex(long long a, long long b, long long& x, long long& y) {
            if (!b) {
                x = 1;
                y = 0;
                return a;
            }
            long long x1, y1, d = gcdex(b, a % b, x1, y1);
            x = y1;
            y = x1 - a / b * y1;
            return d;
        }

    public:
        ModInt(long long value = 0) : value((value% MOD + MOD) % MOD) {}

        ModInt operator + (const ModInt& that) const {
            return value + that.value;
        }

        ModInt operator - (const ModInt& that) const {
            return value - that.value;
        }

        ModInt operator * (const ModInt& that) const {
            return value * that.value;
        }

        ModInt operator / (const ModInt& that) const {
            long long x, y;
            gcdex(that.value, MOD, x, y);
            return value * x;
        }

        bool canDivide(const ModInt& that) const {
            long long x, y;
            return that.value && gcdex(that.value, MOD, x, y) == 1;
        }

        friend istream& operator >> (istream& in, ModInt& m) {
            long long value;
            in >> value;
            m = ModInt(value);
            return in;
        }

        friend ostream& operator << (ostream& out, const ModInt& m) {
            return out << m.value;
        }
    };



    namespace fft
    {
        struct num
        {
            ld x,y;
            num() {x=y=0;}
            num(ld x,ld y):x(x),y(y){}
        };
        inline num operator+(num a,num b) {return num(a.x+b.x,a.y+b.y);}
        inline num operator-(num a,num b) {return num(a.x-b.x,a.y-b.y);}
        inline num operator*(num a,num b) {return num(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
        inline num conj(num a) {return num(a.x,-a.y);}
     
        ll base=1;
        vector<num> roots={{0,0},{1,0}};
        vll rev={0,1};
        const ld PI=acosl(-1.0);
     
        void ensure_base(ll nbase)
        {
            if(nbase<=base) return;
            rev.resize(1<<nbase);
            for(ll i=0;i<(1<<nbase);i++)
                rev[i]=(rev[i>>1]>>1)+((i&1)<<(nbase-1));
            roots.resize(1<<nbase);
            while(base<nbase)
            {
                ld angle=2*PI/(1<<(base+1));
                for(ll i=1<<(base-1);i<(1<<base);i++)
                {
                    roots[i<<1]=roots[i];
                    ld angle_i=angle*(2*i+1-(1<<base));
                    roots[(i<<1)+1]=num(cos(angle_i),sin(angle_i));
                }
                base++;
            }
        }
     
        void fft(vector<num> &a,ll n=-1)
        {
            if(n==-1) n=a.size();
            assert((n&(n-1))==0);
            ll zeros=__builtin_ctz(n);
            ensure_base(zeros);
            ll shift=base-zeros;
            for(ll i=0;i<n;i++)
                if(i<(rev[i]>>shift))
                    swap(a[i],a[rev[i]>>shift]);
            for(ll k=1;k<n;k<<=1)
            {
                for(ll i=0;i<n;i+=2*k)
                {
                    for(ll j=0;j<k;j++)
                    {
                        num z=a[i+j+k]*roots[j+k];
                        a[i+j+k]=a[i+j]-z;
                        a[i+j]=a[i+j]+z;
                    }
                }
            }
        }
     
        vector<num> fa,fb;
        
        vll multiply(vll &a, vll &b)
        {
            ll need=a.size()+b.size()-1;
            ll nbase=0;
            while((1<<nbase)<need) nbase++;
            ensure_base(nbase);
            ll sz=1<<nbase;
            if(sz>(ll)fa.size()) fa.resize(sz);
            for(ll i=0;i<sz;i++)
            {
                ll x=(i<(int)a.size()?a[i]:0);
                ll y=(i<(int)b.size()?b[i]:0);
                fa[i]=num(x,y);
            }
            fft(fa,sz);
            num r(0,-0.25/sz);
            for(ll i=0;i<=(sz>>1);i++)
            {
                ll j=(sz-i)&(sz-1);
                num z=(fa[j]*fa[j]-conj(fa[i]*fa[i]))*r;
                if(i!=j) fa[j]=(fa[i]*fa[i]-conj(fa[j]*fa[j]))*r;
                fa[i]=z;
            }
            fft(fa,sz);
            vector<ll> res(need);
            for(ll i=0;i<need;i++) 
                res[i]=fa[i].x+0.5;
            return res;
        }
        vll multiply_mod(vll &a,vll &b,ll m,ll eq=0)
        {
            ll need=a.size()+b.size()-1;
            ll nbase=0;
            while((1<<nbase)<need) nbase++;
            ensure_base(nbase);
            ll sz=1<<nbase;
            if(sz>(ll)fa.size()) fa.resize(sz);
            for(ll i=0;i<(ll)a.size();i++)
            {
                ll x=(a[i]%m+m)%m;
                fa[i]=num(x&((1<<15)-1),x>>15);
            }
            fill(fa.begin()+a.size(),fa.begin()+sz,num{0,0});
            fft(fa,sz);
            if(sz>(ll)fb.size()) fb.resize(sz);
            if(eq) copy(fa.begin(),fa.begin()+sz,fb.begin());
            else
            {
                for(ll i=0;i<(ll)b.size();i++)
                {
                    ll x=(b[i]%m+m)%m;
                    fb[i]=num(x&((1<<15)-1),x>>15);
                }
                fill(fb.begin()+b.size(),fb.begin()+sz,num{0,0});
                fft(fb,sz);
            }
            ld ratio=0.25/sz;
            num r2(0,-1),r3(ratio,0),r4(0,-ratio),r5(0,1);
            for(ll i=0;i<=(sz>>1);i++)
            {
                ll j=(sz-i)&(sz-1);
                num a1=(fa[i]+conj(fa[j]));
                num a2=(fa[i]-conj(fa[j]))*r2;
                num b1=(fb[i]+conj(fb[j]))*r3;
                num b2=(fb[i]-conj(fb[j]))*r4;
                if(i!=j)
                {
                    num c1=(fa[j]+conj(fa[i]));
                    num c2=(fa[j]-conj(fa[i]))*r2;
                    num d1=(fb[j]+conj(fb[i]))*r3;
                    num d2=(fb[j]-conj(fb[i]))*r4;
                    fa[i]=c1*d1+c2*d2*r5;
                    fb[i]=c1*d2+c2*d1;
                }
                fa[j]=a1*b1+a2*b2*r5;
                fb[j]=a1*b2+a2*b1;
            }
            fft(fa,sz);fft(fb,sz);
            vll res(need);
            for(ll i=0;i<need;i++){
                ll aa=fa[i].x+0.5;
                ll bb=fb[i].x+0.5;
                ll cc=fa[i].y+0.5;
                res[i]=(aa+((bb%m)<<15)+((cc%m)<<30))%m;
            }
            return res;
        }
        vll square_mod(vll& a,ll m)
        {
            return multiply_mod(a,a,m,1);
        }
    };
    namespace Geometry {
        const double EPS = 1e-9;
        struct Point {
            double x, y;

            Point() {}

            Point(double x, double y) : x(x), y(y) {}

            Point(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {}

            bool operator == (const Point& that) const {
                return abs(x - that.x) < EPS && abs(y - that.y) < EPS;
            }

            bool operator < (const Point& that) const {
                if (abs(x - that.x) >= EPS)
                    return x < that.x;
                return y + EPS < that.y;
            }

            double angle() const {
                double a = atan2(y, x);
                if (a < -EPS)
                    a += 2 * acos(-1.0);
                return a;
            }

            double length() const {
                return hypot(x, y);
            }

            double distanceTo(const Point& that) const {
                return hypot(x - that.x, y - that.y);
            }

            Point operator + (const Point& that) const {
                return Point(x + that.x, y + that.y);
            }

            Point operator - (const Point& that) const {
                return Point(x - that.x, y - that.y);
            }

            Point operator * (double k) const {
                return Point(x * k, y * k);
            }

            Point setLength(double newLength) const {
                double k = newLength / length();
                return Point(x * k, y * k);
            }

            Point rotate(double angle) {
                return Point(x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle));
            }

            double dotProduct(const Point& that) const {
                return x * that.x + y * that.y;
            }

            double angleTo(const Point& that) const {
                return acos(max(-1.0, min(1.0, dotProduct(that) / (length() * that.length()))));
            }

            bool isOrthogonalTo(const Point& that) const {
                return abs(dotProduct(that)) < EPS;
            }

            Point orthogonalPoint() const {
                return Point(-y, x);
            }

            double crossProduct(const Point& that) const {
                return x * that.y - y * that.x;
            }

            bool isCollinearTo(const Point& that) const {
                return abs(crossProduct(that)) < EPS;
            }

            friend istream& operator >> (istream& in, Point& p) {
                return in >> p.x >> p.y;
            }

            friend ostream& operator << (ostream& out, const Point& p) {
                return out << p.x << " " << p.y;
            }
        };
        struct Line {
            double a, b, c;

            Line() {}

            Line(double a, double b, double c) : a(a), b(b), c(c) {}

            Line(const Point& p1, const Point& p2) : a(p1.y - p2.y), b(p2.x - p1.x), c(p1.x* p2.y - p2.x * p1.y) {}

            static Line LineByVector(const Point& p, const Point& v) {
                return Line(p, p + v);
            }

            static Line LineByNormal(const Point& p, const Point& n) {
                return LineByVector(p, n.orthogonalPoint());
            }

            Point normal() const {
                return Point(a, b);
            }

            Line orthogonalLine(const Point& p) const {
                return LineByVector(p, normal());
            }

            Line parallelLine(const Point& p) const {
                return LineByNormal(p, normal());
            }

            Line parallelLine(double distance) const {
                Point p = (abs(a) < EPS ? Point(0, -c / b) : Point(-c / a, 0));
                Point p1 = p + normal().setLength(distance);
                return LineByNormal(p1, normal());
            }

            int side(const Point& p) const {
                double r = a * p.x + b * p.y + c;
                if (abs(r) < EPS)
                    return 0;
                else
                    return r > 0 ? 1 : -1;
            }

            double distanceTo(const Point& p) const {
                return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
            }

            bool has(const Point& p) const {
                return distanceTo(p) < EPS;
            }

            double distanceTo(const Line& that) const {
                if (normal().isCollinearTo(that.normal())) {
                    Point p = (abs(a) < EPS ? Point(0, -c / b) : Point(-c / a, 0));
                    return that.distanceTo(p);
                }
                else
                    return 0;
            }

            bool intersectsWith(const Line& that) const {
                return distanceTo(that) < EPS;
            }

            Point intersection(const Line& that) const {
                double d = a * that.b - b * that.a;
                double dx = -c * that.b - b * -that.c;
                double dy = a * -that.c - -c * that.a;
                return Point(dx / d, dy / d);
            }

            friend istream& operator >> (istream& in, Line& l) {
                return in >> l.a >> l.b >> l.c;
            }

            friend ostream& operator << (ostream& out, const Line& l) {
                return out << l.a << " " << l.b << " " << l.c;
            }
        };
        struct Ray {
            Point p1, p2;
            double a, b, c;

            Ray(const Point& p1, const Point& p2) : p1(p1), p2(p2), a(p1.y - p2.y), b(p2.x - p1.x), c(p1.x* p2.y - p2.x * p1.y) {}

            double distanceTo(const Point& p) const {
                if (Point(p1, p).dotProduct(Point(p1, p2)) >= -EPS)
                    return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
                else
                    return p1.distanceTo(p);
            }

            bool has(const Point& p) const {
                return distanceTo(p) < EPS;
            }

            double distanceTo(const Ray& that) const {
                Line l(a, b, c), thatL(that.a, that.b, that.c);
                if (l.intersectsWith(thatL)) {
                    Point p = l.intersection(thatL);
                    if (has(p) && that.has(p))
                        return 0;
                }
                return min(distanceTo(that.p1), that.distanceTo(p1));
            }

            bool intersectsWith(const Ray& that) const {
                return distanceTo(that) < EPS;
            }
        };
        struct Segment {
            Point p1, p2;
            double a, b, c;

            Segment(const Point& p1, const Point& p2) : p1(p1), p2(p2), a(p1.y - p2.y), b(p2.x - p1.x), c(p1.x* p2.y - p2.x * p1.y) {}

            double distanceTo(const Point& p) const {
                if (Point(p1, p).dotProduct(Point(p1, p2)) >= -EPS && Point(p2, p).dotProduct(Point(p2, p1)) >= -EPS)
                    return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
                else
                    return min(p1.distanceTo(p), p2.distanceTo(p));
            }

            bool has(const Point& p) const {
                return distanceTo(p) < EPS;
            }

            double distanceTo(const Segment& that) const {
                Line l(a, b, c), thatL(that.a, that.b, that.c);
                if (l.intersectsWith(thatL)) {
                    Point p = l.intersection(thatL);
                    if (has(p) && that.has(p))
                        return 0;
                }
                return min(min(distanceTo(that.p1), distanceTo(that.p2)), min(that.distanceTo(p1), that.distanceTo(p2)));
            }

            bool intersectsWith(const Segment& that) const {
                return distanceTo(that) < EPS;
            }
        };
        struct Polygon {
            vector<Point> points;

            void addPoint(const Point& p) {
                points.push_back(p);
            }

            bool has(const Point& p) const {
                bool pos = 0, neg = 0;
                for (int i = 0; i < points.size(); i++) {
                    const Point& a = points[i], & b = points[(i + 1) % points.size()];
                    Point ab(a, b), ap(a, p);
                    double cross = ab.crossProduct(ap);
                    pos |= cross > EPS;
                    neg |= cross < -EPS;
                }
                return !pos || !neg;
            }

            bool isConvex() {
                bool pos = 0, neg = 0;
                for (int i = 0; i < points.size(); i++) {
                    const Point& a = points[i], & b = points[(i + 1) % points.size()], & c = points[(i + 2) % points.size()];
                    Point ab(a, b), ac(a, c);
                    double cross = ab.crossProduct(ac);
                    pos |= cross > EPS;
                    neg |= cross < -EPS;
                }
                return !pos || !neg;
            }

            double perimeter() const {
                double p = 0;
                for (int i = 0; i < points.size(); i++)
                    p += points[i].distanceTo(points[(i + 1) % points.size()]);
                return p;
            }

            double area() const {
                double s = 0;
                for (int i = 0; i < points.size(); i++)
                    s += points[i].crossProduct(points[(i + 1) % points.size()]);
                return abs(s) / 2;
            }

            Polygon convex_hull() {
                Point p0 = points[0];
                for (Point p : points)
                    if (p.x < p0.x || (p.x == p0.x && p.y < p0.y))
                        p0 = p;
                for (Point &x : points) {
                    x.x -= p0.x;
                    x.y -= p0.y;
                }
                sort(points.begin(), points.end(), [&](Point a, Point b){
                    return (a.crossProduct(b)) > 0 || (a.crossProduct(b)) == 0 && a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
                });
                vector<Point> hull;
                for (Point p : points) {
                    while (hull.size() >= 2 && ((p - hull.back()).crossProduct((hull[hull.size() - 2] - hull.back()))) <= 0) {
                        hull.pop_back();
                    }
                    hull.push_back(p);
                }
                for (Point &x : hull) {
                    x.x += p0.x;
                    x.y += p0.y;
                }
                return Polygon(hull);
            }
        };
    };
};


ll solve() {
    return 0;
}

int main() {
    IOS;
    ll tc = 1;
    //cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
