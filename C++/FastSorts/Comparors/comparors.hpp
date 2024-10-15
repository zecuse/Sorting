#include <tuple>
#include <vector>

namespace Comparors
{
	std::tuple<int, int> RecMerge(std::vector<int> &vals, bool auxInfo);
	std::tuple<int, int> RecMerge(std::vector<int> &vals, int lo, int hi, int &cmps, int &swps);
	std::tuple<int, int> ItMerge(std::vector<int> &vals, bool auxInfo);
	std::tuple<int, int> ItMerge(std::vector<int> &vals, int lo, int hi, int &cmps, int &swps);
	std::tuple<int, int> RecQuick(std::vector<int> &vals, bool auxInfo);
	std::tuple<int, int> RecQuick(std::vector<int> &vals, int lo, int hi, int &cmps, int &swps);
}