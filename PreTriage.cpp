/*
Final Project Milestone 5
Name : Yujin Won
Email: ywon9@myseneca.ca
Student ID: 153565197
Date: 2020/12/02

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream> 
#include "utils.h" 
#include "PreTriage.h"
#include "CovidPatient.h" 
#include "TriagePatient.h" 
using namespace std;
namespace sdds {
  void PreTriage::reg() {
    int selection;
    bool ok = true;

    if (m_lineupSize == maxNoOfPatients) {
      cout << "Line up full!" << endl;
      ok = false; 
    }
    if (ok) {
      m_pMenu.display();
      cin >> selection; 
    
      if (selection == 1) {
        m_lineup[m_lineupSize] = new CovidPatient();
      }
      else if (selection == 2) {
        m_lineup[m_lineupSize] = new TriagePatient();
      }

      if (selection == 1 || selection == 2) {
        m_lineup[m_lineupSize]->setArrivalTime();
        cout << "Please enter patient information: " << endl;
        m_lineup[m_lineupSize]->fileIO(false);
        m_lineup[m_lineupSize]->read(cin);

        cout << endl << "******************************************" << endl;
        m_lineup[m_lineupSize]->write(cout);
        cout << "Estimated Wait Time: ";
        getWaitTime(*m_lineup[m_lineupSize]).write(cout) << endl;
        cout << "******************************************" << endl << endl;

        m_lineupSize++; 
      }
    }
  }

  void PreTriage::admit() {
    int selection;
    char type = 'X';
    int indexFound;

    m_pMenu.display();
    cin >> selection;
 
    if (selection == 1) {
      type = 'C';
    }
    else if (selection == 2) {
      type = 'T';
    }

    if (selection == 1 || selection == 2) {
      indexFound = indexOfFirstInLine(type);

      if (indexFound != -1) {
        cout << endl << "******************************************" << endl;
        cout << "Calling for ";
        m_lineup[indexFound]->write(cout);
        cout << "******************************************" << endl << endl;
        setAverageWaitTime(*m_lineup[indexFound]);
        removePatientFromLineup(indexFound);
      }
    }
  }

  const Time PreTriage::getWaitTime(const Patient& p)const {
    int numOfPatients = 0;
    Time waitTime; 

    for (int i = 0; i < m_lineupSize; i++) {
      if (m_lineup[i]->type() == p.type()) {
        numOfPatients++;
      }
    }
    if (p.type() == 'C') {
      waitTime = m_averCovidWait; 
    }
    else if (p.type() == 'T') {
      waitTime = m_averTriageWait;
    }
    return waitTime *= numOfPatients; 
  }

  void PreTriage::setAverageWaitTime(const Patient& p) {
    int numOfTicket = p.number();
    int ticketTime = Time(p); 
    int currentTime = getTime();

    if (p.type() == 'C') {
      m_averCovidWait = ((currentTime - ticketTime) + (m_averCovidWait * (numOfTicket - 1))) / numOfTicket;
    }
    else if (p.type() == 'T') {
      m_averTriageWait = ((currentTime - ticketTime) + (m_averTriageWait * (numOfTicket - 1))) / numOfTicket;
    }
  }

  void PreTriage::removePatientFromLineup(int index) {
    removeDynamicElement(m_lineup, index, m_lineupSize);
  }

  void PreTriage::load() {
    Patient* p = nullptr; 
    char singleChar;
    bool ok;
    
    cout << "Loading data..." << endl;

    ifstream file(m_dataFilename);

    if (file) {
      ok = true;
      file >> m_averCovidWait;
      file.ignore(1000, ',');
      file >> m_averTriageWait;
      file.ignore(1000, '\n');

      for (int i = 0; i < maxNoOfPatients && ok; i++) {
        if (!file.eof()) {
          singleChar = file.get();
          file.ignore(1000, ',');

          if (singleChar == 'C') {
            p = new CovidPatient();
          }
          else if (singleChar == 'T') {
            p = new TriagePatient();
          }
          else {
            if (p != nullptr) {
              p = nullptr;
            }
          }

          if (p != nullptr) {
            p->fileIO(true);
            p->csvRead(file);
            file.ignore(1000, '\n');
            p->fileIO(false);
            m_lineup[m_lineupSize] = p;
            m_lineupSize++;
          }
        }
        else {
          ok = false;
        }
      }
    }

    if (file && !file.eof()) {
      cout << "Warning: number of records exceeded " << maxNoOfPatients << endl; 
    }

    if (m_lineupSize == 0) {
      cout << "No data or bad data file!" << endl << endl;
    }
    else {
      cout << m_lineupSize << " Records imported..." << endl << endl;
    }

    file.close(); 
  }

  int PreTriage::indexOfFirstInLine(char type) const {
    int indexFound = -1;
    bool ok = true;
    for (int i = 0; i < m_lineupSize && ok; i++) {
      if (m_lineup[i]->type() == type) {
        indexFound = i;
        ok = false;
      }
    }
    return indexFound;
  }

  PreTriage::PreTriage(const char* dataFilename): m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2) {
    m_averCovidWait = 15;
    m_averTriageWait = 5;

    delete[] m_dataFilename;
    m_dataFilename = new char[strlen(dataFilename) + 1];
    strcpy(m_dataFilename, dataFilename);
    load();
  }

  PreTriage::~PreTriage() {  
    int i;
    ofstream file(m_dataFilename);

    if (file) {
      m_averCovidWait.write(file);
      file << ',';
      m_averTriageWait.write(file) << endl;

      cout << "Saving Average Wait Times," << endl;
      cout << "   COVID Test: ";
      m_averCovidWait.write(cout) << endl;
      cout << "   Triage: ";
      m_averTriageWait.write(cout) << endl;
      cout << "Saving m_lineup..." << endl;

      for (i = 0; i < m_lineupSize; i++) {
        m_lineup[i]->csvWrite(file) << endl;
        cout << i + 1 << "- ";
        m_lineup[i]->csvWrite(cout) << endl;
      }
    }

    for (i = 0; i < m_lineupSize; i++) {
      delete m_lineup[i];
    }

    delete[] m_dataFilename;
    cout << "done!" << endl;

    file.close(); 
  }

  void PreTriage::run(void) {
    int selection;
    bool ok = true;
    
    do {
      m_appMenu.display();
      cin >> selection;

      if (selection == 0) {
        ok = false;
      }
      else if (selection == 1) {
        reg();
      }
      else if (selection == 2) {
        admit();
      }
      else { 
        cout << "Please select the option between 0 and 2" << endl;
      }
    } while (ok);
  }
}