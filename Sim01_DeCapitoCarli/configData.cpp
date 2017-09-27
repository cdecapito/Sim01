// Program Information /////////////////////////////////////////////////////////
/**
  * @file configData.cpp
  *
  * @brief implementation of member functions    
  * 
  * @details constructor, destructor, and member functions implemented
  *
  * @version Carli DeCapito 1.0
  *			 Original Version 9/11/17
  *
  * @note None
  */

//Precompiler Directives
#ifndef CONFIGDATA_CPP
#define CONFIGDATA_CPP

//Header Files
#include <iostream> 
#include <cstring>	//string manipulation
#include <cstdio>
#include <stdlib.h> //for atoi
#include <fstream>	//file i/o
#include "configData.h"

using namespace std;

bool logFileValid( char string[] );

//Implementation 


/**
 * @brief constructor
 *
 * @details initializes data members
 *          
 * @pre none
 *
 * @post members are initialized
 *
 * @par Algorithm 
 *      Assignment operators
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
configData::configData()
{
	//set strings to null
	version[ 0 ] = '\0';
	filePath[ 0 ] = '\0';
	logInfo[ 0 ] = '\0';
	logFilePath[ 0 ] = '\0';

	//set numerical data to 0
	processorCT = 0;
	monitorDT = 0;
	hardDriveCT = 0;
	printerCT = 0;
	keyboardCT = 0;
	memoryCT = 0;
	mouseCT = 0;
	speakerCT = 0;
}

/**
 * @brief ~configData
 *
 * @details destructor
 *          
 * @pre does nothing
 *
 * @post none
 *
 * @par Algorithm 
 *      None
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
configData::~configData()
{
	//nothing
}

/**
 * @brief getConfigData
 *
 * @details reads configuration data from file
 *          
 * @pre file exists
 *
 * @post file is read into system
 *
 * @par Algorithm 
 *      Parse through file, read in data using file input
 *      
 * @exception None
 *
 * @param [in] filename provides name that pass passed 
 *				through command line arguments
 *
 * @param [out] None
 *
 * @return bool if file was read, return true, otherwise false
 *
 * @note None
 */
bool configData::getConfigData( char filename[] )
{
	ifstream fin;
	char temp[ STR_LEN ];
	bool empty;

	//open file
	fin.open( filename );

	if( !fin.good() )
	{
		cout << "Error: Invalid Configuration File." << endl;
		return false;
	}

	//get first line 
	fin.getline( temp, STR_LEN, '\n' );

	//check if first lines says file is config file
	if( strcmp( temp, "Start Simulator Configuration File") != 0 )
	{
		//string is not equal to temp
		cout << "Error: File is empty or is not Configuration File" << endl;
		return false;
	}

	//loop until get all data
	while( fin.good() )
	{
		fin.getline( temp, STR_LEN, ':');
		//remove spaces from temp
		removeSpace( temp );
		
		//Read in Version/Phase
		if ( strcmp( temp, "Version/Phase") == 0 )
		{
			//get info until new line
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				strcpy( version, temp );
			}
		}
		//read in file path
		else if ( strcmp( temp, "File Path") == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if( !logFileValid( temp ) )
			{
				cout << "Error. Invalid Meta-Data File Extension." << endl;
				return false;
			}

			if ( !empty )
			{
				strcpy( filePath, temp );
			}
		}
		//read in processor CT
		else if ( strcmp( temp, "Processor cycle time (msec)" ) == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				//char to int conversion
				processorCT = atoi( temp );
			}
		}
		//read in Monitor DT
		else if ( strcmp( temp, "Monitor display time (msec)") == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				//char to int conversion
				monitorDT = atoi( temp );
			}
		} 
		//read in HD CT
		else if ( strcmp( temp, "Hard drive cycle time (msec)") == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				//char to int conversion
				hardDriveCT = atoi( temp );
			}
		}
		//read in printer CT
		else if ( strcmp( temp, "Printer cycle time (msec)") == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				//char to int conversion
				printerCT = atoi( temp );
			}
		}
		//read in keyboard CT
		else if ( strcmp( temp, "Keyboard cycle time (msec)") == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				//char to int conversion
				keyboardCT = atoi( temp );
			}
		}
		//read in Memory CT
		else if ( strcmp( temp, "Memory cycle time (msec)") == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				//char to int conversion
				memoryCT = atoi( temp );
			}
		}
		//read in mouse CT
		else if ( strcmp( temp, "Mouse cycle time (msec)") == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				//char to int conversion
				mouseCT = atoi( temp );
			}
		}
		// read in speaker CT
		else if ( strcmp( temp, "Speaker cycle time (msec)") == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				//char to int conversion
				speakerCT = atoi( temp );
			}
		}
		//read in log
		else if ( strcmp( temp, "Log") == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				strcpy( logInfo, temp );
			}
		}
		// read in log file path
		else if ( strcmp( temp, "Log File Path") == 0 )
		{
			//get rest of line, remove front spaces
			//check if data is there
			fin.getline( temp, STR_LEN, '\n' );
			removeSpace( temp );
			empty = isEmpty( temp );

			if ( !empty )
			{
				strcpy( logFilePath, temp );
			}
		}
		//end of file 
		else 
		{
			if ( strcmp( temp, "End Simulator Configuration File\n") == 0 )
			{
				return true;
			}
		}
	}

	fin.close();

	return true;

}

