// Program Information /////////////////////////////////////////////////////////
/**
  * @file metaData.h
  *
  * @brief defines metadata class     
  * 
  * @details defines member functions and data members
  *
  * @version Carli DeCapito
  *          1.0 Version 9/11/17
  *
  * @note None
  */

//Precompiler Directors
#ifndef METADATA_H
#define METADATA_H

//Header Files
#include "configData.h"
#include <vector>

using namespace std;
class configData;

//Class Definitions
class metaData{
  //constants
  static const int STR_LEN = 100;
  //Error Codes
  static const int CODE_ERROR = 0;
  static const int DESCRIPTOR_ERROR = 1;
  static const int CYCLES_ERROR = 2;

  public:
    //Constructor
    metaData();

    //Destructor
    ~metaData();

    //Member Functions
    bool createMetaStr( char string[], configData cData );
    void returnError( char string[], int errorCode );
    bool isDescriptorValid( configData cData );

    //Data Members
    char metaCode;
    char metaDescriptor[ STR_LEN ];
    int cycles;
    int time; 
    bool used;
};

#endif
