/* ------------------------------------------------------
Project Project Milestone 3
Module: Utilities
Filename: Utilities.cpp
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

#include <string>
#include "Utilities.h"

using namespace std;
namespace sdds{
   char Utilities::m_delimiter = ',';
   void Utilities::setFieldWidth(size_t newWidth){
      m_widthField = newWidth;
   }
   size_t Utilities::getFieldWidth() const{
      return m_widthField;
   }
   string Utilities::extractToken(const string& str, size_t& next_pos, bool& more){
      string token{};

      size_t pos = str.find(m_delimiter, next_pos);
      if(pos == next_pos){
         more = false;
         throw string("ERROR: Invalid position!");
      }
      if(pos == std::string::npos){
         more = false;
         token = str.substr(next_pos);
         token =trim(token);
      } else {
         more = true;
         token = str.substr(next_pos, pos - next_pos);
         token = trim(token);
         next_pos = pos + 1;
      }
      size_t length = token.length();
      if(m_widthField < length){
         m_widthField = length;
      }
      return token;
   }
   void Utilities::setDelimiter(char newDelimiter){
      m_delimiter = newDelimiter;
   }
   char Utilities::getDelimiter(){
      return m_delimiter;
   }
   string& Utilities::trim(string& str){
      size_t pos = str.find_first_not_of(' ');
      if(pos != string::npos)
         str = str.substr(pos);
      pos = str.find_last_not_of(' ');
      if(pos != string::npos)
         str = str.substr(0, pos+1);
      return str; 
   }
}