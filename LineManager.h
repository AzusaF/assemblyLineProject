/* ------------------------------------------------------
Project Project Milestone 3
Module: LineManager
Filename: LineManager.h
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

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include "Workstation.h"
#include <vector>
namespace sdds{
   class LineManager{
      std::vector<Workstation*> m_activeLine;
      size_t m_cntCustomerOrder;
      Workstation* m_firstStation;
   public:
      LineManager(const std::string& file, const std::vector<Workstation*>& stations);
      void reorderStations();
      bool run(std::ostream& os);
      void display(std::ostream& os) const;
   };
}
#endif