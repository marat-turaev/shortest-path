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


template<class T, class Comp>
void priority_queue<T, Comp>::key_changed_(T const& v, size_t idx) {
   if (vec_ != 0) {
      (*vec_)[v.id()] = idx;
   }  
}

template<class T, class Comp>
priority_queue<T, Comp>::priority_queue()
   : vec_(0) {
}

template<class T, class Comp>
priority_queue<T, Comp>::priority_queue(vector<size_t>* vec)
   : vec_(vec) {
}

template<class T, class Comp>
void priority_queue<T, Comp>::set_vec(vector<size_t>* vec) {
   vec_ = vec;
}

template<class T, class Comp>
void priority_queue<T, Comp>::push(T const& val) {
   data_.push_back(val);
   key_changed_(val, size());
   move_up(size());
}

template<class T, class Comp>
void priority_queue<T, Comp>::pop() {
   key_changed_(at(1), 0);
   key_changed_(at(size()), 1);

   std::swap(at(1), at(size()));
   data_.pop_back();

   if (!empty())
      move_down(1);
}

template<class T, class Comp>
void priority_queue<T, Comp>::clear() {
   data_.clear();
}

template<class T, class Comp>
T const& priority_queue<T, Comp>::top() const {
   return at(1);
}

template<class T, class Comp>
size_t priority_queue<T, Comp>::change_key(size_t queue_index, T const& val) {
   key_changed_(at(queue_index), 0);
   key_changed_(val, queue_index);
   
   at(queue_index) = val;
   size_t idx = move_down(queue_index);

   if (idx != queue_index)
      return idx;

   return move_up(queue_index);
}

template<class T, class Comp>
size_t priority_queue<T, Comp>::size() const {
   return data_.size();
}

template<class T, class Comp>
bool priority_queue<T, Comp>::empty() const {
   return data_.empty();
}

template<class T, class Comp>
size_t priority_queue<T, Comp>::move_down(size_t queue_index) {
   assert(queue_index > 0 && queue_index <= size());

   while(queue_index <= size()) {
      size_t lc = 2 * queue_index;
      size_t rc = 2 * queue_index + 1;

      size_t best_idx = queue_index;
      if (lc <= size() && Comp()(at(lc), at(best_idx)))
         best_idx = lc;

      if (rc <= size() && Comp()(at(rc), at(best_idx)))
         best_idx = rc;

      if (best_idx != queue_index) {
       key_changed_(at(best_idx), queue_index);
       key_changed_(at(queue_index), best_idx);

         std::swap(at(best_idx), at(queue_index));
         queue_index = best_idx;
      }
      else 
         return queue_index;
   }

   return queue_index;
}

template<class T, class Comp>
size_t priority_queue<T, Comp>::move_up(size_t queue_index) {
   assert(queue_index > 0 && queue_index <= size());

   while (queue_index > 0) {
      size_t parent = queue_index / 2;

      if (parent > 0 && Comp()(at(queue_index), at(parent))) {
        key_changed_(at(parent), queue_index);
       key_changed_(at(queue_index), parent);

         std::swap(at(queue_index), at(parent));
         queue_index = parent;
      }
      else 
         return queue_index;
   }

   return queue_index;
}

template<class T, class Comp>
T& priority_queue<T, Comp>::at(size_t queue_index) {
   assert(queue_index > 0);
   return data_[queue_index - 1];
}

template<class T, class Comp>
T const& priority_queue<T, Comp>::at(size_t queue_index) const {
   assert(queue_index > 0);
   return data_[queue_index - 1];
}
