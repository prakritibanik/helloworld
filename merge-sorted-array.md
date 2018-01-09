# In order to win the prize for most cookies sold, my friend Alice and I are going to merge our Girl Scout Cookies orders and enter as one unit.

Each order is represented by an "order id" (an integer).

We have our lists of orders sorted numerically already, in vectors. Write a function to merge our vectors of orders into one sorted vector.

For example:
```c++
const vector<int> myVector {3, 4, 6, 10, 11, 15};
const vector<int> alicesVector {1, 5, 8, 12, 14, 19};

vector<int> mergedVector = mergeVectors(myVector, alicesVector);

cout << "[";
for (size_t i = 0; i < mergedVector.size(); ++i) {
    if (i > 0) {
        cout << ", ";
    }
    cout << mergedVector[i];
}
cout << "]" << endl;
// prints [1, 3, 4, 5, 6, 8, 10, 11, 12, 14, 15, 19]
```
So in general we could say something like:

- We'll start at the beginnings of our input vectors, since the smallest elements will be there.
- As we put items in our final mergedVector, we'll keep track of the fact that they're "already merged."
- At each step, each vector has a first "not-yet-merged" item.
- At each step, the next item to put in the mergedVector is the smaller of those two "not-yet-merged" items!

**Think about edge cases!** What happens when we've merged in all of the elements from one of our vectors but we still have elements to merge in from our other vector?

**Here are some edge cases:**

1. One or both of our input vectors is 0 elements or 1 element
2. One of our input vectors is longer than the other.
3. One of our vectors runs out of elements before we're done merging.
Actually, (3) will always happen. In the process of merging our vectors, we'll certainly exhaust one before we exhaust the other.

Does our function handle these cases correctly?

We'll get a segfault in all three cases!

## Solution
First, we allocate our answer vector, getting its size by adding the size of myVector and alicesVector.

We keep track of a current index in myVector, a current index in alicesVector, and a current index in mergedVector. So at each step, there's a "current item" in alicesVector and in myVector. The smaller of those is the next one we add to the mergedVector!

But careful: we also need to account for the case where we exhaust one of our vectors and there are still elements in the other. To handle this, we say that the current item in myVector is the next item to add to mergedVector only if myVector is not exhausted AND, either:

alicesVector is exhausted, or
the current item in myVector is less than the current item in alicesVector
```c++
vector<int> mergeVectors(const vector<int>& myVector, const vector<int>& alicesVector)
{
    // set up our mergedVector
    vector<int> mergedVector(myVector.size() + alicesVector.size());

    size_t currentIndexAlices = 0;
    size_t currentIndexMine   = 0;
    size_t currentIndexMerged = 0;

    while (currentIndexMerged < mergedVector.size()) {

        bool isMyVectorExhausted = currentIndexMine >= myVector.size();
        bool isAlicesVectorExhausted = currentIndexAlices >= alicesVector.size();

        // case: next comes from my vector
        // my vector must not be exhausted, and EITHER:
        // 1) Alice's vector IS exhausted, or
        // 2) the current element in my vector is less
        //    than the current element in Alice's vector
        if (!isMyVectorExhausted && (isAlicesVectorExhausted
                || (myVector[currentIndexMine] < alicesVector[currentIndexAlices]))) {

            mergedVector[currentIndexMerged] = myVector[currentIndexMine];
            ++currentIndexMine;

        // case: next comes from Alice's vector
        }
        else {
            mergedVector[currentIndexMerged] = alicesVector[currentIndexAlices];
            ++currentIndexAlices;
        }

        ++currentIndexMerged;
    }

    return mergedVector;
}
```
The if statement is carefully constructed to avoid undefined behavior from indexing past the end of the vector. We take advantage of C++ short circuit evaluation ↴ and check first if the vectors are exhausted.

## Complexity
O(n)O(n) time and O(n)O(n) additional space, where nn is the number of items in the merged vector.

The added space comes from allocating the mergedVector. There's no way to do this " in-place" ↴ because neither of our input vectors are necessarily big enough to hold the merged vector.

But if our inputs were linked lists, we could avoid allocating a new structure and do the merge by simply adjusting the next pointers in the list nodes!

In our implementation above, we could avoid tracking currentIndexMerged and just compute it on the fly by adding currentIndexMine and currentIndexAlices. This would only save us one integer of space though, which is hardly anything. It's probably not worth the added code complexity.

## Bonus
What if we wanted to merge several sorted vectors? Write a function that takes as an input a vector of sorted vectors and outputs a single sorted vector with all the items from each vector.

Do we absolutely have to allocate a new vector to use for the merged output? Where else could we store our merged vector? How would our function need to change?

## What We Learned
We spent a lot of time figuring out how to cleanly handle edge cases.

Sometimes it's easy to lose steam at the end of a coding interview when you're debugging. But keep sprinting through to the finish! Think about edge cases. Look for off-by-one errors.
