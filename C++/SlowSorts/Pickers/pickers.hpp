#include <tuple>
#include <vector>

namespace Pickers
{
	std::tuple<int, int> SelectionSort(std::vector<int> &vals);
	std::tuple<int, int> InsertionSort(std::vector<int> &vals);
	std::tuple<int, int> PancakeSort(std::vector<int> &vals);
}