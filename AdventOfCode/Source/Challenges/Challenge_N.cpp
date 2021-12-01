#include "Challenge_N.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_N::sm_inputFilePath = "Inputs/Input_Challenge_N.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_N::SetUp_FirstPart()
{
	EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines_);
	if (readErrorCode != EErrorCode::Success)
	{
		return readErrorCode;
	}

	return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_N::Run_FirstPart()
{
	return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_N::CleanUp_FirstPart()
{
	return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_N::SetUp_SecondPart()
{
	EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines_);
	if (readErrorCode != EErrorCode::Success)
	{
		return readErrorCode;
	}

	return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_N::Run_SecondPart()
{
	return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_N::CleanUp_SecondPart()
{
	return EErrorCode::NotImplemented;
}
