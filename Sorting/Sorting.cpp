#include <iostream>
#include <time.h>
#include <vector>

#include "Sorter.h"

bool verify(int *vals, int n)
{
	for (int ii = 1; ii < n; ++ii)
		if (vals[ii - 1] > vals[ii])
			return false;
	return true;
}

bool allTrue(bool *cases, int n)
{
	for (int ii = 0; ii < n; ++ii)
		if (!cases[ii])
			return false;
	return true;
}

struct Point
{
	double x;
	double y;

	Point(double xx, double yy)
	{
		x = xx;
		y = yy;
	}
};

void LagrangePoints(std::vector<Point> *dataset)
{
	(*dataset).push_back(Point(0, 0));
	(*dataset).push_back(Point(0.5, 0.15));
	(*dataset).push_back(Point(0.75, 0.35));
	(*dataset).push_back(Point(0.9, 0.7));
	(*dataset).push_back(Point(1, 1));
}

//Lagrange Interpolation of val from the dataset of Points.
// n    n
// Σ yᵢ*Π (x - xⱼ)/(xᵢ - xⱼ)
//i=0  j=0,j!=i
double Lagrange(std::vector<Point> dataset, double val)
{
	double result = 0;

	for (Point xy1 : dataset)
	{
		double term = xy1.y;
		for (Point xy2 : dataset)
		{
			if (xy1.x != xy2.x)
			{
				term *= (val - xy2.x) / (xy1.x - xy2.x);
			}
		}
		result += term;
	}

	return result;
}

int main()
{
	//Lagrange Interpolation Test
	//std::vector<Point> dataset;
	//LagrangePoints(&dataset);
	//std::cout << Lagrange(dataset, 0) << std::endl;
	//std::cout << Lagrange(dataset, 0.5) << std::endl;
	//std::cout << Lagrange(dataset, 1) << std::endl;
	//std::cout << Lagrange(dataset, 0.25) << std::endl;

	//Sorter Test
	const int SIZE = 1024;
	const int NUMCASES = 1000;
	const int SHUFFLES = 50;
	int max = 10000, min = 0;
	srand(time(0));
	int vals[SIZE];
	bool cases[NUMCASES];

	for (int ii = 0; ii < SIZE; ++ii)
		vals[ii] = rand() % (max - min) + min;
	for (int ii = 0; ii < NUMCASES; ++ii)
		cases[ii] = false;

	Sorter sort;
	for (int ii = 0; ii < NUMCASES; ++ii)
	{
		for(int jj = 0; jj < SHUFFLES; ++jj)
			sort.Shuffle(vals, SIZE);
		sort.Bubble(vals, SIZE);
		cases[ii] = verify(vals, SIZE);
	}
	std::cout << "Bubble: " << (allTrue(cases, NUMCASES) ? "good" : "bad") << std::endl;

	return 0;
}