/**
 * @file deque.hpp
 * @author getylman
 * @date 25.03.2023
 */

/*
 * Я ЗАПРЕЩАЮ КОМУ ЛИБО МЕНЬ РАНГ ДЕКА
 * ПРОБЛЕМЫ НА ВАЩУ СОВЕСТЬ
 */

#pragma once
#include <iterator>
#include <memory>
#include <type_traits>

template <typename TempT, typename Alloc = std::allocator<TempT>>
class Deque {
 protected:
  using value_type = TempT;
  // type of inserted type
  using allocator_type = Alloc;
  // type of inserted allocator
  using Type_alloc_type = typename std::allocator_traits<
      allocator_type>::template rebind<TempT>::other;
  // allocator type of inner type
  using Alloc_traits = std::allocator_traits<Type_alloc_type>;
  // allocator_traits
  using PrPtr = Alloc_traits::pointer;
  // private allocator traits pointer
  using PrPtr_const = Alloc_traits::const_pointer;
  // private allocator traits constant pointer
  using pointer = Alloc_traits::pointer;
  using const_pointer = Alloc_traits::const_pointer;
  using reference = Alloc_traits::reference;
  using const_reference = Alloc_traits::const_reference;
  using difference_type = ptrdiff_t;

 public:
  //===================Iterator===================
  template <bool IsConst>
  struct common_iterator;
  //**************Iterator usings*****************
  using iterator = common_iterator<false>;
  using const_iterator = common_iterator<true>;
  using reverse_iterator = std::reverse_iterator<common_iterator<false>>;
  using const_reverse_iterator = std::reverse_iterator<common_iterator<true>>;
  //**********************************************
  //==============================================

 private:
  const uint64_t kChunkSize = 512;  // size of chunks
                                    // I cannot explane why 512
  const uint64_t kDefaultDequeLenth = 4;
  // --------------------------------
  // reason why default 4
  // # - using space, * - free space
  // ******
  // ****##
  // ##****
  // ******
  // --------------------------------
  static constexpr const uint64_t set_chunk_rank() noexcept {
    const uint64_t kChunkRank = 512;
    return kChunkRank;
  }  // function to set a rank for chunk
  static constexpr const uint64_t set_chunk_rank(
      const uint64_t& rank) noexcept {
    return rank;
  }
  //====================Chunk=====================
  template <uint64_t ChunkRank = set_chunk_rank()>
  class Chunk;
  //==============================================
  //===============Deque Body=====================
  struct DequeBody;
  // struct to keep all Deque fields
  //==============================================

 protected:
  using Chunk_alloc_type =
      typename Alloc_traits::template rebind<Chunk<>>::other;
  // allocator type of chunk
  using Chunk_alloc_traits = std::allocator_traits<Chunk_alloc_type>;
  // allocator trits for chunk
  using Chunk_pointer = Chunk_alloc_traits::pointer;
  // pointer for chunks
  Chunk_alloc_type all_ch_;
  // object of chunk allocator type
 private:
  //============Deque Memory Controllere==========
  struct MemCntAndBodyOfDeque;
  // struct which one can use memory resources
  Type_alloc_type& get_unit_allocator() noexcept;
  const Type_alloc_type& get_unit_allocator() const noexcept;
  Chunk_alloc_type get_chunk_allocator() const noexcept;
  pointer chunk_allocation();
  void chunk_dealocation(pointer ptr) noexcept;         //---
  Chunk_pointer body_allocation(const uint64_t& size);  //---
  void body_dealocation(Chunk_pointer ptr,
                        const uint64_t& size) noexcept;  //---
  void allocation_attempt_of_deque_body(Chunk_pointer& ptr,
                                        const uint64_t& size);  //---
  void constrcution_attempt_of_deque_body(Chunk_pointer& ptr_head_chunk,
                                          Chunk_pointer& ptr_tail_chunk,
                                          Chunk_pointer& ptr_body,
                                          uint64_t& size);  //---
  // functions which used in reserve_memory_in_deque
  void reserve_memory_in_deque(const uint64_t& num_of_units);  //---
  // function for allocation memory for vector of chunks
  // kinda it will reserve enought chunks to keeping our units
  void body_range_construction(Chunk_pointer head, Chunk_pointer tail);  //---
  void body_range_destruction(Chunk_pointer head,
                              Chunk_pointer tail) noexcept;  //---
  // functions for building
  //==============================================
  //========Functions for unit monipulations======
  void priv_push_back(TempT&& elem);
  void priv_push_front(TempT&& elem);
  void priv_pop_back() noexcept;
  void priv_pop_front() noexcept;
  // priv -> private
  // I want realize all logic in private function
  // and call them in public functions
  //==============================================

