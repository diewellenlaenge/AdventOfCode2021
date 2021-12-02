#include "Challenge_N.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_N::sm_inputFilePath = "Inputs/Input_Challenge_N.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_N::SetUp_FirstPart()
{
#define FIRSTPART_SETUP_VERSION 1

	std::vector<std::string> lines;
	EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
	if (readErrorCode != EErrorCode::Success)
	{
		return readErrorCode;
	}

	// version 1: 
#if FIRSTPART_SETUP_VERSION == 1

#endif

	return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_N::Run_FirstPart()
{
#define FIRSTPART_VERSION 1

	// version 1: 
#if FIRSTPART_VERSION == 1

#endif

	return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_N::CleanUp_FirstPart()
{
	return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_N::SetUp_SecondPart()
{
#define SECONDPART_SETUP_VERSION 1

	std::vector<std::string> lines;
	EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
	if (readErrorCode != EErrorCode::Success)
	{
		return readErrorCode;
	}

	// version 1: 
#if SECONDPART_SETUP_VERSION == 1

#endif

	return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_N::Run_SecondPart()
{
#define SECONDPART_VERSION 1

	// version 1: 
#if SECONDPART_VERSION == 1

#endif

	return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_N::CleanUp_SecondPart()
{
	return EErrorCode::NotImplemented;
}
