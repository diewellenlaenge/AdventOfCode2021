#pragma once

#include "Common/Challenge.h"

class CChallenge_05 : public CChallenge
{
private:
	virtual EErrorCode SetUp_FirstPart() override;
	virtual EErrorCode Run_FirstPart() override;
	virtual EErrorCode CleanUp_FirstPart() override;

	virtual EErrorCode SetUp_SecondPart() override;
	virtual EErrorCode Run_SecondPart() override;
	virtual EErrorCode CleanUp_SecondPart() override;

	static std::string const sm_inputFilePath;
	std::vector<std::vector<int>> lines_;
	std::size_t count_;
};
