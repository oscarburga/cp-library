namespace Geo {
	template<typename T, typename V> // 0 for edge, 1 inside, -1 outside
	int point_in_poly(const int n, const pt<T>& u, const V& pts) {
		bool onedge = false, inters = false;
		pt<T> p, q;
		for(int i = 0; i<n && !onedge; i++) {
			p = pts[i], q = pts[(i+1)%n];
			onedge |= (sgn((p-u) % (q-u)) == 0) && (sgn((p-u) * (q-u)) <= 0);
			if (p.y < q.y) swap(p, q);
			inters ^= (p.y >= u.y) && (q.y < u.y) && (sgn((q-p) % (u-p)) < 0);
		}
		return onedge ? 0 : inters ? 1 : -1;
	}
	//TODO: Add O(logN) inclusion test for convex polygons. 
};
 
