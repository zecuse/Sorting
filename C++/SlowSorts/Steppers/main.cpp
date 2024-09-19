#include <chrono>
#include <iostream>

#include <Steppers/steppers.hpp>
#include <Utilities/utils.hpp>

using namespace std;

void selectSort(Utilities::StartShape shape, int traits)
{
	bool bench = false, shortInfo = false;
	vector<int> vals{};
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
	int size = shortInfo ? 1000 : 25, min = -10000, max = 10000;
	Utilities::Create(vals, size, min, max, shape, traits);
	if (shortInfo)
		cout << size << " elements, [" << min << ", " << max << "]" << endl;
	else
	{
		cout << "Before sort:\t";
		Utilities::Print(vals);
	}

	char cont = 'y';
	while (cont == 'y')
	{
		bool ran = true;
		char sort = ' ';
		cout << "Select a sorting algorithm\n";
		cout << "1. Bubble\n";
		cout << "2. Cocktail\n";
		cout << "3. Gnome\n";
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
				Utilities::Print(vals);
			}
		}

		cout << "Perform another? [y/n]: ";
		cin >> cont;
		if (cont == 'y')
			Utilities::Create(vals, size, min, max, shape, traits);
	}
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
			switch (sha)
			{
			case 'r':
				cout << "Random";
				break;
			case 's':
				cout << "Sorted";
				break;
			case 't':
				cout << "Triangle";
				break;
			case 'j':
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
			options(shape, traits);
			break;
		}
	}
	return 0;
}