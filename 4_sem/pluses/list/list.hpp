#pragma once

#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

template <typename TempT, typename Alloc = std::allocator<TempT>>
class List {
 public:
  //=================Usings=================
  using value_type = TempT;
  using allocator_type = Alloc;
  using pointer = TempT*;
  using const_pointer = const TempT*;
  using reference = TempT&;
  using const_reference = const TempT&;
  using difference_type = ptrdiff_t;
  //========================================
  //===============Iterator=================
  template <bool IsConst>
  class common_iterator;
  //========================================

 private:
  //=================Node===================
  struct Node;
  //========================================
  //===============ListBody=================
  struct ListBody;
  //========================================
  //==============List Fields===============
  ListBody list_body_;
  //========================================
  //============Private usings==============
  using type_alloc_type = typename std::allocator_traits<
      allocator_type>::template rebind_alloc<value_type>;
  using type_alloc_traits = std::allocator_traits<type_alloc_type>;
  using node_alloc_type =
      typename type_alloc_traits::template rebind_alloc<Node>;
  using node_alloc_traits = std::allocator_traits<node_alloc_type>;
  //========================================

 public:
  //=================Usings=================
  using iterator = common_iterator<false>;
  using const_iterator = common_iterator<true>;
  using reverse_iterator = std::reverse_iterator<common_iterator<false>>;
  using const_reverse_iterator = std::reverse_iterator<common_iterator<true>>;
  //========================================
  //=============Alloc Getters==============
  Alloc get_allocator() noexcept;
  Alloc get_allocator() const noexcept;
  //========================================
  //==============Constructors==============
  List();
  List(const size_t& count, const TempT& value, const Alloc& alloc = Alloc());
  explicit List(const size_t& count, const Alloc& alloc = Alloc());
  List(const List& other);
  List(List&& other);
  List(std::initializer_list<TempT> init, const Alloc& alloc = Alloc());
  ~List();
  List<TempT, Alloc>& operator=(const List<TempT, Alloc>& other) &;
  List<TempT, Alloc>& operator=(List<TempT, Alloc>&& other) & noexcept;
  //========================================
  //========Element access methods==========
  TempT& front() noexcept;
  const TempT& front() const noexcept;
  TempT& back() noexcept;
  const TempT& back() const noexcept;
  //========================================
  //================Capacity================
  size_t size() const noexcept;
  bool empty() const noexcept;
  //========================================
  //================Modifiers===============
  void pop_front() noexcept;
  void pop_back() noexcept;
  void push_back(const TempT& value);
  void push_back(TempT&& value);
  void push_front(const TempT& value);
  void push_front(TempT&& value);
  //========================================
  //===========Iterator Methods=============
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
  //========================================
  friend struct Node;
  friend struct ListBody;
};

//=================Node=====================
template <typename TempT, typename Alloc>
struct List<TempT, Alloc>::Node {
  //************Private Getters*************
  const Node* get_next_neighbour() const noexcept { return next_node_; }
  const Node* get_prev_neighbour() const noexcept { return prev_node_; }
  const TempT& get_body() const noexcept { return *node_body_; }
  Node* get_next_neighbour() noexcept { return next_node_; }
  Node* get_prev_neighbour() noexcept { return prev_node_; }
  TempT& get_body() noexcept { return *node_body_; }
  //****************************************
 private:
  //**********Allocator functions***********
  const type_alloc_type& node_get_allocator() const noexcept {
    return type_alloc_;
  }
  type_alloc_type& node_get_allocator() noexcept { return type_alloc_; }
  //****************************************
  //********Private Memory Functions********
  void node_construct_attempt(const TempT& value) {
    try {
      type_alloc_traits::construct(node_get_allocator(), node_body_, value);
    } catch (...) {
      type_alloc_traits::deallocate(node_get_allocator(), node_body_, 1);
      throw;
    }
  }
  void node_construct_attempt(TempT&& value) {
    try {
      type_alloc_traits::construct(node_get_allocator(), node_body_,
                                   std::move_if_noexcept(value));
    } catch (...) {
      type_alloc_traits::deallocate(node_get_allocator(), node_body_, 1);
      throw;
    }
  }
  template <typename... Args>
  void node_construct_attempt(Args&&... args) {
    try {
      type_alloc_traits::construct(node_get_allocator(), node_body_,
                                   std::forward<Args>(args)...);
    } catch (...) {
      type_alloc_traits::deallocate(node_get_allocator(), node_body_, 1);
      throw;
    }
  }

