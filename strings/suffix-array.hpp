namespace SA {
	int m[maxn], nm[maxn], head[maxn], sbs[maxn];
	template<typename V, typename S>
	void build(const int n, V& a, const S& s) {
		iota(begin(a), begin(a)+n, 0);
		sort(begin(a), begin(a)+n, [&](int i, int j) { return s[i] < s[j]; });
		m[a[0]] = 0;
		for(int i = 1; i<n; i++) m[a[i]] = m[a[i-1]] + (s[a[i]] != s[a[i-1]]);
		for(int len = 1; len < n; len <<= 1) {
			for(int i = 0; i<n; i++) sbs[i] = (a[i]-len+n) % n;
			for(int i = n-1; i>=0; i--) head[m[a[i]]] = i;
			for(int i = 0; i<n; i++) a[head[m[sbs[i]]]++] = sbs[i];
			nm[a[0]] = 0;
			for(int i = 1; i<n; i++) {
				if (m[a[i]] != m[a[i-1]]) nm[a[i]] = nm[a[i-1]] + 1;
				else nm[a[i]] = nm[a[i-1]] + (m[(a[i]+len)%n] != m[(a[i-1]+len)%n]);
			}
			swap(m, nm);
		}
	}
	template<typename V, typename S> //recompute_m = true if 'a' wasnt the last SA to be built
	void lcp_array(const int n, const V& a, const S& s, V& lcp, bool recompute_m = false) {
		for(int i = 0; recompute_m && i<n; i++) m[a[i]] = i;
		for(int i = 0, k = 0; i+1<n; i++, k-= k > 0) {
			for(int j = a[m[i]-1]; s[i+k] == s[j+k]; k++);
			lcp[m[i]-1] = k;
		}
	}
};
