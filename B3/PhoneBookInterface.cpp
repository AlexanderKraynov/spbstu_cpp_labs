#include <iostream>
#include "PhoneBookInterface.hpp"

const std::string current = "current";
const std::string invalidBookmark = "<INVALID BOOKMARK>\n";
const std::string empty = "<EMPTY>\n";

PhoneBookInterface::PhoneBookInterface()
{
  bookmarks.insert({current, phonebook.begin()});
}

void PhoneBookInterface::add(const PhoneBook::record_t &record)
{
  phonebook.push_back(record);

  if (std::next(phonebook.begin()) == phonebook.end())
  {
    revalidate();
  }
}

void PhoneBookInterface::store(const std::string &currBookmark, const std::string &newBookmark)
{
  if (bookmarks.find(currBookmark) == bookmarks.end() || bookmarks.find(newBookmark) != bookmarks.end())
  {
    throw std::invalid_argument(invalidBookmark);
  }
  if (phonebook.empty())
  {
    throw std::out_of_range(empty);
  }
  bookmarks.insert({newBookmark, bookmarks.at(currBookmark)});
}

void PhoneBookInterface::insertBefore(const std::string &bookmark, const PhoneBook::record_t &record)
{
  if (bookmarks.find(bookmark) == bookmarks.end())
  {
    throw std::invalid_argument(invalidBookmark);
  }
  phonebook.insert(bookmarks.at(bookmark), record);
  revalidate();
}

void PhoneBookInterface::insertAfter(const std::string &bookmark, const PhoneBook::record_t &record)
{
  if (bookmarks.find(bookmark) == bookmarks.end())
  {
    throw std::invalid_argument(invalidBookmark);
  }
  auto it = bookmarks.at(bookmark);
  it++;
  if (it == phonebook.end())
  {
    phonebook.push_back(record);
  }
  else
  {
    phonebook.insert(it, record);
  }
  revalidate();
}

void PhoneBookInterface::remove(const std::string &bookmark)
{
  auto it = bookmarks.find(bookmark);
  if (it == bookmarks.end())
  {
    throw std::invalid_argument(invalidBookmark);
  }

  if (phonebook.empty())
  {
    throw std::out_of_range(empty);
  }

  auto removeIt = it->second;

  std::for_each(bookmarks.begin(), bookmarks.end(), [&](auto &i)
  {
    if (i.second == removeIt)
    {
      i.second = std::next(i.second);
    }
  });
  phonebook.erase(removeIt);
  revalidate();
}

void PhoneBookInterface::advance(const std::string &bookmark, long long distance)
{
  auto it = bookmarks.find(bookmark);
  if (it == bookmarks.end())
  {
    throw std::invalid_argument(invalidBookmark);
  }
  if (distance < 0)
  {
    long long margin = std::distance(it->second, phonebook.begin());
    distance = std::max(distance, margin);
  }
  else
  {
    long long margin = std::distance(it->second, --phonebook.end());
    distance = std::min(distance, margin);
  }

  std::advance(it->second, distance);
  bookmarks.at(bookmark) = it->second;
}

void PhoneBookInterface::show(const std::string &bookmark)
{
  auto it = bookmarks.find(bookmark);
  if (it == bookmarks.end())
  {
    throw std::invalid_argument(invalidBookmark);
  }
  if (phonebook.empty())
  {
    throw std::out_of_range(empty);
  }
  std::cout << it->second->phone << " " << it->second->name << std::endl;
}

void PhoneBookInterface::revalidate()
{
  if (phonebook.empty())
  {
    std::for_each(bookmarks.begin(), bookmarks.end(), [&](auto &bookmark)
    {
      bookmark.second = phonebook.end();
    });
    return;
  }

  std::for_each(bookmarks.begin(), bookmarks.end(), [&](auto &bookmark)
  {
    if (bookmark.second == phonebook.end())
    {
      bookmark.second = std::prev(phonebook.end());
    }
  });
}

void PhoneBookInterface::moveToFirst(const std::string &bookmark)
{
  if (bookmarks.find(bookmark) == bookmarks.end())
  {
    throw std::invalid_argument(invalidBookmark);
  }
  bookmarks.at(bookmark) = phonebook.begin();
}

void PhoneBookInterface::moveToLast(const std::string &bookmark)
{
  if (bookmarks.find(bookmark) == bookmarks.end())
  {
    throw std::invalid_argument(invalidBookmark);
  }
  if (!phonebook.empty())
  {
    bookmarks.at(bookmark) = --phonebook.end();
  }
  else
    throw std::out_of_range(empty);
}
