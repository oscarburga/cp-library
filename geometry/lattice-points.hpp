namespace Geo {
	template<typename V> //returns tuple of I, B, 2A
	tuple<long long, long long, long long> lattice_points(const int n, V& pts) {
		ll area = 0, B = 0, I;
		for(int i = 0; i<n; i++) {
			pt<ll> &p = pts[i], &q = pts[(i+1)%n], d1;
			area += p % q;
			d1 = q-p;
			B += __gcd(abs(d1.x), abs(d1.y));
		}
		area = abs(area);
		I = (area-B+2) >> 1;
		return { I, B, area };
	}
};

/* Pick's theorem: 
	* I: Lattice points strictly in the interior
	* B: Lattice points on the boundary of polygon
	* A: Area of polygon
	A = I + (B/2) - 1
	2A - B + 2 = 2I
*/
