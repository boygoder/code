#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;
template<typename T>
concept Equality_comparable = requires(T a, T b)
{
    {a == b}-> std::convertible_to<bool>;
    {a != b}-> std::convertible_to<bool>;
};


void f()
{
	//static_assert(Equality_comparable<int>);
	//struct S { int a; }; 
	//static_assert(Equality_comparable<S>);

}; // 受约束的 C++20 函数模板


void print_directory(fs::path p) 
{
	try { 
		if (is_directory(p)) { 
			std::cout << p << ":\n"; 
			for (const fs::directory_entry& x : fs::directory_iterator{p}) 
				std::cout << " " << x.path() << '\n'; 
		} 
	} 
	catch (const fs::filesystem_error& ex) {
			std::cerr << ex.what() << '\n'; 
	}
}

int main()
{
	print_directory("."); // Windows volume C
	return 0;
}