 public:
  //=================Constructors=================
  static_assert(std::is_same_v<typename Alloc::value_type, TempT>);
  // if types are not same will be CE
  Deque();
  explicit Deque(const size_t& count, const Alloc& alloc = Alloc());
  explicit Deque(const Alloc& alloc);
  explicit Deque(const size_t& count, const TempT& value,
                 const Alloc& alloc = Alloc());
  template <typename AnotherAlloc = std::allocator<TempT>>
  Deque(const Deque<TempT, AnotherAlloc>& deq);
  template <typename AnotherAlloc = std::allocator<TempT>>
  Deque(Deque<TempT, AnotherAlloc>&& deq);
  ~Deque() noexcept;
  template <typename AnotherAlloc = std::allocator<TempT>>
  Deque<TempT, AnotherAlloc>& operator=(
      const Deque<TempT, AnotherAlloc>& deq) &;
  // will called only for lvalue
  template <typename AnotherAlloc = std::allocator<TempT>>
  Deque<TempT, AnotherAlloc>& operator=(Deque<TempT, AnotherAlloc>&& deq) &&;
  // will called only for rvalue
  //==============================================
  //=============Accessing an element=============
  TempT& operator[](const size_t& index) noexcept;
  const TempT& operator[](const size_t& index) const noexcept;
  TempT& at(const size_t& index);
  const TempT& at(const size_t& index) const;
  TempT& front() noexcept;
  const TempT& front() const noexcept;
  TempT& back() noexcept;
  const TempT& back() const noexcept;
  //==============================================
  //==============SizeInformation=================
  size_t size() const noexcept;
  bool empty() const noexcept;
  //==============================================
  //===========Modification methods===============
  // void push_back(const TempT& elem);
  void push_back(TempT&& elem);
  void pop_back() noexcept;
  // void push_front(const TempT& elem);
  void push_front(TempT&& elem);
  void pop_front() noexcept;
  //==============================================
  //================Iterator methods==============
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;
  reverse_iterator rbegin() noexcept;
  const_reverse_iterator rbegin() const noexcept;
  const_reverse_iterator crbegin() const noexcept;
  reverse_iterator rend() noexcept;
  const_reverse_iterator rend() const noexcept;
  const_reverse_iterator crend() const noexcept;
  //==============================================

 private:
  //================Deque Fields=================
  // DequeBody body_;  // full body of our container
  MemCntAndBodyOfDeque mc_body_;
  //=============================================
};

// free space to my orientation
// free space to my orientation
// free space to my orientation
// free space to my orientation
// free space to my orientation
// free space to my orientation

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//    NO MEMBER DEFINITION AND DECLARATION
//==============Deque Body===================
template <typename TempT, typename Alloc>
struct Deque<TempT, Alloc>::DequeBody {
  uint64_t total_size = 0;             // size of in full container
  uint64_t num_of_chunks = 0;          // how many chunks have a container
  Chunk_pointer body = nullptr;        // pointer of full deque. the end is just
                                       // body plus size
  Chunk_pointer head_chunk = nullptr;  // pointer of current head
  Chunk_pointer tail_chunk = nullptr;  // pointer of current tail

  DequeBody() noexcept : body(), head_chunk(), tail_chunk() {
  }
  DequeBody(const DequeBody&) = default;
  DequeBody& operator=(const DequeBody&) = default;
  DequeBody(DequeBody&& dqb) noexcept : DequeBody(dqb) {
    dqb = DequeBody();
  }
  void exchange_data(DequeBody& dqb) noexcept {
    std::swap(*this, dqb);
  }
  void stretch_left_end(const size_t& new_len);
  void stretch_right_end(const size_t& new_len);
  // function for reallocation memory for unit monipulation
};
//===========================================

//=================ITERATOR==================
template <typename TempT, typename Alloc>
template <bool IsConst>
struct Deque<TempT, Alloc>::common_iterator {
  //***************Public usings****************
  using iterator_category = std::random_access_iterator_tag;
  using value_type = TempT;
  using pointer = TempT*;
  using reference = TempT&;
  using difference_type = int64_t;  // ptrdiff_t;
  //********************************************
 private:
  //**************Private usings****************
  using conditional_ptr = std::conditional_t<IsConst, const pointer, pointer>;
  using conditional_ref =
      std::conditional_t<IsConst, const reference, reference>;
  // size_t index_;                // index of current nod in container
  conditional_ptr ptr_ = nullptr;         // pointer of current node
  conditional_ptr top_ptr_ = nullptr;     // pointer of upper bound
  conditional_ptr bottom_ptr_ = nullptr;  // pointer of lower bound
  Chunk_pointer cur_chunk_ptr_ = nullptr;
  // pointer of current chunk

