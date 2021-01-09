namespace RH { // Rolling Hash, temporary while I figure out a pretty implementation
	using Hash = array<int, 2>;
	const Hash mod = { int(1e9)+7, int(1e9)+9 };
	const Hash zero = { 0, 0 };
	const Hash bas = { 31, 37 }; 
	const Hash ibas = { 129032259, 297297300 }; 
	inline int add(int x, int y, const int mod) { return (x+y) % mod; }
	inline int sub(int x, int y, const int mod) { return (((x-y)%mod)+mod)%mod; }
	inline int mul(int x, int y, const int mod) { return (1ll * x * y) % mod; }
	Hash operator + (const Hash &p, const Hash &q) {
		return { add(p[0], q[0], mod[0]), add(p[1], q[1], mod[1]) };
	}
	Hash operator - (const Hash &p, const Hash &q) {
		return { sub(p[0], q[0], mod[0]), sub(p[1], q[1], mod[1]) };
	}
	Hash operator * (const Hash &p, const Hash &q) {
		return { mul(p[0], q[0], mod[0]), mul(p[1], q[1], mod[1]) };
	}
	Hash& operator *= (Hash &p, const Hash &q) { 
		p[0] = mul(p[0], q[0], mod[0]), p[1] = mul(p[1], q[1], mod[1]);
		return p;
	}
	vector<Hash> pwr, inv;
	void init(const int n) {
		pwr.resize(n+1);
		inv.resize(n+1);
		pwr[0] = inv[0] = { 1, 1 };
		for(int i = 1; i<=n; i++) {
			pwr[i] = pwr[i-1] * bas;
			inv[i] = inv[i-1] * ibas;
		}
	}
	Hash single(const char c) { return Hash{ c - 'a' + 1, c - 'a' + 1 }; }
};
