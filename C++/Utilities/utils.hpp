#include <vector>

namespace Utilities
{
	enum class StartShape
	{
		Random,
		Sorted,
		Triangle,
		Jagged,
	};
	enum Traits
	{
		None = 0,
		Inverted = 1 << 0,
		Fuzzy = 1 << 1,
		Stairs = 1 << 2,
	};
	void Print(std::vector<int> &vals);
	void Create(std::vector<int> &vals, int size, int min, int max, StartShape start = StartShape::Random, int traits = Traits::None);
	void Shuffle(std::vector<int> &vals);
	void Swap(std::vector<int> &vals, int i, int j);
	void Flip(std::vector<int> &vals, int lo, int hi);
	void AuxMerger(std::vector<int> &vals, int lo, int mid, int hi);
	int BinarySearch(std::vector<int> &vals, int key, int lo, int hi);
}