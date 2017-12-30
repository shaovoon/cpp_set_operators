#pragma once

#include <iostream>
#include <vector>
#include <cctype>
#include "set_interection_operators.h"

namespace operator_examples
{
	void intersection_example()
	{
		std::vector<int> v1{ 1,2,3,4,5,6,7,8 };
		std::vector<int> v2{         5,  7,  9,10 };

		std::vector<int> v_intersection = s(v1) & s(v2);

		for (int n : v_intersection)
			std::cout << n << ' ';
	}

	void union_example()
	{
		std::vector<int> v1 = { 1, 2, 3, 4, 5 };
		std::vector<int> v2 = {       3, 4, 5, 6, 7 };

		std::vector<int> dest1 = s(v1) | s(v2);

		for (int n : dest1)
			std::cout << n << ' ';
	}

	void set_difference_example()
	{
		std::vector<int> v1{ 1, 2, 5, 5, 5, 9 };
		std::vector<int> v2{    2, 5,       7 };

		std::vector<int> diff = s(v1) - s(v2);

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

		std::vector<int> v_symDifference = s(v1) ^ s(v2);

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

		for (auto i : v1) std::cout << i << ' ';
		std::cout << "\nincludes:\n" << std::boolalpha;

		for (auto i : v2) std::cout << i << ' ';
		std::cout << ": " << (s(v1) >= s(v2)) << '\n';
		for (auto i : v3) std::cout << i << ' ';
		std::cout << ": " << (s(v1) >= s(v3)) << '\n';
		for (auto i : v4) std::cout << i << ' ';
		std::cout << ": " << (s(v1) >= s(v4)) << '\n';
		for (auto i : v5) std::cout << i << ' ';
		std::cout << ": " << (s(v1) >= s(v5)) << '\n';

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