#include <iostream>
#include "Workstation.h"
#include "Station.h"

using namespace std;
namespace sdds{
   std::deque<CustomerOrder> g_pending = std::deque<CustomerOrder>{};
   std::deque<CustomerOrder> g_completed = std::deque<CustomerOrder>{};
   std::deque<CustomerOrder> g_incomplete = std::deque<CustomerOrder>{};
   Workstation::Workstation(const string& str):Station(str){
   }
   void Workstation::fill(std::ostream& os){
      if(!m_orders.empty()){
         m_orders.front().fillItem(*this, os);
      }
   }
   bool Workstation::attemptToMoveOrder(){
      bool isMoved{false};
      if(m_orders.size() > 0 && (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity()== 0)){
         isMoved = true;
         if(m_pNextStation == nullptr){
            if(m_orders.front().isOrderFilled()){
               g_completed.push_back(move(m_orders.front()));
               m_orders.pop_front();
            }else{
               g_incomplete.push_back(move(m_orders.front()));
               m_orders.pop_front();
            }
         }else{
            *m_pNextStation += std::move(m_orders.front());
            m_orders.pop_front();
         }
      }
      return isMoved;
   }
   void Workstation::setNextStation(Workstation* station){
      m_pNextStation = station;
   }
   Workstation* Workstation::getNextStation() const{
      return m_pNextStation;
   }
   void Workstation::display(std::ostream& os) const{
      if(m_pNextStation == nullptr){
         os << getItemName() <<  " --> End of Line" << endl;
      } else{
         os << getItemName() <<  " --> " << m_pNextStation->getItemName() << endl; 
      }
   }
   Workstation& Workstation::operator+=(CustomerOrder&& newOrder){
      m_orders.push_back(move(newOrder));
      return *this;
   }
}