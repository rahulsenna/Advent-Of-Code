# C++ STL Algorithm Functions


## Non-modifying sequence operations:

    std::all_of
    std::any_of
    std::none_of
    std::for_each
    std::count
    std::count_if
    std::mismatch
    std::find
    std::find_if
    std::find_if_not
    std::find_end
    std::find_first_of
    std::adjacent_find
    std::search
    std::search_n
    std::lexicographical_compare
    std::lexicographical_compare_three_way

## Modifying sequence operations:

    std::copy
    std::copy_if
    std::copy_n
    std::copy_backward
    std::move
    std::move_backward
    std::fill
    std::fill_n
    std::transform
    std::generate
    std::generate_n
    std::remove
    std::remove_if
    std::remove_copy
    std::remove_copy_if
    std::replace
    std::replace_if
    std::replace_copy
    std::replace_copy_if
    std::swap
    std::swap_ranges
    std::iter_swap
    std::reverse
    std::reverse_copy
    std::rotate
    std::rotate_copy
    std::random_shuffle
    std::shuffle
    std::unique
    std::unique_copy
    std::is_partitioned
    std::partition
    std::stable_partition
    std::partition_copy
    std::partition_point
    std::is_sorted
    std::is_sorted_until

## Sorting and related operations:

    std::sort
    std::partial_sort
    std::partial_sort_copy
    std::stable_sort
    std::nth_element
    std::merge
    std::inplace_merge
    std::includes
    std::set_union
    std::set_intersection
    std::set_difference
    std::set_symmetric_difference

## Binary search operations:

    std::lower_bound
    std::upper_bound
    std::binary_search
    std::equal_range

## Heap operations:

    std::push_heap
    std::pop_heap
    std::make_heap
    std::sort_heap
    std::is_heap
    std::is_heap_until

## Minimum/maximum operations:

    std::min
    std::max
    std::minmax
    std::min_element
    std::max_element
    std::minmax_element

## Numeric operations:

    std::accumulate
    std::inner_product
    std::adjacent_difference
    std::partial_sum
    std::exclusive_scan
    std::inclusive_scan
    std::transform_reduce

## Set operations (on sorted ranges):

    std::merge
    std::inplace_merge
    std::includes
    std::set_union
    std::set_intersection
    std::set_difference
    std::set_symmetric_difference

## Permutations:

    std::next_permutation
    std::prev_permutation

## Other operations:

    std::iota
    std::sample


---

## std::accumulate

```cpp

#include <numeric>
int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
```

Computes the sum of a range of values.

---

## std::adjacent_find

```cpp

#include <algorithm>
auto it = std::adjacent_find(numbers.begin(), numbers.end());
```

Finds the first occurrence of two adjacent elements that are equal.

---

## std::all_of

```cpp

#include <algorithm>
bool all_even = std::all_of(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 0; });
```

Checks if all elements in a range satisfy a given predicate.

---

## std::any_of

```cpp

#include <algorithm>
bool any_odd = std::any_of(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 1; });
```

Checks if any element in a range satisfies a given predicate.

---

## std::binary_search

```cpp

#include <algorithm>
bool exists = std::binary_search(numbers.begin(), numbers.end(), value);
```

Checks if a value exists in a sorted range using binary search.

---

## std::copy

```cpp

#include <algorithm>
std::copy(numbers.begin(), numbers.end(), destination.begin());
```

Copies elements from one range to another.

---

## std::copy_backward

```cpp

#include <algorithm>
std::copy_backward(numbers.begin(), numbers.end(), destination.end());
```

Copies elements from one range to another in reverse order.

---

## std::copy_if

```cpp

#include <algorithm>
std::copy_if(numbers.begin(), numbers.end(), destination.begin(), [](int num) { return num % 2 == 0; });
```

Copies elements from a range to another range if they satisfy a given predicate.

---

## std::copy_n

```cpp

#include <algorithm>
std::copy_n(numbers.begin(), 5, destination.begin());
```

Copies a specified number of elements from one range to another.

---

## std::count

```cpp

#include <algorithm>
int count = std::count(numbers.begin(), numbers.end(), value);
```

Counts the number of occurrences of a value in a range.

---

## std::count_if

```cpp

#include <algorithm>
int even_count = std::count_if(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 0; });
```