  void node_suicide() noexcept {
    if (node_body_ == nullptr) {
      return;
    }
    type_alloc_traits::destroy(node_get_allocator(), node_body_);
    type_alloc_traits::deallocate(node_get_allocator(), node_body_, 1);
  }
  void node_copy_neighbours(const Node& other) noexcept {
    next_node_ = other.get_next_neighbour();
    prev_node_ = other.get_prev_neighbour();
  }
  void node_copy_neighbours(Node&& other) noexcept {
    next_node_ = other.get_next_neighbour();
    prev_node_ = other.get_prev_neighbour();
  }
  //****************************************
 public:
  //**************Constructors**************
  /// TODO: change by using allocator in constructor arguments
  Node() = default;
  Node(const allocator_type& alr, const TempT& value)
      : type_alloc_(type_alloc_type(alr)),
        node_body_(type_alloc_traits::allocate(node_get_allocator(), 1)) {
    // if throws exception in allocation it will throwen further
    node_construct_attempt(value);
  }
  Node(const TempT& value)
      : type_alloc_(type_alloc_type(allocator_type())),
        node_body_(type_alloc_traits::allocate(node_get_allocator(), 1)) {
    // if throws exception in allocation it will throwen further
    node_construct_attempt(value);
  }
  Node(const allocator_type& alr, TempT&& value)
      : type_alloc_(type_alloc_type(alr)),
        node_body_(type_alloc_traits::allocate(node_get_allocator(), 1)) {
    // if throws exception in allocation it will throwen further
    node_construct_attempt(std::move_if_noexcept(value));
  }
  Node(TempT&& value)
      : type_alloc_(type_alloc_type(allocator_type())),
        node_body_(type_alloc_traits::allocate(node_get_allocator(), 1)) {
    // if throws exception in allocation it will throwen further
    node_construct_attempt(std::move_if_noexcept(value));
  }
  template <typename... Args>
  Node(const allocator_type& alr, Args&&... args)
      : type_alloc_(type_alloc_type(alr)),
        node_body_(type_alloc_traits::allocate(node_get_allocator(), 1)) {
    // if throws exception in allocation it will throwen further
    node_construct_attempt(std::forward<Args>(args)...);
  }
  ~Node() { node_suicide(); }
  Node(const Node& other)
      : type_alloc_(other.node_get_allocator()),
        node_body_(type_alloc_traits::allocate(node_get_allocator(), 1)) {
    node_construct_attempt(other.get_body());
    node_copy_neighbours(other);
  }
  Node(Node&& other)
      : type_alloc_(other.node_get_allocator()),
        node_body_(type_alloc_traits::allocate(node_get_allocator(), 1)) {
    node_construct_attempt(std::move(other.get_body()));
    node_copy_neighbours(other);
  }
  Node& operator=(Node&& other) & noexcept {
    if (*this == other) {
      node_suicide();
      type_alloc_ = std::move(other.node_get_allocator());
      node_body_ = &other.get_body();
      node_copy_neighbours(std::move(other));
      other.next_node_ = other.prev_node_ = other.node_body_ = nullptr;
    }
    return *this;
  }
  Node& operator=(const Node& other) & {
    if (other != *this) {
      type_alloc_ = other.node_get_allocator();
      *node_body_ = other.get_body();
      node_copy_neighbours(other);
    }
    return *this;
  }
  //****************************************
  //**************Comparation***************
  friend bool operator==(const Node& left, const Node& right) noexcept {
    return left.get_body() == right.get_body();
  }
  friend bool operator!=(const Node& left, const Node& right) noexcept {
    return left.get_body() != right.get_body();
  }
  //****************************************
  //****************Setters*****************
  void node_set_next_neighbour(Node* node) noexcept {
    if (node->get_prev_neighbour() != nullptr) {
      if (node->prev_node_->next_node_ != nullptr) {
        node->prev_node_->next_node_ = nullptr;
        // untie the old next node from previous node of the node
      }
      // думаю тут второй иф не нужен (который вложенный)
    }
    if (get_next_neighbour() != nullptr) {
      if (next_node_->prev_node_ != nullptr) {
        next_node_->prev_node_ = nullptr;
        // untie the old previous node from next node of this
      }
      // думаю тут второй иф не нужен (который вложенный)
    }
    next_node_ = node;
    node->prev_node_ = &(*this);
  }
  void node_set_prev_neighbour(Node* node) noexcept {
    if (node->get_next_neighbour() != nullptr) {
      if (node->next_node_->prev_node_ != nullptr) {
        node->next_node_->prev_node_ = nullptr;
        // untie the old previous node from next node of the node
      }
      // думаю тут второй иф не нужен (который вложенный)
    }
    if (get_prev_neighbour() != nullptr) {
      if (prev_node_->next_node_ != nullptr) {
        prev_node_->next_node_ = nullptr;
        // untie the old next node from previous node of this
      }
      // думаю тут второй иф не нужен (который вложенный)
    }
    prev_node_ = node;
    node->next_node_ = &(*this);
  }
  //****************************************
 private:
  Node* prev_node_ = nullptr;
  Node* next_node_ = nullptr;
  pointer node_body_ = nullptr;
  allocator_type type_alloc_;
  friend struct List<TempT, Alloc>::ListBody;
};
//==========================================

