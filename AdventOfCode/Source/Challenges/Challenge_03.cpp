#include "Challenge_03.h"
#include "../Helpers/FileHelpers.h"

#include <algorithm>
#include <ranges>



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_03::sm_inputFilePath = "Inputs/Input_Challenge_03.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_03::SetUp_FirstPart()
{
#define FIRSTPART_SETUP_VERSION 1

	std::vector<std::string> lines;
	EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
	if (readErrorCode != EErrorCode::Success)
	{
		return readErrorCode;
	}

	// version 1: ranges
#if FIRSTPART_SETUP_VERSION == 1
	data_.reserve(lines.size());
	std::ranges::transform(lines, std::back_inserter(data_),
		[this](const auto& line)
		{
			parity_.resize(std::max(parity_.size(), line.length()));
			return std::stoi(line, nullptr, 2);
		});
#endif

	return EErrorCode::Success;
}

template<std::ranges::input_range T>
std::size_t GetParity(T data, int idx)
{
	std::size_t count{ 0 };

	for (auto number : data)
	{
		if (number & (1 << idx)) ++count;
	}

	return count;
}

EErrorCode CChallenge_03::Run_FirstPart()
{
	// solution: 2595824

#define FIRSTPART_VERSION 2

	// version 1: crude
#if FIRSTPART_VERSION == 1
	// count number of 1 per index to parity_
	for (auto idx{ 0 }; idx < parity_.size(); ++idx)
	{
		for (auto number : data_)
		{
			if (number & (1 << idx)) ++parity_[idx];
		}
	}

	// create final gamma
	auto treshold{ data_.size() / 2 };
	for (auto idx{ 0 }; idx < parity_.size(); ++idx)
	{
		auto treshold{ data_.size() - parity_[idx] };

		// is 1 most common?
		if (parity_[idx] > treshold)
			gamma_ |= 1U << idx;

		// is 0 most common?
		if (parity_[idx] < treshold)
			epsilon_ |= 1U << idx;
	}
#endif

	// version 1: a bit better than crude
#if FIRSTPART_VERSION == 2
	for (auto idx{ 0 }; idx < parity_.size(); ++idx)
	{
		auto parity = GetParity(data_, idx);
		auto treshold{ data_.size() - parity };

		// is 1 most common?
		if (parity > treshold) gamma_ |= 1U << idx;
	}

	auto mask = (1U << (parity_.size())) - 1;
	epsilon_ = ~(gamma_ & (mask)) & mask;
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_03::CleanUp_FirstPart()
{
	std::cout
		<< "Most common values counted, so"
		<< " gamma = " << gamma_
		<< " and epsilon = " << epsilon_
		<< " results in " << (gamma_ * epsilon_)
		<< std::endl;

	return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_03::SetUp_SecondPart()
{
	return SetUp_FirstPart();
}

EErrorCode CChallenge_03::Run_SecondPart()
{
	// solution: 2135254

#define SECONDPART_VERSION 1

	// version 1: crude, please ignore this crap
#if SECONDPART_VERSION == 1
	auto oxygenData{ data_ };
	auto scrubberData{ data_ };

	for (signed idx{ static_cast<signed>(parity_.size() - 1) }; idx >= 0; --idx)
	{
		if (oxygenData.size() > 1)
		{
			auto parity = GetParity(oxygenData, idx);
			auto treshold{ oxygenData.size() - parity };
			auto common = parity >= treshold;

			std::erase_if(oxygenData,
				[this, common, idx](const auto number)
				{
					return (!common && number & (1 << idx))
						|| (common && !(number & (1 << idx)));
				});
		}

		if (scrubberData.size() > 1)
		{
			auto parity = GetParity(scrubberData, idx);
			auto treshold{ scrubberData.size() - parity };
			auto common = parity >= treshold;

			std::erase_if(scrubberData,
				[this, common, idx](const auto number)
				{
					return (!common && !(number & (1 << idx)))
						|| (common && number & (1 << idx));
				});
		}
	}

	if (oxygenData.size() != 1)
	{
		std::cout << "Failed to calculate oxygen" << std::endl;
		return EErrorCode::Failure;
	}

	oxygen_ = oxygenData[0];

	if (scrubberData.size() != 1)
	{
		std::cout << "Failed to calculate scrubber" << std::endl;
		return EErrorCode::Failure;
	}

	scrubber_ = scrubberData[0];
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_03::CleanUp_SecondPart()
{
	std::cout
		<< "Most common values counted and sorted out, so"
		<< " oxygen = " << oxygen_
		<< " and scrubber = " << scrubber_
		<< " results in " << (oxygen_ * scrubber_)
		<< std::endl;

	return EErrorCode::Success;
}
