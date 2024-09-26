#include <Pickers/pickers.hpp>
#include <Utilities/utils.hpp>

using namespace std;

tuple<int, int> Pickers::SelectionSort(vector<int> &vals)
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

tuple<int, int> Pickers::InsertionSort(vector<int> &vals)
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

tuple<int, int> Pickers::PancakeSort(vector<int> &vals)
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
