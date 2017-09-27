CS 446/646 Project 1: Sim01

Written by: Carli DeCapito (9/18/17)
			Version 1.0 - Original 

How to Run: 
		-$ make
		-$ ./Sim01 <CONFIG_FILE>

		<CONFIG_FILE> - filename of the Configuration Data

Files Included:

Sim01.cpp - Main Driver: Calls major functions within main implementation.
			@ line 48, configuration file is read into configData class
			@ line 53, metaData file is read into metaData class
			@ line 58, data is logged to appropriate file or monitor

simFuncs.cpp - Function Helpers: Implements functions to aid in parsing/reading files
			@line 66, calls functions to read Meta-Data from file and store
			@line 129, parses through string (line) of metaData
			@line 169, reads char by char & saves into class
			@line 299, calls funcs to log data to either terminal/file
			@line 351, logs data to file
			@line 488, logs data to monitor (terminal)

configData.h - Configuration Data Class Header File: Provides class data members and member functions.

configData.cpp - Configuration Data Class Implementation File: Provides implementation for member functions
			@line 125, read configuration data into configuration class
			@line 377, creates string of data to print to file/terminal
			@line 476, returns error with configData

metaData.h - Meta-Data Class Header File: Provides class data members and member functions

metaData.cpp - Meta-Data Class Implementation File: Provides implementatoin for member functions
			@line 114, creates string to output to terminal/file
			@line 191, returns a error string to getMetaStr
			@line 256, returns whether or not Meta-Data descriptor is valid


