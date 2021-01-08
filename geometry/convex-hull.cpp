namespace Geo {
	template<typename T> //change comparators >= and <= to strict if need collinears
	vector<pt<T>> convex_hull(vector<pt<T>> &pts) { 
		sort(pts.begin(), pts.end());
		pts.erase(unique(pts.begin(), pts.end()), pts.end());
		vector<pt<T>> upper, lower;
		for(int i = 0, lu = 0, lo = 0; i<int(pts.size()); i++) { 
			while(lu > 1 && sgn((upper[lu-1] - upper[lu-2]) % (pts[i] - upper[lu-2])) >= 0) {
				upper.pop_back(), lu--;
			}
			upper.emplace_back(pts[i]), lu++;
			while(lo > 1 && sgn((lower[lo-1] - lower[lo-2]) % (pts[i] - lower[lo-2])) <= 0) {
				lower.pop_back(), lo--;
			}
			lower.emplace_back(pts[i]), lo++;
		}
		reverse(upper.begin(), upper.end());
		lower.pop_back();
		lower.insert(lower.end(), upper.begin(), upper.end());
		lower.pop_back();
		return lower;
	}
};
