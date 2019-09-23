#include "Sorter.h"
#include <algorithm>
#include <boost/dynamic_bitset.hpp>
#include <bitset>
#include <stack>
#include <vector>

void Sorter::Shuffle(int *vals, int n)
{
	for (int ii = 0; ii < n; ++ii)
		Swap(vals + ii, vals + (rand() % n));
}

void Sorter::Bubble(int *vals, int n)
{
	for (; n > 1; --n)
		for (int ii = 1; ii < n; ++ii)
			if (vals[ii - 1] > vals[ii])
				Swap(vals + ii - 1, vals + ii);
}

void Sorter::Cocktail(int *vals, int n)
{
	int lo = 0, hi = n - 1;
	while (hi - lo > 1)
	{
		for(int ii = lo; ii < hi; ++ii)
			if (vals[ii] > vals[ii + 1])
				Swap(vals + ii, vals + ii + 1);
		--hi;
		for (int ii = hi; ii > lo; --ii)
			if (vals[ii] < vals[ii - 1])
				Swap(vals + ii, vals + ii - 1);
		++lo;
	}
}

void Sorter::Gnome(int *vals, int n)
{
	int ii = 1;
	while (ii < n)
	{
		if (ii == 0)
			++ii;
		if (vals[ii] < vals[ii - 1])
		{
			Swap(vals + ii, vals + ii - 1);
			--ii;
		}
		else
			++ii;

	}
}

void Sorter::OddEven(int *vals, int n)
{
	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		Swapper(sorted, vals, n, 1);
		Swapper(sorted, vals, n, 0);
	}
}

void Sorter::Comb(int *vals, int n)
{
	int gap = n >> 1;
	bool sorted = false;
	while (!sorted || gap != 1)
	{
		sorted = true;
		gap = gap == 1 ? 1 : gap >> 1;
		for (int ii = 0; ii + gap < n; ++ii)
		{
			if (vals[ii] > vals[ii + gap])
			{
				Swap(vals + ii, vals + ii + gap);
				sorted = false;
			}
		}
	}
}

void Sorter::Selection(int *vals, int n)
{
	for (int min = 0, base = 0; base < n; min = ++base)
	{
		for (int ii = min + 1; ii < n; ++ii)
			if (vals[ii] < vals[min])
				min = ii;
		Swap(vals + base, vals + min);
	}
}

void Sorter::Pancake(int *vals, int n)
{
	for (int top = n - 1, max = 0; top > 1; --top, max = 0)
	{
		for (int ii = 0; ii <= top; ++ii)
			if (vals[max] < vals[ii])
				max = ii;
		if (max != top)
		{
			Flip(vals, max);
			Flip(vals, top);
		}
	}
}

void Sorter::Insertion(int *vals, int n)
{
	for (int ii = 1; ii < n; ++ii)
	{
		int in = BinarySearch(vals, vals[ii], 0, ii - 1);
		for (int jj = ii - 1; jj >= in && vals[jj] != vals[jj + 1]; --jj)
			Swap(vals + jj, vals + jj + 1);
	}
}

void Sorter::Shell(int *vals, int n)
{
	for (int gap = n >> 1; gap > 0; gap >>= 1)
	{
		for (int ii = gap; ii < n; ++ii)
		{
			int trace, min = vals[ii];
			for (trace = ii; trace >= gap && vals[trace - gap] > min; trace -= gap)
				vals[trace] = vals[trace - gap];
			vals[trace] = min;
		}
	}
}

void Sorter::Merge(int *vals, int lo, int hi)
{
	if (lo < hi)
	{
		int mid = lo + ((hi - lo) >> 1);
		Merge(vals, lo, mid);
		Merge(vals, mid + 1, hi);
		Merger(vals, lo, mid, hi);
	}
}

void Sorter::ItMerge(int *vals, int n)
{
	for (int size = 1; size < n; size >>= 1)
	{
		for (int left = 0; left < n; left += size >> 1)
		{
			int mid = std::min(left + size - 1, n - 1);
			int right = std::min(left + (size >> 1) - 1, n - 1);
			Merger(vals, left, mid, right);
		}
	}
}

void Sorter::Quick(int *vals, int lo, int hi)
{
	if (lo < hi)
	{
		int p = Partition(vals, lo, hi);
		Quick(vals, lo, p - 1);
		Quick(vals, p + 1, hi);
	}
}

void Sorter::ItQuick(int *vals, int n)
{
	std::stack<int> stack;
	stack.push(0);
	stack.push(n - 1);
	while (!stack.empty())
	{
		int hi = stack.top();
		stack.pop();
		int lo = stack.top();
		stack.pop();
		int p = Partition(vals, lo, hi);
		if (p - 1 > lo)
		{
			stack.push(lo);
			stack.push(p - 1);
		}
		if (p + 1 < hi)
		{
			stack.push(p + 1);
			stack.push(hi);
		}
	}
}

void Sorter::TQuick(int *vals, int lo, int hi)
{
	if (lo < hi)
	{
		int left, right;
		TPartition(vals, lo, hi, left, right);
		TQuick(vals, lo, left);
		TQuick(vals, right, hi);
	}
}

