#pragma once 

#include <vector>
#include <functional>
#include <assert.h>

using std::vector;

template <class T, class Comp = std::less< T > >
struct priority_queue {
   priority_queue();
   priority_queue(vector<size_t>*);

public:
   void set_vec(vector<size_t>*);

   void push(T const& val);
   void pop ();
   void clear();

   T const& top() const;

   size_t change_key(size_t queue_index, T const& val);

   size_t size () const;
   bool   empty() const;  

   T const& at(size_t queue_index) const;
   T&       at(size_t queue_index);

private:
   size_t move_down(size_t queue_index);
   size_t move_up  (size_t queue_index);

   void key_changed_(T const&, size_t);
      
private:
   vector<T> data_;
   vector<size_t>* vec_;
};