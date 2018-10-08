#include <gtest/gtest.h>
#include "OptionSet.h"

enum class Color { Black, Blue, Red };
enum class Weight { Normal, Bold, Light };
enum class FontType { Verdana, Monaco, TimesNewRoman, Arial };

TEST(OptionSet, TakesDefaultValues)
{
    auto opts = MakeOptionSet(cex(Color::Black), cex(Weight::Normal), cex(FontType::TimesNewRoman));
    ASSERT_EQ(Color::Black, opts.get<Color>());
    ASSERT_EQ(Weight::Normal, opts.get<Weight>());
    ASSERT_EQ(FontType::TimesNewRoman, opts.get<FontType>());

    opts.set(FontType::Monaco)
        .set(Weight::Bold);

    ASSERT_EQ(Weight::Bold, opts.get<Weight>());
    ASSERT_EQ(FontType::Monaco, opts.get<FontType>());
}
