#include <Pickers/pickers.hpp>
#include <Utilities/utils.hpp>

using namespace std;

tuple<int, int> Pickers::SelectionSort(vector<int> &vals)
{
	int runs = vals.size(), cmps = 0, swps = 0;
	for (int base = 0, min = 0; base < runs - 1; min = ++base)
	{
		for (int i = min + 1; i < runs; ++i)
		{
			if (vals[i] < vals[min])
				min = i;
			++cmps;
		}
		if (base != min)
		{
			Utilities::Swap(vals, base, min);
			++swps;
		}
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
		{
			Utilities::Swap(vals, j, j + 1);
			++swps;
		}
	}
	return { cmps, swps };
}
