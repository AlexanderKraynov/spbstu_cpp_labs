#include "DataStruct.hpp"

#include <utility>


DataStruct::DataStruct(int k1, int k2, std::string s) :
  key1(k1),
  key2(k2),
  str(std::move(s))
{
  if (abs(key1) > 5 || abs(key2) > 5)
  {
    throw std::invalid_argument("Key value should be [-5,5]");
  }
}


std::ostream &operator<<(std::ostream &out, const DataStruct &dataStruct)
{
  out << dataStruct.key1 << "," << dataStruct.key2 << "," << dataStruct.str << "\n";
  return out;
}

std::istream &operator>>(std::istream &in, DataStruct &dataStruct)
{
  int key1 = 0;
  int key2 = 0;
  in >> skipIsBlank >> key1 >> skipIsBlank >> ReadDelimiter(',') >> skipIsBlank >> skipIsBlank >> key2 >> skipIsBlank
     >> ReadDelimiter(',') >> skipIsBlank;
  std::string str;
  getline(in, str);
  if (str.empty())
  {
    in.setstate((std::ios_base::failbit));
    return in;
  }
  dataStruct = DataStruct(key1, key2, str);
  return in;
}
