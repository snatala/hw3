#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int num;
  PComparator c;
  void heapify(std::vector<T>& data);
};

// Add implementation of member functions here
template<typename T, typename PComparator>
Heap<T, PComparator>::Heap(int nums, PComparator comparer) : num(nums), c(comparer) {}

template<typename T, typename PComparator>
Heap<T,PComparator>::Heap::~Heap(){}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(data.empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data.front();


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(data.empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty.");

  }

  if(data.size() == 1){
    data.pop_back();
    return;
  }

  heapify(data);

}


template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(std::vector<T>& data){
  std::size_t ind = 0;

  int lI = num*ind + 1;
  int rI = num*ind + num;
  bool trickle = true;

  data[0] = data[data.size()-1];
  data.pop_back();

  while(trickle){
    if(lI >= data.size()){
      break;
    }

    int bestI = lI;
    for(int i = lI; i < rI; i++){
      if(i + 1 < data.size()){
        if(c(data[i+1], data[bestI])){
          bestI = i+1;
        }
      }
    }

    if(c(data[bestI], data[ind])){
      std::swap(data[bestI], data[ind]);
      ind = bestI;

      lI = num*ind +1;
      rI = num*ind + num;
    } else {
      trickle = false;
    }
  }
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  if(data.empty()){
    return true;
  }
  return false;
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{
  size_t size_ = data.size();
  return size_;
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  data.push_back(item);

  std::size_t index = data.size() -1;

  while(index != 0){
    std::size_t pIndex = (index -1)/num;


    if(pIndex < 0){
      break;
    }

    T& curr = data[index];
    T& par = data[pIndex];

    if(c(curr, par)){
      std::swap(curr, par);
      index = pIndex;
    } else {
      break;
    }
  }
}

#endif

