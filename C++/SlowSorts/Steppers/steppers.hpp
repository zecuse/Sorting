#include <tuple>
#include <vector>

namespace Steppers
{
	std::tuple<int, int, int> BubbleSort(std::vector<int> &vals);
	std::tuple<int, int, int> CocktailSort(std::vector<int> &vals);
	std::tuple<int, int, int> GnomeSort(std::vector<int> &vals);
}