#include <iostream>
#include <memory>
using namespace std;
typedef int int_32t;
class DynamicArray
{
private:
    std::unique_ptr<int_32t[]> arr_;
    int capacity_;
    int size_;
    void ResizeForSize(int candidAte_size)
    {
        if (size_ < candidAte_size)
        {
            if (size_ == capacity_)
            {
                IncreaseSize();
            }
        }
        else if (size_ > candidAte_size)
        {
            if (size_ < capacity_ / 4)
            {
                DecreaseSize();
            }
        }
    }
    void DecreaseSize()
    {
        std::unique_ptr<int[]> new_arr = std::unique_ptr<int[]>(new int[capacity_/2]);
        for (int i = 0; i < size_; i++)
        {
            new_arr[i] = arr_[i];
        }
        arr_ = std::move(new_arr);
        capacity_ /= 2;
    }
    void IncreaseSize()
    {
        std::unique_ptr<int[]> new_arr = std::unique_ptr<int[]>(new int[2 * capacity_]);
        for (int i = 0; i < size_; i++)
        {
            new_arr[i] = arr_[i];
        }
        arr_ = std::move(new_arr);
        capacity_ *= 2;
    }
public:
    DynamicArray(int _capacity_ = 10)
    {
        if (_capacity_ >= 1)
        {
            this->capacity_ = _capacity_;
            arr_ = std::unique_ptr<int_32t[]>(new int[capacity_]);
            this->size_ = 0;
        }
        else
        {
            cerr << "DynamicArray:capacity_ < 0" << endl;
        }
    }
    ~DynamicArray(){};
    int32_t At(int index) const
    {
        if ((index < 0) || (index > size_))
        {
            cerr << "At:index out of range" << endl;
        }
        return arr_[index];
    }
    void Set(int index, int32_t val)
    {
        if ((index < 0) || (index > size_))
        {
            cerr << "Get:index out of range" << endl;
        }
        arr_[index] = val;
    }
    void Push(int val)
    {
        ResizeForSize(size_+1);
        arr_[size_] = val;
        size_ += 1;
    }
    void Insert(int index, int_32t item)
    {
        if (index < 0 or index >= size_) 
        {
            std::cout << "Index out of bounds." << std::endl;
            exit(EXIT_FAILURE);
        }
        ResizeForSize(size_+1);
        for (int i = size_; i > index; i--)
        {
            arr_[i] = arr_[i - 1];
        }
        arr_[index] = item;
        size_ += 1;
    }
    void Prepend(int32_t item)
    {
        Insert(0, item);
    }
    int_32t Pop()
    {
        if (IsEmpty())
        {
            cerr << "Pop:arr_ay is already empty" << endl;
        }
        int_32t tmp = arr_[size_ - 1]; //如何真正删除呢？
        size_ = size_ - 1;
        ResizeForSize(size_-1);
        return tmp;
    }
    void Del(int index)
    {
        if ((index < 0) || (index > size_))
        {
            cerr << "Get:index out of range" << endl;
        }
        for (int j = index; j < size_ - 1; j++)
        {
            arr_[j] = arr_[j + 1];
        }
        ResizeForSize(size_-1);
        size_ -= 1;
    }
    DynamicArray *Remove(int32_t item)
    {
        DynamicArray *index = new DynamicArray(1);
        for (int i = 0; i < size_; i++)
        {
            if (arr_[i] == item)
            {
                index->Push(i);
            }
        }
        if (index->IsEmpty())
        {
            cout << "remove:not found" << endl;
        }
        for (int i = index->Size() - 1; i >= 0; i--)
        {
            Del(index->At(i));
        }
        ResizeForSize(size_-1);
        return index;
    }
    int Find(int_32t item)
    {
        for (int i = 0; i < size_; i++)
        {
            if (arr_[i] == item)
            {
                return i;
            }
        }
        return -1;
    }
    int Size()
    {
        return this->size_;
    }
    int Capacity()
    {
        return this->capacity_;
    }
    bool IsEmpty()
    {
        if (size_ != 0)
        {
            return false;
        }
        return true;
    }
    void print()
    {
        for (int i = 0; i < size_; i++)
        {
            cout << " " << arr_[i];
        }
        cout << endl;
    }
};
