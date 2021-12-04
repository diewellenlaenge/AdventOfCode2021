#include "Challenge_04.h"
#include "../Helpers/FileHelpers.h"

#include <algorithm>
#include <ranges>
#include <cassert>

// :harold:
// https://stackoverflow.com/a/8625010
constexpr std::size_t isqrt_impl
(std::size_t sq, std::size_t dlt, std::size_t value) {
	return sq <= value ?
		isqrt_impl(sq + dlt, dlt + 2, value) : (dlt >> 1) - 1;
}

constexpr std::size_t isqrt(std::size_t value) {
	return isqrt_impl(1, 3, value);
}

constexpr auto board_size = 25;
constexpr auto board_length = isqrt(board_size); // 5



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_04::sm_inputFilePath = "Inputs/Input_Challenge_04.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_04::SetUp_FirstPart()
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
	std::ranges::copy(lines[0]
		| std::ranges::views::split(',')
		| std::ranges::views::transform(
			[](auto&& number) {
				return std::stoi(std::string{ std::string_view(&*number.begin(), std::ranges::distance(number)) });
			}),
		std::back_inserter(numbers_));

	for (const auto& line : lines
		| std::ranges::views::drop(1)
		| std::ranges::views::filter([](const auto& line) { return !line.empty(); }))
	{
		if (boards_.empty() || boards_.back().size() >= board_size) boards_.emplace_back().reserve(board_size + 1);

		std::ranges::copy(line
			| std::ranges::views::split(' ')
			| std::ranges::views::filter([](const auto& number) { return !number.empty(); })
			| std::ranges::views::transform(
				[](auto&& number) {
					return std::stoi(std::string{ std::string_view(&*number.begin(), std::ranges::distance(number)) });
				}),
			std::back_inserter(boards_.back()));

		assert(boards_.back().size() <= board_size);
	}
#endif

	return EErrorCode::Success;
}

bool CheckBoard(const board_type& board, int& sumUnmarked) {
	sumUnmarked = 0;

	// a board can never win if its disabled (vector size higher than actual board size)
	if (board.size() != board_size) return false;

	std::array<std::size_t, board_length * 2> count{ 0 };

	for (auto idx{ 0 }; idx < board_length; ++idx)
	{
		for (auto idx2{ 0 }; idx2 < board_length; ++idx2)
		{
			// check row
			if (board[idx * board_length + idx2] == -1) ++count[idx];
			else sumUnmarked += board[idx * board_length + idx2];

			// check column
			if (board[idx2 * board_length + idx] == -1) ++count[idx + board_length];
		}
	}

	return std::ranges::find(count, board_length) != count.end();
}

EErrorCode CChallenge_04::Run_FirstPart()
{
#define FIRSTPART_VERSION 1

	// version 1: crude
#if FIRSTPART_VERSION == 1
	for (auto number : numbers_)
	{
		for (auto& board : boards_)
		{
			std::ranges::replace(board, number, -1);

			if (auto sumUnmarked{ 0 }; CheckBoard(board, sumUnmarked))
			{
				score_ = sumUnmarked * number;
				goto end;
			}
		}
	}
end:
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_04::CleanUp_FirstPart()
{
	std::cout
		<< "Winner board will win with score = " << score_
		<< std::endl;

	return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_04::SetUp_SecondPart()
{
	return SetUp_FirstPart();
}

EErrorCode CChallenge_04::Run_SecondPart()
{
#define SECONDPART_VERSION 1

	// version 1: crude
#if SECONDPART_VERSION == 1
	for (auto number : numbers_)
	{
		for (auto& board : boards_)
		{
			std::ranges::replace(board, number, -1);

			if (auto sumUnmarked{ 0 }; CheckBoard(board, sumUnmarked))
			{
				score_ = sumUnmarked * number;
				board.push_back(1); // disable the board by increasing its size
			}
		}
	}
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_04::CleanUp_SecondPart()
{
	std::cout
		<< "Loser board will win with score = " << score_
		<< std::endl;

	return EErrorCode::Success;
}
