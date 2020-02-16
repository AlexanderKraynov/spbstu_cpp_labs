#include <exception>
#include <vector>
#include <iterator>
#include <algorithm>
#include "boost/io/ios_state.hpp"
#include "DataStruct.hpp"

const auto keyComparator = [](const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.str.size() < rhs.str.size();
};

int main()
{
  try
  {
    boost::io::ios_flags_saver fs(std::cin);
    std::vector<DataStruct> data((std::istream_iterator<DataStruct>(std::cin >> std::noskipws)),
                                 std::istream_iterator<DataStruct>());
    if (!std::cin.eof())
    {
      throw std::invalid_argument("Input failed.");
    }
    std::sort(data.begin(), data.end(), keyComparator);
    std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout));
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