/**
 * @brief createConfigDataString
 *
 * @details creates string to output to file/monitor
 *          
 * @pre data exists
 *
 * @post data is copied to string
 *
 * @par Algorithm 
 *      use switch case to determine if cycles are valid
 *      
 * @exception None
 *
 * @param [in] string provides string of characters to be outputed 
 *
 * @param [in] provides index of value in config file
 *
 * @return bool - true if successful, false if not
 *
 * @note None
 */
bool configData::createConfigDataStr( char string[], int dataNum )
{
	char configProcess[ STR_LEN ];
	char cycleTimeStr[ STR_LEN ];
	int cycleTimeInt;

	switch ( dataNum )
	{
		case 0: 
		{
			strcpy( configProcess, "Processor" );
			cycleTimeInt = processorCT;
			break;
		}
		case 1:
		{
			strcpy( configProcess, "Monitor" );
			cycleTimeInt = monitorDT;
			break;
		}
		case 2:
		{
			strcpy( configProcess, "Hard Drive" );
			cycleTimeInt = hardDriveCT;
			break;
		}
		case 3:
		{
			strcpy( configProcess, "Printer" );
			cycleTimeInt = printerCT;
			break;
		}
		case 4:
		{
			strcpy( configProcess, "Keyboard" );
			cycleTimeInt = keyboardCT;
			break;
		}
		case 5:
		{
			strcpy( configProcess, "Memory" );
			cycleTimeInt = memoryCT;
			break;
		}
		case 6:
		{
			strcpy( configProcess, "Mouse" );
			cycleTimeInt = mouseCT;
			break;
		}
		case 7:
		{
			strcpy( configProcess, "Speaker" );
			cycleTimeInt = speakerCT;
			break;
		}

	}
	//if CT is invalid number
	if( cycleTimeInt <= 0 )
	{
		returnError( string, configProcess );
		return false;
	}
	//copy process to string since no error
	strcpy( string, configProcess );
	//convert CT to string
	sprintf( cycleTimeStr, "%d", cycleTimeInt );
	//concat data
	strcat( string, " = " );
	strcat( string, cycleTimeStr );
	strcat( string, " ms/cycle" );

	return true;
}


/**
 * @brief returnError
 *
 * @details returns error that occurs
 *          
 * @pre error code is nonempty
 *
 * @post string is concatenated 
 *
 * @par Algorithm 
 *      use string functions to copy and concatenate
 *      
 * @exception None
 *
 * @param [in] string provides string to output
 *
 * @param [in] errorCode provides error that occured
 *
 * @return None
 *
 * @note None
 */
void configData::returnError( char string[], char errorCode[] )
{
	strcpy( string, "Error. Invalid Time or String for: " );
	strcat( string, errorCode );
}


/**
 * @brief removeSpace
 *
 * @details removes spaces at beginning of the string
 *          
 * @pre string exists
 *
 * @post spaces are removed from beginning
 *
 * @par Algorithm 
 *      Traversing string
 *      
 * @exception None
 *
 * @param [in] string contains char of a line from file
 *
 * @param [out] none
 *
 * @return none
 *
 * @note None
 */
void configData::removeSpace( char string[] )
{
	int index = 0;
	//check if first index is space or newline
	while( string[0] == ' ' || string[0] == '\n' )
	{
		//while it is not the end of the string
		while ( string[ index ] != '\0' )
		{
			//shift every char down one
			string[ index ] = string [ index + 1 ];
			index++;
		}
	}
}


/**
 * @brief isEmpty
 *
 * @details returns if a string is empty
 *          
 * @pre string exists
 *
 * @post if string is empty, return true, otherwise false
 *
 * @par Algorithm 
 *      if, else statement with checking first element
 *      
 * @exception None
 *
 * @param [in] string provides array of char to check if empty
 *
 * @param [out] None
 *
 * @return bool: if string is empty, return false, otherwise true
 *
 * @note None
 */
bool configData::isEmpty( char string[] )
{
	//if first element is null
	if ( string[ 0 ] == '\0')
	{
		//string is empty
		return true;
	}
	//otherwise it is not empty
	return false;
}


bool logFileValid( char string[] )
{
	int index = 0;
	while( string[ index ] != '\0')
	{
		if ( string[ index ] == '.' )
		{
			if( string[ index + 1 ] == 'm' &&
				string[ index + 2 ] == 'd' &&
				string[ index + 3 ] == 'f' )

			{
				return true;
			}
		}
		index++;
	}
	return false;
}

#endif
