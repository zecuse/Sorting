#include <chrono>
#include <numeric>
#include <iostream>

#include <Steppers/steppers.hpp>
#include <Utilities/utils.hpp>

using namespace std;

void getLoAvgHi(vector<int> stats, int &lo, float &avg, int &hi)
{
	lo = *ranges::min_element(stats);
	hi = *ranges::max_element(stats);
	avg = accumulate(next(stats.begin()), stats.end(), stats[0]) / static_cast<float>(stats.size());
}

void selectSort(Utilities::StartShape shape, int traits)
{
	bool bench = false, shortInfo = true;
	int size = shortInfo ? 1000 : 30, min = shortInfo ? -10000 : 0, max = 10000;
	vector<int> vals{};
	auto sortFunc = [&](auto sorter)
	{
		int runs = 100, curr = 0, lo = INT_MAX, hi = INT_MIN;
		float avg = 0.0f;
		vector<int> shorts{}, comps{}, swaps{};
		chrono::duration<double, milli> loT, hiT, avgT{ 0 };
		vector<chrono::duration<double, milli>> times{};
		do
		{
			if (curr != 0)
				Utilities::Create(vals, size, min, max, shape, traits);
			auto start = chrono::high_resolution_clock::now();
			auto [saved, cmps, swps] = sorter(vals);
			auto end = chrono::high_resolution_clock::now();
			auto time = chrono::duration<double, milli>(end - start);
			shorts.push_back(saved);
			comps.push_back(cmps);
			swaps.push_back(swps);
			times.push_back(time);
		} while (bench && ++curr != runs);
		if (bench)
			cout << "Benchmark ran " << runs << " times." << endl;

		if (shorts[0] > 0)
		{
			getLoAvgHi(shorts, lo, avg, hi);
			cout << "Short circuit saved " << format("[{}, {:.3f}, {}]", lo, avg, hi) << " out of ";
			cout << vals.size() << " runs." << endl;
		}
		getLoAvgHi(comps, lo, avg, hi);
		cout << "This algo made " << format("[{}, {:.3f}, {}]", lo, avg, hi) << " compares and performed ";
		getLoAvgHi(swaps, lo, avg, hi);
		cout << format("[{}, {:.3f}, {}]", lo, avg, hi) << " swaps." << endl;

		loT = *ranges::min_element(times);
		hiT = *ranges::max_element(times);
		for (auto &time : times)
			avgT += time;
		avgT /= static_cast<int>(times.size());
		cout << "Took [" << loT << ", " << avgT << ", " << hiT << "]" << endl;
	};

	char cont = 'y';
	do
	{
		Utilities::Clear();
		Utilities::Create(vals, size, min, max, shape, traits);
		Utilities::PrintShapeTraits(shape, traits);
		if (shortInfo)
			cout << size << " elements, [" << min << ", " << max << "]" << endl;
		else
		{
			cout << "Before sort:\t";
			Utilities::PrintVals(vals);
		}

		bool ran = true;
		char sort = ' ';
		cout << "Select a sorting algorithm\n";
		cout << "1. Bubble\n";
		cout << "2. Cocktail\n";
		cout << "3. Gnome\n";
		cout << "4. Comb\n";
		cout << "b#. Benchmark\n";
		cin >> sort;

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
		case '4':
			sortFunc(Steppers::CombSort);
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
			if (!shortInfo)
			{
				cout << "After sort:\t";
				Utilities::PrintVals(vals);
			}
		}

		cout << "Perform another? [y/n]: ";
		cin >> cont;
	} while (cont == 'y');
}

void options(Utilities::StartShape &shape, int &traits)
{
	char sel = ' ', sha = 'r', tra = 'n';
	while (sel != 'b')
	{
		cout << "These are the available options\n";
		cout << "s. Starting shape\n";
		cout << "t. Traits\n";
		cout << "b. Back\n";
		cin >> sel;

		switch (sel)
		{
		case 's':
			cout << "These are the available starting shapes the data can take.\n";
			cout << "r. Random - Completely random order.\n";
			cout << "s. Sorted - Already sorted.\n";
			cout << "t. Triangle - Left half non-decreasing, right half non-increasing.\n";
			cout << "j. Jagged - Non-decreasing for a small portion, then reset and repeat.\n";
			cout << "b. Back - Return.\n";
			cout << "Current shape is: ";
			switch (shape)
			{
			case Utilities::StartShape::Random:
				cout << "Random";
				break;
			case Utilities::StartShape::Sorted:
				cout << "Sorted";
				break;
			case Utilities::StartShape::Triangle:
				cout << "Triangle";
				break;
			case Utilities::StartShape::Jagged:
				cout << "Jagged";
				break;
			}
			cout << endl;
			cin >> sha;
			switch (sha)
			{
			case 'r':
				shape = Utilities::StartShape::Random;
				break;
			case 's':
				shape = Utilities::StartShape::Sorted;
				break;
			case 't':
				shape = Utilities::StartShape::Triangle;
				break;
			case 'j':
				shape = Utilities::StartShape::Jagged;
				break;
			}
			break;
		case 't':
			while (tra != 'b')
			{
				cout << "These are the available traits the data can start as. lower = on, UPPER = OFF\n";
				cout << "n. None - No trait.\n";
				cout << "i. Inverted - Invert the shape, applied last.\n";
				cout << "f. Fuzzy - Blur each value based on its surrounding neighbors. I.e. creates near sorted data.\n";
				cout << "s. Stairs - Force repeat the same value.\n";
				cout << "b. Back - Return.\n";
				cout << "Current traits include: ";
				if ((traits & Utilities::Traits::Inverted) == Utilities::Traits::Inverted)
					cout << "Inverted ";
				if ((traits & Utilities::Traits::Fuzzy) == Utilities::Traits::Fuzzy)
					cout << "Fuzzy ";
				if ((traits & Utilities::Traits::Stairs) == Utilities::Traits::Stairs)
					cout << "Stairs ";
				cout << endl;
				cin >> tra;
				switch (tra)
				{
				case 'N':
				case 'n':
					traits = Utilities::Traits::None;
					break;
				case 'i':
					traits |= Utilities::Traits::Inverted;
					break;
				case 'I':
					traits &= ~Utilities::Traits::Inverted;
					break;
				case 'f':
					traits |= Utilities::Traits::Fuzzy;
					break;
				case 'F':
					traits &= ~Utilities::Traits::Fuzzy;
					break;
				case 's':
					traits |= Utilities::Traits::Stairs;
					break;
				case 'S':
					traits &= ~Utilities::Traits::Stairs;
					break;
				default:
					cout << tra << " is an invalid selection.\n";
				}
			}
			break;
		}
		Utilities::Clear();
	}
}

int main()
{
	char sel = ' ';
	Utilities::StartShape shape = Utilities::StartShape::Random;
	int traits = Utilities::Traits::None;
	while (sel != 'q')
	{
		cout << "Select an option\n";
		cout << "s. Sort\n";
		cout << "o. Options\n";
		cout << "q. Quit\n";
		cin >> sel;

		switch (sel)
		{
		case 's':
			selectSort(shape, traits);
			break;
		case 'o':
			Utilities::Clear();
			options(shape, traits);
			break;
		}
		Utilities::Clear();
	}
	return 0;
}