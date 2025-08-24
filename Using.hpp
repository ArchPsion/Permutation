#ifndef __USING_HPP__
#define __USING_HPP__

#include <cstdint>
#include <unordered_map>
#include <unordered_set>

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

namespace std
{
	template <typename Type>
	using uset = unordered_set<Type>;
	
	template <typename Type1, typename Type2>
	using umap = unordered_map<Type1, Type2>;
}

#endif
