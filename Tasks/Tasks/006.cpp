#include "Headers.h"
#include <algorithm>
#include <unordered_map>

// https://www.hackerrank.com/challenges/gridland-metro/problem

namespace {

	struct Track
	{
		unsigned begin;
		unsigned end;

		unsigned length() const { return end - begin + 1; }
	};

	size_t getOccupiedCells(std::vector<Track>& tracks)
	{
		std::sort(tracks.begin(), tracks.end(), [](const Track& lhs, const Track& rhs) {
			return lhs.begin < rhs.begin;
		});

		auto curr = tracks.begin();
		auto next = tracks.begin() + 1;

		size_t total = 0;

		while (next != tracks.end())
		{
			if (curr->end >= next->begin)
			{
				curr->end = std::max(curr->end, next->end);
				++next;
			}
			else 
			{
				total += curr->length();
				curr = next;
				++next;
			}
		}

		total += curr->length();
		
		return total;
	}

} // unnamed namespace

void t006(unsigned run)
{
	FileTestData cin (__FUNCTION__, run);
	Result       cout(__FUNCTION__, run);
	PerfTimer    perf;

	size_t N, M, numTracks;
	cin >> N >> M >> numTracks;

	std::unordered_map<unsigned, std::vector<Track>> tracks;

	for (size_t i = 0; i < numTracks; ++i)
	{
		unsigned row, begin, end;
		cin >> row >> begin >> end;
		tracks[row].emplace_back(Track{ begin, end });
	}

	size_t totalCells = N * M;
	for (auto& row : tracks)
	{
		totalCells -= getOccupiedCells(row.second);
	}

	cout << totalCells;


	perf.PrintResult();
}