//================Iterator==================
template <typename TempT, typename Alloc>
template <bool IsConst>
class List<TempT, Alloc>::common_iterator : public std::iterator<std::bidirectional_iterator_tag, std::conditional_t<IsConst, const TempT, TempT>> {
  //***************Fields*******************
  /// TODO: тут надо отдельно в поле хранить conditioanal_ptr
  Node* cur_node_;
  //****************************************
  //**************Private usings****************
  using conditional_ptr = std::conditional_t<IsConst, const TempT*, TempT*>;
  using conditional_ref = std::conditional_t<IsConst, const TempT&, TempT&>;
  //********************************************
 public:
  //***************Usings*******************
  // using difference_type = ptrdiff_t;
  // using value_type = TempT;
  // using reference = TempT&;
  // using pointer = TempT*;
  // using iterator_category = std::bidirectional_iterator_tag;
  //****************************************
  //************Constructors****************
  common_iterator() noexcept : cur_node_() {}
  explicit common_iterator(const Node* other_node) noexcept
      : cur_node_(const_cast<Node*>(other_node)) {}
  template <bool IsConstTmp>
  common_iterator(const common_iterator<IsConstTmp>& other) noexcept
      : cur_node_(other.cur_node_) {}
  template <bool IsConstTmp>
  common_iterator<IsConst>& operator=(
      const common_iterator<IsConstTmp>& other) {
    cur_node_ = other.cur_node_;
    return *this;
  }
  //****************************************
  //*********Memory Access Operators********
  conditional_ptr operator->() const noexcept { return &cur_node_->get_body(); }
  conditional_ptr operator->() noexcept { return &cur_node_->get_body(); }
  conditional_ref operator*() const noexcept { return cur_node_->get_body(); }
  conditional_ref operator*() noexcept { return cur_node_->get_body(); }
  //****************************************
  //***********Arithmetic Operators*********
  common_iterator<IsConst>& operator++() noexcept {
    cur_node_ = cur_node_->get_next_neighbour();
    return *this;
  }
  common_iterator<IsConst>& operator--() noexcept {
    cur_node_ = cur_node_->get_prev_neighbour();
    return *this;
  }
  common_iterator<IsConst> operator++(int) noexcept {
    common_iterator<IsConst> tmp = *this;
    tmp.cur_node_ = tmp.cur_node_->get_next_neighbour();
    return *this;
  }
  common_iterator<IsConst> operator--(int) noexcept {
    common_iterator<IsConst> tmp = *this;
    tmp.cur_node_ = tmp.cur_node_->get_prev_neighbour();
    return *this;
  }
  //****************************************
  //*********Comparation Operators**********
  template <bool IsConstTmp>
  friend bool operator==(const common_iterator<IsConst>& left,
                         const common_iterator<IsConstTmp>& right) noexcept {
    return left.cur_node_ == right.cur_node_;
  }
  template <bool IsConstTmp>
  friend bool operator!=(const common_iterator<IsConst>& left,
                         const common_iterator<IsConstTmp>& right) noexcept {
    return left.cur_node_ != right.cur_node_;
  }
  //****************************************
  friend struct List<TempT, Alloc>::ListBody;
};
//==========================================

