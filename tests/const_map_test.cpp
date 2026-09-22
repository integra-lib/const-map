#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <integra/const_map.hpp>
#include <string_view>
#include <utility>

namespace
{

enum class Code : std::uint8_t
{
    eOk      = 0U,
    eTimeout = 1U,
    eCrc     = 2U,
    eUnknown = 3U,
};

constexpr integra::ConstMap<Code, std::string_view, 3> NAMES{{{
    {Code::eOk, "ok"},
    {Code::eTimeout, "timeout"},
    {Code::eCrc, "crc"},
}}};

TEST(ConstMapTest, FindsAPresentKey)
{
    const auto name = NAMES.Find(Code::eTimeout);
    ASSERT_TRUE(name.has_value());
    EXPECT_EQ(name.value(), "timeout");
}

TEST(ConstMapTest, FindsTheFirstAndTheLastKey)
{
    EXPECT_EQ(NAMES.Find(Code::eOk).value(), "ok");
    EXPECT_EQ(NAMES.Find(Code::eCrc).value(), "crc");
}

// Regression: the ported version threw std::range_error on a missing key, which
// does not survive a build with exceptions disabled.
TEST(ConstMapTest, ReturnsNulloptForAMissingKey)
{
    const auto name = NAMES.Find(Code::eUnknown);
    EXPECT_FALSE(name.has_value());
}

TEST(ConstMapTest, WorksAtCompileTime)
{
    static_assert(NAMES.Find(Code::eCrc).has_value());
    static_assert(!NAMES.Find(Code::eUnknown).has_value());
    SUCCEED();
}

} // namespace
