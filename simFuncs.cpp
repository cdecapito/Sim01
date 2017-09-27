 // Program Information /////////////////////////////////////////////////////////
/**
  * @file simFuncs.cpp
  *
  * @brief Modularizes functions used to read/output data to file or monitor  
  * 
  * @details implements functions to 
  *
  * @version Carli DeCapito
  *		     Version 1.00 9/17/17
  *
  * @note None
  */

//Global constants
static const int STR_LEN = 100;
static const int STR_LEN_LNG = 400;
static const int LOG_TO_BOTH = 0;
static const int LOG_TO_MONITOR = 1;
static const int LOG_TO_FILE = 2;


//Header Files
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include "metaData.h"
#include "configData.h"

using namespace std;

//Function Definitions
bool getMetaData ( char filename[], vector<metaData> &mData );
void parseString( char string[], vector<metaData> &mData );
metaData parseData( int &index, char string [] );
void logData( configData cData, vector<metaData> mData );
void logToFile( configData cData, vector<metaData> mData, int logCode );
void logToMonitor( configData cData, vector<metaData> mData, int logCode );


//Function Implementation
/**
 * @brief getMetaData
 *
 * @details reads meta data from file and stores in class
 *          
 * @pre filename exists, mData has been created
 *
 * @post mData is set
 *
 * @par Algorithm 
 *      use ifstream library function to read metadata
 *      
 * @exception None
 *
 * @param [in] filename provides string that contains metadata
 *
 * @param [out] mData provides metaData class vector
 *
 * @return bool, true if successful, false if not
 *
 * @note None
 */
bool getMetaData ( char filename[], vector<metaData> &mData )
{
	//declare and initalize variables
	char temp[ STR_LEN_LNG ];
	ifstream fin;

	//open file
	fin.open ( filename );

	//if file does not exist or failed when open
	if ( !fin.good() )
	{
		cout << "Error: Invalid Meta-Data filename. " << endl;
		return false;
	}

	fin.getline( temp, STR_LEN, '\n' );

	//if start of program does not say this, then it is wrong file
	if ( strcmp( temp, "Start Program Meta-Data Code:" ) != 0 ) 
	{
		cout << "Error: Invalid Meta-Data File." << endl;
	}

	while ( fin.good() )
	{
		fin.getline( temp, STR_LEN_LNG, '\n' );

		//end of file 
		if ( strcmp( temp, "End Program Meta-Data Code." ) == 0 )
		{
			return true;
		}
		//otherwise parse line of meta-data
		parseString( temp, mData);
	}

	return true;
}


/**
 * @brief parseString
 *
 * @details parses metaData line by line
 *          
 * @pre string exists and mData exists
 *
 * @post mData is set
 *
 * @par Algorithm 
 *      parse through string
 *      
 * @exception None
 *
 * @param [in] string provides mData to parse
 *
 * @param [out] mData provides metaData
 *
 * @return None
 *
 * @note None
 */
void parseString( char string[], vector<metaData> &mData )
{
	//initalize/declare variables
	int index = 0;
	metaData temp; 
	int strLen = strlen( string );
	
	while ( index < strLen - 2 )
	{
		//save meta data
		temp = parseData( index, string );

		//store data in vector
		mData.push_back( temp );
	}
}


/**
 * @brief parseData
 *
 * @details parses through the string and saves metaData
 *          
 * @pre string exists
 *
 * @post metadata is saved
 *
 * @par Algorithm 
 *      increment index until find specific symbols
 *      
 * @exception None
 *
 * @param [in] string provides string read from file that is being parsed
 *
 * @param [out] index provides index in string that 
 *
 * @return metaData
 *
 * @note None
 */