//================ListBody==================
template <typename TempT, typename Alloc>
struct List<TempT, Alloc>::ListBody {
 private:
  //************Private usings**************
  using type_alloc_type = typename std::allocator_traits<
      allocator_type>::template rebind_alloc<value_type>;
  using type_alloc_traits = std::allocator_traits<type_alloc_type>;
  using node_alloc_type =
      typename type_alloc_traits::template rebind_alloc<Node>;
  using node_alloc_traits = std::allocator_traits<node_alloc_type>;
  using iterator = common_iterator<false>;
  using const_iterator = common_iterator<true>;
  using reverse_iterator = std::reverse_iterator<common_iterator<false>>;
  using const_reverse_iterator = std::reverse_iterator<common_iterator<true>>;
  //****************************************
 public:
  //*********Allocator functions************
  node_alloc_type& lb_get_node_allocator() noexcept { return node_alloc_; }
  const node_alloc_type& lb_get_node_allocator() const noexcept {
    return node_alloc_;
  }
  //****************************************
  //***********Member function**************
  typename List<TempT, Alloc>::Node* lb_get_head_node() noexcept {
    return im_node_->get_next_neighbour();
  }
  const typename List<TempT, Alloc>::Node* lb_get_head_node() const noexcept {
    return im_node_->get_next_neighbour();
  }
  typename List<TempT, Alloc>::Node* lb_get_tail_node() noexcept {
    return im_node_->get_prev_neighbour();
  }
  const typename List<TempT, Alloc>::Node* lb_get_tail_node() const noexcept {
    return im_node_->get_prev_neighbour();
  }
  typename List<TempT, Alloc>::Node* lb_get_imag_node() noexcept {
    return im_node_;
  }
  const typename List<TempT, Alloc>::Node* lb_get_imag_node() const noexcept {
    return im_node_;
  }
  //****************************************
 private:
  //*****************Fields*****************
  node_alloc_type node_alloc_;
  size_t size_ = 0;
  Node* im_node_ = nullptr;  // imageinary node
  //****************************************
  //**********Allocator functions***********
  typename List<TempT, Alloc>::Node* lb_node_allocate() {
    return node_alloc_traits::allocate(node_alloc_, 1);
    // if it throw exception it will throw further
  }
  void lb_node_deallocate(
      typename List<TempT, Alloc>::Node* node_ptr) noexcept {
    node_alloc_traits::deallocate(node_alloc_, node_ptr, 1);
  }
  //****************************************
  //************Node functoins**************
  template <typename... Args>
  typename List<TempT, Alloc>::Node* lb_create_node(Args&&... args) {
    Node* ptr = lb_node_allocate();
    node_alloc_type all_node = lb_get_node_allocator();
    try {
      node_alloc_traits::construct(all_node, ptr, all_node,
                                   std::forward<Args>(args)...);
    } catch (...) {
      lb_node_deallocate(ptr);
      throw;
    }
    return ptr;
  }
  void lb_creat_imaginary_node() {
    im_node_ = lb_node_allocate();
    im_node_->next_node_ = im_node_;
    im_node_->prev_node_ = im_node_;
  }  // function to creat imaginary node
  void lb_destroy_imaginary_node() noexcept {
    if (im_node_ == nullptr) {
      return;
    }
    // node_alloc_traits::destroy(lb_get_node_allocator(), im_node_);
    node_alloc_traits::deallocate(lb_get_node_allocator(), im_node_, 1);
  }
  template <typename... Args>
  void lb_insert_right(iterator pos, Args&&... args) {
    Node* tmp_node = lb_create_node(std::forward<Args>(args)...);
    // if throws exception in construction it will throwen further
    Node* pos_cur_node = pos.cur_node_;
    Node* pos_prev_node = pos.cur_node_->get_prev_neighbour();
    if (pos_prev_node != nullptr) {
      pos_prev_node->node_set_next_neighbour(tmp_node);
    }
    pos_cur_node->node_set_prev_neighbour(tmp_node);
    ++size_;
  }  // this is usual insert
  template <typename... Args>
  void lb_insert_left(iterator pos, Args&&... args) {
    Node* tmp_node = lb_create_node(std::forward<Args>(args)...);
    // if throws exception in construction it will throwen further
    Node* pos_cur_node = pos.cur_node_;
    Node* pos_next_node = pos.cur_node_->get_next_neighbour();
    if (pos_next_node != nullptr) {
      pos_next_node->node_set_prev_neighbour(tmp_node);
    }
    pos_cur_node->node_set_next_neighbour(tmp_node);
    ++size_;
  }
  void lb_erase(iterator pos) noexcept {
    --size_;
    Node* pos_prev_node = pos.cur_node_->get_prev_neighbour();
    Node* pos_next_node = pos.cur_node_->get_next_neighbour();
    Node* pos_cur_node = pos.cur_node_;
    pos_prev_node->node_set_next_neighbour(pos_next_node);
    pos_next_node->node_set_prev_neighbour(pos_prev_node);
    if (pos_cur_node != nullptr) {
      node_alloc_traits::destroy(lb_get_node_allocator(), pos_cur_node);
      lb_node_deallocate(pos_cur_node);
    }
  }
  //****************************************
  //*************Range Functions************
  void lb_range_poper(const size_t& idx) noexcept {
    for (size_t i = 0; i < idx; ++i) {
      lb_pop_back();
    }
  }
  // if have been throwen exception it clean all and throw furthen
  // the exception
  void lb_range_defaultly_init(const size_t& len) {
    size_t idx = 0;
    try {
      for (; idx < len; ++idx) {
        lb_emplace_back();
      }
    } catch (...) {
      lb_range_poper(idx);
      throw;
    }
  }  // construct list with default value
  void lb_range_fill_init(const size_t& len, const TempT& value) {
    size_t idx = 0;
    try {
      for (; idx < len; ++idx) {
        lb_push_back(value);
      }
    } catch (...) {
      lb_range_poper(idx);
      throw;
    }
  }  // len times push_back into list
  template <typename Iter>
  void lb_range_copy_init(Iter start, Iter finish) {
    size_t idx = 0;
    try {
      for (; start != finish; ++start) {
        lb_emplace_back(*start);
        ++idx;
      }
    } catch (...) {
      lb_range_poper(idx);
      throw;
    }
  }  // to init list by two iterators
  void lb_pocca_true_s(const ListBody& other) {
    // pocca -> propagate_on_container_copy_assignment
    ListBody tmp_list(other);
    // if throw exception it will be catched outer
    lb_clear();
    lb_destroy_imaginary_node();
    // destroy *this fields
    im_node_ = std::move(tmp_list.lb_get_imag_node());
    node_alloc_ = std::move(tmp_list.lb_get_node_allocator());
    size_ = tmp_list.lb_size();
    // move new fields into *this
    tmp_list.size_ = 0;
    tmp_list.im_node_ = nullptr;
    // push default value into tmp
  }  // used into operator=
  void lb_pocca_false_s(const ListBody& other) {
    // pocca -> propagate_on_container_copy_assignment
    ListBody tmp_list;
    iterator iter(other.lb_get_head_node());
    iterator fin_iter(other.lb_get_tail_node()->get_next_neighbour());
    try {
      for (; iter != fin_iter; ++iter) {
        tmp_list.lb_push_back(*iter);
      }
    } catch (...) {
      tmp_list.lb_clear();
      // tmp_list.lb_destroy_imaginary_node();
      throw;
    }
    // create tmp list
    lb_clear();
    lb_destroy_imaginary_node();
    // destroy old nodes
    im_node_ = std::move(tmp_list.lb_get_imag_node());
    node_alloc_ = std::move(tmp_list.lb_get_node_allocator());
    size_ = tmp_list.lb_size();
    // move new fields into *this
    tmp_list.size_ = 0;
    tmp_list.im_node_ = nullptr;
    // push default value into tmp
  }
  //****************************************
 public:
  //**************Constructors**************
  ListBody() : node_alloc_(node_alloc_type(allocator_type())) {}
  ListBody(const allocator_type& alr) : node_alloc_(node_alloc_type(alr)) {}
  ListBody(const size_t& len, const allocator_type& alr = allocator_type())
      : node_alloc_(node_alloc_type(alr)) {
    lb_creat_imaginary_node();
    lb_range_defaultly_init(len);
  }
  ListBody(const size_t& len, const value_type& value,
           const allocator_type& alr = allocator_type())
      : node_alloc_(node_alloc_type(alr)) {
    lb_creat_imaginary_node();
    lb_range_fill_init(len, value);
  }
  // ListBody(ListBody&& other) = default; make normal
  ListBody(const ListBody& other)
      : node_alloc_(node_alloc_traits::select_on_container_copy_construction(
            other.lb_get_node_allocator())) {
    lb_creat_imaginary_node();
    lb_range_copy_init(
        iterator(other.lb_get_head_node()),
        iterator(other.lb_get_tail_node()->get_next_neighbour()));
  }
  ListBody(const ListBody& other, const allocator_type& alr)
      : node_alloc_(node_alloc_type(alr)) {
    lb_creat_imaginary_node();
    lb_range_copy_init(
        iterator(other.lb_get_head_node()),
        iterator(other.lb_get_tail_node()->get_next_neighbour()));
  }
  ListBody(std::initializer_list<TempT> init_l,
           const allocator_type& alr = allocator_type())
      : node_alloc_(node_alloc_type(alr)) {
    lb_creat_imaginary_node();
    lb_range_copy_init(init_l.begin(), init_l.end());
  }
  ~ListBody() {
    lb_clear();
    lb_destroy_imaginary_node();
  }
  ListBody& operator=(const ListBody& other) & {
    const bool kRes =
        node_alloc_traits::propagate_on_container_copy_assignment::value;
    if (kRes) {
      lb_pocca_true_s(other);
    } else {
      lb_pocca_false_s(other);
    }
    return *this;
  }
  ListBody& operator=(ListBody&& other) & noexcept {
    if (lb_get_imag_node() != nullptr) {
      lb_clear();
      lb_destroy_imaginary_node();
      // suicide
    }
    im_node_ = std::move(other.lb_get_imag_node());
    size_ = other.lb_size();
    node_alloc_ = std::move(other.lb_get_node_allocator());
    // move all fields
    other.size_ = 0;
    im_node_ = nullptr;
    // push default value into other
    return *this;
  }

