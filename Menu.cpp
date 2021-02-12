/*
Final Project Milestone 1
Name : Yujin Won
Email: ywon9@myseneca.ca
Student ID: 153565197
Date: 2020/11/12

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "utils.h"
#include "Menu.h"
using namespace std;
namespace sdds
{
  void Menu::setInvalid() {
    m_text = nullptr;
    m_noOfSel = -1;
  }

  void Menu::setText(const char* text) {
    delete[] m_text;
    if (text != nullptr) {
      m_text = new char[strlen(text) + 1];
      strcpy(m_text, text);
    }
  }

  Menu::Menu(const char* text, int NoOfSelections) {
    setInvalid();
    setText(text);
    m_noOfSel = NoOfSelections;
  }

  Menu::~Menu() {
    delete[] m_text;
  }

  ostream& Menu::display(ostream& ostr)const {
    ostr << m_text << endl;
    ostr << "0- Exit" << endl;
    ostr << "> ";
    return ostr;
  }

  int& Menu::operator>>(int& Selection) {
    int optionNum;
    bool ok = false;
    display();

    while (!ok) {
      cin >> optionNum;
      if (cin.fail()) {
        cout << "Bad integer value, try again: ";
        cin.clear();
        cin.ignore(2000, '\n');
      }
      else {
        if (optionNum >= 0 && optionNum <= 3) {
          Selection = optionNum;
          ok = true;
        }
        else {
          cout << "Invalid value enterd, retry[0 <= value <= 3]: ";
        }
      }
    }
    return Selection;
  }
}