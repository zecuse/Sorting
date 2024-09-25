#include <chrono>
#include <numeric>
#include <iostream>

#include <Pickers/pickers.hpp>
#include <Utilities/utils.hpp>

using namespace std;

void getStats(vector<int> stats, int &lo, float &avg, int &hi)
{
	lo = *ranges::min_element(stats);
	hi = *ranges::max_element(stats);
	avg = accumulate(next(stats.begin()), stats.end(), stats[0]) / static_cast<float>(stats.size());
}

void doSort(tuple<int, int>(*sort)(vector<int>&), bool bench, vector<int> vals, int size, int min, int max, Utilities::StartShape shape, int traits)
{
	int runs = 100, curr = 0, lo = INT_MAX, hi = INT_MIN, fails = 0, cnt = 0;
	float avg = 0.0f;
	vector<int> comps{}, swaps{};
	chrono::duration<double, milli> loT, hiT, avgT{ 0 };
	vector<chrono::duration<double, milli>> times{};

	do
	{
		if (curr != 0)
			Utilities::Create(vals, size, min, max, shape, traits);
		auto start = chrono::high_resolution_clock::now();
		auto [cmps, swps] = sort(vals);
		auto end = chrono::high_resolution_clock::now();
		auto time = chrono::duration<double, milli>(end - start);
		comps.push_back(cmps);
		swaps.push_back(swps);
		times.push_back(time);

		bool check = true;
		int i = 0;
		for (i = 0; check && i < vals.size() - 1; ++i)
			if (vals[i] > vals[i + 1])
				check = false;
		if (!check && cnt++ == 0)
			cout << format("Failed to sort!!! vals[{}] = {} > vals[{}] = {}", i - 1, vals[i - 1], i, vals[i]) << endl;
	} while (bench && ++curr != runs);
	if (cnt > 0)
		cout << format("There were {} failures!", cnt) << endl;
	if (bench)
		cout << format("Benchmark ran {} times.", runs) << endl;

	getStats(comps, lo, avg, hi);
	cout << format("This algo made [{}, {:.3f}, {}] compares ", lo, avg, hi);
	getStats(swaps, lo, avg, hi);
	cout << format("and performed [{}, {:.3f}, {}] swaps.", lo, avg, hi) << endl;

	loT = *ranges::min_element(times);
	hiT = *ranges::max_element(times);
	for (auto &time : times)
		avgT += time;
	avgT /= static_cast<int>(times.size());
	cout << format("Took [{}ms, {:.4f}ms, {}ms]", loT.count(), avgT.count(), hiT.count()) << endl;
}

void selectSort(Utilities::StartShape shape, int traits)
{
	bool bench = false, shortInfo = true;
	int size = shortInfo ? 1000 : 30, min = shortInfo ? -10000 : 0, max = 10000;
	vector<int> vals{};
	char cont = 'y';

	do
	{
		Utilities::Clear();
		Utilities::Create(vals, size, min, max, shape, traits);
		Utilities::PrintShapeTraits(shape, traits);
		if (shortInfo)
			cout << format("{} elements, [{}, {}]", size, min, max) << endl;
		else
		{
			cout << "Before sort:\t";
			Utilities::PrintVals(vals);
		}

		bool ran = true;
		char opt = ' ', sort = ' ';
		int runs = 1;
		cout << "Select a sorting algorithm\n";
		cout << "1. Selection\n";
		cout << "2. Insertion\n";
		cout << "b#. Benchmark\n";
		cout << "c##. Compare\n";
		cin >> opt;

		if (opt == 'c')
			++runs;
		while (runs-- > 0)
		{
			if (opt == 'b' || opt == 'c')
			{
				bench = true;
				cin >> sort;
			}
			else
				sort = opt;
			switch (sort)
			{
			case '1':
				doSort(Pickers::SelectionSort, bench, vals, size, min, max, shape, traits);
				break;
			case '2':
				doSort(Pickers::InsertionSort, bench, vals, size, min, max, shape, traits);
				break;
			default:
				cout << "Failed to select a valid sort." << endl;
				ran = false;
			}
			if (ran && !shortInfo)
			{
				cout << "After sort:\t";
				Utilities::PrintVals(vals);
			}
			if (runs == 1)
				Utilities::Create(vals, size, min, max, shape, traits);
		}

		cout << "Perform another? [y/n]: ";
		cin >> cont;
	} while (cont == 'y');
}

void options(Utilities::StartShape &shape, int &traits)
{
	char sel = ' ', sha = 'r', tra = 'n';
	string shapeSel;
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
				shapeSel = "Random";
				break;
			case Utilities::StartShape::Sorted:
				shapeSel = "Sorted";
				break;
			case Utilities::StartShape::Triangle:
				shapeSel = "Triangle";
				break;
			case Utilities::StartShape::Jagged:
				shapeSel = "Jagged";
				break;
			}
			cout << shapeSel << endl;
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
			default:
				cout << format("{} is an invalid selection. Reverting to {}.", sha, shapeSel) << endl;
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
					cout << format("{} is an invalid selection.", tra) << endl;
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
		if (sel != 'q')
			Utilities::Clear();
	}
	return 0;
}