Counts the number of elements in a range that satisfy a given predicate.

---

## std::equal

```cpp

#include <algorithm>
bool equal = std::equal(range1.begin(), range1.end(), range2.begin());
```

Checks if two ranges are equal.

---

## std::fill

```cpp

#include <algorithm>
std::fill(numbers.begin(), numbers.end(), value);
```

Fills a range with a specific value.

---

## std::find

```cpp

#include <algorithm>
auto it = std::find(numbers.begin(), numbers.end(), value);
```

Finds the first occurrence of a value in a range.

---

## std::find_end

```cpp

#include <algorithm>
auto it = std::find_end(numbers.begin(), numbers.end(), subsequence.begin(), subsequence.end());
```

Finds the last subsequence of elements in a range.

---

## std::find_first_of

```cpp

#include <algorithm>
auto it = std::find_first_of(numbers.begin(), numbers.end(), values.begin(), values.end());
```

Finds the first occurrence of any of a set of values in a range.

---

## std::find_if

```cpp

#include <algorithm>
auto it = std::find_if(numbers.begin(), numbers.end(), [](int num) { return num > 10; });
```

Finds the first element in a range that satisfies a given predicate.

---

## std::find_if_not

```cpp

#include <algorithm>
auto it = std::find_if_not(numbers.begin(), numbers.end(), [](int num) { return num > 10; });
```

Finds the first element in a range that does not satisfy a given predicate.

---

## std::for_each

```cpp

#include <algorithm>
std::for_each(numbers.begin(), numbers.end(), [](int num) { /* function code here */ });
```

Applies a function to each element in a range.

---

## std::generate

```cpp

#include <algorithm>
std::generate(numbers.begin(), numbers.end(), []() { return rand(); });
```

Fills a range with values generated by a given function.

---

## std::generate_n

```cpp

#include <algorithm>
std::generate_n(numbers.begin(), 5, []() { return rand(); });
```

Fills a specified number of elements in a range with values generated by a given function.

---

## std::includes

```cpp

#include <algorithm>
bool includes = std::includes(range1.begin(), range1.end(), range2.begin(), range2.end());
```

Checks if one range includes another.

---

## std::inplace_merge

```cpp

#include <algorithm>
std::inplace_merge(numbers.begin(), numbers_middle, numbers.end());
```

Merges two sorted ranges into one in-place.

---

## std::is_partitioned

```cpp

#include <algorithm>
bool is_partitioned = std::is_partitioned(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 0; });
```

Checks if a range is partitioned according to a given predicate.

---

## std::is_sorted

```cpp

#include <algorithm>
bool is_sorted = std::is_sorted(numbers.begin(), numbers.end());
```

Checks if a range is sorted in non-descending order.

---

## std::is_sorted_until

```cpp

#include <algorithm>
auto sorted_until = std::is_sorted_until(numbers.begin(), numbers.end());
```

Finds the largest sorted subrange within a range.

---

## std::iter_swap

```cpp

#include <algorithm>
std::iter_swap(it1, it2);
```

Swaps the values of two iterators.

---

## std::lexicographical_compare

```cpp

#include <algorithm>
bool lex_compare = std::lexicographical_compare(range1.begin(), range1.end(), range2.begin(), range2.end());
```

Checks if one range is lexicographically less than another.

---

## std::max

```cpp

#include <algorithm>
int max_value = std::max(a, b);
```

Returns the larger of two values.

---

## std::max_element

```cpp

#include <algorithm>
auto max_it = std::max_element(numbers.begin(), numbers.end());
```

Finds the maximum element in a range.

---

## std::merge

```cpp

#include <algorithm>
std::merge(range1.begin(), range1.end(), range2.begin(), range2.end(), destination.begin());
```

Merges two sorted ranges into one.

---

## std::min

```cpp

#include <algorithm>
int min_value = std::min(a, b);
```

Returns the smaller of two values.

---

## std::min_element

```cpp

#include <algorithm>
auto min_it = std::min_element(numbers.begin(), numbers.end());
```

Finds the minimum element in a range.

---

## std::minmax

```cpp

#include <algorithm>
std::pair<int, int> minmax_values = std::minmax(a, b);
```

Returns both the minimum and maximum of two values.

---

## std::minmax_element

