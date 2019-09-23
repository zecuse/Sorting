#pragma once
class Sorter
{
public:
	void Shuffle(int *vals, int n);
	void Bubble(int *vals, int n);
	void Cocktail(int *vals, int n);
	void Gnome(int *vals, int n);
	void OddEven(int *vals, int n);
	void Comb(int *vals, int n);
	void Selection(int *vals, int n);
	void Pancake(int *vals, int n);
	void Insertion(int *vals, int n);
	void Shell(int *vals, int n);
	void Merge(int *vals, int lo, int hi);
	void ItMerge(int *vals, int n);
	void Quick(int *vals, int lo, int hi);
	void ItQuick(int *vals, int n);
	void TQuick(int *vals, int lo, int hi);
	void Pigeonhole(int *vals, int n);
	void Bucket(int *vals, int n, int b);
	void Counting(int *vals, int n);
	void Radix(int *vals, int n, int b);
	void Gravity(int *vals, int n);
private:
	void Swap(int *a, int *b);
	void Swapper(bool &sorted, int *vals, int n, int parity);
	void Flip(int *vals, int n);
	int BinarySearch(int *vals, int key, int lo, int hi);
	void Merger(int *vals, int lo, int mid, int hi);
	int Partition(int *vals, int lo, int hi);
	void TPartition(int *vals, int lo, int hi, int &left, int &right);
};

