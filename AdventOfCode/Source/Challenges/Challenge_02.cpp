#include "Challenge_02.h"
#include "../Helpers/FileHelpers.h"

#include <utility>
#include <algorithm>
#include <ranges>
#include <string_view>



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_02::sm_inputFilePath = "Inputs/Input_Challenge_02.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_FirstPart()
{
#define FIRSTPART_SETUP_VERSION 2

	std::vector<std::string> lines;
	EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
	if (readErrorCode != EErrorCode::Success)
	{
		return readErrorCode;
	}

	// version 1: mhhpf
#if FIRSTPART_SETUP_VERSION == 1
	navs_.reserve(lines.size());
	for (const auto& line : lines)
	{
		std::vector<std::string> nav;
		FileHelper::SplitLine(line, " ", nav);
		navs_.emplace_back(nav[0], std::stoi(nav[1]));
	}
#endif

	// version 2: ranges views
#if FIRSTPART_SETUP_VERSION == 2
	navs_.reserve(lines.size());
	std::ranges::transform(lines, std::back_inserter(navs_),
		[](const auto& line) {
			auto split = (line
				| std::ranges::views::split(' ')
				| std::ranges::views::transform(
					[](auto&& data) {
						return std::string_view(&*data.begin(), std::ranges::distance(data));
					})).begin();

			return std::make_pair(std::string{ *split }, std::stoi(std::string { *std::next(split) }));
		});
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_02::Run_FirstPart()
{
	// solution: 1250395

#define FIRSTPART_VERSION 1

	// version 1: crude
#if FIRSTPART_VERSION == 1
	for (const auto& [command, x] : navs_)
	{
		switch (command[0])
		{
		case 'f': pos_ += x; break; // forward
		case 'd': depth_ += x; break; // down
		case 'u': depth_ -= x; break; // up
		}
	}
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_02::CleanUp_FirstPart()
{
	std::cout
		<< "Multiplication of pos = " << pos_
		<< " and depth = " << depth_
		<< " results in " << (pos_ * depth_)
		<< std::endl;

	return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_SecondPart()
{
	return SetUp_FirstPart();
}

EErrorCode CChallenge_02::Run_SecondPart()
{
	// solution: 1451210346

#define SECONDPART_VERSION 1

	// version 1: crude
#if SECONDPART_VERSION == 1
	int aim{ 0 };

	for (const auto& [command, x] : navs_)
	{
		switch (command[0])
		{
		case 'f': // forward
			pos_ += x;
			depth_ += (x * aim);
			break;
		case 'd': aim += x; break; // down
		case 'u': aim -= x; break; // up
		}
	}
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_02::CleanUp_SecondPart()
{
	return CleanUp_FirstPart();
}