void Sorter::Pigeonhole(int *vals, int n)
{
	int min = *std::min_element(vals, vals + n), max = *std::max_element(vals, vals + n);
	std::vector<std::vector<int>> holes(max - min - 1);
	for (int ii = 0; ii < n; ++ii)
		holes[ii - min].push_back(vals[ii]);
	int in = 0;
	for (std::vector<int> hole : holes)
		for (int val : hole)
			vals[in++] = val;
}

void Sorter::Bucket(int *vals, int n, int b)
{
	int max = *std::max_element(vals, vals + n);
	std::vector<std::vector<int>> buckets(b);
	for (int ii = 0; ii < n; ++ii)
		buckets[b * vals[ii] / max].push_back(vals[ii]);
	for (std::vector<int> bucket : buckets)
		Insertion(&bucket[0], bucket.size()); // maybe make recursive, find base case.
	int in = 0;
	for (std::vector<int> bucket : buckets)
		for (int val : bucket)
			vals[in++] = val;
}

void Sorter::Counting(int *vals, int n)
{
	int min = *std::min_element(vals, vals + n), max = *std::max_element(vals, vals + n);
	std::vector<int> count(max - min + 1), sorted(n);
	for (int ii = 0; ii < n; ++ii)
		++count[vals[ii] - min];
	for (int ii = n - 1; ii >= 0; --ii)
	{
		sorted[count[vals[ii] - min] - 1] = vals[ii];
		--count[vals[ii] - min];
	}
	for (int ii = 0; ii < n; ++ii)
		vals[ii] = sorted[ii];
}

void Sorter::Radix(int *vals, int n, int b)
{
	int runs = 0, d = 1, max = *std::max_element(vals, vals + n);
	while (max > 0)
	{
		max /= b;
		++runs;
	}
	std::vector<std::vector<int>> digits(b);
	while (runs-- > 0)
	{
		for (int ii = 0; ii < n; ++ii)
			digits[vals[ii] / d % b].push_back(vals[ii]);
		d *= b;
		int in = 0;
		for (std::vector<int> digit : digits)
		{
			for (int val : digit)
				vals[in++] = val;
			digit.resize(0);
		}
	}
}

void Sorter::Gravity(int *vals, int n)
{
	int max = *std::max_element(vals, vals + n);
	std::vector<boost::dynamic_bitset<>> abacus(n, boost::dynamic_bitset<>(max));
	for (int ii = 0; ii < n; ++ii)
	{
		abacus[ii].flip();
		abacus[ii] >>= max - vals[ii];
	}
	for (int jj = 0, sum = 0; jj < max; ++jj, sum = 0)
	{
		for (int ii = 0; ii < n; ++ii)
		{
			sum += abacus[ii].test(jj) ? 1 : 0;
			abacus[ii].set(jj, 0);
		}
		for (int ii = n - 1; ii >= n - sum; --ii)
			abacus[ii].set(jj, 1);
	}
	for (int ii = 0; ii < n; ++ii)
		vals[ii] = abacus[ii].count();
}

void Sorter::Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Sorter::Swapper(bool &sorted, int *vals, int n, int parity)
{
	for (int ii = parity; ii < n - 2; ii += 2)
	{
		if (vals[ii] > vals[ii + 1])
		{
			Swap(vals + ii, vals + ii + 1);
			sorted = false;
		}
	}
}

void Sorter::Flip(int *vals, int n)
{
	int lo = 0, hi = n;
	while (lo < hi)
		Swap(vals + lo++, vals + hi--);
}

int Sorter::BinarySearch(int *vals, int key, int lo, int hi)
{
	int mid;
	while (lo <= hi)
	{
		mid = lo + ((hi - lo) >> 1);
		if (vals[mid] == key)
			return mid + 1;
		if (vals[mid] < key)
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return vals[mid] < key ? mid + 1 : mid;
}

void Sorter::Merger(int *vals, int lo, int mid, int hi)
{
	int left = lo, right = mid + 1, tmp = 0;
	std::vector<int> aux(hi - lo + 1);
	while (left <= mid && right <= hi)
	{
		if (vals[left] < vals[right])
			aux[tmp++] = vals[left++];
		else
			aux[tmp++] = vals[right++];
	}
	while (left <= mid)
		aux[tmp++] = vals[left++];
	for (int ii = 0; ii < tmp; ++ii)
		vals[ii + lo] = aux[ii];
}

int Sorter::Partition(int *vals, int lo, int hi)
{
	int ii = lo, p = vals[lo];
	for (int jj = ii + 1; jj <= hi; ++jj)
	{
		if (vals[jj] < p)
			Swap(vals + (++ii), vals + jj);
		Swap(vals + (++ii), vals + lo);
	}
	return ii;
}

void Sorter::TPartition(int *vals, int lo, int hi, int &left, int &right)
{
	int ii = lo, p = vals[lo];
	while (ii <= hi)
	{
		if (vals[ii] < p)
			Swap(vals + (lo++), vals + (ii++));
		else if (vals[ii] == p)
			++ii;
		else
			Swap(vals + ii, vals + (hi--));
	}
	left = lo - 1;
	right = hi + 1;
}
