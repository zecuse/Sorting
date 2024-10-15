#include <Pickers/pickers.hpp>
#include <Utilities/utils.hpp>

#include <iostream>

using namespace std;

tuple<int, int> Pickers::SelectionSort(vector<int> &vals, bool auxInfo)
{
	int runs = vals.size() - 1, cmps = 0, swps = 0;
	auto findMin = [](int a, int b) { return a < b; };
	for (int base = 0, min = base; base <= runs; min = ++base)
	{
		min = Utilities::FindExtreme(vals, min, runs, findMin, cmps);
		if (base != min)
			Utilities::Swap(vals, base, min, swps);
		++cmps;
	}
	return { cmps, swps };
}

tuple<int, int> Pickers::PancakeSort(vector<int> &vals, bool auxInfo)
{
	int runs = vals.size() - 1, cmps = 0, swps = 0;
	auto findMax = [](int a, int b) { return a > b; };
	for (int top = runs, max = top; top > 0; max = --top)
	{
		max = Utilities::FindExtreme(vals, 0, top, findMax, cmps);
		if (max != top)
		{
			if (max != 0)
				Utilities::Flip(vals, 0, max, swps);
			++cmps;
			Utilities::Flip(vals, 0, top, swps);
		}
		++cmps;
	}
	return { cmps, swps };
}

tuple<int, int> Pickers::InsertionSort(vector<int> &vals, bool auxInfo)
{
	int runs = vals.size(), cmps = 0, swps = 0;
	for (int i = 1; i < runs; ++i)
	{
		int idx = Utilities::BinarySearch(vals, vals[i], 0, i - 1, cmps);
		for (int j = i - 1; j >= idx && vals[j] != vals[j + 1]; --j)
			Utilities::Swap(vals, j, j + 1, swps);
	}
	return { cmps, swps };
}

// OEIS sequence A102549 (finite)
tuple<int, int> Pickers::ShellSortSimple(vector<int> &vals, bool auxInfo)
{
	vector<int> gaps{ 1750, 701, 301, 132, 57, 23, 10, 4, 1 };
	return Pickers::ShellSort(vals, gaps, auxInfo);
}

// OEIS sequence A366726 (infinite)
tuple<int, int> Pickers::ShellSortGamma(vector<int> &vals, bool auxInfo)
{
	vector<int> gaps{};
	int ins = 1;
	float gamma = 2.243609061420001, power = gamma;
	while (ins < vals.size())
	{
		gaps.insert(gaps.begin(), ins);
		power *= gamma;
		ins = ceil((power - 1) / (gamma - 1));
	}
	return Pickers::ShellSort(vals, gaps, auxInfo);
}

tuple<int, int> Pickers::ShellSort(vector<int> &vals, vector<int> &gaps, bool auxInfo)
{
	if (auxInfo)
	{
		cout << "The following gaps were used for the shells:" << endl;
		Utilities::PrintVals(gaps);
	}

	int runs = vals.size(), cmps = 0, swps = 0;
	for (int gap : gaps)
	{
		for (int i = gap; i < runs; ++i)
		{
			for (int min = i; min >= gap && vals[min - gap] > vals[min]; min -= gap)
			{
				++cmps;
				Utilities::Swap(vals, min, min - gap, swps);
			}
			++cmps;
		}
	}
	return { cmps, swps };
}
