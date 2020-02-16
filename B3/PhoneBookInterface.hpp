#ifndef LABS_LABS_PHONEBOOKINTERFACE_HPP
#define LABS_LABS_PHONEBOOKINTERFACE_HPP

#include <algorithm>
#include <map>
#include "PhoneBook.hpp"

class PhoneBookInterface
{
public:
  PhoneBookInterface();
  void add(const PhoneBook::record_t &record);
  void store(const std::string &currBookmark, const std::string &newBookmark);
  void insertBefore(const std::string &bookmark, const PhoneBook::record_t &record);
  void insertAfter(const std::string &bookmark, const PhoneBook::record_t &record);
  void remove(const std::string &bookmark);
  void show(const std::string &bookmark);
  void advance(const std::string &bookmark, long long distance);
  void moveToFirst(const std::string &);
  void moveToLast(const std::string &);

private:
  PhoneBook phonebook;
  std::map<std::string, PhoneBook::iterator> bookmarks;
  void revalidate();
};

#endif
