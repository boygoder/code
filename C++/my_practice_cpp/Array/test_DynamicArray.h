#include "DynamicArray.h"
#include <assert.h>
class test_DynamicArray{
 public:
  void RunTests() const;
  void TestSize() const;
  // Tests increases and decreases in capacity based on number of items stored.
  void TestCapacity() const;
  void TestIsEmpty() const;
  void TestGetValueAt() const;
  void TestPop() const;
  void TestInsert() const;
  void TestPrepend() const;
  void TestDelete() const;
  void TestRemove() const;
  void TestFind() const;
};

void test_DynamicArray::RunTests() const
{
    TestSize();
    TestCapacity();
    TestIsEmpty();
    TestGetValueAt();
    TestPop();
    TestInsert();
    TestPrepend();
    TestDelete();
    TestRemove();
    TestFind();
}

void test_DynamicArray::TestSize() const {
  DynamicArray tester(3);
  assert(tester.Size() == 0);

  int items_to_add = 5;
  for (int i = 0; i < items_to_add; ++i) {
    tester.Push(i + 1);
  }
  assert(tester.Size() == items_to_add);
}

void test_DynamicArray::TestIsEmpty() const {
  DynamicArray tester(3);
  assert(tester.IsEmpty());
}

void test_DynamicArray::TestCapacity() const {
  DynamicArray tester(4);

  // test increasing size
  for (int i = 0; i < 17; ++i) {
    tester.Push(i + 1);
  }
  for (int j = 0; j < 20; ++j) {
    tester.Push(j + 1);
  }

  // test decreasing size
  for (int k = 0; k < 30; ++k) {
    tester.Pop();
  }

  for (int k = 0; k < 7; ++k) {
    tester.Pop();
  }

}

void test_DynamicArray::TestGetValueAt() const {
  DynamicArray tester(3);
  tester.Push(4);
  tester.Push(9);
  tester.Push(12);
  assert(tester.At(0) == 4);
  assert(tester.At(1) == 9);
  assert(tester.At(2) == 12);
}

void test_DynamicArray::TestPop() const {
  DynamicArray tester(1);
  tester.Push(3);

  int popped = tester.Pop();
  assert(popped == 3);
  tester.Push(9);
  tester.Push(8);

  assert(tester.Size() == 2);
  int popped2 = tester.Pop();
  assert(popped2 == 8);
  assert(tester.Size() == 1);
}

void test_DynamicArray::TestInsert() const {
  DynamicArray tester(3);
  tester.Push(5);
  tester.Push(7);
  tester.Push(9);
  tester.Insert(0, 4);
  assert(tester.At(0) == 4);
  assert(tester.At(1) == 5);
  assert(tester.At(2) == 7);
  assert(tester.At(3) == 9);
  tester.Insert(3, 8);
  assert(tester.At(3) == 8);
  assert(tester.At(4) == 9);
}

void test_DynamicArray::TestPrepend() const {
  DynamicArray tester(3);
  tester.Push(9);
  tester.Push(8);
  tester.Push(7);
  tester.Prepend(6);
  assert(tester.Size() == 4);
  assert(tester.At(0) == 6);
  assert(tester.At(1) == 9);
  assert(tester.At(3) == 7);
}

void test_DynamicArray::TestDelete() const {
  DynamicArray tester(1);
  tester.Push(5);
  tester.Del(0);
  assert(tester.Size() == 0);

  tester.Push(9);
  tester.Push(10);
  tester.Push(11);
  tester.Del(1);
  assert(tester.Size() == 2);
  assert(tester.At(0) == 9);
  assert(tester.At(1) == 11);
}

void test_DynamicArray::TestRemove() const {
  DynamicArray tester(5);
  tester.Push(50);
  tester.Push(2);
  tester.Push(50);
  tester.Push(4);
  tester.Push(50);
  tester.Remove(50);
  assert(tester.Size() == 2);
  assert(tester.At(0) == 2);
  assert(tester.At(1) == 4);
}

void test_DynamicArray::TestFind() const {
  DynamicArray tester(3);
  tester.Push(4);
  tester.Push(7);
  tester.Push(11);
  assert(tester.Find(5) == -1);
  assert(tester.Find(4) == 0);
  assert(tester.Find(7) == 1);
  assert(tester.Find(11) == 2);
}
