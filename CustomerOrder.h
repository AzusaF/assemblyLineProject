/* ------------------------------------------------------
Project Project Milestone 3
Module: CustmerOrder
Filename: CustomerOrder.h
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

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include "Station.h"
namespace sdds{
   struct Item {
      std::string m_itemName;
      size_t m_serialNumber{0};
      bool m_isFilled{false};

      Item(const std::string& src) : m_itemName(src) {};
   };
   class CustomerOrder {
      std::string m_name{};
      std::string m_product{};
      size_t m_cntItem{};
      Item** m_lstItem{};
      static size_t m_widthField;
   public:
      CustomerOrder();
      CustomerOrder(const std::string str);
      CustomerOrder(CustomerOrder& CO);
      CustomerOrder& operator=(CustomerOrder& RO) = delete;
      CustomerOrder(CustomerOrder&& CO);
      CustomerOrder& operator=(CustomerOrder&& RO)noexcept;
      ~CustomerOrder();
      bool isOrderFilled() const;
      bool isItemFilled(const std::string& itemName) const;
      void fillItem(Station& station, std::ostream& os);
      void display(std::ostream& os) const;
      void addItem(std::string item);
   };
}

#endif