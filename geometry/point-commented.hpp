/* Class was designed to work with "long long" and "long double" types.
Should work fine for any integer type, but beware of overflow! Modify cross and dot product for it.
Should work fine with other floating point types, but beware of precision issues.
Modify return types as needed if using different types (long double -> double/float, etc) */

const long double eps = 1e-9;
template<typename T> int sgn(T x) { return (x > 0) - (x < 0); }
template<> int sgn(long double x) { return (x > eps) - (x < -eps); }

template<typename T> 
struct pt { 
	T x, y;
	explicit pt(T x = 0, T y = 0) : x(x), y(y) {}
	template<typename R> explicit pt(const pt<R> &p) : x(p.x), y(p.y) {}

	//Vector addition and substraction (pairwise)
	friend pt operator + (const pt &p, const pt &q) { return pt(p.x + q.x, p.y + q.y); } 
	friend pt operator - (const pt &p, const pt &q) { return pt(p.x - q.x, p.y - q.y); }
	pt& operator += (const pt &p) { x += p.x, y += p.y; return *this; } 
	pt& operator -= (const pt &p) { x -= p.x, y -= p.y; return *this; }

	//Multiplication and division by constant (scalar)
	friend pt operator * (const pt &p, const T &k) { return pt(p.x * k, p.y * k); }
	friend pt operator / (const pt &p, const T &k) { return pt(p.x / k, p.y / k); }
	pt& operator *= (const T &k) { x *= k, y *= k; return *this; }
	pt& operator /= (const T &k) { x /= k, y /= k; return *this; }

	//Rotations 
	friend pt ccw90(const pt &p) { return pt(-p.y, p.x); }
	friend pt cw90(const pt &p) { return pt(p.y, -p.x); }
	friend pt<long double> rot(const pt &p, const long double &t) { // Rotate by angle 't' (in radians)
		long double cost = cosl(t), sint = sinl(t);
		return pt<long double>(cost * p.x - sint * p.y, sint * p.x + cost * p.y); 
	}

	//Dot product and Cross product
	friend T operator * (const pt &p, const pt &q) { return p.x * q.x + p.y * q.y; }
	friend T operator % (const pt &p, const pt &q) { return p.x * q.y - p.y * q.x; }

	//Squared length of vector and squared distance between 2 points
	friend T len2(const pt &p) { return p.x * p.x + p.y * p.y; } 
	friend T dis2(const pt &p, const pt &q) { return (q-p) * (q-p); }
	
	//Length of vector and distance between 2 points
	friend long double len(const pt &p) { return sqrtl(len2(p)); } 
	friend long double dis(const pt &p, const pt &q) { return sqrtl(dis2(p, q)); }

	//Get the angle between two vectors 
	friend long double angle(const pt &p, const pt &q) { return atan2l(p % q, p * q); }

	//Get the normalized vector
	friend pt<long double> unit(const pt &p) { return pt<long double>(p) / len(p); }

	//Get the point with swapped X and Y coords
	friend pt swapxy(const pt &p) { return pt(p.y, p.x); }

	//Overload << operator for easy debugging
	friend ostream& operator << (ostream &o, const pt &p) { return o<<'('<<p.x<<", "<<p.y<<")\n"; }
	
	//Lexicographical comparison 
	bool operator == (const pt &q) const { return sgn(x-q.x) == 0 && sgn(y-q.y) == 0; }
	bool operator < (const pt &q) const { return sgn(x-q.x) < 0 || (sgn(x-q.x) == 0 && sgn(y-q.y) < 0); }
};
// Auxiliary functions for reading point from input
void read(pt<long double> &p) { scanf("%Lf %Lf", &p.x, &p.y); }
void read(pt<long long> &p) { scanf("%lld %lld", &p.x, &p.y); }
