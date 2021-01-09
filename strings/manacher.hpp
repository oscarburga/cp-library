namespace manacher {
	template<typename V, typename S> 
	void build(int n, V& d, const S& s) { //d[0] is odds, d[1] is evens
		for(int v = 0; v<2; v++) { 
			for(int i = 0, l = 0, r = -1; i<n; i++) {
				int k = i > r ? (v^1) : min(r-i+1, d[v][l+r-i+v]);
				while(i >= k+v && i+k < n && s[i-k-v] == s[i+k]) k++;
				d[v][i] = k--;
				if (i+k > r) r = i+k, l = i-k-v;
			}
		}
	}
};
