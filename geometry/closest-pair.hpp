namespace Geo {
	template<typename T, typename V>  //use Eps = 1e-9 for doubles, 1 for integers
	pair<pt<T>, pt<T>> closest_pair(const int n, V& pts, const T& Eps = T(1)) {
		sort(begin(pts), begin(pts)+n);
		set<pt<T>> st;
		pt<T> p;
		T best = 8e18;
		pair<pt<T>, pt<T>> ret = make_pair(p, p);
		#define sqr(x) ((x)*(x))
		for(int i = 0, j = 0; i<n; i++) {
			p = pts[i];
			while(j < i && sqr(p.x - pts[j].x) >= best) st.erase(swapxy(pts[j++]));
			T cur = sqrtl(best);
			T lo = p.y - cur - Eps;
			T hi = p.y + cur + Eps;
			auto it = st.lower_bound(pt<T>(lo, -8e18));
			p = swapxy(p);
			for(; it != st.end() && it->x <= hi; it++) {
				T aux = dis2(p, *it);
				if (aux < best) ret = make_pair(p, *it), best = aux;
			}
			st.insert(p);
		}
		#undef sqr
		return make_pair(swapxy(ret.first), swapxy(ret.second));
	} //returns pair(pt(0, 0), pt(0,0)) for n = 1
};
