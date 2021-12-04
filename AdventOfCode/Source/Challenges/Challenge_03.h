#pragma once

#include "Common/Challenge.h"

class CChallenge_03 : public CChallenge
{
private:
	virtual EErrorCode SetUp_FirstPart() override;
	virtual EErrorCode Run_FirstPart() override;
	virtual EErrorCode CleanUp_FirstPart() override;

	virtual EErrorCode SetUp_SecondPart() override;
	virtual EErrorCode Run_SecondPart() override;
	virtual EErrorCode CleanUp_SecondPart() override;

	static std::string const sm_inputFilePath;
	std::vector<int> data_;
	std::vector<std::size_t> parity_;
	unsigned gamma_;
	unsigned epsilon_;
	unsigned oxygen_;
	unsigned scrubber_;
};
