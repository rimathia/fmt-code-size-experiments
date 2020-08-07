#include <gtest/gtest.h>
#include <memory_buffer/memory_buffer.h>

using namespace membuf;

TEST(memory_buffer_basic, starting_capacity) {
  memory_buffer<FactorTwo, 17> buf;
  ASSERT_EQ(buf.size(), 0);
  ASSERT_EQ(buf.capacity(), 17);
}

TEST(memory_buffer_basic, reserve) {
  memory_buffer<FactorTwo, 5> buf;
  ASSERT_EQ(buf.capacity(), 5);
  buf.reserve(6);
  ASSERT_EQ(buf.capacity(), 10);
}

TEST(memory_buffer_basic, push_back_growth) {
  memory_buffer<FactorTwo, 0> buf;
  buf.push_back('a');
  const std::vector<char> t0{'a'};
  ASSERT_TRUE(
      std::equal(std::begin(buf), std::end(buf), std::begin(t0), std::end(t0)));
  const auto b0 = std::begin(buf);
  buf.push_back('b');
  const std::vector<char> t1{'a', 'b'};
  ASSERT_TRUE(
      std::equal(std::begin(buf), std::end(buf), std::begin(t1), std::end(t1)));
  const auto b1 = std::begin(buf);
  ASSERT_FALSE(b0 == b1);
  buf.push_back('c');
  ASSERT_TRUE(buf.capacity() == 4);
  const auto b2 = std::begin(buf);
  buf.push_back('d');
  const auto b3 = std::begin(buf);
  ASSERT_TRUE(b2 == b3);
}

TEST(memory_buffer_basic, push_back_internal) {
  memory_buffer<FactorOnePoint5, 4> buf;
  const auto b0 = std::begin(buf);
  buf.push_back('a');
  buf.push_back('b');
  buf.push_back('c');
  buf.push_back('d');
  const auto b4 = std::begin(buf);
  ASSERT_TRUE(b0 == b4);
  buf.push_back('e');
  const auto b5 = std::begin(buf);
  ASSERT_FALSE(b0 == b5);
  ASSERT_EQ(buf.capacity(), 6);
  const std::vector<char> t5{'a', 'b', 'c', 'd', 'e'};
  ASSERT_TRUE(
      std::equal(std::begin(buf), std::end(buf), std::begin(t5), std::end(t5)));
}