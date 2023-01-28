/* ------------------------------------------------------
Project Project Milestone 3
Module: Utilities
Filename: Utilities.h
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
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
namespace sdds{
   class Utilities{
      size_t m_widthField = 1;
      static char m_delimiter;
   public:
      void setFieldWidth(size_t newWidth);
      size_t getFieldWidth() const;
      std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
      static void setDelimiter(char newDelimiter);
      static char getDelimiter();
      std::string& trim(std::string& str);
   };
}
#endif