/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SHARED_OBJECT_LIST_H
#define SHARED_OBJECT_LIST_H

#include <list>
#include <memory>
#include <iterator>

/**
 *  @brief A list of (polymorphic) objects, managed by std::shared_ptr - an aggregration
 *
 *  This list will take ownership of the objects passed to it.
 */
template <class T>
class SharedObjectList
  : public std::list<std::shared_ptr<T> >
{
public:
  typedef T &reference;
  typedef const T &const_reference;
  typedef std::shared_ptr<T> holder;
  typedef std::shared_ptr<const T> const_holder;

  class Iterator
    : public std::iterator<std::bidirectional_iterator_tag, T, void, T*, T&>
  {
  public:
    typedef typename std::list<std::shared_ptr<T> >::iterator basic_iterator;

    explicit Iterator() : m_basic() { }
    explicit Iterator(const basic_iterator &i) : m_basic(i) { }
    bool operator==(const Iterator &other) const { return m_basic == other.m_basic; }
    bool operator!=(const Iterator &other) const { return m_basic != other.m_basic; }
    Iterator operator++() { ++m_basic; return *this; }
    Iterator operator++(int) { Iterator ret = *this; ++m_basic; return ret; }
    Iterator operator+(int n) const { Iterator result = *this; for (int i = 0; i < n; ++i) ++result; return result; }
    Iterator &operator+=(int n) { for (int i = 0; i < n; ++i) ++m_basic; return *this; }
    Iterator operator--() { --m_basic; return *this; }
    Iterator operator--(int) { Iterator ret = *this; --m_basic; return ret; }
    Iterator operator-(int n) const { Iterator result = *this; for (int i = 0; i < n; ++i) --result; return result; }
    Iterator &operator-=(int n) { for (int i = 0; i < n; ++i) --m_basic; return *this; }
    reference operator*() const { return **m_basic; }
    T *operator->() const { return (*m_basic).get(); }
    holder &ref() const { return *m_basic; }

  private:
    friend class SharedObjectList<T>;
    friend class SharedObjectList<T>::ConstIterator;
    basic_iterator m_basic;
  };

  class ConstIterator
    : public std::iterator<std::bidirectional_iterator_tag, T, void, const T*, const T&>
  {
  public:
    typedef typename std::list<std::shared_ptr<T> >::const_iterator basic_iterator;

    explicit ConstIterator() : m_basic() { }
    explicit ConstIterator(const basic_iterator &i) : m_basic(i) { }
    ConstIterator(const Iterator &i) : m_basic(i.m_basic) { }
    bool operator==(const ConstIterator &other) const { return m_basic == other.m_basic; }
    bool operator!=(const ConstIterator &other) const { return m_basic != other.m_basic; }
    ConstIterator operator++() { ++m_basic; return *this; }
    ConstIterator operator++(int) { ConstIterator ret = *this; ++m_basic; return ret; }
    ConstIterator operator+(int n) const { ConstIterator result = *this; for (int i = 0; i < n; ++i) ++result; return result; }
    ConstIterator &operator+=(int n) { for (int i = 0; i < n; ++i) ++m_basic; return *this; }
    ConstIterator operator--() { --m_basic; return *this; }
    ConstIterator operator--(int) { ConstIterator ret = *this; --m_basic; return ret; }
    ConstIterator operator-(int n) const { ConstIterator result = *this; for (int i = 0; i < n; ++i) --result; return result; }
    ConstIterator &operator-=(int n) { for (int i = 0; i < n; ++i) --m_basic; return *this; }
    reference operator*() const { return **m_basic; }
    const T *operator->() const { return (*m_basic).get(); }
    const const_holder &ref() const { return *m_basic; }

  private:
    friend class SharedObjectList<T>;
    basic_iterator m_basic;
  };

  typedef Iterator iterator;
  typedef ConstIterator const_iterator;

  reference front () { return *std::list<std::shared_ptr<T> >::front(); }
  const reference front () const { return *std::list<std::shared_ptr<T> >::front(); }
  reference back () { return *std::list<std::shared_ptr<T> >::back(); }
  const reference back () const { return *std::list<std::shared_ptr<T> >::back(); }

  iterator begin() { return Iterator(std::list<std::shared_ptr<T> >::begin()); }
  const_iterator begin() const { return ConstIterator(std::list<std::shared_ptr<T> >::begin()); }
  iterator end() { return Iterator(std::list<std::shared_ptr<T> >::end()); }
  const_iterator end() const { return ConstIterator(std::list<std::shared_ptr<T> >::end()); }

  //  creates a copy
  iterator insert(ConstIterator pos, const holder &value) { return Iterator(std::list<std::shared_ptr<T> >::insert(pos.m_basic, value)); }
  iterator insert(ConstIterator pos, const T &value) { return Iterator(std::list<std::shared_ptr<T> >::insert(pos.m_basic, std::shared_ptr<T>(new T(value)))); }
  iterator insert(ConstIterator pos, T &&value) { return Iterator(std::list<std::shared_ptr<T> >::insert(pos.m_basic, std::shared_ptr<T>(new T(value)))); }
  //  takes ownership of the object
  iterator insert(ConstIterator pos, T *value) { return Iterator(std::list<std::shared_ptr<T> >::insert(pos.m_basic, std::shared_ptr<T>(value))); }

  //  creates a copy
  void push_back(const holder &value) { std::list<std::shared_ptr<T> >::push_back(value); }
  void push_back(const T &value) { std::list<std::shared_ptr<T> >::push_back(std::shared_ptr<T>(new T(value))); }
  void push_back(T &&value) { std::list<std::shared_ptr<T> >::push_back(std::shared_ptr<T>(new T(value))); }
  //  takes ownership of the object
  void push_back(T *value) { std::list<std::shared_ptr<T> >::push_back(std::shared_ptr<T>(value)); }

  //  creates a copy
  void push_front(const holder &value) { std::list<std::shared_ptr<T> >::push_front(value); }
  void push_front(const T &value) { std::list<std::shared_ptr<T> >::push_front(std::shared_ptr<T>(new T(value))); }
  void push_front(T &&value) { std::list<std::shared_ptr<T> >::push_front(std::shared_ptr<T>(new T(value))); }
  //  takes ownership of the object
  void push_front(T *value) { std::list<std::shared_ptr<T> >::push_front(std::shared_ptr<T>(value)); }

  void erase(ConstIterator pos) { std::list<std::shared_ptr<T> >::erase(pos.m_basic); }
  void erase(Iterator pos) { std::list<std::shared_ptr<T> >::erase(pos.m_basic); }
  void erase(ConstIterator from, ConstIterator to) { std::list<std::shared_ptr<T> >::erase(from.m_basic, to.m_basic); }
  void erase(Iterator from, Iterator to) { std::list<std::shared_ptr<T> >::erase(from.m_basic, to.m_basic); }

  //  finds an element by pointer
  ConstIterator find(const T *ptr) const
  {
    auto i = begin();
    for ( ; i != end() && i.operator->() != ptr; ++i)
      ;
    return i;
  }

  //  finds an element by pointer
  Iterator find(const T *ptr)
  {
    auto i = begin();
    for ( ; i != end() && i.operator->() != ptr; ++i)
      ;
    return i;
  }

  //  finds an element by pointer
  Iterator find(const holder &ref)
  {
    auto i = begin();
    for ( ; i != end() && i.ref() != ref; ++i)
      ;
    return i;
  }

  //  removes an element by pointer
  void erase(const T *ptr)
  {
    auto i = find(ptr);
    if (i != end()) {
      erase(i);
    }
  }

  //  removes an element by pointer
  void erase(const holder &ref)
  {
    auto i = find(ref);
    if (i != end()) {
      erase(i);
    }
  }

  //  compatibility with Qt containers
  size_t count() const { return int(this->size()); }
  void prepend(const holder &value) { push_front(value); }
  void prepend(const T &value) { push_front(value); }
  void prepend(T &&value) { push_front(value); }
  void prepend(T *value) { push_front(value); }
  void append(const holder &value) { push_back(value); }
  void append(const T &value) { push_back(value); }
  void append(T &&value) { push_back(value); }
  void append(T *value) { push_back(value); }
  bool isEmpty() const { return this->empty(); }

private:
  //  TODO:
  using std::list<std::shared_ptr<T> >::splice;
  using std::list<std::shared_ptr<T> >::assign;
  using std::list<std::shared_ptr<T> >::rbegin;
  using std::list<std::shared_ptr<T> >::rend;
};

#endif
