#include "Challenge_05.h"
#include "../Helpers/FileHelpers.h"

#include <ranges>
#include <algorithm>
#include <cassert>
#include <string_view>
#include <map>

constexpr auto line_size = 4;



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_05::sm_inputFilePath = "Inputs/Input_Challenge_05.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::SetUp_FirstPart()
{
#define FIRSTPART_SETUP_VERSION 2

	std::vector<std::string> lines;
	EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
	if (readErrorCode != EErrorCode::Success)
	{
		return readErrorCode;
	}

	// version 1: ranges fail
#if FIRSTPART_SETUP_VERSION == 1
	for (const auto& line : lines)
	{
		if (lines_.empty() || lines_.back().size() >= line_size) lines_.emplace_back().reserve(line_size);

		std::ranges::copy(line
			| std::ranges::views::split(std::string_view{ " -> " })
			| std::ranges::views::transform(
				[](auto&& part) {
					return std::string_view(&*part.begin(), std::ranges::distance(part));
				})
			| std::ranges::views::split(',')
			| std::ranges::views::filter([](const auto& number) { return !number.empty(); })
			| std::ranges::views::transform(
				[](auto&& number) {
					return std::stoi(std::string{ std::string_view(&*number.begin(), std::ranges::distance(number)) });
				}),
			std::back_inserter(lines_.back()));

		assert(lines_.back().size() <= line_size);
	}
#endif

	// version 2: at least it works
#if FIRSTPART_SETUP_VERSION == 2
	for (const auto& line : lines)
	{
		if (lines_.empty() || lines_.back().size() >= line_size) lines_.emplace_back().reserve(line_size);

		for (const auto& part : line | std::ranges::views::split(std::string_view{ " -> " }))
		{
			std::ranges::copy(std::string_view(&*part.begin(), std::ranges::distance(part))
				| std::ranges::views::split(',')
				| std::ranges::views::filter([](const auto& number) { return !number.empty(); })
				| std::ranges::views::transform(
					[](auto&& number) {
						return std::stoi(std::string{ std::string_view(&*number.begin(), std::ranges::distance(number)) });
					}),
				std::back_inserter(lines_.back()));
		}

		assert(lines_.back().size() <= line_size);
	}
#endif

	return EErrorCode::Success;
}

struct point_type
{
	int x;
	int y;
};

struct line_type
{
	point_type p1;
	point_type p2;
};

EErrorCode CChallenge_05::Run_FirstPart()
{
	// solution: 6572

#define FIRSTPART_VERSION 1

	// version 1: crude
#if FIRSTPART_VERSION == 1
	std::map<int, std::map<int, std::size_t>> intersections;

	for (const auto& coords : lines_)
	{
		// never do this at home, I'm an expert
		const auto& line{ *reinterpret_cast<const line_type*>(coords.data()) };

		if (line.p1.x == line.p2.x)
		{
			auto end = std::max(line.p1.y, line.p2.y) + 1;

			for (auto y{ std::min(line.p1.y, line.p2.y) }; y < end; ++y)
			{
				intersections[line.p1.x][y]++;
			}
		}
		else if (line.p1.y == line.p2.y)
		{
			auto end = std::max(line.p1.x, line.p2.x) + 1;

			for (auto x{ std::min(line.p1.x, line.p2.x) }; x < end; ++x)
			{
				intersections[x][line.p1.y]++;
			}
		}
	}

	for (const auto& [x, ys] : intersections)
	{
		for (const auto& [y, count] : ys)
		{
			if (count > 1) ++count_;
		}
	}
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_05::CleanUp_FirstPart()
{
	std::cout
		<< "Amount of dangerous points = " << count_
		<< std::endl;

	return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::SetUp_SecondPart()
{
	return SetUp_FirstPart();
}

EErrorCode CChallenge_05::Run_SecondPart()
{
#define SECONDPART_VERSION 1

	// version 1: oh my...
#if SECONDPART_VERSION == 1
	std::map<int, std::map<int, std::size_t>> intersections;

	for (const auto& coords : lines_)
	{
		// never do this at home, I'm an expert
		const auto& line{ *reinterpret_cast<const line_type*>(coords.data()) };

		if (line.p1.x == line.p2.x)
		{
			auto end = std::max(line.p1.y, line.p2.y) + 1;

			for (auto y{ std::min(line.p1.y, line.p2.y) }; y < end; ++y)
			{
				intersections[line.p1.x][y]++;
			}
		}
		else if (line.p1.y == line.p2.y)
		{
			auto end = std::max(line.p1.x, line.p2.x) + 1;

			for (auto x{ std::min(line.p1.x, line.p2.x) }; x < end; ++x)
			{
				intersections[x][line.p1.y]++;
			}
		}
		else
		{
			if (line.p1.x < line.p2.x)
			{
				if (line.p1.y < line.p2.y)
				{
					for (auto x{ line.p1.x }, y{ line.p1.y }; x < line.p2.x + 1 && y < line.p2.y + 1; ++x, ++y)
					{
						intersections[x][y]++;
					}
				}
				else
				{
					for (auto x{ line.p1.x }, y{ line.p1.y }; x < line.p2.x + 1 && y > line.p2.y - 1; ++x, --y)
					{
						intersections[x][y]++;
					}
				}
			}
			else
			{
				if (line.p1.y < line.p2.y)
				{
					for (auto x{ line.p1.x }, y{ line.p1.y }; x > line.p2.x - 1 && y < line.p2.y + 1; --x, ++y)
					{
						intersections[x][y]++;
					}
				}
				else
				{
					for (auto x{ line.p1.x }, y{ line.p1.y }; x > line.p2.x - 1 && y > line.p2.y - 1; --x, --y)
					{
						intersections[x][y]++;
					}
				}
			}

			// what's the problem here?
			/*
			auto x{std::min(line.p1.x, line.p2.x)};
			auto y{ std::min(line.p1.y, line.p2.y) };
			auto endX{ std::max(line.p1.x, line.p2.x) + 1 };
			auto endY{ std::max(line.p1.y, line.p2.y) + 1 };

			assert(y - x == endY - endX);
			
			for (; x < endX && y < endY; ++x, ++y)
			{
				intersections[x][y]++;
			}*/
		}
	}

	for (const auto& [x, ys] : intersections)
	{
		for (const auto& [y, count] : ys)
		{
			if (count > 1) ++count_;
		}
	}
#endif

	return EErrorCode::Success;
}

EErrorCode CChallenge_05::CleanUp_SecondPart()
{
	return CleanUp_FirstPart();
}
