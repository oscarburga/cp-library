/* Only works on gcc/g++ compiler. !!
Ordered_set has most of the regular set functions. Additionally, it also has:
	* order_of_key(T x): Returns number of stored items strictly smaller than X
	* find_by_order(int K): Returns iterator to K-th largest element (counting from zero)
*/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T, typename R = null_type, typename C = less<T>> //<key, map_type, comparator>
using ordered_set = tree<T, R, C, rb_tree_tag, tree_order_statistics_node_update>;
ordered_set<pair<int,int>> example1; 	//use like set
ordered_set<int, int> example2; 	//use like map
//If you need multiset, store a timestamp along with elements (ie: pair<type, int>).
//If you're using a custom struct, then you need to overload the ostream& << operator for it. Example:
struct node {
	string code;
	int id, rel;
	node(const string& code, int id = node_cnt, int rel = 0) : code(code), id(id), rel(rel) {}
	bool operator < (const node&e) const { return rel > e.rel || (rel == e.rel && id < e.id); }
	friend ostream& operator << (ostream &os, const node&t) { return os; } // <- Include this!
};//For iterators, its just like a regular set:
using oset_it = ordered_set<node>::iterator;