metaData parseData( int &index, char string[] )
{
	//declare and initalize variables
	char strTemp[ STR_LEN ];
	int tempIndex = 0;
	metaData metaTemp; 

	while ( string [ index ] != 'S' && 	//uppercase
			string [ index ] != 'A' &&	
			string [ index ] != 'P' &&
			string [ index ] != 'I' &&
			string [ index ] != 'O' &&
			string [ index ] != 'M' &&
			string [ index ] != 'a' &&	//lowercase (ERROR)
			string [ index ] != 'i' &&
			string [ index ] != 'o' &&
			string [ index ] != 'm' &&
			string [ index ] != '(' )	//missing operation (ERROR)
	{
		//increment until find valid operation
		index++;
	}

	//check that '(' is not the code, when reach code, save
	if( string [ index ] != '(' )
	{
		metaTemp.metaCode = string[ index ];
		index++;
	}

	//find meta descriptor
	while ( string [ index ] != '(' )
	{
		//increment until find 
		index++;
	}
	//increment past '('
	index++;

	//increment past spaces
	while( string[ index ] == ' ' )
	{
		index++;
	}

	while ( string[ index ] != ')' )
	{
		//if ( string[ index ] != ' ' )
		{
			//copy data into temp
			strTemp[ tempIndex ] = string [ index ];
			tempIndex++;
		}
		//increment index
		index++;
	}

	//increment past ')'
	index++;

	//put null at end of temp
	strTemp[ tempIndex ] = '\0';

	//copy temp data to temp meta
	strcpy( metaTemp.metaDescriptor, strTemp );
	
	//check for spaces
	while ( string[ index ] == ' ' )
	{
		index++;
	}

	//reset tempIndex
	tempIndex = 0;

	//digits
	while ( string[ index ] == '0' ||
			string[ index ] == '1' ||
			string[ index ] == '2' ||
			string[ index ] == '3' ||
			string[ index ] == '4' ||
			string[ index ] == '5' ||
			string[ index ] == '6' ||
			string[ index ] == '7' ||
			string[ index ] == '8' ||
			string[ index ] == '9' ||
			string[ index ] == '-' ) 	//negative nums (ERROR)
	{
		strTemp[ tempIndex ] = string[ index ];
		tempIndex++;
		index++;
	}

	//skip spaces
	while ( string[ index ] == ' ' )
	{
		index++;
	}

	//put null at end
	strTemp[ tempIndex ] = '\0';

	//store cycles, convert char* to int
	metaTemp.cycles = atoi( strTemp );

	return metaTemp;
}

/**
 * @brief logData
 *
 * @details logs data to designated monitor/file or both
 *          
 * @pre cData and mData initialized
 *
 * @post output logged to file/monitor or both
 *
 * @par Algorithm 
 *      determine where to log to , call appropriate functions
 *      
 * @exception None
 *
 * @param [in] cData proivdes configData
 *
 * @param [out] mData provides metaData
 *
 * @return None
 *
 * @note None
 */
void logData( configData cData, vector<metaData> mData )
{
	if( strcmp( cData.logInfo, "Log to Both" ) == 0 )
	{
		//log to file 
		logToFile( cData, mData, LOG_TO_BOTH );

		//log to monitor
		logToMonitor( cData, mData, LOG_TO_BOTH );
	}
	else if ( strcmp( cData.logInfo, "Log to File" ) == 0 )
	{
		//log to file
		logToFile( cData, mData, LOG_TO_FILE );
	}
	else if ( strcmp( cData.logInfo, "Log to Monitor" ) == 0 )
	{
		//log to monitor
		logToMonitor( cData, mData, LOG_TO_MONITOR );
	}
	else
	{
		cout << "Error. Invalid Logging Information: ";
		cout << cData.logInfo << endl;
	}
}

/**
 * @brief logToFile
 *
 * @details outputs data to file
 *          
 * @pre cData and mData are set
 *
 * @post logFilePath contains data
 *
 * @par Algorithm 
 *      using ofstream, output data to file
 *      
 * @exception None
 *
 * @param [in] cData provides configData
 *			   mData provides metaData
 * 			   logCode provides code for log 
 *
 * @param [out] none
 *
 * @return None
 *
 * @note None
 */