  //****************************************
  //***************Comparation**************
  friend bool operator==(const ListBody& left, const ListBody& right) {
    if (left.lb_size() != right.lb_size()) {
      return false;
    }
    const_iterator it1(left.lb_get_head_node());
    const_iterator it2(right.lb_get_head_node());
    const_iterator fin1(left.lb_get_tail_node()->get_next_neighbour());
    const_iterator fin2(right.lb_get_tail_node()->get_next_neighbour());
    while (it1 != fin1 && it2 != fin2 && *it1 == *it2) {
      ++it1;
      ++it2;
    }
    return it1 == fin1 && it2 == fin2;
  }
  friend bool operator!=(const ListBody& left, const ListBody& right) {
    return !(left == right);
  }
  //****************************************
  //*****************Capacity***************
  size_t lb_size() const noexcept { return size_; }
  bool lb_empty() const noexcept { return size_ == 0; }
  //****************Modifiers***************
  void lb_push_back(const TempT& value) {
    if (lb_get_imag_node() == nullptr) {
      lb_creat_imaginary_node();
    }
    lb_insert_right(iterator(lb_get_imag_node()), value);
  }
  void lb_push_back(TempT&& value) {
    if (lb_get_imag_node() == nullptr) {
      lb_creat_imaginary_node();
    }
    lb_insert_right(iterator(lb_get_imag_node()), std::move_if_noexcept(value));
  }
  template <typename... Args>
  void lb_emplace_back(Args&&... args) {
    if (lb_get_imag_node() == nullptr) {
      lb_creat_imaginary_node();
    }
    lb_insert_right(iterator(lb_get_imag_node()), std::forward<Args>(args)...);
  }
  void lb_push_front(const TempT& value) {
    if (lb_get_imag_node() == nullptr) {
      lb_creat_imaginary_node();
    }
    lb_insert_left(iterator(lb_get_imag_node()), value);
  }
  void lb_push_front(TempT&& value) {
    if (lb_get_imag_node() == nullptr) {
      lb_creat_imaginary_node();
    }
    lb_insert_left(iterator(lb_get_imag_node()), std::move_if_noexcept(value));
  }
  template <typename... Args>
  void lb_emplace_front(Args&&... args) {
    if (lb_get_imag_node() == nullptr) {
      lb_creat_imaginary_node();
    }
    lb_insert_left(iterator(lb_get_imag_node()), std::forward<Args>(args)...);
  }
  void lb_pop_back() noexcept { lb_erase(iterator(lb_get_tail_node())); }
  void lb_pop_front() noexcept { lb_erase(iterator(lb_get_head_node())); }
  void lb_clear() noexcept {
    while (!lb_empty()) {
      lb_pop_back();
    }
  }
  //****************************************
};
//==========================================

