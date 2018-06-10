#include <assert.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <tuple>

int main()
{
	std::cout << "working..." << std::endl;


	std::vector<float> a = {5, 7, 9, 2};
	std::vector<float> b = {1, 5, 7, 4};
	std::vector<float> c = {8, 7, 7, 2};

	auto stats = [](const auto& a, const auto& b) -> std::tuple<float, float>
	{
		assert(a.size() == b.size());

		//take the diff
		std::vector<float> x;
		std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(x), [](auto a, auto b) { return a - b; });

		//calc mean
		auto xm = std::accumulate(x.begin(), x.end(), 0.) / x.size();

		//calc the standard deviation
		auto sd = std::accumulate(x.begin(), x.end(), 0.
				, [&xm](auto s, auto v) { auto x = v - xm; return (s + x*x); }
				) / x.size();

		return {xm, sd};

	};


	{
		auto [mean, sd] = stats(a, b);
		std::clog << "diff_mean=" << mean << " diff_sd=" << sd << std::endl;
	}
	{
		auto [mean, sd] = stats(a, c);
		std::clog << "diff_mean=" << mean << " diff_sd=" << sd << std::endl;
	}

	auto structmatch = [](const auto& a, const auto& b)
	{
		assert(a.size() == b.size());
		auto map = [](const auto& v)
		{
			//value-index mapping (could use std::map here)
			std::vector<std::tuple<float, int>> r;
			for (int i = 0; i < v.size(); ++i) {
				r.emplace(r.end(), v[i], i);
			}
			std::sort(r.begin(), r.end(), [](const auto& v1, const auto& v2) { return std::get<0>(v1) < std::get<0>(v2); });
			return r;
		};

		auto sa = map(a);
		auto sb = map(b);

		//create reverse mapping of the original index to the sorted index
		std::unordered_map<int, int> h;
		for (int i = 0; i < sb.size(); ++i) {
			h.emplace(std::get<1>(sb[i]), i);
		}

		//do the index distances
		float dist = 0.f;

		for (int i = 0; i < sa.size(); ++i) {
			auto hit = h.find(std::get<1>(sa[i]));
			assert(hit != h.end());
			auto n = (i - std::get<1>(*hit));
			dist += n*n;
		}

		return std::sqrt(dist);
	};


	std::clog << "score(a,b)=" << structmatch(a, b) << std::endl;
	std::clog << "score(a,c)=" << structmatch(a, c) << std::endl;

	return 0;
}