  //********************************************
  //***********Private Functions****************
  void change_chunk(Chunk<> new_chunk) noexcept {
    cur_chunk_ptr_ = new_chunk;
    top_ptr_ = new_chunk.chunk_body_;
    bottom_ptr_ =
        new_chunk.chunk_body_ + static_cast<difference_type>(set_chunk_rank());
  }
  //********************************************
 public:
  //****************Constructors****************
  common_iterator() noexcept {
  }
  common_iterator(const pointer& ptr, const Chunk_pointer& curnk_ptr) noexcept
      : ptr_(ptr),
        top_ptr_(curnk_ptr->chunk_body_),
        bottom_ptr_(curnk_ptr->chunk_body_ + curnk_ptr->get_chunk_rank()),
        cur_chunk_ptr_(curnk_ptr) {
  }  // constructor from two pointers
  template <bool IsConstTmp>
  common_iterator(const common_iterator<IsConstTmp>& iter) noexcept
      : ptr_(iter.ptr_),
        top_ptr_(iter.top_ptr_),
        bottom_ptr_(iter.bottom_ptr_),
        cur_chunk_ptr_(iter.cur_chunk_ptr_) {
    static_assert(std::is_same<decltype(*ptr_), decltype(*(iter.ptr_))>::value);
    // make CE if value types of iterators are not same
  }  // copy costructor
  ~common_iterator() {
  }
  template <bool IsConstTmp>
  common_iterator<IsConst>& operator=(
      const common_iterator<IsConstTmp>& iter) & noexcept {
    ptr_ = iter.ptr_;
    cur_chunk_ptr_ = iter.cur_chunk_ptr_;
    top_ptr_ = iter.top_ptr_;
    bottom_ptr_ = iter.bottom_ptr_;
    return *this;
  }
  //********************************************
  //****************Memory operators************
  operator conditional_ptr() {
    return &**this;
  }  // operator c-style cast of iterator
  conditional_ref operator*() const noexcept {
    return *ptr_;
  }
  conditional_ptr operator->() const noexcept {
    return ptr_;
  }
  // template <typename IterT1>
  // IterT& operator->*(IterT1 IterT::*another_ptr) const noexcept {
  //   return (*ptr_).*another_ptr;
  // }
  // commented to the best times
  conditional_ref operator[](const int64_t& idx) const noexcept {
    return *(*this + idx);
  }
  //********************************************
  //************Aithmetic operators*************
  common_iterator<IsConst>& operator+=(const int64_t& delta) noexcept {
    const int64_t distance = static_cast<int64_t>(ptr_ - top_ptr_) + delta;
    if (distance >= 0 and distance < static_cast<int64_t>(set_chunk_rank())) {
      ptr_ += distance;
    } else {
      const int64_t chunk_distance =
          (distance > 0)
              ? distance / static_cast<int64_t>(set_chunk_rank())
              : -((-distance - 1) / static_cast<int64_t>(set_chunk_rank())) - 1;
      change_chunk(cur_chunk_ptr_ + chunk_distance);
      ptr_ = top_ptr_ + distance -
             chunk_distance * static_cast<int64_t>(set_chunk_rank());
    }
    return *this;
  }
  common_iterator<IsConst>& operator-=(const int64_t& delta) noexcept {
    return *this += -delta;
  }
  common_iterator<IsConst> operator+(const int64_t& delta) noexcept {
    common_iterator<IsConst> tmp = *this;
    tmp += delta;
    return tmp;
  }
  common_iterator<IsConst> operator-(const int64_t& delta) noexcept {
    common_iterator<IsConst> tmp = *this;
    tmp -= delta;
    return tmp;
  }
  common_iterator<IsConst>& operator++() noexcept {
    return *this += 1;
  }
  common_iterator<IsConst>& operator--() noexcept {
    return *this -= 1;
  }
  common_iterator<IsConst> operator++(int) noexcept {
    return ++common_iterator<IsConst>(*this);
  }
  common_iterator<IsConst> operator--(int) noexcept {
    return --common_iterator<IsConst>(*this);
  }

  difference_type operator-(const common_iterator<IsConst>& iter) noexcept {
    return static_cast<difference_type>(set_chunk_rank()) *
           static_cast<difference_type>(
               cur_chunk_ptr_ - iter.cur_chunk_ptr_ -
               static_cast<int64_t>(cur_chunk_ptr_ != nullptr) +
               (ptr_ - top_ptr_) + (iter.bottom_ptr_ - iter.ptr_));
  }
  //********************************************
  //**************Compare operators*************
  friend bool operator<(const common_iterator<IsConst>& it1,
                        const common_iterator<IsConst>& it2) noexcept {
    return (it1.cur_chunk_ptr_ == it2.cur_chunk_ptr_)
               ? it1.ptr_ < it2.ptr_
               : it1.cur_chunk_ptr_ < it2.cur_chunk_ptr_;
    // тут надо проверять находимся ли мы в одном чанке или нет
  }
  //********************************************
};

