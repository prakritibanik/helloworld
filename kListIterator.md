# Design an iterator class for a list of lists
For example: 
```
K = 3, List = {{1, 3, 5, 8, 10, 15}, {7, 11, 13, 16}, {2, 5, 6, 9, 20}}
```
All lists inside List is sorted in ascending order.
```
Class ListIterator {

public: 
    ListIterator(vector< <vector<int> >& List);
    bool hasNext(); // returns true if there is a next item else returns false
    iterator next(); // returns the iterator to the next item in the List
                                  // in sorted order
                                  // For eg. first time next will return 1, then it will return 2, then 3, ...
}
```

**Design the hasNext() and next() member function for this class.**

## Constraints
- Input list contain integers only
- Input lists cannot be modified
- List can contain empty list
- K can be very large
- List can contain zero or negative numbers
- List can contain duplicate numbers

## Solution
This problem is similar to merging K sorted lists but insteadof merging all the lists at once we are just to return the next element in the sorted order. Also we need to return the iterator, not just the value.

Whenever there is a problem that asks for top K elements priority queue is a good candidate to solve that problem. Here, we can start by constructing a priority queue that contains K elements, the first element from each lists in List. So when next() is called we first check if hasNext() returns true, if so we return the next iterator

  
