#include <vector>

namespace Utilities
{
	void Print(std::vector<int> &vals);
	void Create(std::vector<int> &vals, int size, int min, int max);
	void Shuffle(std::vector<int> &vals);
	void Swap(std::vector<int> &vals, int i, int j);
	void Flip(std::vector<int> &vals, int lo, int hi);
	void AuxMerger(std::vector<int> &vals, int lo, int mid, int hi);
	int BinarySearch(std::vector<int> &vals, int key, int lo, int hi);
}