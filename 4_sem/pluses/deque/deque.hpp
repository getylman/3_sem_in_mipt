/**
 * @file deque.hpp
 * @author getylman
 * @date 22.02.2023
 */
#pragma once
#include <memory>


template <typename T, typename Allocator = std::allocator<T>>
class Deque {
 public:
  //=================Constructors=================
  Deque();
  Deque(const size_t& count);
  Deque(const size_t& count, const T& value);
  Deque(const Deque<T, Allocator>& deq);
  ~Deque();
  Deque<T, Allocator>& operator=(cosnt Deque<T, Allocator>& deq);
  //==============================================
  //=============Accessing an element=============
  T& operator[](const size_t& index);
  const T& operator[](const size_t& index) const;
  T& at(const size_t& index);
  const T& at(const size_t& index) const;
  //==============================================
  //==============SizeInformation=================
  size_t size() const { return total_size_; }
  bool empty() const { return size() == 0; }
  //==============================================
  //===========Modification methods===============
  void push_back(const T& elem);
  void pop_back();
  void push_front(const T& elem);
  void pop_front();
  //==============================================
  //==================ITERATOR====================
  struct iterator {
    
  };
  //==============================================
 private:
  const uint64_t kChunkSize = 0; // size of chunks
  uint64_t total_size_ = 0; // size of in full container
  uint64_t fc_size_ = 0; // first chunk size
  uint64_t lc_size_ = 0; // last chunk size
};
//using Deque = std::deque<T>;