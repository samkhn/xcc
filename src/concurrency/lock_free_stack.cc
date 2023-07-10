// Lock Free Stack

#include <atomic>
#include <iostream>

template <typename T>
struct Node {
  Node(const T& data) : data_(data), next_(nullptr) {}
  T data_;
  Node* next_;
};

template <typename T>
class Stack {
 public:
  Stack() : n_(0) {}

  void Push(const T& data) {
    Node<T>* new_node = new Node<T>(data);
    new_node->next_ = head_.load(std::memory_order_relaxed);
    while (!head_.compare_exchange_weak(new_node->next_, new_node,
                                        std::memory_order_release,
                                        std::memory_order_relaxed))
      ;
    n_++;
  }

  void Pop() {
    Node<T>* del = head_.load(std::memory_order_relaxed);
    while (!head_.compare_exchange_weak(del, del->next_,
                                        std::memory_order_release,
                                        std::memory_order_relaxed))
      ;
    delete del;
    n_--;
  }

  std::size_t Size() const { return n_; }

 private:
  std::atomic<Node<T>*> head_;
  std::size_t n_;
};

int main() {
  Stack<int> s;
  s.Push(1);
  s.Push(2);
  std::size_t n = s.Size();
  if (n != 2) {
    std::cout << "s.Size() fail. Got " << n << ". Want " << 2 << "\n";
    return -1;
  }
  s.Pop();
  n = s.Size();
  if (n != 1) {
    std::cout << "s.Size() fail. Got " << n << ". Want " << 1 << "\n";
    return -1;
  }
  std::cout << "Lock free stack: all tests passed\n";
  return 0;
}