//************Aithmetic operators************
template <typename TempT, typename Alloc = std::allocator<TempT>, bool IsConst>
typename Deque<TempT, Alloc>::common_iterator<IsConst> operator+(
    const int64_t& delta,
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>&
        iter) noexcept {
  return iter + delta;
}
template <typename TempT, typename Alloc = std::allocator<TempT>, bool IsConst>
typename Deque<TempT, Alloc>::common_iterator<IsConst> operator-(
    const int64_t& delta,
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>&
        iter) noexcept {
  return iter - delta;
}
//*******************************************
//*************Compare operators*************
template <typename TempT, typename Alloc = std::allocator<TempT>, bool IsConst>
bool operator>(
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>& it1,
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>&
        it2) noexcept {
  return it2 < it1;
}
template <typename TempT, typename Alloc = std::allocator<TempT>, bool IsConst>
bool operator>=(
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>& it1,
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>&
        it2) noexcept {
  return !(it1 < it2);
}
template <typename TempT, typename Alloc = std::allocator<TempT>, bool IsConst>
bool operator<=(
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>& it1,
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>&
        it2) noexcept {
  return !(it1 > it2);
}
template <typename TempT, typename Alloc = std::allocator<TempT>, bool IsConst>
bool operator==(
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>& it1,
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>&
        it2) noexcept {
  return !(it1 < it2 || it1 > it2);
}
template <typename TempT, typename Alloc = std::allocator<TempT>, bool IsConst>
bool operator!=(
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>& it1,
    const typename Deque<TempT, Alloc>::common_iterator<IsConst>&
        it2) noexcept {
  return !(it1 == it2);
}
//*******************************************
//===========================================

//==================Chunk====================
template <typename TempT, typename Alloc>
template <uint64_t ChunkRank>
class Deque<TempT, Alloc>::Chunk {
 private:
  uint64_t chunk_size_ = 0;            // current size
  int16_t l_changing_delta_ = -1;      // delta for moving to left
  int16_t r_changing_delta_ = 1;       // delta for moving to right
  pointer l_chunk_confine_ = nullptr;  // left confine
  pointer r_chunk_confine_ = nullptr;  // right confine
  pointer chunk_body_ = nullptr;       // pointer of head
  pointer chunk_head_ = nullptr;       // head end of using chunk
  pointer chunk_tail_ = nullptr;       // tail end of using chunk
  // bool is_head_ = true;     // means is this chunk is head node or tail node
  Type_alloc_type all_tp_;  // object of our allocator
  //**************Private Functions************
  void allocation_attempt_of_chunk(pointer& ptr) {
    try {
      ptr = Alloc_traits::allocate(all_tp_, ChunkRank);
    } catch (...) {  // if allocation of memory failed it will stop
      throw;         // constructing and throw the exception of this situation
    }
  }  // tring to allocate memeory for chunk
  void coping_chunk_inside(Chunk<>& src, Chunk<>& dst) noexcept {
    // src -> source   dst -> destination
    dst.chunk_head_ = dst.chunk_body_ + (src.chunk_head_ - src.chunk_body_);
    dst.chunk_tail_ = dst.chunk_body_ + (src.chunk_tail_ - src.chunk_body_);
    dst.r_chunk_confine_ =
        dst.chunk_body_ + (src.r_chunk_confine_ - src.chunk_body_);
    dst.l_chunk_confine_ =
        dst.chunk_body_ + (src.l_chunk_confine_ - src.chunk_body_);
    dst.chunk_size_ = src.chunk_size_;
  }  // function for copy chunk fields
  void copy_attempt_of_chunk(Chunk<>& src, Chunk<>& dst) {
    // src -> source   dst -> destination
    uint64_t idx = static_cast<uint64_t>(src.chunk_head_ - src.chunk_body_);
    try {
      for (; idx <= static_cast<uint64_t>(src.chunk_tail_ - src.chunk_body_);
           ++idx) {
        Alloc_traits::construct(all_tp_, dst.chunk_body_ + idx,
                                src.chunk_body_ + idx);
      }
    } catch (...) {
      for (uint64_t i =
               static_cast<uint64_t>(src.chunk_head_ - src.chunk_body_);
           i < idx; ++i) {
        Alloc_traits::destroy(all_tp_, dst.chunk_body_ + i);
      }
      Alloc_traits::deallocate(all_tp_, dst.chunk_body_, ChunkRank);
      throw;
    }
  }  // tring to copy from src to dst chunk
  void construct_unit_attempt_of_chunk(pointer& ptr, TempT&& value,
                                       uint16_t& changing_delta) {
    if (chunk_size_ != 0) {
      ptr += changing_delta;
    }
    try {
      Alloc_traits::construct(all_tp_, ptr, std::forward<TempT>(value));
      // если передастся lvalue то просто скопируется а при rvalue будет просто
      // перемещение
    } catch (...) {
      if (chunk_size_ != 0) {
        ptr -= changing_delta;
      }
      throw;  // if construction of object failed it will stop constructing
              // and throw the exception of this situation
    }
    ++chunk_size_;
  }
  //*******************************************

