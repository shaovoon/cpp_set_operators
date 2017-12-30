#pragma once

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

	return std::move(v_intersection);
}

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

	return std::move(v_symDifference);
}

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

	return std::move(dest1);
}

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

	return std::move(diff);
}

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
