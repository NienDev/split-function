#include "header.h"

MyString::MyString(const char *newStr)
{
  str = new char[strlen(newStr) + 1];

  str[strlen(newStr)] = '\0';
  strcpy(str, newStr);
}

MyString::MyString(const MyString &otherStr)
{
  if (this != &otherStr)
  {
    str = new char[strlen(otherStr.str) + 1];
    str[strlen(otherStr.str)] = '\0';
    strcpy(str, otherStr.str);
  }
}

MyString::~MyString()
{
  delete[] str;
}

ostream &operator<<(ostream &os, const MyString &myString)
{
  os << myString.str;
  return os;
}

char *MyString::getStr()
{
  return str;
}

void MyString::setStr(const char *newStr)
{
  delete[] str;
  str = new char[strlen(newStr) + 1];
  str[strlen(newStr)] = '\0';
  strcpy(str, newStr);
}

MyString operator+(const MyString &a, const MyString &b)
{
  int a_len = strlen(a.str);
  int b_len = strlen(b.str);
  int res_len = a_len + b_len;
  char *p = new char[res_len + 1]; // * plus 1 for the null at the end

  for (int i = 0; i < res_len; i++)
  {
    p[i] = i < a_len ? a.str[i] : b.str[i - a_len];
  }

  p[res_len] = '\0';

  MyString res(p);
  return res;
}

bool MyString::checkEmpty(const char &c, vector<char> &splitChars)
{
  for (int i = 0; i < splitChars.size(); i++)
  {
    if (c == splitChars[i])
      return false;
  }
  return true; // if there is any character that different from all the splitchars
}

vector<MyString> MyString::Split(vector<char> &splitChar, const bool &delEmptySpace)
{
  vector<MyString> res;
  res.push_back(*this);
  for (int i = 0; i < splitChar.size(); i++)
  {
    char splitCh = splitChar[i];
    vector<MyString> tmp_res; // store result after spliting 1 character
    int curSize = res.size();
    for (int j = 0; j < curSize; j++)
    {
      int start = 0; // starting index of each substring
      char *tmp = res[j].str;

      int tmp_len = strlen(tmp);

      for (int k = 0; k < strlen(tmp); k++)
      {
        if (tmp[k] == splitCh)
        {
          if (k - 1 < start && k + 1 >= strlen(tmp))
          {
            MyString tmpObj(" ");
            tmp_res.push_back(tmpObj);
            MyString tmpObj1(" ");
            tmp_res.push_back(tmpObj1);
            tmp_len = -1;
          }
          else if (k - 1 < start || k + 1 >= strlen(tmp))
          {

            MyString tmpObj(" ");
            tmp_res.push_back(tmpObj);
            if (k - 1 < start)
              start = k + 1;
            else
            {
              tmp_len = k;
            }
          }
          else
          {

            char *subStr = new char[k - start + 1];
            subStr[k - start] = '\0';
            for (int m = start, n = 0; m < k; m++, n++)
            {
              subStr[n] = tmp[m];
            }
            MyString subStrObj(subStr);
            tmp_res.push_back(subStrObj);

            start = k + 1;
          }
        }
      }
      if (tmp_len == -1)
        continue;
      char *subStr = new char[tmp_len - start + 1];
      subStr[tmp_len - start] = '\0';

      for (int m = start, n = 0; m < tmp_len; m++, n++)
      {
        subStr[n] = tmp[m];
      }
      MyString subStrObj(subStr);
      tmp_res.push_back(subStrObj);
    }

    res = tmp_res;
  }
  if (delEmptySpace)
  {
    vector<MyString> finalRes;
    for (int i = 0; i < res.size(); i++)
    {
      char *subStr = res[i].str;
      if (strcmp(subStr, " "))
      {
        finalRes.push_back(subStr);
      }
    }
    return finalRes;
  }

  return res;
}

const MyString &MyString::operator=(const MyString &other)
{
  if (this == &other)
    return *this;
  delete[] str;
  str = new char[strlen(other.str) + 1];
  str[strlen(other.str)] = '\0';
  strcpy(str, other.str);
  return *this;
}

int main()
{
  MyString ms1("abcdsf");
  MyString ms2 = "____" + ms1;
  MyString ms3 = ms1 + ms2;
  cout << "ms1= " << ms1 << endl;
  cout << "ms2= " << ms2 << endl;
  cout << "ms3= " << ms3 << endl
       << endl;
  MyString ms = "a,b,c;d.r;.,h;e,w__u,t.f;j_..";
  vector<char> arrChar;
  arrChar.push_back(',');
  arrChar.push_back('.');
  arrChar.push_back(';');
  vector<MyString> vMs = ms.Split(arrChar, false);
  cout << "Split:" << endl;
  for (vector<MyString>::iterator itMS = vMs.begin(); itMS != vMs.end(); itMS++)
  {
    // if (!strcmp(itMS->getStr(), " "))
    // cout << "Empty" << endl;
    cout << *itMS << " ";
  }

  cout << endl
       << "size= " << vMs.size() << endl
       << endl;
  vMs = ms.Split(arrChar, true);
  cout << "Split co loai bo empty:" << endl;
  for (vector<MyString>::iterator itMS = vMs.begin(); itMS != vMs.end(); itMS++)
  {
    cout << *itMS << "-";
  }
  cout << endl
       << "size= " << vMs.size() << endl
       << endl;
  return 0;
}