 public:
  //****************Constructors***************
  Chunk() = default;
  // noexcept(std::is_nothrow_constructible_v<TempT>)
  Chunk(const bool& is_head) {
    // не может быть noexcept тк при попытки аллоцирования пула может вылететь
    // исключение
    allocation_attempt_of_chunk(chunk_body_);
    l_chunk_confine_ = chunk_body_;
    r_chunk_confine_ = chunk_body_ + ChunkRank - 1;
    chunk_tail_ = chunk_head_ = (is_head) ? r_chunk_confine_ : l_chunk_confine_;
    // I hope that you remember the construction which one you used
  }
  ~Chunk() {
    if (chunk_size_ != 0) {
      // if one of elements of chunk is constructed
      for (uint64_t i = static_cast<uint64_t>(chunk_head_ - chunk_body_);
           i <= static_cast<uint64_t>(chunk_tail_ - chunk_body_); ++i) {
        Alloc_traits::destroy(all_tp_, chunk_body_ + i);
      }
    }
    if (chunk_body != nullptr) {
      Alloc_traits::deallocate(all_tp_, chunk_body_, ChunkRank);
    }
    chunk_body_ = chunk_head_ = chunk_tail_ = r_chunk_confine_ =
        l_chunk_confine_ = nullptr;
    chunk_size_ = 0;
  }
  template <typename AnotherAlloc>
  Chunk(const typename Deque<TempT, AnotherAlloc>::Chunk<>& chnk) {
    if (chnk.chunk_body_ != nullptr) {
      allocation_attempt_of_chunk(chunk_body_);
      copy_attempt_of_chunk(*this, chnk);
      chunk_size_ = chnk.chunk_size_;
      chunk_head_ = chunk_body_ + (chnk.chunk_head_ - chnk.chunk_body_);
      chunk_tail_ = chunk_body_ + (chnk.chunk_tail_ - chnk.chunk_body_);
      r_chunk_confine_ = (l_chunk_confine_ = chunk_body_) + ChunkRank - 1;
    }
  }
  Chunk(Chunk<>&& chnk) noexcept
      : chunk_body_(std::move(chnk.chunk_body_)),
        chunk_size_(std::move(chnk.chunk_size_)),
        chunk_head_(std::move(chnk.chunk_head_)),
        chunk_tail_(std::move(chnk.chunk_tail_)),
        l_chunk_confine_(std::move(chnk.l_chunk_confine_)),
        r_chunk_confine_(std::move(chnk.r_chunk_confine_)) {
    chnk.chunk_body_ = chnk.chunk_head_ = chnk.chunk_tail_ =
        chnk.r_chunk_confine_ = chnk.l_chunk_confine_ = nullptr;
    chnk.chunk_size_ = 0;
  }
  template <typename AnotherAlloc>
  Chunk<>& operator=(
      const typename Deque<TempT, AnotherAlloc>::Chunk<>& chnk) & {
    if (chunk_body_ != chnk.chunk_body_) {
      Chunk<> tmp_chunk;
      allocation_attempt_of_chunk(tmp_chunk.chunk_body_);
      copy_attempt_of_chunk(tmp_chunk, chnk);
      for (uint64_t i = static_cast<uint64_t>(chunk_head_ - chunk_head_);
           i <= static_cast<uint64_t>(chunk_tail_ - chunk_body_); ++i) {
        Alloc_traits::destroy(all_tp_, chunk_body_ + i);
      }
      Alloc_traits::deallocate(all_tp_, chunk_body_, ChunkRank);
      chunk_body_ = tmp_chunk.chunk_body_;
      coping_chunk_inside(chnk, *this);
    }
    return *this;
  }
  Chunk<>& operator=(Chunk<>&& chnk) & noexcept {
    if (chunk_body_ != chnk.chunk_body_) {
      ~Chunk();
      chunk_body_ = std::move(chnk.chunk_body_);
      chunk_size_ = std::move(chnk.chunk_size_);
      chunk_head_ = std::move(chnk.chunk_head_);
      chunk_tail_ = std::move(chnk.chunk_tail_);
      l_chunk_confine_ = std::move(chnk.l_chunk_confine_);
      r_chunk_confine_ = std::move(chnk.r_chunk_confine_);
      chnk.chunk_body_ = chnk.chunk_head_ = chnk.chunk_tail_ =
          chnk.r_chunk_confine_ = chnk.l_chunk_confine_ = nullptr;
      chnk.chunk_size_ = 0;
    }
    return *this;
  }

  //*******************************************
  //*****************Getters*******************
  uint64_t get_chunk_size() const noexcept {
    return chunk_size_;
  }  // <- how many cells are filled
  bool chunk_empty() const noexcept {
    return get_chunk_size() == 0;
  }
  bool chunk_full() const noexcept {
    return chunk_size_ == ChunkRank;
  }
  constexpr const uint64_t get_chunk_rank() const noexcept {
    return ChunkRank;
  }
  //*******************************************
  //*****************Setters*******************
  // void left_set_chunk(const value_type& value) noexcept(
  //     std::is_nothrow_constructible_v<TempT>) {
  //   construct_unit_attempt_of_chunk(chunk_head_, value, l_changing_delta_);
  // }
  // void right_set_chunk(const value_type& value) noexcept(
  //     std::is_nothrow_constructible_v<TempT>) {
  //   construct_unit_attempt_of_chunk(
  //       chunk_tail_, value,
  //       r_changing_delta_);  // подумать над move_if_noexxcept и как тут это
  //                            // заюзать
  // }
  // commented because have better versions with &&
  void left_set_chunk(value_type&& value) {
    construct_unit_attempt_of_chunk(chunk_head_, value, l_changing_delta_);
    // что там после перемещения останется неопределенное значени то мне без
    // разницы
  }
  void right_set_chunk(value_type&& value) {
    construct_unit_attempt_of_chunk(chunk_tail_, value, r_changing_delta_);
    // что там после перемещения останется неопределенное значени то мне без
    // разницы
  }
  //*******************************************
  //*****************Erasers*******************
  void left_pop_chunk() noexcept {
    Alloc_traits::destroy(all_tp_, chunk_head_);
    // if chunk was empty it will be UB
    --chunk_size_;
    if (chunk_size_ != 0) {
      chunk_head_ -= l_changing_delta_;
    }
  }
  void right_pop_chunk() noexcept {
    Alloc_traits::destroy(all_tp_, chunk_tail_);
    // if chunk was empty it will be UB
    --chunk_size_;
    if (chunk_size_ != 0) {
      chunk_tail_ -= r_changing_delta_;
    }
  }
  //*******************************************
};
//===========================================

