#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <optional>
#include <utility>

namespace integra
{

/// @brief Compile-time key-value table
///
/// The lookup is linear, so the table is meant to stay small. A missing key is
/// not an error: Find returns std::nullopt, which keeps the component usable
/// with exceptions disabled.
template<typename Key, typename Value, std::size_t SIZE>
struct ConstMap
{
    std::array<std::pair<Key, Value>, SIZE> data;

    [[nodiscard]] constexpr std::optional<Value> Find(const Key& key) const
    {
        const auto it =
            std::find_if(data.cbegin(), data.cend(), [&key](const auto& entry) { return entry.first == key; });
        if (it == data.cend())
        {
            return std::nullopt;
        }
        return it->second;
    }
};

template<typename Key, typename Value, std::size_t SIZE>
ConstMap(std::array<std::pair<Key, Value>, SIZE>) -> ConstMap<Key, Value, SIZE>;

} // namespace integra
