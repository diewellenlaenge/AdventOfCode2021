#include "Challenge_01.h"
#include "../Helpers/FileHelpers.h"

#include <algorithm>
#include <optional>



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_01::sm_inputFilePath = "Inputs/Input_Challenge_01.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_FirstPart()
{
	EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines_);
	if (readErrorCode != EErrorCode::Success)
	{
		return readErrorCode;
	}

	std::transform(lines_.begin(), lines_.end(), std::back_inserter(depths_),
			   [](const std::string& str) { return std::stoi(str); });

	return EErrorCode::Success;
}

EErrorCode CChallenge_01::Run_FirstPart()
{
	std::size_t count = 0;
	auto it = depths_.rbegin();
	const auto stop = std::prev(depths_.rend());

	while (it != stop)
	{
		auto current = *it;
		++it;
		auto previous = *it;

		if (current > previous) ++count;
	}

	std::cout
		<< "There are "
		<< count
		<< " measurements that are larger than the previous measurement"
		<< std::endl;

	return EErrorCode::Success;
}

EErrorCode CChallenge_01::CleanUp_FirstPart()
{
	return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_SecondPart()
{
	EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines_);
	if (readErrorCode != EErrorCode::Success)
	{
		return readErrorCode;
	}

	return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_01::Run_SecondPart()
{
	return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_01::CleanUp_SecondPart()
{
	return EErrorCode::NotImplemented;
}
