#include "PhoneBook.hpp"

void PhoneBook::push_back(const PhoneBook::record_t &record)
{
  data.push_back(record);
}

void PhoneBook::replace(PhoneBook::iterator pos, const PhoneBook::record_t &record)
{
  *pos = record;
}

PhoneBook::iterator PhoneBook::erase(PhoneBook::iterator pos)
{
  return data.erase(pos);
}

PhoneBook::iterator PhoneBook::begin()
{
  return data.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return data.end();
}

PhoneBook::const_iterator PhoneBook::cbegin() const
{
  return data.cbegin();
}

PhoneBook::const_iterator PhoneBook::cend() const
{
  return data.cend();
}

int PhoneBook::size() const
{
  return data.size();
}

bool PhoneBook::empty() const
{
  return data.empty();
}

PhoneBook::iterator PhoneBook::insert(PhoneBook::const_iterator pos, const PhoneBook::record_t &record)
{
  return data.insert(pos, record);
}
