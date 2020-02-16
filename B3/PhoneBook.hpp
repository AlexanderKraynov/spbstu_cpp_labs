#ifndef LABS_LABS_PHONEBOOK_HPP
#define LABS_LABS_PHONEBOOK_HPP

#include <string>
#include <list>

class PhoneBook
{
public:
  struct record_t
  {
    std::string name;
    std::string phone;
  };
  using iterator = std::list<record_t>::iterator;
  using const_iterator = std::list<record_t>::const_iterator;

  void push_back(const record_t &record);
  static void replace(iterator pos, const record_t &record);
  iterator erase(iterator pos);
  iterator insert(const_iterator pos, const record_t &record);

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  int size() const;
  bool empty() const;
private:
  std::list<record_t> data;
};

#endif
