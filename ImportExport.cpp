/***********************************************************************************************************************
*
* Copyright (c) 2010 - 2026 by Tech Soft 3D, Inc.
* The information contained herein is confidential and proprietary to Tech Soft 3D, Inc., and considered a trade secret
* as defined under civil and criminal statutes. Tech Soft 3D shall pursue its civil and criminal remedies in the event
* of unauthorized use or misappropriation of its trade secrets. Use of this information by anyone other than authorized
* employees of Tech Soft 3D, Inc. is granted only under a written non-disclosure agreement, expressly prescribing the
* scope and manner of such use.
*
***********************************************************************************************************************/

/*
* This sample demonstrates how to load a model and export it as a model file of a different format. The chosen
* format is determined by the file extension of the output file name.
*/

#define INITIALIZE_A3D_API
#include <A3DSDKIncludes.h>
#include <hoops_license.h>

#include "common.hpp"
#include <sstream>

static MY_CHAR acSrcFileName[_MAX_PATH * 2];
static MY_CHAR acDstFileName[_MAX_PATH * 2];
static MY_CHAR acLogFileName[_MAX_PATH * 2];

//######################################################################################################################
#ifdef _MSC_VER
int wmain(A3DInt32 iArgc, A3DUniChar** ppcArgv)
#else
int main(A3DInt32 iArgc, A3DUTF8Char** ppcArgv)
#endif
{
	//
	// ### COMMAND LINE ARGUMENTS
	//
	if (iArgc > 1) MY_STRCPY(acSrcFileName, ppcArgv[1]);
	else           MY_STRCPY(acSrcFileName, DEFAULT_INPUT_CAD);
	if (iArgc > 2) MY_STRCPY(acDstFileName, ppcArgv[2]);
	else           MY_SPRINTF(acDstFileName, "%s.prc", acSrcFileName);
	if (iArgc > 3) MY_STRCPY(acLogFileName, ppcArgv[3]);
	else           MY_SPRINTF(acLogFileName, "%s_Log.txt", acDstFileName);
	GetLogFile(acLogFileName); // Initialize log file

	//
	// ### INITIALIZE HOOPS EXCHANGE
	//
	std::wstringstream bin_dir;
#ifdef _DEBUG
	{
		// Safely retrieve HEXCHANGE_INSTALL_DIR and handle required buffer size
		DWORD required = GetEnvironmentVariableW(L"HEXCHANGE_INSTALL_DIR", nullptr, 0);
		if (required > 0) {
			std::wstring buffer;
			buffer.resize(required);
			DWORD got = GetEnvironmentVariableW(L"HEXCHANGE_INSTALL_DIR", &buffer[0], required);
			if (got > 0 && got < required) {
				buffer.resize(got);
				// normalize trailing separators and use Windows-style separators for the bin path
				if (!buffer.empty() && (buffer.back() == L'\\' || buffer.back() == L'/'))
					buffer.pop_back();
				bin_dir << buffer << L"\\bin\\win64_v142";
			}
			else {
				_tprintf(_T("[Warning] Failed to read environment variable HEXCHANGE_INSTALL_DIR. Using default loader path.\n"));
				bin_dir << L"";
			}
		}
		else {
			_tprintf(_T("[Warning] Environment variable HEXCHANGE_INSTALL_DIR is not set. Using default loader path.\n"));
			bin_dir << L"";
		}
	}
#else
	bin_dir << L"";
#endif

	A3DSDKHOOPSExchangeLoader sHoopsExchangeLoader(bin_dir.str().data(), HOOPS_LICENSE);
	CHECK_RET(sHoopsExchangeLoader.m_eSDKStatus);

	CHECK_RET(A3DDllSetCallbacksMemory(CheckMalloc, CheckFree));
	CHECK_RET(A3DDllSetCallbacksReport(PrintLogMessage, PrintLogWarning, PrintLogError));

	//
	// ### PROCESS SAMPLE CODE
	//

	// specify input file
	A3DImport sImport(acSrcFileName); // see A3DSDKInternalConvert.hxx for import and export detailed parameters
									  // specify output file
	A3DExport sExport(acDstFileName); // see A3DSDKInternalConvert.hxx for import and export detailed parameters

									  // perform conversion
	CHECK_RET(sHoopsExchangeLoader.Convert(sImport, sExport));

	//
	// ### TERMINATE HOOPS EXCHANGE
	//

	// Check memory allocations
	return (int)ListLeaks();
}
