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
	void Clear();
	void PrintShapeTraits(StartShape shape, int traits);
	void PrintVals(std::vector<int> &vals);
	void Create(std::vector<int> &vals, int size, int min, int max, StartShape start = StartShape::Random, int traits = Traits::None);
	void Shuffle(std::vector<int> &vals);
	void Swap(std::vector<int> &vals, int i, int j);
	void Swap(std::vector<int> &vals, int i, int j, int &swps);
	int FindExtreme(std::vector<int> &vals, int lo, int hi, bool (*op)(int a, int b));
	int FindExtreme(std::vector<int> &vals, int lo, int hi, bool (*op)(int a, int b), int &cmps);
	void Flip(std::vector<int> &vals, int lo, int hi);
	void Flip(std::vector<int> &vals, int lo, int hi, int &swps);
	void AuxMerger(std::vector<int> &vals, int lo, int mid, int hi);
	void AuxMerger(std::vector<int> &vals, int lo, int mid, int hi, int &cmps, int &swps);
	int BinarySearch(std::vector<int> &vals, int key, int lo, int hi);
	int BinarySearch(std::vector<int> &vals, int key, int lo, int hi, int &cmps);
}