void logToFile( configData cData, vector<metaData> mData, int logCode )
{
	//declare and initalize variables
	ofstream fout;
	metaData metaTemp;
	bool isDataValid = true;
	char strTemp[ STR_LEN ];
	int index = 0;
	int configDataNum = 8;
	int mDataSize = mData.size();

	//check file path is valid
	if( cData.logFilePath[ 0 ] == '\0' )
	{
		cout << "Error: Missing Log File Path" << endl;
		return;
	}

	//open file
	fout.open( cData.logFilePath );

	if( !fout.good() )
	{
		cout << "Error. Invalid Log File Path Name." << endl;
		return;
	}
	
	fout << "Configuration File Data" << endl;

	while( isDataValid && ( index < configDataNum ) )
	{
		//check if data is valid
		isDataValid = cData.createConfigDataStr( strTemp, index );
		//print configData to file
		fout << strTemp << endl;
		//increment 
		index++;
	}
	fout << "Logged to: ";
	
	if( logCode == 0 )
	{
		fout << "monitor and " << cData.logFilePath << endl << endl;
	}
	else if( logCode == 1 )
	{
		fout << "monitor" << endl << endl;
	}
	else if( logCode == 2 )
	{
		fout << cData.logFilePath << endl << endl;
	}

	if( isDataValid )
	{
		fout << "Meta-Data Metrics" << endl;

		for ( index = 0; index < mDataSize; index++ )
		{
			metaTemp = mData[ index ];

			if( metaTemp.metaCode != 'S' && metaTemp.metaCode != 'A' )
			{
				//check if data is Valid
				isDataValid = metaTemp.createMetaStr( strTemp, cData);
				fout << strTemp << endl;
			}
		}
	}
	//close file
	fout.close();
}


/**
 * @brief logToMonitor
 *
 * @details outputs data to monitor (terminal)
 *          
 * @pre parameters are set
 *
 * @post monitor displays output
 *
 * @par Algorithm 
 *      use cout to output to terminal
 *      
 * @exception None
 *
 * @param [in] cData provides configData
 *			   mData provides metaData
 * 			   logCode provides code for log 
 *
 * @param [out] None
 *
 * @return None
 *
 * @note None
 */
void logToMonitor( configData cData, vector<metaData> mData, int logCode )
{
	//declare and initalize variables
	metaData metaTemp;
	bool isDataValid = true;
	char strTemp[ STR_LEN ];
	int index = 0;
	int configDataNum = 8;
	int mDataSize = mData.size();

	//check that file path exists
	if( logCode == LOG_TO_BOTH && cData.logFilePath[ 0 ] == '\0' )
	{
		cout << "Error. Missing Log File Path." << endl;
		return;
	}

	cout << "Configuration File Data" << endl;

	while( isDataValid && ( index < configDataNum ) )
	{
		//check if data is valid
		isDataValid = cData.createConfigDataStr( strTemp, index );
		//print configData to file
		cout << strTemp << endl;
		//increment 
		index++;
	}

	cout << "Logged to: ";
	if( logCode == 0 )
	{
		cout << "monitor and " << cData.logFilePath << endl << endl;
	}
	else if( logCode == 1 )
	{
		cout << "monitor" << endl << endl;
	}
	else if( logCode == 2 )
	{
		cout << cData.logFilePath << endl << endl;
	}

	if( isDataValid )
	{
		cout << "Meta-Data Metrics" << endl;

		for ( index = 0; index < mDataSize; index++ )
		{
			metaTemp = mData[ index ];

			if( metaTemp.metaCode != 'S' && metaTemp.metaCode != 'A' )
			{
				//check if data is Valid
				isDataValid = metaTemp.createMetaStr( strTemp, cData);
				cout << strTemp << endl;
			}
		}
	}

}