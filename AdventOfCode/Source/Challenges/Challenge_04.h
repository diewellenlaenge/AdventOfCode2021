#pragma once

#include "Common/Challenge.h"

using board_type = std::vector<int>;

class CChallenge_04 : public CChallenge
{
private:
	virtual EErrorCode SetUp_FirstPart() override;
	virtual EErrorCode Run_FirstPart() override;
	virtual EErrorCode CleanUp_FirstPart() override;

	virtual EErrorCode SetUp_SecondPart() override;
	virtual EErrorCode Run_SecondPart() override;
	virtual EErrorCode CleanUp_SecondPart() override;

	static std::string const sm_inputFilePath;
	std::vector<int> numbers_;
	std::vector<board_type> boards_;
	int score_;
};
