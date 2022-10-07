#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>
using namespace std;
struct Record {
	string name;
	int product_code;
};

struct RhashMap {
	bool operator()(const Record& lhs, const Record& rhs) const {
		return lhs.name > rhs.name;
	}
};




struct Rhash {
	size_t operator()(const Record& r) const {
		return hash<string>()(r.name)^hash<int>()(r.product_code);
	}
};

namespace std {
	template<> struct hash<Record> {
	 	using argument_type = Record;
	 	using result_type = size_t;
	 	size_t operator()(const Record& r) const {
			return hash<string>()(r.name)^hash<int>()(r.product_code);
		}
	};
}


auto Rhash2 = [](const Record& r){
	return hash<string>()(r.name)^hash<int>()(r.product_code);
};




int main()
{
	unordered_set<Record,Rhash> my_set1;
	unordered_set<Record,decltype(Rhash2)> my_set2;
	unordered_set<Record> my_set3;
	map<Record,RhashMap> my_map;
	return 0;
}