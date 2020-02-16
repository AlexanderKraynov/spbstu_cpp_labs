#ifndef LABS_LABS_DATASTRUCT_HPP
#define LABS_LABS_DATASTRUCT_HPP

#include <string>
#include <iostream>
#include "Manipulators.hpp"

struct DataStruct
{
  int key1{};
  int key2{};
  std::string str;
  DataStruct(int k1, int k2, std::string s);
  DataStruct() = default;
};

std::ostream &operator<<(std::ostream &out, const DataStruct &dataStruct);
std::istream &operator>>(std::istream &input, char);
std::istream &operator>>(std::istream &in, DataStruct &dataStruct);

#endif
