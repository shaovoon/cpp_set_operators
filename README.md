## Table of Contents

* Introduction
* Set Intersection
* Set Union
* Set Difference
* Set Symmetric Difference
* Superset and Subset
* "I have no use for all these!"

## Introduction

Ever since I started working with Python and that have gotten me into a lot of thinking how to redesign my libraries to be pythonic, if I were to implement them from scratch again. In this first article of the series, I want to introduce Python&#39;s wonderful and intuitive operators for working with set algebra into C++ world. These operators are nothing more than syntatic-sugar to reduce the amount of code to write.

[Table of Python Set Operators](https://docs.python.org/2/library/sets.html)

![PythonSetOperators.png](/images/PythonSetOperators.png)

## Set Intersection

![set_intersection2.png](/images/set_intersection2.png)

[C++ Reference: std::set_intersection](http://en.cppreference.com/w/cpp/algorithm/set_intersection)

* __Commutative__

`set_intersection` is an algorithm that produces a set of elements which are common to both sets. It is commutative, meaning that even the 2 sets are switched places, the algorithm returns the same result.

```Cpp
void intersection_example()
{
    std::vector<int> v1{ 1,2,3,4,5,6,7,8 };
    std::vector<int> v2{         5,  7,  9,10 };
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::vector<int> v_intersection;

    std::set_intersection(v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        std::back_inserter(v_intersection));

    for (int n : v_intersection)
        std::cout << n << &#39; &#39;;
}
```

__Output__

```
5 7
```

This is the example using `&` operator to do intersection.

```Cpp
void intersection_example()
{
    std::vector<int> v1{ 1,2,3,4,5,6,7,8 };
    std::vector<int> v2{         5,  7,  9,10 };

    std::vector<int> v_intersection = s(v1) & s(v2);

    for (int n : v_intersection)
        std::cout << n << &#39; &#39;;
}
```

I skip showing the output of the operator example as it is the same.

`s` is a function, not class. If s is to be a class, to instantiate it, a container type would have to be specified (see below).

```Cpp
std::vector<int> v_intersection = s<std::vector<int>>(v1) & s<std::vector<int>>(v2);
```

In order to make use of automatic type deduction, `s` has to be a function that does nothing but returns the `wrapper` class.

```Cpp
#include <algorithm>
#include <iterator>

template<typename T>
struct wrapper
{
    wrapper(T& container) : cont(container) {}
    T& cont;
};

template<typename T>
wrapper<T> s(T& s_cont)
{
    return wrapper<T>(s_cont);
}
```

The `&` operator function checks whether to sort the container. Since `std::sort` only works with random access iterators, so we cannot use this function with STL `list` and `slist` which has non-random access iterators. In my 15 years of work, I have not seen a single use of `list` in any codebase.

```Cpp
template<typename T>
T operator&(wrapper<T>& left, wrapper<T>& right)
{
    T& c1 = left.cont;
    T& c2 = right.cont;
    if (!std::is_sorted(c1.begin(), c1.end()))
        std::sort(c1.begin(), c1.end());
    if (!std::is_sorted(c2.begin(), c2.end()))
        std::sort(c2.begin(), c2.end());

    T v_intersection;

    std::set_intersection(c1.begin(), c1.end(),
        c2.begin(), c2.end(),
        std::back_inserter(v_intersection));

    return v_intersection;
}
```

All set algorithm precondition requires the ranges to be sorted, hence this `is_sorted` check.

## Set Union

![set_union2.png](/images/set_union2.png)

[C++ Reference: std::set_union](http://en.cppreference.com/w/cpp/algorithm/set_union)

* __Commutative__

`set_union`&nbsp;is an algorithm that produces a set of elements from&nbsp;both sets. For the elements appearing in intersection, it always picks them from the 1<sup>st</sup> set, not 2<sup>nd</sup> set.

```Cpp
void union_example()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5 };
    std::vector<int> v2 = {       3, 4, 5, 6, 7 };
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::vector<int> dest1;

    std::set_union(v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        std::back_inserter(dest1));

    for (const auto &i : dest1) {
        std::cout << i << &#39; &#39;;
    }
    std::cout << &#39;\n&#39;;
}
```

__Output__

```
1 2 3 4 5 6 7
```

The code required to write is much less, therefore the code is more concise.

```Cpp
void union_example()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5 };
    std::vector<int> v2 = {       3, 4, 5, 6, 7 };

    std::vector<int> dest1 = s(v1) | s(v2);

    for (int n : dest1)
        std::cout << n << &#39; &#39;;
}
```

The `|` operator is almost similar to `&` operator except that algorithm is different.

```Cpp
template<typename T>
T operator|(wrapper<T>& left, wrapper<T>& right)
{
    T& c1 = left.cont;
    T& c2 = right.cont;
    if (!std::is_sorted(c1.begin(), c1.end()))
        std::sort(c1.begin(), c1.end());
    if (!std::is_sorted(c2.begin(), c2.end()))
        std::sort(c2.begin(), c2.end());

    T dest1;

    std::set_union(c1.begin(), c1.end(),
        c2.begin(), c2.end(),
        std::back_inserter(dest1));

    return dest1;
}
```

## Set Difference

![set_difference2.png](/images/set_difference2.png)

[C++ Reference: std::set_difference](http://en.cppreference.com/w/cpp/algorithm/set_difference)

* __Non-Commutative__

`set_difference`&nbsp;returns&nbsp;the elements in&nbsp;1<sup>st</sup> set which is not in the 2<sup>nd</sup> set and is represented by minus operator in Python. For obvious reasons, the results are different when the arguments have swapped places. `set_difference` is non-commutative like minus operation.

```Cpp
void set_difference_example() 
{
    std::vector<int> v1{ 1, 2, 5, 5, 5,    9 };
    std::vector<int> v2{    2, 5,       7 };
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::vector<int> diff;

    std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
        std::inserter(diff, diff.begin()));

    for (auto i : v1) std::cout << i << &#39; &#39;;
    std::cout << "minus ";
    for (auto i : v2) std::cout << i << &#39; &#39;;
    std::cout << "is: ";

    for (auto i : diff) std::cout << i << &#39; &#39;;
    std::cout << &#39;\n&#39;;
}
```

__Output__

```
1 2 5 5 5 9 minus 2 5 7 is: 1 5 5 9
```

This is an example with minus operator.

```Cpp
void set_difference_example()
{
    std::vector<int> v1{ 1, 2, 5, 5, 5, 9 };
    std::vector<int> v2{    2, 5,       7 };

    std::vector<int> diff = s(v1) - s(v2);

    for (auto i : v1) std::cout << i << &#39; &#39;;
    std::cout << "minus ";
    for (auto i : v2) std::cout << i << &#39; &#39;;
    std::cout << "is: ";

    for (auto i : diff) std::cout << i << &#39; &#39;;
    std::cout << &#39;\n&#39;;
}
```

The code for minus operator is shown below:

```Cpp
template<typename T>
T operator-(wrapper<T>& left, wrapper<T>& right)
{
    T& c1 = left.cont;
    T& c2 = right.cont;
    if (!std::is_sorted(c1.begin(), c1.end()))
        std::sort(c1.begin(), c1.end());
    if (!std::is_sorted(c2.begin(), c2.end()))
        std::sort(c2.begin(), c2.end());

    T diff;

    std::set_difference(c1.begin(), c1.end(),
        c2.begin(), c2.end(),
        std::back_inserter(diff));

    return diff;
}
```

## Set Symmetric Difference

![set_sym_difference2.png](/images/set_sym_difference2.png)

[C++ Reference: std::set_symmetric_difference](http://en.cppreference.com/w/cpp/algorithm/set_symmetric_difference)

* __Commutative__

`set_symmetric_difference` computes the elements in either&nbsp;set but not both.

```Cpp
void set_symmetric_difference_example()
{
    std::vector<int> v1{ 1,2,3,4,5,6,7,8 };
    std::vector<int> v2{         5,  7,  9,10 };
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::vector<int> v_symDifference;

    std::set_symmetric_difference(
        v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        std::back_inserter(v_symDifference));

    for (int n : v_symDifference)
        std::cout << n << &#39; &#39;;
}
```

__Output__

```
1 2 3 4 6 8 9 10
```

`set_symmetric_difference` is represented by logical exclusive or operator.

```Cpp
void set_symmetric_difference_example()
{
    std::vector<int> v1{ 1,2,3,4,5,6,7,8 };
    std::vector<int> v2{         5,  7,  9,10 };

    std::vector<int> v_symDifference = s(v1) ^ s(v2);

    for (int n : v_symDifference)
        std::cout << n << &#39; &#39;;
}
```

The code for logical exclusive or operator is shown below:

```Cpp
template<typename T>
T operator^(wrapper<T>& left, wrapper<T>& right)
{
    T& c1 = left.cont;
    T& c2 = right.cont;
    if (!std::is_sorted(c1.begin(), c1.end()))
        std::sort(c1.begin(), c1.end());
    if (!std::is_sorted(c2.begin(), c2.end()))
        std::sort(c2.begin(), c2.end());

    T v_symDifference;

    std::set_symmetric_difference(c1.begin(), c1.end(),
        c2.begin(), c2.end(),
        std::back_inserter(v_symDifference));

    return v_symDifference;
}
```

## Superset and Subset

![set_superset2.png](/images/set_superset2.png)

[C++ Reference: std::includes](http://en.cppreference.com/w/cpp/algorithm/includes)

* __Non-Commutative__

STL `includes` can be used to find out whether a set is a superset (returns a boolean). To check if it is a subset, just switch the 2 sets.

```Cpp
void is_superset_example()
{
    std::vector<char> v1{ &#39;a&#39;, &#39;b&#39;, &#39;c&#39;, &#39;f&#39;, &#39;h&#39;, &#39;x&#39; };
    std::vector<char> v2{ &#39;a&#39;, &#39;b&#39;, &#39;c&#39; };
    std::vector<char> v3{ &#39;a&#39;, &#39;c&#39; };
    std::vector<char> v4{ &#39;g&#39; };
    std::vector<char> v5{ &#39;a&#39;, &#39;c&#39;, &#39;g&#39; };
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::sort(v3.begin(), v3.end());
    std::sort(v4.begin(), v4.end());
    std::sort(v5.begin(), v5.end());

    for (auto i : v1) std::cout << i << &#39; &#39;;
    std::cout << "\nincludes:\n" << std::boolalpha;

    for (auto i : v2) std::cout << i << &#39; &#39;;
    std::cout << ": " 
              << std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << &#39;\n&#39;;
    for (auto i : v3) std::cout << i << &#39; &#39;;
    std::cout << ": " 
              << std::includes(v1.begin(), v1.end(), v3.begin(), v3.end()) << &#39;\n&#39;;
    for (auto i : v4) std::cout << i << &#39; &#39;;
    std::cout << ": " 
              << std::includes(v1.begin(), v1.end(), v4.begin(), v4.end()) << &#39;\n&#39;;
    for (auto i : v5) std::cout << i << &#39; &#39;;
    std::cout << ": " 
              << std::includes(v1.begin(), v1.end(), v5.begin(), v5.end()) << &#39;\n&#39;;

    auto cmp_nocase = [](char a, char b) {
        return std::tolower(a) < std::tolower(b);
    };

    std::vector<char> v6{ &#39;A&#39;, &#39;B&#39;, &#39;C&#39; };
    for (auto i : v6) std::cout << i << &#39; &#39;;
    std::cout << ": (case-insensitive) "
        << std::includes(v1.begin(), v1.end(), v6.begin(), v6.end(), cmp_nocase)
        << &#39;\n&#39;;
}
```

__Output__

```
a b c f h x
includes:
a b c : true
a c : true
g : false
a c g : false
A B C : (case-insensitive) true
```

The `>=` operator example is below. The `<=` operator example is not shown in this article.

```Cpp
void is_superset_example()
{
    std::vector<char> v1{ &#39;a&#39;, &#39;b&#39;, &#39;c&#39;, &#39;f&#39;, &#39;h&#39;, &#39;x&#39; };
    std::vector<char> v2{ &#39;a&#39;, &#39;b&#39;, &#39;c&#39; };
    std::vector<char> v3{ &#39;a&#39;, &#39;c&#39; };
    std::vector<char> v4{ &#39;g&#39; };
    std::vector<char> v5{ &#39;a&#39;, &#39;c&#39;, &#39;g&#39; };

    for (auto i : v1) std::cout << i << &#39; &#39;;
    std::cout << "\nincludes:\n" << std::boolalpha;

    for (auto i : v2) std::cout << i << &#39; &#39;;
    std::cout << ": " << (s(v1) >= s(v2)) << &#39;\n&#39;;
    for (auto i : v3) std::cout << i << &#39; &#39;;
    std::cout << ": " << (s(v1) >= s(v3)) << &#39;\n&#39;;
    for (auto i : v4) std::cout << i << &#39; &#39;;
    std::cout << ": " << (s(v1) >= s(v4)) << &#39;\n&#39;;
    for (auto i : v5) std::cout << i << &#39; &#39;;
    std::cout << ": " << (s(v1) >= s(v5)) << &#39;\n&#39;;

    auto cmp_nocase = [](char a, char b) {
        return std::tolower(a) < std::tolower(b);
    };

    std::vector<char> v6{ &#39;A&#39;, &#39;B&#39;, &#39;C&#39; };
    for (auto i : v6) std::cout << i << &#39; &#39;;
    std::cout << ": (case-insensitive) "
        << std::includes(v1.begin(), v1.end(), v6.begin(), v6.end(), cmp_nocase)
        << &#39;\n&#39;;
}
```

User cannot opt for use of a custom comparator in the `>=` and `<=` overloaded operators at the moment, as shown in the case-insensitive example. In this situation, `includes` has to be called directly.

```Cpp
// Returns true if left is superset of right?
template<typename T>
bool operator>=(wrapper<T>& left, wrapper<T>& right)
{
    T& c1 = left.cont;
    T& c2 = right.cont;

    if (!std::is_sorted(c1.begin(), c1.end()))
        std::sort(c1.begin(), c1.end());
    if (!std::is_sorted(c2.begin(), c2.end()))
        std::sort(c2.begin(), c2.end());

    return std::includes(
        c1.begin(), c1.end(),
        c2.begin(), c2.end());
}

// Returns true if left is subset of right?
template<typename T>
bool operator<=(wrapper<T>& left, wrapper<T>& right)
{
    T& c1 = left.cont;
    T& c2 = right.cont;

    if (!std::is_sorted(c1.begin(), c1.end()))
        std::sort(c1.begin(), c1.end());
    if (!std::is_sorted(c2.begin(), c2.end()))
        std::sort(c2.begin(), c2.end());

    return std::includes(
        c2.begin(), c2.end(),
        c1.begin(), c1.end());
}
```

## "I Have No Use For All These!"

Before you are quick to exclaim that you have no use for these set algorithms, I like to show to you a typical selection example where you can use this. Imagine you are writing a subject enrollment website for college students. On the form, there are currently selected subjects which the student added, and the available subject dropdown which student can pick. It makes sense to remove subject from available dropdown after addition because you do not want the student to accidentally add the same subject twice. One way to compute leftover subjects available for selection, is to just subtract the selected set from the complete set of subjects with minus operator introduced in this article.

Article source code is hosted at [Github](https://github.com/shaovoon/cpp_set_operators)

Article related to the performance of set-intersection: [Intersection of ordered sets](http://0x80.pl/articles/set-intersection.html)

## History

* __30 Dec 2017__: First version
* __16 Jun 2018__: Version 1.1 Remove the `std::move` during return to enable the "Named Return Value Optimization"
