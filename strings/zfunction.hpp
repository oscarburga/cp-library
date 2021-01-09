namespace ZF {
	template<typename V, typename S>
	void build(const int n, V& z, const S& s) {
		z[0] = 0;
		for(int i = 1, l = 0, r = -1; i<n; i++) {
			int k = i > r ? 0 : min(z[i-l], r-i+1);
			while(i+k < n && s[k] == s[i+k]) k++;
			z[i] = k--;
			if (i + k > r) l = i, r = i+k;
		}
	}
}