//^^^^^^^^^^^^^^^^^^List^^^^^^^^^^^^^^^^^^^^
//===============Constructors===============
template <typename TempT, typename Alloc>
List<TempT, Alloc>::List() : list_body_() {}

template <typename TempT, typename Alloc>
List<TempT, Alloc>::List(const size_t& count, const TempT& value,
                         const Alloc& alloc)
    : list_body_(count, value, alloc) {}

template <typename TempT, typename Alloc>
List<TempT, Alloc>::List(const size_t& count, const Alloc& alloc)
    : list_body_(count, alloc) {}

template <typename TempT, typename Alloc>
List<TempT, Alloc>::List(const List& other) : list_body_(other.list_body_) {}

template <typename TempT, typename Alloc>
List<TempT, Alloc>::List(std::initializer_list<TempT> init, const Alloc& alloc)
    : list_body_(init, alloc) {}

template <typename TempT, typename Alloc>
List<TempT, Alloc>::~List() = default;

template <typename TempT, typename Alloc>
List<TempT, Alloc>& List<TempT, Alloc>::operator=(
    const List<TempT, Alloc>& other) & {
  list_body_ = other.list_body_;
  return *this;
}
//==========================================
//=================Capacity=================
template <typename TempT, typename Alloc>
size_t List<TempT, Alloc>::size() const noexcept {
  return list_body_.lb_size();
}
template <typename TempT, typename Alloc>
bool List<TempT, Alloc>::empty() const noexcept {
  return list_body_.lb_empty();
}
//==========================================
//=================Modifiers================
template <typename TempT, typename Alloc>
void List<TempT, Alloc>::pop_back() noexcept {
  list_body_.lb_pop_back();
}
template <typename TempT, typename Alloc>
void List<TempT, Alloc>::pop_front() noexcept {
  list_body_.lb_pop_front();
}
template <typename TempT, typename Alloc>
void List<TempT, Alloc>::push_back(const TempT& value) {
  list_body_.lb_push_back(value);
}
template <typename TempT, typename Alloc>
void List<TempT, Alloc>::push_back(TempT&& value) {
  list_body_.lb_push_back(std::move_if_noexcept(value));
}
template <typename TempT, typename Alloc>
void List<TempT, Alloc>::push_front(const TempT& value) {
  list_body_.lb_push_front(value);
}
template <typename TempT, typename Alloc>
void List<TempT, Alloc>::push_front(TempT&& value) {
  list_body_.lb_push_front(std::move_if_noexcept(value));
}
//==========================================
//=============Iterator Methods=============
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::iterator List<TempT, Alloc>::begin() noexcept {
  return typename List<TempT, Alloc>::iterator(list_body_.lb_get_head_node());
}
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::const_iterator List<TempT, Alloc>::begin()
    const noexcept {
  return typename List<TempT, Alloc>::const_iterator(
      list_body_.lb_get_head_node());
}
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::const_iterator List<TempT, Alloc>::cbegin()
    const noexcept {
  return typename List<TempT, Alloc>::const_iterator(
      list_body_.lb_get_head_node());
}
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::iterator List<TempT, Alloc>::end() noexcept {
  return typename List<TempT, Alloc>::iterator(
      list_body_.lb_get_tail_node()->get_next_neighbour());
}
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::const_iterator List<TempT, Alloc>::end()
    const noexcept {
  return typename List<TempT, Alloc>::const_iterator(
      list_body_.lb_get_tail_node()->get_next_neighbour());
}
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::const_iterator List<TempT, Alloc>::cend()
    const noexcept {
  return typename List<TempT, Alloc>::const_iterator(
      list_body_.lb_get_tail_node()->get_next_neighbour());
}

