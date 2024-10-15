#include <Comparors/comparors.hpp>
#include <Utilities/utils.hpp>

#include <iostream>

using namespace std;

tuple<int, int> Comparors::RecMerge(vector<int> &vals, bool auxInfo)
{
	int cmps = 0, swps = 0;
	return Comparors::RecMerge(vals, 0, vals.size() - 1, cmps, swps);
}

tuple<int, int> Comparors::RecMerge(vector<int> &vals, int lo, int hi, int &cmps, int &swps)
{
	if (lo < hi)
	{
		int mid = ((hi - lo) >> 1) + lo;
		Comparors::RecMerge(vals, lo, mid, cmps, swps);
		Comparors::RecMerge(vals, mid + 1, hi, cmps, swps);
		Utilities::AuxMerger(vals, lo, mid, hi, cmps, swps);
	}
	++cmps;
	return { cmps, swps };
}

tuple<int, int> Comparors::ItMerge(vector<int> &vals, bool auxInfo)
{
	int cmps = 0, swps = 0;
	return Comparors::ItMerge(vals, 0, vals.size() - 1, cmps, swps);
}

tuple<int, int> Comparors::ItMerge(vector<int> &vals, int lo, int hi, int &cmps, int &swps)
{
	int size = vals.size();
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

tuple<int, int> Comparors::RecQuick(vector<int> &vals, bool auxInfo)
{
	int cmps = 0, swps = 0;
	return Comparors::RecQuick(vals, 0, vals.size() - 1, cmps, swps);
}

tuple<int, int> Comparors::RecQuick(vector<int> &vals, int lo, int hi, int &cmps, int &swps)
{
	if (lo < hi)
	{
		int p = Utilities::Partition(vals, lo, hi, cmps, swps);
		Comparors::RecQuick(vals, lo, p - 1, cmps, swps);
		Comparors::RecQuick(vals, p + 1, hi, cmps, swps);
	}
	++cmps;
	return { cmps, swps };
}
