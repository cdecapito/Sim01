// Program Information /////////////////////////////////////////////////////////
/**
  * @file configData.h
  *
  * @brief defines class with class definitions 
  * 
  * @details creates class members as well as functions
  *
  * @version Carli DeCapito version 1.0
  *			 Original Code (9/11/17)
  *
  * @note None
  */

//precompiler directives
#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

//header files
//none

//class definition
class configData{
	//constants
	static const int STR_LEN = 100;

public:
	//Constructor
	configData();
	//Destructor
	~configData();

	//Member functions
	bool getConfigData( char filename[] );
	bool createConfigDataStr( char string[], int dataNum );
	void returnError( char string[], char process[] );
	void removeSpace( char string[] );
	bool isEmpty( char string[] );

private:
	char version[ STR_LEN ];
	char filePath[ STR_LEN ];
	char logInfo[ STR_LEN ];
	char logFilePath[ STR_LEN ];
	int processorCT;
	int monitorDT;
	int hardDriveCT;
	int printerCT;
	int keyboardCT;
	int memoryCT;
	int mouseCT;
	int speakerCT;
};

#endif