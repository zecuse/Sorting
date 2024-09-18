#include <chrono>
#include <iostream>

#include <Steppers/steppers.hpp>
#include <Utilities/utils.hpp>

using namespace std;

void selectSort(vector<int> &vals)
{
	bool ran = true, bench = false;
	cout << "Select a sorting algorithm\n";
	cout << "1. Bubble\n";
	cout << "2. Cocktail\n";
	cout << "3. Gnome\n";
	cout << "b#. Benchmark\n";
	char sort = ' ';
	cin >> sort;
	auto sortFunc = [&](auto sorter)
	{
		int runs = 100, curr = 0;
		float shorts = 0.0f, comps = 0.0f, swaps = 0.0f;
		auto times = chrono::duration<double, milli>(0);
		do
		{
			if (curr != 0)
				Utilities::Shuffle(vals);
			auto start = chrono::high_resolution_clock::now();
			auto [saved, cmps, swps] = sorter(vals);
			auto end = chrono::high_resolution_clock::now();
			auto time = chrono::duration<double, milli>(end - start);
			shorts += saved;
			comps += cmps;
			swaps += swps;
			times += time;
		} while (bench && ++curr != runs);
		if (bench)
		{
			shorts /= runs;
			comps /= runs;
			swaps /= runs;
			times /= runs;
			cout << "Benchmark ran " << runs << " times." << endl;
		}
		if (shorts > 0)
			cout << "Short circuit saved " << shorts << " out of " << vals.size() << " runs." << endl;
		cout << "This algo made " << comps << " compares and performed " << swaps << " swaps." << endl;
		cout << "Took " << times << endl;
	};
	if (sort == 'b')
	{
		bench = true;
		cin >> sort;
	}
	switch (sort)
	{
	case '1':
		sortFunc(Steppers::BubbleSort);
		break;
	case '2':
		sortFunc(Steppers::CocktailSort);
		break;
	case '3':
		sortFunc(Steppers::GnomeSort);
		break;
	default:
		cout << "Failed to select a valid sort." << endl;
		ran = false;
	}
	if (ran)
	{
		bool check = true;
		int i;
		for (i = 0; check && i < vals.size() - 1; ++i)
			if (vals[i] > vals[i + 1])
				check = false;
		if (!check)
			cout << "Failed to sort!!! " << vals[i - 1] << " > " << vals[i] << endl;
	}
}

int main()
{
	bool shortInfo = true;
	int size = 1000, min = -10000, max = 10000;
	vector<int> vals{};
	Utilities::Create(vals, size, min, max);
	char cont = 'y';
	while (cont == 'y')
	{
		if (shortInfo)
			cout << size << " elements, [" << min << ", " << max << "]" << endl;
		else
		{
			cout << "Before sort:\t";
			Utilities::Print(vals);
		}
		selectSort(vals);
		if (!shortInfo)
		{
			cout << "After sort:\t";
			Utilities::Print(vals);
		}

		cout << "Perform another? [y/n]: ";
		cin >> cont;
		if (cont == 'y')
			Utilities::Shuffle(vals);
	}
	return 0;
}