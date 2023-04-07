// The Continuation and Optional Monad
// Mainly applicable to C++11 (before std::future, promise)
//
// Monad is a structure that combines functions and wraps their return values
// in a type with additional computation.
//
// Functional languages typically use monads as a way to turn a sequence of
// functions into a pipeline that abstracts the control flow and side-effects.
//
// Example of monad is the Maybe type. Procedural languages tend to use tests
// on pointers to determine if a function returned a proper value.

#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <vector>

// An example of a Maybe Monad
std::optional<int> getFirst(const std::vector<int>& v) {
  if (v.empty()) return std::optional<int>();
  return std::optional<int>(v[0]);
}

// Say you have some asynchronous API e.g. file API where the underlying
// hardware sends disk I/O. Instead of sending a blocking call, you can compose
// a series of asynchronous API calls.
void asyncAPI(std::function<void(std::string&)> handler) {
  std::thread t([handler]() {
    std::cout << "Started async\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::string r = "result";
    handler(r);
  });
  t.detach();
}

// Continuator is an example of a Continuation monad
// Continuators are values that have not materialized yet.
// It is a promise to eventually yield a result.
// For instance, a continuator can wrap the result of a file handler formed from
// an async file open().
template <typename R, typename A>
struct Continuator {
  // Empty destructor to prevent early destruction?
  virtual ~Continuator() {}
  virtual R andThen(std::function<R(A)> k) {}
};

struct AsyncAPI : Continuator<void, std::string> {
  // continuation, k, is the handler for the async API
  void andThen(std::function<void(std::string&)> k) { asyncAPI(k); }
  std::string s_;
};

// Return is useful for composing a series of asynchronous API calls.
// Functional languages convert loops into recursion. Here we do something
// similar by calling the API with a handler where the handler calls the
// API again and passes itself the handler.
template <typename R, typename A>
struct Return : Continuator<R, A> {
  Return(A a) : a_(a) {}
  R andThen(std::function<R(A)> k) { return k(a_); }
  A a_;
};

// Bind lets you compose two calculations represented by continuators.
// Continuators wrap special values we might not have received yet.
// Bind allows you to pass the result of a computation to another computation
// after e.g. after an asynch file open(), you would want to pass the
// Continuator that wraps the file handler to an async read(file_chunk).
//
// Bind composes an arbitrary continuator called ctor with a continuator for
// the rest of the computation.
template <typename R, typename A, typename C>
struct Bind : Continuator<R, A> {
  Bind(C&& first, std::function<std::unique_ptr<Continuator<R, A>>(A)> second)
      : first_(first), second_(second) {}
  void andThen(std::function<R(A)> k) {
    std::function<std::unique_ptr<Continuator<R, A>>(A)> second = second_;
    std::function<R(A)> f = [k, second](A a) { return second(a)->andThen(k); };
    first_.andThen(f);
  }
  C first_;
  std::function<std::unique_ptr<Continuator<R, A>>(A)> second_;
};

// NOTE: Loop is untested because it infinitely loops
struct Loop : Continuator<void, std::string> {
  Loop(std::string s) : s_(s) {}
  void andThen(std::function<void(std::string)> k) {
    std::cout << "Loop::andThen: " << s_ << "\n";
    Bind<void, std::string, AsyncAPI>(AsyncAPI(), [](std::string t) {
      return std::unique_ptr<Continuator>(new Loop(t));
    }).andThen(k);
  }
  std::string s_;
};

// Interestingly, LoopN will be reused on each iteration. Neat!
struct LoopN : Continuator<void, std::string> {
  LoopN(std::string s, int n) : s_(s), n_(n) {}
  void andThen(std::function<void(std::string)> k) {
    std::cout << "[LoopN::andThen] " << s_ << " " << n_ << "\n";
    int n = n_;
    Bind<void, std::string, AsyncAPI>(
        AsyncAPI(),
        [n](std::string s) -> std::unique_ptr<Continuator> {
          if (n > 0) {
            return std::unique_ptr<Continuator>(new LoopN(s, n - 1));
          } else {
            return std::unique_ptr<Continuator>(
                new Return<void, std::string>("Done!"));
          }
        })
        .andThen(k);
  }
  std::string s_;
  int n_;
};

// Combinator acts as a barrier waiting for all computations to reach it to
// be combined
struct Combinator : Continuator<void, std::string> {
  Combinator(std::unique_ptr<Continuator<void, std::string>>& a,
             std::unique_ptr<Continuator<void, std::string>>& b)
      : a_(std::move(a)), b_(std::move(b)) {}
  void andThen(std::function<void(std::pair<std::string, std::string>)> k) {
    a_->andThen([this, k](std::string s1) {
      std::lock_guard<std::mutex> l(m_);
      if (s2_.empty()) {
        s1_ = s1;
      } else {
        k(std::make_pair(s1, s2_));
      }
    });
    b_->andThen([this, k](std::string s2) {
      std::lock_guard<std::mutex> l(m_);
      if (s1_.empty()) {
        s2_ = s2;
      } else {
        k(std::make_pair(s1_, s2));
      }
    });
  }
  std::mutex m_;
  std::string s1_;
  std::string s2_;
  std::unique_ptr<Continuator<void, std::string>> a_;
  std::unique_ptr<Continuator<void, std::string>> b_;
};

int main() {
  std::vector<int> a{1, 2, 3};
  std::vector<int> b;

  auto an_integer = getFirst(a);
  if (an_integer) {
    std::cout << "*an_integer: " << *an_integer << '\n';
    std::cout << "an_integer.value(): " << an_integer.value() << '\n';
    std::cout << "an_integer.value_or(2017): " << an_integer.value_or(2017)
              << '\n';
  }
  std::cout << '\n';

  auto an_empty_integer = getFirst(b);
  if (!an_empty_integer) {
    std::cout << "an_empty_integer.value_or(2017): "
              << an_empty_integer.value_or(2017) << '\n';
  }

  AsyncAPI dial;
  dial.andThen(
      std::function([](std::string& s) -> void { std::cout << s << '\n'; }));

  LoopN("Begin ", 3).andThen([](std::string s) {
    std::cout << "Finally " << s << "\n";
  });
  // NOTE: may need to adjust number of iterations to reach "Done!"
  for (int i = 0; i < 20; ++i) {
    std::cout << "Iteration " << i << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };

  std::unique_ptr<Continuator<void, std::string>> one_api(
      new Return<void, std::string>("One!"));
  std::unique_ptr<Continuator<void, std::string>> two_api(
      new Return<void, std::string>("Two!"));
  Combinator combine(one_api, two_api);
  combine.andThen([](std::pair<std::string, std::string> ss) {
    std::cout << ss.first + ", " + ss.second << "\n";
  });
  return 0;
}
