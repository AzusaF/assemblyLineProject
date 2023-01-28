/* ------------------------------------------------------
Project Project Milestone 3
Module: LineManager
Filename: LineManager.cpp
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

#include "LineManager.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
namespace sdds{
   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
      if(file.empty()){
         throw string("ERROR: Something wrong with the filename: " + file);
      }
      ifstream in(file); 
      if(!in){
         throw string("ERROR: Unable to open the file: " + file);
      }
      string line;
      while(!in.eof()){
         getline(in, line);
         string itemName1 = line.substr(0,line.find('|'));
         string itemName2 = line.erase(0, itemName1.size()+1);
         auto station = find_if(stations.begin(), stations.end(), [&](Workstation* workStation){
                           return workStation->getItemName().compare(itemName1) == 0;
                        });
         m_activeLine.push_back(*station);
         if(!itemName2.empty()){
            for_each(stations.begin(), stations.end(), [&](Workstation* workStation){
                        if(workStation->getItemName().compare(itemName2) == 0){
                           m_activeLine.back()->setNextStation(workStation);
                        }
                     });
         }else{
            m_activeLine.back()->setNextStation();
         }
      }
      for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workStation){
                  auto firstStation = find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workStation2){
                                                return workStation == workStation2->getNextStation();
                                             });
                  if(firstStation == m_activeLine.end()){
                     m_firstStation = workStation;
                  }
               });
      m_cntCustomerOrder = g_pending.size();
   }
   void LineManager::reorderStations(){
      std::vector<Workstation*> tempList{};
      Workstation* tempStation = m_firstStation;

      tempList.push_back(tempStation);
      while (tempStation->getNextStation()) {
         tempStation = tempStation->getNextStation();
         tempList.push_back(tempStation);
      }
      m_activeLine = tempList;
   }
   bool LineManager::run(std::ostream& os){
      static unsigned int counter = 0u;
		os << "Line Manager Iteration: " << ++counter << endl;
		if (!g_pending.empty()){
			*m_firstStation += move(g_pending.front());
			g_pending.pop_front();
		}
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws){
				      ws->fill(os);
			      });
		for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* ws){
				      ws->attemptToMoveOrder();
			      });
		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
   }
   void LineManager::display(std::ostream& os) const{
      vector<Workstation*>::const_iterator it;
      for (it = m_activeLine.begin(); it < m_activeLine.end(); it++){
         (*it)->display(os);
      }
   }
}