```cpp

#include <algorithm>
auto minmax_it = std::minmax_element(numbers.begin(), numbers.end());
```

Finds both the minimum and maximum elements in a range.

---

## std::mismatch

```cpp

#include <algorithm>
auto mismatch_it = std::mismatch(range1.begin(), range1.end(), range2.begin());
```

Finds the first pair of elements that differ between two ranges.

---

## std::move

```cpp

#include <algorithm>
std::move(source.begin(), source.end(), destination.begin());
```

Moves elements from one range to another.

---

## std::next_permutation

```cpp

#include <algorithm>
std::next_permutation(numbers.begin(), numbers.end());
```

Rearranges the elements in a range to the next lexicographically greater permutation.

---

## std::none_of

```cpp

#include <algorithm>
bool none_odd = std::none_of(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 1; });
```

Checks if none of the elements in a range satisfy a given predicate.

---

## std::nth_element

```cpp

#include <algorithm>
std::nth_element(numbers.begin(), numbers.begin() + n, numbers.end());
```

Partitions a range such that the element at the nth position is in its sorted position.

---

## std::partial_sort

```cpp

#include <algorithm>
std::partial_sort(numbers.begin(), numbers.begin() + k, numbers.end());
```

Partially sorts a range up to the kth element.

---

## std::partial_sort_copy

```cpp

#include <algorithm>
std::partial_sort_copy(numbers.begin(), numbers.end(), destination.begin(), destination.end());
```

Copies and partially sorts elements from a range into another range.

---

## std::partition

```cpp

#include <algorithm>
auto partition_it = std::partition(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 0; });
```

Partitions a range based on a given predicate.

---

## std::partition_copy

```cpp

#include <algorithm>
std::partition_copy(numbers.begin(), numbers.end(), even_numbers.begin(), odd_numbers.begin(), [](int num) { return num % 2 == 0; });
```

Copies elements from a range into two different ranges based on a given predicate.

---

## std::partition_point

```cpp

#include <algorithm>
auto partition_point_it = std::partition_point(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 0; });
```

Finds the partition point in a range that satisfies a given predicate.

---

## std::pop_heap

```cpp

#include <algorithm>
std::pop_heap(numbers.begin(), numbers.end());
```

Reorganizes elements in a range to make it a max heap and moves the largest element to the last position.

---

## std::prev_permutation

```cpp

#include <algorithm>
std::prev_permutation(numbers.begin(), numbers.end());
```

Rearranges the elements in a range to the previous lexicographically smaller permutation.

---

## std::push_heap

```cpp

#include <algorithm>
std::push_heap(numbers.begin(), numbers.end());
```

Reorganizes elements in a range to make it a max heap and incorporates the new element.

---

## std::random_shuffle

```cpp

#include <algorithm>
std::random_shuffle(numbers.begin(), numbers.end());
```

Randomly shuffles the elements in a range.

---

## std::remove

```cpp

#include <algorithm>
auto new_end = std::remove(numbers.begin(), numbers.end(), value);
```

Removes all elements equal to a specific value from a range.

---

## std::remove_copy

```cpp

#include <algorithm>
auto new_end = std::remove_copy(numbers.begin(), numbers.end(), destination.begin(), value);
```

Copies elements from a range to another range, excluding all occurrences of a specific value.

---

## std::remove_copy_if

```cpp

#include <algorithm>
auto new_end = std::remove_copy_if(numbers.begin(), numbers.end(), destination.begin(), [](int num) { return num % 2 == 0; });
```

Copies elements from a range to another range, excluding elements that satisfy a given predicate.

---

## std::remove_if

```cpp

#include <algorithm>
auto new_end = std::remove_if(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 0; });
```

Removes all elements from a range that satisfy a given predicate.

---

## std::replace

```cpp

#include <algorithm>
std::replace(numbers.begin(), numbers.end(), old_value, new_value);
```

Replaces all occurrences of a specific value in a range with a new value.

---

## std::replace_copy

```cpp

#include <algorithm>
std::replace_copy(numbers.begin(), numbers.end(), destination.begin(), old_value, new_value);
```

Copies elements from a range to another range, replacing all occurrences of a specific value with a new value.

---

## std::replace_copy_if

```cpp

#include <algorithm>
std::replace_copy_if(numbers.begin(), numbers.end(), destination.begin(), [](int num) { return num % 2 == 0; }, new_value);
```

