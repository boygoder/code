#include "SingleLinkedList.h"
#include <string>

int main(int argc, char *argv[])
{

  SingleLinkedList<int> ilist;
  ilist.push_front(4);
  ilist.push_front(9);

  std::cout << "Size of int list is: " << ilist.Size() << std::endl;
  SingleLinkedList<std::string> strlist{};
  strlist.push_front("string 1");
  strlist.push_front("another");
  strlist.push_front("and another");
  std::cout << "Should be 3.  Size of string list is : " << strlist.Size() << std::endl;

  std::cout << strlist.pop_front() << std::endl;
  std::cout << strlist.pop_front() << std::endl;
  std::cout << strlist.pop_front() << std::endl;

  std::cout << "Should be 0.  Size of string list is : " << strlist.Size() << std::endl;
  strlist.push_back("string 1");
  std::cout << "front: " << strlist.front() << std::endl;
  std::cout << "Should be 1.  Size of string list is : " << strlist.Size() << std::endl;
  strlist.push_back("another");
  std::cout << "Should be 2.  Size of string list is : " << strlist.Size() << std::endl;
  strlist.push_back("and another");
  std::cout << "Should be 3.  Size of string list is : " << strlist.Size() << std::endl;

  std::cout << "front: " << strlist.front() << std::endl;
  std::cout << "pop_back:" << std::endl;
  std::cout << strlist.pop_back() << std::endl;
  std::cout << strlist.pop_back() << std::endl;
  std::cout << strlist.pop_back() << std::endl;

  strlist.insert(0, "string 1");
  strlist.insert(0, "another");
  strlist.insert(0, "and another");
  std::cout << "Should be 3.  Size of string list is : " << strlist.Size() << std::endl;
  std::cout << "Front:" << strlist.front() << "  Back:" << strlist.back() << std::endl;

  strlist.erase(0);
  std::cout << "Front:" << strlist.front() << "  Back:" << strlist.back() << std::endl;
  strlist.erase(1);
  std::cout << "Front:" << strlist.front() << "  Back:" << strlist.back() << std::endl;

  strlist.insert(0, "string 1");
  strlist.insert(0, "another");
  strlist.insert(0, "and another");
  for(int i=0; i < 4;i++)
    std::cout << "倒数第 " << i <<"个节点:"  << strlist.value_n_from_end(i) <<std::endl;
  std::cout << "Should be 4.  Size of string list is : " << strlist.Size() << std::endl;
  strlist.reverse();
  for(int i=0; i < 4;i++)
    std::cout << "倒数第 " << i <<"个节点:"  << strlist.value_n_from_end(i) <<std::endl;
}