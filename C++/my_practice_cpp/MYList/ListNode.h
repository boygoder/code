#include <iostream>
#include <memory>

template <typename T>
class ListNode
{
private:
    T item_;
    ListNode<T>* next_ = nullptr;
public:
  ListNode(const T &value) : next_(nullptr), item_(value) {}
  ~ListNode() {}
  ListNode(const ListNode &) = delete;
  ListNode &operator=(const ListNode &) = default;

    const T& getItem() const
    {
        return item_;
    }
    ListNode<T>* getNext() const
    {
        return next_;
    }
    void setNext(ListNode<T>* next)
    {
        this->next_ = next;
    }
    void insertAfter(T& item)
    {
        next_ = new ListNode<T>(item,next_);
    }
    T nth(int position)
    {
        if(position==0)
        {
            return this->item_;
        }
        else if((position <0)||(next_ == nullptr))
        {
            std::cerr << "nth: no position." << std::endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            return next_->nth(position-1);
        }

    }
};
