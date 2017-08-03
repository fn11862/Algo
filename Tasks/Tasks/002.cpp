#include "Headers.h"
#include <unordered_map>

//https://www.hackerrank.com/challenges/attribute-parser/problem

std::unordered_map<std::string, std::string> parse(unsigned N, FileTestData& cin)
{
	std::unordered_map<std::string, std::string> ret;

	std::string currentTag;

	std::string line;
	for (unsigned i = 0; i < N; ++i)
	{
		std::getline(cin, line);
		if (line[1] == '/')
		{
			//This is one-way closing tag. Just remove the last in the line
			size_t pos = currentTag.rfind('.');
			if (pos != std::string::npos)
			{
				currentTag = currentTag.erase(pos, currentTag.size());
			}
			else
			{
				currentTag.clear();
			}
		}
		else 
		{
			if (!currentTag.empty())
			{
				currentTag += '.';
			}
			size_t pos = line.find(' ');
			if (pos == std::string::npos)
			{
				//<tag5>
				currentTag += line.substr(1, line.size()-2);
				continue;
			}

			currentTag += line.substr(1, pos-1);

			size_t posEnd = line.find("\">");
			while (pos < posEnd)
			{
				const size_t posValNameBegin = line.find(' ', pos);
				const size_t posValNameEnd   = line.find(' ', posValNameBegin+1);
				std::string valueName = line.substr(posValNameBegin+1, posValNameEnd - posValNameBegin - 1);

				const size_t posValDataBegin = line.find('\"', posValNameEnd);
				const size_t posValDataEnd   = line.find('\"', posValDataBegin+1);
				std::string valueData = line.substr(posValDataBegin+1, posValDataEnd - posValDataBegin - 1);

				ret[currentTag + '~' + valueName] = valueData;

				pos = posValDataEnd;
			}
		}
	}

	return ret;
}

void t002(unsigned run)
{
	FileTestData cin(__FUNCTION__, run);
	Result       cout(__FUNCTION__, run);
	PerfTimer    perf;

	unsigned N, Q;
	cin >> N >> Q >> std::ws;

	auto values = parse(N, cin);

	std::string line;
	for (unsigned i = 0; i < Q; ++i)
	{
		std::getline(cin, line);
		auto it = values.find(line);
		if (it == values.end())
		{
			cout << "Not Found!";
		}
		else
		{
			cout << it->second;
		}
	}

	perf.PrintResult();
}