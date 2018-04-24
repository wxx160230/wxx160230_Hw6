#ifndef _PROGRAM6_H_INCLUDED
#define  _PROGRAM6_H_INCLUDED

//Wulan Xu
//wxx160230@utdallas.edu
//3377.002

#include <stdint.h>

class BinaryFileHeader 
{  
public: 
 
  uint32_t magicNumber;         /* Should be 0xFEEDFACE */   
  uint32_t versionNumber;   
  uint64_t numRecords; 
};

/*  
* Records in the file have a fixed length buffer  
* that will hold a C-Style string. This is the  
* size of the fixed length buffer.  
*/ 
const int maxRecordStringLength = 25; 
 
class BinaryFileRecord 
{  
public: 
 
  uint8_t strLength;   
  char stringBuffer[maxRecordStringLength]; 
}; 

#endif //  _PROGRAM6_H_
