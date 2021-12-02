#include "Challenge_01.h"
#include "../Helpers/FileHelpers.h"

#include <algorithm>
#include <numeric>
#include <ranges>



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_01::sm_inputFilePath = "Inputs/Input_Challenge_01.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_FirstPart()
{
#define FIRSTPART_SETUP_VERSION 2

	std::vector<std::string> lines;
	EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
	if (readErrorCode != EErrorCode::Success)
	{
		return readErrorCode;
	}

	// version 1: C++11
#if FIRSTPART_SETUP_VERSION == 1
	depths_.reserve(lines.size());
	std::transform(lines.begin(), lines.end(), std::back_inserter(depths_),
		[](const std::string& line) { return std::stoi(line); });
#endif

	// version 2: ranges
#if FIRSTPART_SETUP_VERSION == 2
	depths_.reserve(lines.size());
	std::ranges::transform(lines, std::back_inserter(depths_),
		[](const auto& line) { return std::stoi(line); });
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_01::Run_FirstPart()
{
	// solution: 1548

#define FIRSTPART_VERSION 3

	// version 1: crude
#if FIRSTPART_VERSION == 1
	auto it = depths_.rbegin();
	const auto stop = std::prev(depths_.rend());

	while (it != stop)
	{
		auto current = *it;
		++it;
		auto previous = *it;

		if (current > previous) ++count_;
}
#endif

	// version 2: ranges
#if FIRSTPART_VERSION == 2
	auto previous = std::ranges::begin(depths_);
	auto current = std::next(previous);
	const auto stop = std::ranges::end(depths_);

	while (current != stop)
	{
		if (*current > *previous) ++count_;
		++previous;
		++current;
	}
#endif

	// version 3: ranges views
#if FIRSTPART_VERSION == 3
	auto previous{ depths_.begin() };

	for (const auto depth : depths_ | std::ranges::views::drop(1))
	{
		if (depth > *previous) ++count_;
		++previous;
	}
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_01::CleanUp_FirstPart()
{
	std::cout
		<< "There are "
		<< count_
		<< " measurements that are larger than the previous measurement"
		<< std::endl;

	return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_SecondPart()
{
	return SetUp_FirstPart();
}

EErrorCode CChallenge_01::Run_SecondPart()
{
	// solution: 1589

#define SECONDPART_VERSION 1

	// version 1: crude
#if SECONDPART_VERSION == 1
	auto previousDepth{ 0 };

	for (auto current = depths_.begin(); current != std::prev(depths_.end(), 2); ++current)
	{
		auto sum{ std::ranges::views::counted(current, 3) };
		auto depth{ std::accumulate(sum.begin(), sum.end(), 0) };

		if (current != depths_.begin())
		{
			if (depth > previousDepth) ++count_;
		}

		previousDepth = depth;
	}
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_01::CleanUp_SecondPart()
{
	std::cout
		<< "There are "
		<< count_
		<< " sums that are larger than the previous sum"
		<< std::endl;

	return EErrorCode::Success;
}
