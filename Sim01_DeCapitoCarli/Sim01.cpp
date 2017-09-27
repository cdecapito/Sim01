// Program Information /////////////////////////////////////////////////////////
/**
  * @file Sim01.cpp
  *
  * @brief main driver for OS simulation    
  * 
  * @details Read metaData from files, handle errors and output data
  *
  * @version Carli DeCapito
  *			 Version 1.00 9/11/17
  *
  * @note None
  */

//Header Files
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include "metaData.h"
#include "configData.h"
#include "simFuncs.cpp"

using namespace std;

//function definitions
bool configFileValid( char string[] );

//main implementation
int main( int argc, char * argv[] )
{
	configData cData;
	vector<metaData> mData;
	
	if( argc != 2 )
	{
		cout << "Error: Invalid Number of Command Line Arguments." << endl;
		return 0;
	}

	if( !configFileValid( argv[ 1 ] ) )
	{
		cout << "Error. Invalid Configuration Data File Extension." << endl;
		return 0;
	}

	if( !cData.getConfigData( argv[1] ) )
	{
		return 0;
	}

	if ( !getMetaData( cData.filePath, mData ) )
	{
		return 0;
	}

	logData( cData, mData );

	return 0;
}


bool configFileValid( char string[] )
{
	int index = 0;
	while( string[ index ] != '\0')
	{
		if ( string[ index ] == '.' )
		{
			if( string[ index + 1 ] == 'c' &&
				string[ index + 2 ] == 'o' &&
				string[ index + 3 ] == 'n' &&
				string[ index + 4 ] == 'f' )

			{
				return true;
			}
		}
		index++;
	}
	return false;
}
