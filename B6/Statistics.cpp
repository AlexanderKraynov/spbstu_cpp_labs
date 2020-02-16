#include "Statistics.hpp"
#include <limits>
#include <algorithm>

Statistics::Statistics() :
  max(std::numeric_limits<int>::min()),
  min(std::numeric_limits<int>::max()),
  average(0),
  count(0),
  countPositive(0),
  countNegative(0),
  sumOdd(0),
  sumEven(0),
  firstNumber(0),
  firstMatchesLast(false)
{
}

void Statistics::operator()(int x)
{
  if (!count)
  {
    firstNumber = x;
  }
  max = std::max(x, max);
  min = std::min(x, min);
  count++;
  average = static_cast<double>(sumOdd + sumEven + x) / (count);
  if (x > 0)
  {
    countPositive++;
  }
  else if (x < 0)
  {
    countNegative++;
  }
  (x % 2 ? sumOdd : sumEven) += x;
  firstMatchesLast = firstNumber == x;
}

std::ostream &operator<<(std::ostream &out, const Statistics &statistics)
{
  if (statistics.count == 0)
  {
    out << "No Data";
    return out;
  }
  out << "Max: " << statistics.max << std::endl
      << "Min: " << statistics.min << std::endl
      << "Mean: " << std::fixed << statistics.average << std::endl
      << "Positive: " << statistics.countPositive << std::endl
      << "Negative: " << statistics.countNegative << std::endl
      << "Odd Sum: " << statistics.sumOdd << std::endl
      << "Even Sum: " << statistics.sumEven << std::endl
      << "First/Last Equal: " << (statistics.firstMatchesLast ? "yes" : "no") << std::endl;
  return out;
}