Copies elements from a range to another range, replacing elements that satisfy a given predicate with a new value.

---

## std::replace_if

```cpp

#include <algorithm>
std::replace_if(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 0; }, new_value);
```

Replaces elements in a range that satisfy a given predicate with a new value.

---

## std::reverse

```cpp

#include <algorithm>
std::reverse(numbers.begin(), numbers.end());
```

Reverses the order of elements in a range.

---

## std::reverse_copy

```cpp

#include <algorithm>
std::reverse_copy(numbers.begin(), numbers.end(), destination.begin());
```

Copies elements from a range to another range in reverse order.

---

## std::rotate

```cpp

#include <algorithm>
std::rotate(numbers.begin(), numbers.begin() + n, numbers.end());
```

Rotates the elements in a range such that the element at the nth position becomes the first element.

---

## std::rotate_copy

```cpp

#include <algorithm>
std::rotate_copy(numbers.begin(), numbers.begin() + n, numbers.end(), destination.begin());
```

Copies and rotates the elements from a range to another range.

---

## std::search

```cpp

#include <algorithm>
auto it = std::search(numbers.begin(), numbers.end(), subsequence.begin(), subsequence.end());
```

Searches for the first occurrence of a subsequence within a range.

---

## std::search_n

```cpp

#include <algorithm>
auto it = std::search_n(numbers.begin(), numbers.end(), count, value);
```

Searches for the first occurrence of a subsequence consisting of a specific value repeated a certain number of times.

---

## std::set_difference

```cpp

#include <algorithm>
std::set_difference(range1.begin(), range1.end(), range2.begin(), range2.end(), destination.begin());
```

Computes the difference between two sorted ranges.

---

## std::set_intersection

```cpp

#include <algorithm>
std::set_intersection(range1.begin(), range1.end(), range2.begin(), range2.end(), destination.begin());
```

Computes the intersection of two sorted ranges.

---

## std::set_symmetric_difference

```cpp

#include <algorithm>
std::set_symmetric_difference(range1.begin(), range1.end(), range2.begin(), range2.end(), destination.begin());
```

Computes the symmetric difference between two sorted ranges.

---

## std::set_union

```cpp

#include <algorithm>
std::set_union(range1.begin(), range1.end(), range2.begin(), range2.end(), destination.begin());
```

Computes the union of two sorted ranges.

---

## std::shuffle

```cpp

#include <algorithm>
std::shuffle(numbers.begin(), numbers.end(), std::mt19937(std::random_device()()));
```

Randomly shuffles the elements in a range using a specified random number generator.

---

## std::sort

```cpp

#include <algorithm>
std::sort(numbers.begin(), numbers.end());
```

Sorts the elements in a range in non-descending order.

---

## std::sort_heap

```cpp

#include <algorithm>
std::sort_heap(numbers.begin(), numbers.end());
```

Sorts the elements in a range that represents a max heap.

---

## std::stable_partition

```cpp

#include <algorithm>
auto partition_it = std::stable_partition(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 0; });
```

Partitions a range based on a given predicate while preserving the relative order of elements.

---

## std::stable_sort

```cpp

#include <algorithm>
std::stable_sort(numbers.begin(), numbers.end());
```

Sorts the elements in a range in non-descending order while preserving the relative order of elements with equal values.

---

## std::swap

```cpp

#include <algorithm>
std::swap(a, b);
```

Swaps the values of two objects.

---

## std::swap_ranges

```cpp

#include <algorithm>
std::swap_ranges(range1.begin(), range1.end(), range2.begin());
```

Swaps the values of elements in two ranges.

---

## std::transform

```cpp

#include <algorithm>
std::transform(numbers1.begin(), numbers1.end(), numbers2.begin(), result.begin(), [](int a, int b) { return a + b; });
```

Applies a function to pairs of elements from two ranges and stores the result in another range.

---

## std::unique

```cpp

#include <algorithm>
auto new_end = std::unique(numbers.begin(), numbers.end());
```

Removes consecutive duplicate elements from a range.

---

## std::unique_copy

```cpp

#include <algorithm>
auto new_end = std::unique_copy(numbers.begin(), numbers.end(), destination.begin());
```

Copies elements from a range to another range, removing consecutive duplicate elements.
