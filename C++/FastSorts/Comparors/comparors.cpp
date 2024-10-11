#include <Comparors/comparors.hpp>
#include <Utilities/utils.hpp>

#include <iostream>

using namespace std;

tuple<int, int> Comparors::RecMerge(vector<int> &vals, bool auxInfo)
{
	int cmps = 0, swps = 0;
	return RecMerger(vals, 0, vals.size(), cmps, swps);
}

tuple<int, int> Comparors::RecMerger(vector<int> &vals, int lo, int hi, int &cmps, int &swps)
{
	if (lo < hi)
	{
		int mid = ((hi - lo) >> 1) + lo;
		RecMerger(vals, lo, mid, cmps, swps);
		RecMerger(vals, mid + 1, hi, cmps, swps);
		Utilities::AuxMerger(vals, lo, mid, hi, cmps, swps);
	}
	++cmps;
	return { cmps, swps };
}

tuple<int, int> Comparors::ItMerge(vector<int> &vals, bool auxInfo)
{
	int size = vals.size(), cmps = 0, swps = 0;
	for (int width = 1; width < size; width <<= 1)
	{
		for (int lo = 0; lo < size; lo += width << 1)
		{
			int mid = min(lo + width - 1, size - 1);
			int hi = min(lo + (width << 1) - 1, size - 1);
			Utilities::AuxMerger(vals, lo, mid, hi, cmps, swps);
		}
	}
	return { cmps, swps };
}
