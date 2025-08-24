#ifndef __HEX_PERMUTATION_HPP__
#define __HEX_PERMUTATION_HPP__

#include <map>
#include <string>
#include <vector>
#include "Using.hpp"

class HexPermutation
{
	private:
	
		std::umap<u32, u32>				table;
		
		inline 						HexPermutation(const std::umap<u32, u32>&);
		
		template<typename... OtherType> void		addCycles(const std::vector<u32>&, OtherType...);
		inline void					addCycles(void) const;
		inline HexPermutation				elevate(u32) const;
	
	public:
	
		template<typename... OtherType> inline		HexPermutation(OtherType...);
		
		inline u32					img(u32) const;
		inline std::string				info(void) const;
		inline HexPermutation				inverse(void) const;
		inline HexPermutation				power(i32) const;
		inline i32					signature(void) const;
		
		inline HexPermutation				operator*(const HexPermutation&) const;
};

template<typename... OtherType>
HexPermutation::HexPermutation(OtherType... args)
{
	HexPermutation::addCycles(args...);
}

HexPermutation::HexPermutation(const std::umap<u32, u32>& t) : table(t)
{
}

template<typename... OtherType>
void HexPermutation::addCycles(const std::vector<u32>& v, OtherType... args)
{
	if (v.size() > 1u)
	{
		const auto end = v.cend();
		auto temp = v[0u];
		
		for (auto it = v.cbegin() + 1u; it != end; ++it)
		{
			if (HexPermutation::table.count(temp) != 0u)
				return HexPermutation::table.clear();
			
			HexPermutation::table[temp] = *it;
			temp = *it;
		}
		
		if (HexPermutation::table.count(temp) != 0u)
			return HexPermutation::table.clear();
		else
			HexPermutation::table[temp] = v[0u];
	}
	
	HexPermutation::addCycles(args...);
}

void HexPermutation::addCycles(void) const
{
}

HexPermutation HexPermutation::elevate(u32 p) const
{
	switch (p)
	{
		case 0u: return HexPermutation();
		case 1u: return (*this);
		default: break;
	}
	
	if (p & 1u)
		return HexPermutation::operator*(HexPermutation::operator*(*this).elevate(p >> 1u));
	
	return HexPermutation::operator*(*this).elevate(p >> 1u);
}

u32 HexPermutation::img(u32 k) const
{
	const auto prit = HexPermutation::table.find(k);
	return (HexPermutation::table.cend() != prit ? prit->second : k);
}

std::string HexPermutation::info(void) const
{
	std::map<u32, std::string> cycles;
	std::uset<u32> elements;
	
	for (const auto& pr : HexPermutation::table)
	{
		std::vector<u32> chain;
		auto min = ~0u;
		
		for (auto el = pr.first; elements.count(el) < 1u; el = HexPermutation::table.at(el))
		{
			elements.insert(el);
			chain.push_back(el);
			min = std::min(el, min);
		}
		
		if (chain.empty())
			continue;
		
		const auto end = chain.cend();
		auto it = chain.cbegin();
		
		auto& info = cycles[min];
		std::string str;
		info = '(' + std::to_string(min) + ' ';
		
		while (*it != min)
		{
			str += std::to_string(*it) + ' ';
			++it;
		}
		
		++it;
		
		while (it != end)
		{
			info += std::to_string(*it) + ' ';
			++it;
		}
		
		info += str;
		info.back() = ')';
	}
	
	std::string result;
	
	for (const auto& pr : cycles)
		result += pr.second;
	
	return (result.empty() ? "Id" : result);
}

HexPermutation HexPermutation::inverse(void) const
{
	std::umap<u32, u32> result;
	
	for (const auto& pr : HexPermutation::table)
		result[pr.second] = pr.first;
	
	return HexPermutation(result);
}

HexPermutation HexPermutation::power(i32 p) const
{
	if (p < 0)
		return HexPermutation::inverse().elevate(static_cast<u32>(-p));
	
	return HexPermutation::elevate(static_cast<u32>(p));
}

i32 HexPermutation::signature(void) const
{
	std::uset<u32> elements;
	auto result = true;
	
	for (const auto& pr : HexPermutation::table)
	{
		auto count = 0u;
		
		for (auto el = pr.first; elements.count(el) < 1u; el = HexPermutation::table.at(el))
		{
			elements.insert(el);
			++count;
		}
		
		if (count != 0u and count % 2u == 0u)
			result = not result;
	}
	
	return (result ? 1 : -1);
}

HexPermutation HexPermutation::operator*(const HexPermutation& s) const
{
	const auto end = HexPermutation::table.cend();
	std::umap<u32, u32> result;
	std::uset<u32> used;
	
	for (const auto& pr : s.table)
	{
		const auto prit = HexPermutation::table.find(pr.second);
		used.insert(pr.first);
		
		if (prit == end)
			result.insert(pr);
		else if (prit->second != pr.first)
			result[pr.first] = prit->second;
	}
	
	for (const auto& pr : HexPermutation::table)
	{
		if (used.count(pr.first) < 1u)
			result.insert(pr);
	}
	
	return HexPermutation(result);
}

#endif
