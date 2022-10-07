#include <variant>
#include <iostream>
#include <concepts>
#include <utility>
using namespace std;
using Node = variant<Sequence,Statement,Declaration,Type>;
void check(Node* p) 
{ 
	if (holds_alternative<Sequence>(*p)) 
	{ 
		Sequence& e = get<Sequence>(*p); // ... 
	} 
	else if (holds_alternative<Statement>(*p)) 
	{ 
		Statement& s = get<Statement>(*p); // ... 
	} // ... Declaration and Type ... 
}

void checkVisit(Node* p) 
{ 
	visit(overloaded { [](Sequence& e) { /* ... */ }, 
					   [](Statement& s) { /* ... */ },
					   [](Declaration& d) {},
					   [](Type& t) {} // ... Declaration and Type ... 
	}, *p); 
}

int main()
{
	return 0;
}