#include "ListNode.h"
void test_constructor()
{
    int i = 2;
    ListNode<int> node1(i);
    ListNode<int> node2;
    ListNode<int> node3(i, &node1);
    ListNode<int> node4(node3);
};
void test_insertAfter()
{
    int i = 1;
    ListNode<int> *listnode = new ListNode<int>(i);
    for (i = 2; i <= 10; i++)
    {
        listnode->insertAfter(i);
        std::cout << "Item:" << listnode->getItem() << "  Next: " << listnode->getNext() << std::endl;
        listnode = listnode->getNext();
    }
};

void test_getItem()
{
    int i = 10;
    ListNode<int> node(i);
    std::cout << node.getItem() << std::endl;
};

void test_getNext()
{
    int i = 10;
    ListNode<int> node(i);
    ListNode<int> node2(i, &node);
    std::cout << node2.getNext() << std::endl;
};

void test_nth()
{
    int i = 0;
    ListNode<int> *node = new ListNode<int>(i);
    for (i = 10; i > 0; i--)
    {
        node->insertAfter(i);
    }
    for (int i = 0; i < 11; i++)
    {
        std::cout << "Index "<< i << ":" << node->nth(i) << std::endl;
    }
}
void Test()
{
    std::cout << "test_constructor:" << std::endl;
    test_constructor();
    std::cout << "test_getItem():" << std::endl;
    test_getItem();
    std::cout << "test_getNext():" << std::endl;
    test_getNext();
    std::cout << "test_insertAfter:" << std::endl;
    test_insertAfter();
    std::cout << "test_nth:" << std::endl;
    test_nth();
};
int main()
{
    Test();
    return 0;
};