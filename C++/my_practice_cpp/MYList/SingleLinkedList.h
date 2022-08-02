#include <iostream>
#include "ListNode.h"
template <typename T>
class SingleLinkedList
{
private:
    ListNode<T> *head = nullptr;
    int size = 0;

public:
    explicit SingleLinkedList() : head(nullptr) {}
    ~SingleLinkedList()
    {
        ListNode<T> *current = head;
        ListNode<T> *next = nullptr;

        while (current)
        {
            next = current->getNext();
            delete current;
            current = next;
        }
    };
    SingleLinkedList(const SingleLinkedList &) = delete;
    SingleLinkedList &operator=(const SingleLinkedList &) = delete;
    // - [ ] size() —— 返回链表中数据元素的个数
    int Size()
    {
        return this->size;
    };
    // - [ ] empty() —— 若链表为空则返回一个布尔值 true
    bool empty()
    {
        return (size == 0) ? true : false;
    }
    // - [ ] value_at(index) —— 返回第 n 个元素的值（从0开始计算）
    T value_at(int index)
    {
        // if(index<0 || index > size-1)
        // {
        //     std::cerr << "value_at: index out of range." <<std::endl;
        // }
        T item = head->nth(index);
        return item;
    }
    // - [ ] push_front(value) —— 添加元素到链表的首部
    void push_front(T item)
    {
        ListNode<T> *node = new ListNode<T>(item);
        node->setNext(head);
        head = node;
        size += 1;
    }
    // - [ ] pop_front() —— 删除首部元素并返回其值
    T pop_front()
    {
        if (head == nullptr)
        {
            std::cerr << "pop_front: empty list." << std::endl;
            exit(EXIT_FAILURE);
        }
        T item = head->getItem();
        ListNode<T> *node = head;
        head = head->getNext();
        size -= 1;
        delete node;
        return item;
    }
    // - [ ] push_back(value) —— 添加元素到链表的尾部
    void push_back(T item)
    {
        ListNode<T> *node = new ListNode<T>(item);
        if (head == nullptr)
        {
            head = node;
            size = 1;
        }
        else
        {
            ListNode<T> *tmp = head;
            while (tmp->getNext() != nullptr)
            {
                tmp = tmp->getNext();
            }
            tmp->setNext(node);
            size += 1;
        }
    }
    // - [ ] pop_back() —— 删除尾部元素并返回其值
    T pop_back()
    {
        T item;
        if (head == nullptr)
        {
            std::cerr << "front: empty list." << std::endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            ListNode<T>* current = head;
            ListNode<T>* prevous = nullptr;
            while (current->getNext())
            { 
                prevous = current;
                current = current->getNext();
            }
            if (prevous == nullptr)
            {
                head = nullptr;
            }
            else
            {
                prevous->setNext(nullptr);
            }
            item = current->getItem();
            delete current;
            size -= 1;
            return item;
        }
    }
    // - [ ] front() —— 返回首部元素的值
    T front()
    {
        if (head == nullptr)
        {
            std::cerr << "front: empty list." << std::endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            return head->getItem();
        }
    }
    // - [ ] back() —— 返回尾部元素的值
    T back()
    {
        /*T item;
        if(head == nullptr)
        {
            std::cerr <<"front: empty list."<<std::endl;
            exit(EXIT_FAILURE);
        }
        else{
            ListNode<T>* node = head;
            while(node->next_!=nullptr)
            {
                node = node->next_;
            }
            item = node->item_;
            delete node;
            return item;
        }
        */
        if (head == nullptr)
        {
            std::cerr << "front: empty list." << std::endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            return value_at(size - 1);
        }
    }
    // - [ ] insert(index, value) —— 插入值到指定的索引，并把当前索引的元素指向到新的元素
    // 原文应该是说在Index前面插入
    void insert(int index, T value)
    {
        if (index == 0)
        {
            push_front(value);
        }
        else if (index < 0 || index > size - 1)
        {
            std::cerr << "insert:index out of range";
            exit(EXIT_FAILURE);
        }
        else
        {
            ListNode<T> *node = new ListNode<T>(value);
            ListNode<T> *prevous = head;
            while (index > 1)
            {
                prevous = prevous->getNext();
                index--;
            }
            node->setNext(prevous->getNext());
            prevous->setNext(node);
            size += 1;
        }
    }
    // - [ ] erase(index) —— 删除指定索引的节点
    void erase(int index)
    {
        if (index < 0 || index > size-1)
        {
            std::cerr << "insert:index out of range";
            exit(EXIT_FAILURE);
        }
        else if(index==0)
        {
            pop_front();
        }
        else
        {
            ListNode<T>* current = head;
            ListNode<T>* prevous = nullptr;
            for(int i = 0;i < index && current; i++)
            {
                prevous = current;
                current = current->getNext();
            }
            prevous->setNext(current->getNext());
            delete current;
            size -= 1;
        }
    }
    // - [ ] value_n_from_end(n) —— 返回倒数第 n 个节点的值
    T value_n_from_end(int n)
    {
        if (n < 0 || n > size - 1)
        {
            std::cerr << "value_n_from_end:n out of range" << std::endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            int forwardsize = size - 1 - n;
            return value_at(forwardsize);
        }
    }
    // - [ ] reverse() —— 逆序链表
    void reverse()
    {
        if (size < 2)
            return;
        else
        {
            ListNode<T> *prevous = nullptr;
            ListNode<T> *now = head;
            ListNode<T> *next;
            while (now!= nullptr)
            {
                next = now->getNext();
                now->setNext(prevous);
                prevous = now;
                now = next;
            }
            head = prevous;
        }

    }
    // - [ ] remove_value(value) —— 删除链表中指定值的第一个元素
    void remove_value(T value)
    {
        for (int i = 0; i < size; i++)
        {
            int nowVal = value_at(i);
            if (value == nowVal)
            {
                erase(i);
                break;
            }
        }
    }
};