#include <Steppers/steppers.hpp>
#include <Utilities/utils.hpp>

using namespace std;

tuple<int, int, int> Steppers::BubbleSort(vector<int> &vals)
{
	int runs = vals.size(), cmps = 0, swps = 0;
	bool sorted = false;

	while (!sorted)
	{
		sorted = true;
		for (int i = 0; i < runs - 1; ++i)
		{
			if (vals[i] > vals[i + 1])
			{
				sorted = false;
				Utilities::Swap(vals, i, i + 1);
				++swps;
			}
			++cmps;
		}
		--runs;
	}

	return { runs, cmps, swps };
}

tuple<int, int, int> Steppers::CocktailSort(vector<int> &vals)
{
	int runs = vals.size(), cmps = 0, swps = 0;
	int left = 0, right = runs - 2;
	bool sorted = false;

	while (!sorted)
	{
		sorted = true;
		for (int i = left; i <= right; ++i)
		{
			if (vals[i] > vals[i + 1])
			{
				sorted = false;
				Utilities::Swap(vals, i, i + 1);
				++swps;
			}
			++cmps;
		}
		++left;
		--runs;
		if (sorted)
			break;
		sorted = true;
		for (int i = right; i >= left; --i)
		{
			if (vals[i - 1] > vals[i])
			{
				sorted = false;
				Utilities::Swap(vals, i, i - 1);
				++swps;
			}
			++cmps;
		}
		--right;
		--runs;
	}

	return { runs, cmps, swps };
}

tuple<int, int, int> Steppers::GnomeSort(vector<int> &vals)
{
	int runs = vals.size(), cmps = 0, swps = 0, i = 0;

	while (i < runs)
	{
		if (i == 0)
		{
			++i;
			++cmps;
		}
		if (vals[i] < vals[i - 1])
		{
			Utilities::Swap(vals, i, i - 1);
			++swps;
			--i;
		}
		else
			++i;
		++cmps;
	}

	return { -runs, cmps, swps };
}