template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::reverse_iterator
List<TempT, Alloc>::rbegin() noexcept {
  return typename List<TempT, Alloc>::reverse_iterator(end());
}
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::const_reverse_iterator List<TempT, Alloc>::rbegin()
    const noexcept {
  return typename List<TempT, Alloc>::const_reverse_iterator(end());
}
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::const_reverse_iterator
List<TempT, Alloc>::crbegin() const noexcept {
  return typename List<TempT, Alloc>::const_reverse_iterator(end());
}
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::reverse_iterator
List<TempT, Alloc>::rend() noexcept {
  return typename List<TempT, Alloc>::reverse_iterator(begin());
}
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::const_reverse_iterator List<TempT, Alloc>::rend()
    const noexcept {
  return typename List<TempT, Alloc>::const_reverse_iterator(begin());
}
template <typename TempT, typename Alloc>
typename List<TempT, Alloc>::const_reverse_iterator List<TempT, Alloc>::crend()
    const noexcept {
  return typename List<TempT, Alloc>::const_reverse_iterator(begin());
}
//==========================================
//=============Alloc Getters================
template <typename TempT, typename Alloc>
Alloc List<TempT, Alloc>::get_allocator() noexcept {
  return (Alloc)(list_body_.lb_get_node_allocator());
}
template <typename TempT, typename Alloc>
Alloc List<TempT, Alloc>::get_allocator() const noexcept {
  return (Alloc)(list_body_.lb_get_node_allocator());
}
//========================================
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^