/* ------------------------------------------------------
Project Project Milestone 3
Module: Station
Filename: Station.h
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
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
namespace sdds{
   class Station{
      size_t m_id{};
      std::string m_itemName;
      std::string m_description;
      size_t m_serialNumber;
      size_t m_numOfItems;
      static size_t m_widthField;
      static size_t id_generator;
   public:
      Station(const std::string& str);
      const std::string& getItemName() const;
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& os, bool full) const;
   };
}
#endif