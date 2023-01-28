/* ------------------------------------------------------
Project Project Milestone 3
Module: Workstation
Filename: Workstation.h
Student Name: Azusa Fukuda
Student ID: 109697219
Section: NCC
Email Address: afukuda@myseneca.ca
Revision History
-----------------------------------------------------------
Initials    Date           Reason
A.F.        12/02/2022     Made the code working
-----------------------------------------------------------
I confirm that I am the only author of this file and the 
content was created entirely by me.
-----------------------------------------------------------*/

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include "CustomerOrder.h"
#include "Station.h"
#include <string>
#include <deque>
namespace sdds{
   extern std::deque<CustomerOrder> g_pending;
   extern std::deque<CustomerOrder> g_completed;
   extern std::deque<CustomerOrder> g_incomplete;
   
   class Workstation: public Station{
      std::deque<CustomerOrder> m_orders{};
      Workstation* m_pNextStation{};
   public:
      Workstation(const std::string& str);
      Workstation(const Workstation&) = delete;
      Workstation(Workstation&&) = delete;
      Workstation& operator=(const Workstation&) = delete;
      Workstation& operator=(Workstation&&) = delete;
      void fill(std::ostream& os);
      bool attemptToMoveOrder();
      void setNextStation(Workstation* station = nullptr);
      Workstation* getNextStation() const;
      void display(std::ostream& os) const;
      Workstation& operator+=(CustomerOrder&& newOrder);
   };
}
#endif