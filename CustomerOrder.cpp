/* ------------------------------------------------------
Project Project Milestone 3
Module: CustmerOrder
Filename: CustomerOrder.cpp
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

#include "CustomerOrder.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
namespace sdds{
   size_t CustomerOrder::m_widthField = 1;
   CustomerOrder::CustomerOrder(){
      m_name = "";
      m_product = "";
      m_cntItem = 0;
      m_lstItem = nullptr;
   }
   CustomerOrder::CustomerOrder(const string str){
      Utilities ut;
      size_t nextPos{};
      bool more{false};
      string tempItem{};
      m_name = ut.extractToken(str, nextPos, more);
      m_product = ut.extractToken(str, nextPos, more);
      while(more){
         tempItem = ut.extractToken(str, nextPos, more);
         addItem(tempItem);
      }
      if(ut.getFieldWidth() > m_widthField) m_widthField = ut.getFieldWidth();
   }
   CustomerOrder::CustomerOrder(CustomerOrder& CO){
      throw string("ERROR: CustomerOrder cannot be copied by copy constructor!");
   }
   CustomerOrder::CustomerOrder(CustomerOrder&& CO){
      operator=(move(CO));
   }
   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& CO)noexcept{
      if(this != &CO){
         for(size_t i = 0; i < m_cntItem; i++){
            delete m_lstItem[i];
         }
         delete[] m_lstItem;
         m_lstItem = CO.m_lstItem;
         m_cntItem = CO.m_cntItem;
         m_name = CO.m_name;
         m_product = CO.m_product;
         m_widthField = CO.m_widthField;
         CO.m_name = "";
         CO.m_product = "";
         CO.m_cntItem = 0;
         CO.m_widthField = 0;
         CO.m_lstItem = nullptr;
      }
      return *this;
   }
   CustomerOrder::~CustomerOrder(){
      for (size_t i = 0; i < m_cntItem; i++) {
         delete m_lstItem[i];
      }      
      delete[] m_lstItem;
   }
   bool CustomerOrder::isOrderFilled() const{
      bool isOrderFilled{true};
      for(size_t i = 0; i < m_cntItem && isOrderFilled; i++){
         if(!m_lstItem[i]->m_isFilled) isOrderFilled = false;
      }
      return isOrderFilled;
   }
   bool CustomerOrder::isItemFilled(const std::string& itemName) const{
      bool areAllFilled{true};
      for (size_t i = 0; i < m_cntItem && areAllFilled; i++){
         if(m_lstItem[i]->m_itemName == itemName){
            if(!m_lstItem[i]->m_isFilled) areAllFilled = false;
         }
      }
      return areAllFilled;
   }
   void CustomerOrder::fillItem(Station& station, std::ostream& os){
      bool filled{false};
      if(m_lstItem){
         for(size_t i = 0; i < m_cntItem && !filled; i++){
            if(!m_lstItem[i]->m_isFilled && m_lstItem[i]->m_itemName == station.getItemName() && station.getQuantity() > 0 ){
               m_lstItem[i]->m_isFilled = true;
               station.updateQuantity();
               m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
               filled = true;
               os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << endl;
            }else if(!m_lstItem[i]->m_isFilled && m_lstItem[i]->m_itemName == station.getItemName() && station.getQuantity() == 0){
               os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << endl;
            }
         }
      }
   }
   void CustomerOrder::display(std::ostream& os) const{
      os << m_name << " - " << m_product << endl;
      for(size_t i = 0; i < m_cntItem; i++){
         os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << "] " << left << setw(32) << setfill(' ') << m_lstItem[i]->m_itemName << " - " ;
         m_lstItem[i]->m_isFilled ? os << "FILLED" << endl : os << "TO BE FILLED" << endl;
      }
   }
   void CustomerOrder::addItem(string item){
      Item** temp = new Item * [m_cntItem + 1] {};
      for (size_t i = 0; i < m_cntItem; i++) {
         temp[i] = m_lstItem[i];
      }
      temp[m_cntItem] = new Item(item);
      delete[] m_lstItem;
      m_lstItem = temp;
      m_cntItem++;
   }
}