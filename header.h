#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class MyString
{
  char *str;

public:
  MyString() : str(nullptr) {}
  MyString(const char *newStr);
  MyString(const MyString &otherStr);
  MyString(char c);
  ~MyString();
  char *getStr();
  bool checkEmpty(const char &c, vector<char> &splitChars);
  void setStr(const char *newStr);
  friend ostream &operator<<(ostream &, const MyString &mystring);
  friend MyString operator+(const MyString &a, const MyString &b);
  vector<MyString> Split(vector<char> &splitChar, const bool &delEmptySpace);
  const MyString &operator=(const MyString &other);
};