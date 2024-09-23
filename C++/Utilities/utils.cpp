#include <Utilities/utils.hpp>

#if defined _WIN32
#include <Windows.h>
#elif defined __unix__
#include <term.h>
#endif

#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <random>
#include <string>

using namespace std;

void Utilities::Clear()
{
#if defined _WIN32
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD cells;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	cells = screen.dwSize.X * screen.dwSize.Y;
	FillConsoleOutputCharacter(console, ' ', cells, topLeft, &written);
	FillConsoleOutputAttribute(console, screen.wAttributes, cells, topLeft, &written);
	SetConsoleCursorPosition(console, topLeft);
#elif defined __unix__
	setupterm(NULL, fileno(stdout), NULL);
	putp(tigetstr("clear"));
#endif
}

void Utilities::PrintShapeTraits(Utilities::StartShape shape, int traits)
{
	switch (shape)
	{
	case StartShape::Random:
		cout << "Random";
		break;
	case StartShape::Sorted:
		cout << "Sorted";
		break;
	case StartShape::Triangle:
		cout << "Triangle";
		break;
	case StartShape::Jagged:
		cout << "Jagged";
		break;
	}
	if ((traits & Utilities::Traits::Inverted) == Utilities::Traits::Inverted)
		cout << ", Inverted";
	if ((traits & Utilities::Traits::Fuzzy) == Utilities::Traits::Fuzzy)
		cout << ", Fuzzy";
	if ((traits & Utilities::Traits::Stairs) == Utilities::Traits::Stairs)
		cout << ", Stairs";
	cout << endl;
}

void Utilities::PrintVals(vector<int> &vals)
{
	auto fold = [](string res, int val)
	{
		return move(res) + ", " + format("{: 5d}", val);
	};
	string print = accumulate(next(vals.begin()), vals.end(), format("{: 5d}", vals[0]), fold);
	cout << print << endl;
}

void Utilities::Create(vector<int> &vals, int size, int min, int max, StartShape start, int traits)
{
	random_device dev{};
	default_random_engine rng{ dev() };
	uniform_int_distribution dist{ min, max };
	uniform_int_distribution smallDist{ 5, 50 };
	int ins, odd, cnt;

	vals.clear();
	switch (start)
	{
	case StartShape::Random:
		while (size-- > 0)
			vals.push_back(dist(rng));
		break;
	case StartShape::Sorted:
		ins = min + smallDist(rng);
		while (size-- > 0)
		{
			vals.push_back(ins);
			ins += smallDist(rng);
			ins = ins > max ? max : ins;
		}
		if ((traits & Traits::Inverted) == Traits::Inverted)
		{
			size = vals.size() - 1;
			for (int i = 0; i < size / 2; ++i)
				Utilities::Swap(vals, i, size - i);
		}
		break;
	case StartShape::Triangle:
		odd = size % 2;
		ins = min + smallDist(rng);
		while (vals.size() <= size / 2)
		{
			vals.push_back(ins);
			ins += smallDist(rng);
			ins = ins > max ? max : ins;
		}
		size += odd;
		size /= 2;
		while (size-- > 0)
		{
			ins -= smallDist(rng);
			ins = ins < min ? min : ins;
			vals.push_back(ins);
		}
		if ((traits & Traits::Inverted) == Traits::Inverted)
		{
			size = vals.size() / 2 + odd;
			for (int i = 0; i < size / 2; ++i)
				Utilities::Swap(vals, i, size - i);
			for (int i = size; i < size + size / 2; ++i)
				Utilities::Swap(vals, i, vals.size() - 1 - i);
		}
		break;
	case StartShape::Jagged:
		cnt = size / 10;
		while (size > 0)
		{
			ins = min + smallDist(rng);
			for (int i = 0; size > 0 && i < cnt; ++i, --size)
			{
				vals.push_back(ins);
				ins += smallDist(rng);
				ins = ins > max ? max : ins;
			}
		}
		if ((traits & Traits::Inverted) == Traits::Inverted)
		{
			size = vals.size() - 1;
			for (int i = 0; i < size / 2; ++i)
				Utilities::Swap(vals, i, size - i);
		}
		break;
	}
}

void Utilities::Shuffle(vector<int> &vals)
{
	random_device dev{};
	default_random_engine rng{ dev() };
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