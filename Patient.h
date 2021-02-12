/*
Final Project Milestone 3
Name : Yujin Won
Email: ywon9@myseneca.ca
Student ID: 153565197
Date: 2020/11/18

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
namespace sdds
{
  class Patient : public IOAble
  {
    char* m_patientName = nullptr;
    int m_ohipNum = 0;
    Ticket m_ticket;
    bool m_fileIO;
  public:
    Patient(int ticketNum = 0, bool flag = false);
    Patient(const Patient& P) = delete;
    Patient& operator=(const Patient& P) = delete;
    ~Patient();
    virtual char type()const = 0;
    bool fileIO()const;
    void fileIO(bool flag);
    bool operator==(const char ch)const;
    bool operator==(const Patient& P)const;
    void setArrivalTime();
    operator Time()const;
    int number()const;
    std::ostream& csvWrite(std::ostream& ostr)const;
    std::istream& csvRead(std::istream& istr);
    std::ostream& write(std::ostream& ostr)const;
    std::istream& read(std::istream& istr);
  };
}
#endif // !SDDS_PATIENT_H_


