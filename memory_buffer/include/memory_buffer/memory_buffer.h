#ifndef MEMORY_BUFFER_H
#define MEMORY_BUFFER_H

#include <cstddef>

// intentionally primitive memory buffer implementation to experiment
// with in-class buffer sizes and growth strategies
// partly copied from the implementation of the fmt memory buffer, errors are my
// own

namespace membuf {

struct FactorOnePoint5 {
  std::size_t operator()(std::size_t c) { return c + c / 2; }
};

struct FactorTwo {
  std::size_t operator()(std::size_t c) { return 2 * c; }
};

template <class NewCapacityGuess, std::size_t buffer_size_>
class memory_buffer {
 public:
  memory_buffer() = default;
  memory_buffer(const memory_buffer&) = delete;
  memory_buffer(memory_buffer&&) = delete;
  memory_buffer& operator=(const memory_buffer&) = delete;
  memory_buffer& operator=(memory_buffer&&) = delete;

  using value_type = char;

  void reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
      grow(new_capacity);
    }
  }

  void grow(size_t min_capacity) {
    size_t new_capacity = NewCapacityGuess{}(capacity_);
    if (min_capacity > new_capacity) {
      new_capacity = min_capacity;
    }
    if (new_capacity > capacity_) {
      char* old_ptr_ = ptr_;
      char* new_ptr_ = new char[new_capacity];
      std::uninitialized_copy(old_ptr_, old_ptr_ + size_, new_ptr_);
      ptr_ = new_ptr_;
      if (old_ptr_ != internal_store_) {
        delete[] old_ptr_;
      }
      capacity_ = new_capacity;
    }
  }

  void push_back(const char& value) {
    reserve(size_ + 1);
    ptr_[size_++] = value;
  }

  std::size_t size() const { return size_; }
  std::size_t capacity() const { return capacity_; }
  const char* begin() const { return ptr_; }
  const char* end() const { return ptr_ + size_; }

 private:
  char* ptr_ = internal_store_;
  size_t size_ = 0;
  size_t capacity_ = buffer_size_;
  char internal_store_[buffer_size_];
};

}  // namespace membuf

#endif