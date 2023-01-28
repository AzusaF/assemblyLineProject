#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace sdds{
   size_t Station::m_widthField = 1;
   size_t Station::id_generator = 0;
   Station::Station(const string& str){
      m_id = ++id_generator;
      size_t next_pos{};
      bool more = false;
      Utilities ut{};
      m_itemName = ut.extractToken(str, next_pos, more);
      m_serialNumber = stoi(ut.extractToken(str, next_pos, more));
      m_numOfItems = stoi(ut.extractToken(str, next_pos, more));
      if (m_widthField < ut.getFieldWidth())
         m_widthField = ut.getFieldWidth();
      m_description = ut.extractToken(str, next_pos, more);
   }
   const string& Station::getItemName() const{
      return m_itemName;
   }
   size_t Station::getNextSerialNumber(){
      return m_serialNumber++;
   }
   size_t Station::getQuantity() const{
      return m_numOfItems;
   }
   void Station::updateQuantity() {
      if(m_numOfItems > 0)
         m_numOfItems--;
   }
   void Station::display(ostream& os, bool full) const{
      os << setw(3) << setfill('0') << right << m_id << " | "  << setfill(' ') <<  left << setw(m_widthField) << m_itemName << "  | " << setw(6) << right << setfill('0')<< m_serialNumber << setfill(' ') << " | "  ;
      if(full)
         os << setw(4) << m_numOfItems << " | " << m_description;
      os << endl;
   }
}