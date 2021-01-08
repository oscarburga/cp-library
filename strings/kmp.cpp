namespace KMP {
	template<typename V, typename S>
	void kmp(const int n, V& b, const S& s) {
		b[0] = 0;
		for(int i = 1, j = 0; i<n; i++) {
			while(j > 0 && s[i] != s[j]) j = b[j-1];
			b[i] = j += (s[i] == s[j]);
		}
	}
	template<typename M, typename V, typename S> 
	void kmp_automaton(const int n, M& go, const V& b, const S& s, const char lo='a', const char hi='z') {
		go[0][s[0]-lo] = 1;
		for(int i = 1; i<n; i++) {
			for(char c = lo; c<=hi; c++) {
				go[i][c-lo] = s[i] == c ? i+1 : go[b[i-1]][c-lo];
			}
		}
	}
};
