#ifndef LABS_LABS_STATISTICS_HPP
#define LABS_LABS_STATISTICS_HPP

#include <ostream>

class Statistics
{
public:
  Statistics();
  void operator()(int x);
  friend std::ostream &operator<<(std::ostream &out, const Statistics &statistics);
private:
  int max;
  int min;
  double average;
  size_t count;
  size_t countPositive;
  size_t countNegative;
  long long sumOdd;
  long long sumEven;
  int firstNumber;
  bool firstMatchesLast;
};

#endif
