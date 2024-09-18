#include <Utilities/utils.hpp>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <string>

using namespace std;

void Utilities::Print(vector<int> &vals)
{
	auto fold = [](string res, int val)
	{
		return move(res) + ", " + to_string(val);
	};
	string print = accumulate(next(vals.begin()), vals.end(), to_string(vals[0]), fold);
	cout << print << endl;
}

void Utilities::Create(vector<int> &vals, int size, int min, int max)
{
	random_device dev{};
	default_random_engine rng{dev()};
	uniform_int_distribution dist{min, max};
	while (size-- > 0)
		vals.push_back(dist(rng));
}

void Utilities::Shuffle(vector<int> &vals)
{
	random_device dev{};
	default_random_engine rng{dev()};
	shuffle(vals.begin(), vals.end(), rng);
}

void Utilities::Swap(vector<int> &vals, int i, int j)
{
	swap(vals[i], vals[j]);
}

void Utilities::Flip(vector<int> &vals, int lo, int hi)
{
	while (lo < hi)
		swap(vals[lo++], vals[hi--]);
}

void Utilities::AuxMerger(vector<int> &vals, int lo, int mid, int hi)
{
	int left = lo, right = mid + 1, tmp = 0;
	vector<int> aux(hi - lo + 1);
	while (left <= mid && right <= hi)
	{
		if (vals[left] < vals[right])
			aux[tmp++] = vals[left++];
		else
			aux[tmp++] = vals[right++];
	}
	while (left <= mid)
		aux[tmp++] = vals[left++];
	for (int i = 0; i < tmp; ++i)
		vals[i + lo] = aux[i];
}

int Utilities::BinarySearch(vector<int> &vals, int key, int lo, int hi)
{
	int mid = -1;
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