//==========Deque Memory Controllere=========
template <typename TempT, typename Alloc>
struct Deque<TempT, Alloc>::MemCntAndBodyOfDeque : public Type_alloc_type,
                                                   public DequeBody {
  MemCntAndBodyOfDeque() noexcept(
      std::is_nothrow_default_constructible_v<Type_alloc_type>)
      : Type_alloc_type() {
  }
  MemCntAndBodyOfDeque(const Type_alloc_type& allc) noexcept
      : Type_alloc_type(allc) {
  }
  MemCntAndBodyOfDeque(Type_alloc_type&& allc) noexcept
      : Type_alloc_type(std::move(allc)) {
  }
  MemCntAndBodyOfDeque(MemCntAndBodyOfDeque&&) = default;
  MemCntAndBodyOfDeque(MemCntAndBodyOfDeque&& mcr, Type_alloc_type&& allc)
      : Type_alloc_type(std::move(allc)), DequeBody(std::move(mcr)) {
  }
};
template <typename TempT, typename Alloc>
typename Deque<TempT, Alloc>::Type_alloc_type&
Deque<TempT, Alloc>::get_unit_allocator() noexcept {
  return mc_body_;
}
template <typename TempT, typename Alloc>
const typename Deque<TempT, Alloc>::Type_alloc_type&
Deque<TempT, Alloc>::get_unit_allocator() const noexcept {
  return mc_body_;
}
template <typename TempT, typename Alloc>
typename Deque<TempT, Alloc>::Chunk_alloc_type
Deque<TempT, Alloc>::get_chunk_allocator() const noexcept {
  return Chunk_alloc_type(get_unit_allocator());
}
template <typename TempT, typename Alloc>
typename Deque<TempT, Alloc>::pointer Deque<TempT, Alloc>::chunk_allocation() {
  return Alloc_traits::allocate(mc_body_, set_chunk_rank());
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::chunk_dealocation(pointer ptr) noexcept {
  Alloc_traits::dealocate(mc_body_, ptr, set_chunk_rank());
}
template <typename TempT, typename Alloc>
typename Deque<TempT, Alloc>::Chunk_pointer
Deque<TempT, Alloc>::body_allocation(const uint64_t& size) {
  Chunk_alloc_type chunk_allocator = get_chunk_allocator();
  return Chunk_alloc_traits::allocate(chunk_allocator, size);
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::body_dealocation(Chunk_pointer ptr,
                                           const uint64_t& size) noexcept {
  Chunk_alloc_type chunk_allocator = get_chunk_allocator();
  Chunk_alloc_traits::dealocate(chunk_allocation, ptr, size);
  ptr = nullptr;
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::body_range_construction(Chunk_pointer head,
                                                  Chunk_pointer tail) {
  Chunk_pointer cur_ptr = nullptr;
  Chunk_alloc_type chunk_allocator = get_chunk_allocator();
  try {
    for (cur_ptr = head; cur_ptr <= tail; ++cur_ptr) {
      Chunk_alloc_traits::construct(chunk_allocator, cur_ptr, false);
    }
  } catch (...) {
    for (Chunk_pointer id_ptr = head; id_ptr < cur_ptr; ++id_ptr) {
      Chunk_alloc_traits::destroy(chunk_allocator, id_ptr);
    }
    throw;
  }
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::body_range_destruction(Chunk_pointer head,
                                                 Chunk_pointer tail) noexcept {
  Chunk_alloc_type chunk_allocator = get_chunk_allocator();
  for (Chunk_pointer cur_ptr = head; cur_ptr <= tail; ++cur_ptr) {
    Chunk_alloc_traits::destroy(chunk_allocator, cur_ptr);
  }
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::allocation_attempt_of_deque_body(
    Chunk_pointer& ptr, const uint64_t& size) {
  try {
    ptr = body_allocation(size);
  } catch (...) {
    throw;
    // did not allocate memory for body of deque but have not any meaning
  }
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::constrcution_attempt_of_deque_body(
    Chunk_pointer& ptr_head_chunk, Chunk_pointer& ptr_tail_chunk,
    Chunk_pointer& ptr_body, uint64_t& size) {
  try {
    body_range_construction(ptr_head_chunk, ptr_tail_chunk);
  } catch (...) {
    body_dealocation(ptr_body, size);
    ptr_body = nullptr;
    size = 0;
    throw;
    // did not allocate memory for chunks
  }
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::reserve_memory_in_deque(
    const uint64_t& num_of_units) {
  const uint64_t required_amount_of_chunks =
      num_of_units / set_chunk_rank() + 1;
  mc_body_.total_size = num_of_units;
  mc_body_.num_of_chunks = std::max(
      kDefaultDequeLenth, static_cast<uint64_t>(required_amount_of_chunks + 2));
  allocation_attempt_of_deque_body(mc_body_.body, mc_body_.num_of_chunks);
  // will try allocate memory for deque body
  Chunk_pointer ptr_head_chunk =
      (mc_body_.body +
       ((mc_body_.num_of_chunks - required_amount_of_chunks) / 2));
  Chunk_pointer ptr_tail_chunk =
      mc_body_.head_chunk + required_amount_of_chunks - 1;
  constrcution_attempt_of_deque_body(ptr_head_chunk, ptr_tail_chunk,
                                     mc_body_.body, mc_body_.num_of_chunks);
  // will try allocate memory for chunks in the deque
  mc_body_.head_chunk = ptr_head_chunk;
  mc_body_.tail_chunk = ptr_tail_chunk;
  // there seems to be no sin
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::DequeBody::stretch_right_end(const size_t& new_len) {
  Chunk_alloc_type chunk_allocator = get_chunk_allocator();
  Chunk_pointer new_body = nullptr;
  uint64_t new_num_of_chunks = num_of_chunks * 2;
  allocation_attempt_of_deque_body(new_body, new_num_of_chunks);
  constrcution_attempt_of_deque_body(new_body + num_of_chunks,
                                     new_body + 2 * num_of_chunks - 1, new_body,
                                     new_num_of_chunks);
  size_t idx = 0;
  try {
    for (idx = 0; idx < num_of_chunks; ++idx) {
      Chunk_alloc_traits::construct(chunk_allocator, new_body + idx,
                                    std::move_if_noexcept(body + idx));
    }
  } catch (...) {
    for (size_t i = 0; i < idx; ++i) {
      Chunk_alloc_traits::destroy(chunk_allocator, new_body + i);
    }
    body_range_destruction(new_body + num_of_chunks,
                           new_body + 2 * num_of_chunks - 1);
    body_deallocation(new_body, num_of_chunks);
    throw;
    // did not moved part from old body
  }
  num_of_chunks *= 2;
  head_chunk = new_body + (head_chunk - body);
  tail_chunk = new_body + (tail_chunk - body);
  body = std::move(new_body);
}
//===========================================
//======Functions for unit monipulations=====
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::priv_push_back(TempT&& elem) {
  if (mc_body_.tail_chunk - mc_body_.body + 1 == mc_body_.num_of_chunks) {
    if (mc_body_.tail_chunk->chunk_tail_ ==
        mc_body_.tail_chunk->r_chunk_confine_) {
      // it means that in this direction have not any capacity
    }
  }
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::priv_pop_back() noexcept {
  mc_body_.tail_chunk->right_pop_chunk();
  if (mc_body_.tail_chunk->chunk_empty()) {
    Chunk_alloc_type chunk_allocator = get_chunk_allocator();
    Chunk_pointer tmp_ptr = mc_body_.tail_chunk;
    --mc_body_.tail_chunk;
    Chunk_alloc_traits::destroy(chunk_allocator, tmp_ptr);
    tmp_ptr = nullptr;
  }
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::priv_pop_front() noexcept {
  mc_body_.head_chunk->left_pop_chunk();
  if (mc_body_.head_chunk->chunk_empty()) {
    Chunk_alloc_type chunk_allocator = get_chunk_allocator();
    Chunk_pointer tmp_ptr = mc_body_.head_chunk;
    --mc_body_.head_chunk;
    Chunk_alloc_traits::destroy(chunk_allocator, tmp_ptr);
    tmp_ptr = nullptr;
  }
}
//===========================================

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//               DECLARATION
// инсерт и ерейс я буду делать через пуш и фронт полсе в нужное место через
// последовательные свапы перенесу

//==============Private Functions============

//===========================================
//================Constructors===============
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::Deque() : mc_body_() {
  reserve_memory_in_deque(0);
}

template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::Deque(const Alloc& alloc) : mc_body_(alloc) {
  reserve_memory_in_deque(0);
}

template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::Deque(const size_t& count, const Alloc& alloc)
    : mc_body_(alloc) {
  reserve_memory_in_deque(count);
}

template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::~Deque() noexcept {
  body_range_destruction(mc_body_.head_chunk, mc_body_.tail_chunk);
  body_dealocation();
}
//===========================================
//==========Accessing a element==============
template <typename TempT, typename Alloc>
TempT& Deque<TempT, Alloc>::operator[](const size_t& index) noexcept {
  size_t new_index = index;
  if (mc_body_.head_chunk->chunk_size_ > index) {
    return *(mc_body_.head_chunk->chunk_head_ + index);
  }
  new_index -= mc_body_.head_chunk->chunk_size_;
  const size_t index_of_chunk = new_index / set_chunk_rank() + 1;
  const size_t index_of_unit = new_index % set_chunk_rank();
  return *((mc_body_.head_chunk + index_of_chunk)->chunk_haed_ + index_of_unit);
}
template <typename TempT, typename Alloc>
const TempT& Deque<TempT, Alloc>::operator[](
    const size_t& index) const noexcept {
  size_t new_index = index;
  if (mc_body_.head_chunk->chunk_size_ > index) {
    return *(mc_body_.head_chunk->chunk_head_ + index);
  }
  new_index -= mc_body_.head_chunk->chunk_size_;
  const size_t index_of_chunk = new_index / set_chunk_rank() + 1;
  const size_t index_of_unit = new_index % set_chunk_rank();
  return *((mc_body_.head_chunk + index_of_chunk)->chunk_haed_ + index_of_unit);
}
template <typename TempT, typename Alloc>
TempT& Deque<TempT, Alloc>::at(const size_t& index) {
  if (index >= size()) {
    throw std::out_of_range("you want to access a non-existent element");
  }
  return *this[index];
}
template <typename TempT, typename Alloc>
const TempT& Deque<TempT, Alloc>::at(const size_t& index) const {
  if (index >= size()) {
    throw std::out_of_range("you want to access a non-existent element");
  }
  return *this[index];
}
template <typename TempT, typename Alloc>
TempT& Deque<TempT, Alloc>::front() noexcept {
  return *this[0];
}
template <typename TempT, typename Alloc>
const TempT& Deque<TempT, Alloc>::front() const noexcept {
  return *this[0];
}
template <typename TempT, typename Alloc>
TempT& Deque<TempT, Alloc>::back() noexcept {
  return *this[size() - 1];
}
template <typename TempT, typename Alloc>
const TempT& Deque<TempT, Alloc>::back() const noexcept {
  return *this[size() - 1];
}
//===========================================
//==============SizeInformation==============
template <typename TempT, typename Alloc>
size_t Deque<TempT, Alloc>::size() const noexcept {
  return static_cast<size_t>(end() - begin());
}
template <typename TempT, typename Alloc>
bool Deque<TempT, Alloc>::empty() const noexcept {
  return size() == 0;
}
//===========================================
//===========Modification methods============
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::pop_back() noexcept {
  priv_pop_back();
}
template <typename TempT, typename Alloc>
void Deque<TempT, Alloc>::pop_front() noexcept {
  priv_pop_front();
}
//===========================================
//=============Iterator methods==============
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::iterator Deque<TempT, Alloc>::begin() noexcept {
  return Deque<TempT, Alloc>::iterator(mc_body_.head_chunk->chunk_head,
                                       mc_body_.head_chunk);
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::const_iterator Deque<TempT, Alloc>::begin()
    const noexcept {
  return Deque<TempT, Alloc>::const_iterator(mc_body_.head_chunk->chunk_head,
                                             mc_body_.head_chunk);
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::const_iterator Deque<TempT, Alloc>::cbegin()
    const noexcept {
  return Deque<TempT, Alloc>::const_iterator(mc_body_.head_chunk->chunk_head,
                                             mc_body_.head_chunk);
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::iterator Deque<TempT, Alloc>::end() noexcept {
  return Deque<TempT, Alloc>::iterator(mc_body_.tail_chunk->chunk_tail,
                                       mc_body_.tail_chunk) +
         1;
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::const_iterator Deque<TempT, Alloc>::end() const noexcept {
  return Deque<TempT, Alloc>::const_iterator(mc_body_.tail_chunk->chunk_tail,
                                             mc_body_.tail_chunk) +
         1;
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::const_iterator Deque<TempT, Alloc>::cend() const noexcept {
  return Deque<TempT, Alloc>::const_iterator(mc_body_.tail_chunk->chunk_tail,
                                             mc_body_.tail_chunk) +
         1;
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::reverse_iterator Deque<TempT, Alloc>::rbegin() noexcept {
  return reverse_iterator(end() - 1);
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::const_reverse_iterator Deque<TempT, Alloc>::rbegin()
    const noexcept {
  return const_reverse_iterator(end() - 1);
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::const_reverse_iterator Deque<TempT, Alloc>::crbegin()
    const noexcept {
  return const_reverse_iterator(end() - 1);
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::reverse_iterator Deque<TempT, Alloc>::rend() noexcept {
  return reverse_iterator(begin() - 1);
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::const_reverse_iterator Deque<TempT, Alloc>::rend()
    const noexcept {
  return const_reverse_iterator(begin() - 1);
}
template <typename TempT, typename Alloc>
Deque<TempT, Alloc>::const_reverse_iterator Deque<TempT, Alloc>::crend()
    const noexcept {
  return const_reverse_iterator(begin() - 1);
}
//===========================================

// добавить функцию для увелечения памяти под чанки при переполнения
// аллоцированной части
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^