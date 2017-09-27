 // Program Information /////////////////////////////////////////////////////////
/**
  * @file metaData.cpp
  *
  * @brief Implements member functions    
  * 
  * @details Implements member functions used to obtain meta data
  *
  * @version Carli DeCapito
  *		     Version 1.00 9/11/17
  *
  * @note None
  */

//Precompiler directives
#ifndef METADATA_CPP
#define METADATA_CPP

//Header Files
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <vector>
#include "metaData.h"
#include "configData.h"

using namespace std;

//Class Implementation
/**
 * @brief metaData
 *
 * @details constructor 
 *          
 * @pre initializes data member 
 *
 * @post data members are initialized
 *
 * @par Algorithm 
 *      use assignment operator and strcpy function
 *      
 * @exception None
 *
 * @param [in] None
 *
 * @param [out] None
 *
 * @return None
 *
 * @note None
 */
metaData::metaData()
{
	metaCode = 'd'; //d for default
    strcpy( metaDescriptor, "default" );
    cycles = 0;
    time = 0;
    used = false;
}


/**
 * @brief ~metadata
 *
 * @details destructor
 *          
 * @pre none
 *
 * @post none
 *
 * @par Algorithm 
 *      none
 *      
 * @exception None
 *
 * @param [in] none
 *
 * @param [out] none
 *
 * @return None
 *
 * @note None
 */
metaData::~metaData()
{
	//nothing
}


/**
 * @brief createMetaString
 *
 * @details creates as string of meta data
 *          
 * @pre data in configData exists
 *
 * @post string contains metadata organized for output
 *
 * @par Algorithm 
 *      check for errors in metadata, report if are any
 * 		if not, concat string with metadata
 *      
 * @exception None
 *
 * @param [in] string[] provides string that will be concat
 *
 * @param [in]  cData provides configuration data class
 *
 * @return true if can get string ( no errors ), false if errors
 *
 * @note None
 */
bool metaData::createMetaStr( char string[], configData cData )
{
	char temp[ STR_LEN ];

	if( metaCode == 'd' || 	//default
		metaCode == 'p' ||	//lowercase
		metaCode == 'i' ||
		metaCode == 'o' ||
		metaCode == 'm' )
	{
		returnError( string, CODE_ERROR );
		return false;
	}

	//since no ERROR, copy Code to string
	sprintf( temp, "%c", metaCode );
	strcpy( string, temp );

	//check if meta descriptor is valid
	if( !isDescriptorValid( cData ) )
	{
		returnError( string, DESCRIPTOR_ERROR );
		return false;
	}

	//since no ERROR, concat string
	strcat( string, "(" );
	strcat( string, metaDescriptor );
	strcat( string, ")" );

	//check if cycles is valid
	if( cycles <= 0 )
	{
		returnError( string, CYCLES_ERROR );
		return false;
	}
	
	//since no ERROR, concat string 
	sprintf( temp, "%d", cycles );
	strcat( string, temp );
	strcat( string, " - " );

	//print time data
	sprintf( temp, "%d", time );
	strcat( string, temp );

	//ms 
	strcat( string, " ms" );

	return true;
}


/**
 * @brief returnError	
 *
 * @details returns an error "interrupt"
 *          
 * @pre error code exists
 *
 * @post error is returned
 *
 * @par Algorithm 
 *      use switch case to alternate b/w error code
 *      
 * @exception None
 *
 * @param [in] errorCode provides what is wrong with the metaData
 *
 * @param [in] string[] provides string to print to monitor/file
 *
 * @param [out] none
 *
 * @return None
 *
 * @note None
 */
void metaData::returnError( char string[], int errorCode )
{
	char temp[ STR_LEN ];

	switch( errorCode )
	{
		case 0: 
		{
			//output error
			strcpy( string, "Error. Invalid Code: ");

			//check if default code
			if ( metaCode == 'd' )
			{
				strcat( string, "Missing Code" );
			}
			//otherwise concat error
			else
			{
				sprintf( temp, "%c", metaCode );
				strcat( string, temp );
			}
			break;
		}
		case 1: 
		{
			//missing action 
			strcpy( string, "Error. Invalid or Missing Action: " );
			strcat( string, metaDescriptor );
			break;
		}
		case 2: 
		{
			//missing or invalid cycle time
			strcpy( string, "Error. Invalid or Missing Cycle Number: " );
			sprintf( temp, "%d", cycles );
			strcat( string, temp );
			break;
		}
	}
}


/**
 * @brief isDescriptorValid
 *
 * @details determines if metadata descriptor is valid
 *          
 * @pre metaDescriptor is initialized
 *
 * @post returns true if valid or false otherwise
 *
 * @par Algorithm 
 *      compares strings and calculates time
 *      
 * @exception None
 *
 * @param [in] cData provides configuration data for calculation
 *
 * @param [out] None
 *
 * @return returns true if valid or false otherwise
 *
 * @note None
 */
bool metaData::isDescriptorValid( configData cData )
{
	if( strcmp( metaDescriptor, "end" ) == 0 )
	{
		time = cData.processorCT * cycles;
		return true;
	}
	else if( strcmp( metaDescriptor, "hard drive" ) == 0 )
	{
		time = cData.hardDriveCT * cycles;
		return true;
	}
	else if( strcmp( metaDescriptor, "keyboard" ) == 0 )
	{
		time = cData.keyboardCT * cycles;
		return true;
	}
	else if( strcmp( metaDescriptor, "printer" )  == 0 )
	{
		time = cData.printerCT * cycles;
		return true;
	}
	else if( strcmp( metaDescriptor, "monitor" )  == 0 )
	{
		time = cData.monitorDT * cycles;
		return true;
	}
	else if( strcmp( metaDescriptor, "run" )  == 0 )
	{
		time = cData.processorCT * cycles;
		return true;
	}
	else if( strcmp( metaDescriptor, "start" )  == 0 )
	{
		time = cData.processorCT * cycles;
		return true;
	}
	else if( strcmp( metaDescriptor, "allocate" )  == 0 )
	{
		time = cData.memoryCT * cycles;
		return true;
	}
	else if( strcmp( metaDescriptor, "mouse" )  == 0 )
	{
		time = cData.mouseCT * cycles;
		return true;
	}
	else if( strcmp( metaDescriptor, "speaker" )  == 0 )
	{
		time = cData.speakerCT * cycles;
		return true;
	}
	else if( strcmp( metaDescriptor, "block" )  == 0 )
	{
		time = cData.memoryCT * cycles;
		return true;
	}

	return false;
}

#endif

