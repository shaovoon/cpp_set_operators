#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cctype>

namespace normal_examples
{
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
			std::cout << n << ' ';
	}

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
			std::cout << i << ' ';
		}
		std::cout << '\n';
	}

	void set_difference_example() 
	{
		std::vector<int> v1{ 1, 2, 5, 5, 5,    9 };
		std::vector<int> v2{	2, 5,       7 };
		std::sort(v1.begin(), v1.end());
		std::sort(v2.begin(), v2.end());

		std::vector<int> diff;

		std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
			std::inserter(diff, diff.begin()));

		for (auto i : v1) std::cout << i << ' ';
		std::cout << "minus ";
		for (auto i : v2) std::cout << i << ' ';
		std::cout << "is: ";

		for (auto i : diff) std::cout << i << ' ';
		std::cout << '\n';
	}

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
			std::cout << n << ' ';
	}

	void is_superset_example()
	{
		std::vector<char> v1{ 'a', 'b', 'c', 'f', 'h', 'x' };
		std::vector<char> v2{ 'a', 'b', 'c' };
		std::vector<char> v3{ 'a', 'c' };
		std::vector<char> v4{ 'g' };
		std::vector<char> v5{ 'a', 'c', 'g' };
		std::sort(v1.begin(), v1.end());
		std::sort(v2.begin(), v2.end());
		std::sort(v3.begin(), v3.end());
		std::sort(v4.begin(), v4.end());
		std::sort(v5.begin(), v5.end());

		for (auto i : v1) std::cout << i << ' ';
		std::cout << "\nincludes:\n" << std::boolalpha;

		for (auto i : v2) std::cout << i << ' ';
		std::cout << ": " << std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << '\n';
		for (auto i : v3) std::cout << i << ' ';
		std::cout << ": " << std::includes(v1.begin(), v1.end(), v3.begin(), v3.end()) << '\n';
		for (auto i : v4) std::cout << i << ' ';
		std::cout << ": " << std::includes(v1.begin(), v1.end(), v4.begin(), v4.end()) << '\n';
		for (auto i : v5) std::cout << i << ' ';
		std::cout << ": " << std::includes(v1.begin(), v1.end(), v5.begin(), v5.end()) << '\n';

		auto cmp_nocase = [](char a, char b) {
			return std::tolower(a) < std::tolower(b);
		};

		std::vector<char> v6{ 'A', 'B', 'C' };
		for (auto i : v6) std::cout << i << ' ';
		std::cout << ": (case-insensitive) "
			<< std::includes(v1.begin(), v1.end(), v6.begin(), v6.end(), cmp_nocase)
			<< '\n';
	}

}