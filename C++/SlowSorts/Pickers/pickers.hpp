#include <tuple>
#include <vector>

namespace Pickers
{
	std::tuple<int, int> SelectionSort(std::vector<int> &vals, bool auxInfo);
	std::tuple<int, int> PancakeSort(std::vector<int> &vals, bool auxInfo);
	std::tuple<int, int> InsertionSort(std::vector<int> &vals, bool auxInfo);
	std::tuple<int, int> ShellSortSimple(std::vector<int> &vals, bool auxInfo);
	std::tuple<int, int> ShellSortGamma(std::vector<int> &vals, bool auxInfo);
	std::tuple<int, int> ShellSort(std::vector<int> &vals, std::vector<int> &gaps, bool auxInfo);
}