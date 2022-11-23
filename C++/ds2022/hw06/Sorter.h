#include <vector>
#include <concepts>
#include <functional>
using namespace std;
template<typename T>
concept Comparable = requires(T a, T b)
{
    {a < b}-> same_as<bool>;
    //{a > b}-> same_as<bool>;
};

template <Comparable Type, typename Comparator = less<Type>>
class Sorter
{
public:
    Sorter() = default;
    virtual ~Sorter() = default;
    virtual void sort(vector<Type>& array, Comparator lessThan = less<Type>{}) = 0;
};

template <Comparable Type,typename Comparator = less<Type>>
class InsertionSorter : public Sorter<Type,Comparator>
{
public:
    virtual void sort(vector<Type>& array, Comparator lessThan = less<Type>{}) override
    {
        sort(array, 0, array.size() - 1, lessThan);
    }
    void sort(vector<Type>& array, int left, int right, 
              Comparator lessThan = less<Type>{})
    {
        for (int p = left; p <= right; p++)
        {
            Type tmp = move(array.at(p));
            int j;
            for(j = p; j > 0 && lessThan(tmp,array.at(j-1)); --j)
            {
                array[j] = move(array.at(j-1));
            }
            array[j] = move(tmp);
        }
    }
};

template <Comparable Type,typename Comparator = less<Type>>
class MergeSorter : public Sorter<Type,Comparator>
{
public:
    virtual void sort(vector<Type>& array, Comparator lessThan = less<Type>{}) override
    {
        vector<Type> tmpArray(array.size());
        mergeSort(array, tmpArray, 0, array.size() - 1, lessThan);
    }
private:
    void mergeSort(vector<Type>& array, vector<Type>& tmpArray,
                   int left, int right, Comparator lessThan)
    {
        if(left < right)
        {
            int center = (left + right) / 2;
            mergeSort(array, tmpArray, left, center, lessThan);
            mergeSort(array, tmpArray, center+1, right, lessThan);
            merge(array, tmpArray, left, center+1, right, lessThan);
        }
    }
    void merge(vector<Type>& array, vector<Type>& tmpArray, int leftPos, 
               int rightPos, int rightEnd, Comparator lessThan)
    {
        int leftEnd = rightPos - 1;
        int tmpPos = leftPos;
        int numElements = rightEnd - leftPos + 1;

        while(leftPos <= leftEnd && rightPos <= rightEnd)
        {
            if(lessThan(array.at(rightPos), array.at(leftPos)))
            {
                tmpArray[tmpPos++] = move(array[rightPos++]);   
            }
            else
            {
                tmpArray[tmpPos++] = move(array[leftPos++]);
            }
        }

        while(leftPos <= leftEnd)
        {
            tmpArray[tmpPos++] = move(array[leftPos++]);
        }
        while(rightPos <= rightEnd)
        {
            tmpArray[tmpPos++] = move(array[rightPos++]);
        }

        for(int i = 0; i < numElements;++i,--rightEnd)
        {
            array[rightEnd] = move(tmpArray[rightEnd]);
        }

    }
};

template<Comparable Type, typename Comparator = less<Type>>
class QuickSorter : public Sorter<Type,Comparator>
{
public:
    virtual void sort(vector<Type>& array, Comparator lessThan = less<Type>{}) override
    {
        quickSort(array, 0, array.size() - 1, lessThan);
    }
private:
    InsertionSorter<Type,Comparator> insertSorter;
    const Type& median3(vector<Type>& array, int left, int right, 
                        Comparator lessThan)
    {
        int center = (left + right) / 2;

        if (lessThan(array[center], array[left]))
        {
            swap(array[left],array[center]);
        }
        if(lessThan(array[left], array[center]))
        {
            swap(array[left], array[center]);
        }
        if(lessThan(array[right],array[center]))
        {
            swap(array[center],array[right]);
        }

        //将枢纽元置于right-1处
        swap(array[center], array[right - 1]);
        return array[right - 1];

    }
    void quickSort(vector<Type>& array, int left, int right,
                   Comparator lessThan)
    {
        if (left + 10 <= right)
        {
            const Type& pivot = median3(array, left, right, lessThan);
            int i = left, j = right - 1;
            //双指针，一个从前，一个从后，将大于pivot的元素挪到右侧
            for( ; ; )
            {
                while(lessThan(array[++i],pivot)) {};
                while(lessThan(pivot,array[--j])) {};
                //i > j说明所有左右交汇，所有元素都处理好了。
                if(i < j)
                {
                    swap(array[i], array[j]);
                }
                else
                {
                    break;
                }
            }
            //有序，将枢纽元移到它应该在的位置
            swap(array[i], array[right - 1]);
            quickSort(array, left, i-1, lessThan);
            quickSort(array, i+1, right, lessThan);
        }
        else
        {

            insertSorter.sort(array, left, right, lessThan);
        }

    }
};

