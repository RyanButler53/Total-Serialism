#include "note.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(CompareNotes, SameOctave){
    Note c{"c", 3};
    Note cs{"cs", 3};
    Note d{"d", 3};
    Note ef{"ef", 3};
    Note e{"e", 3};
    Note f{"f", 3};
    Note fs{"fs", 3};
    Note g{"g", 3};
    Note af{"af", 3};
    Note a{"a", 3};
    Note bf{"bf", 3};
    Note b{"b", 3};

    ASSERT_TRUE(a < bf);
    ASSERT_TRUE(c < bf);
    ASSERT_TRUE(a < b);
    ASSERT_TRUE(f < g);
    ASSERT_TRUE(ef < f);
    ASSERT_TRUE(f < fs);
    ASSERT_TRUE(f < a);
    ASSERT_TRUE(e < g);
    ASSERT_TRUE(cs < a);
    ASSERT_TRUE(g < b);
    ASSERT_TRUE(d < ef);
    ASSERT_TRUE(c < cs);

    ASSERT_EQ(g,g);
    ASSERT_FALSE(g > g);
    ASSERT_NE(f, g);
    ASSERT_EQ(f, f);

    ASSERT_TRUE(g > f);
    ASSERT_TRUE(f > e);
    ASSERT_TRUE(cs > c);
    ASSERT_TRUE(bf > f);
    ASSERT_TRUE(bf > ef);
    ASSERT_TRUE(f > d);
}

TEST(CompareNotes, DiffOctave){
    Note c{"c", 3};
    Note cs{"cs", 2};
    Note d{"d", -1};
    Note ef{"ef", -4};
    Note e{"e", -2};
    Note f{"f", 3};
    Note fs{"fs", 5};
    Note g{"g", 7};
    Note af{"af", 1};
    Note a{"a", 6};
    Note bf{"bf", 2};
    Note b{"b", 1};
    Note a2{"a", 5};

    ASSERT_TRUE(b > ef);
    ASSERT_TRUE(a > bf);
    ASSERT_TRUE(a2 < a);
    ASSERT_NE(a2, a);
    ASSERT_TRUE(ef < f);
    ASSERT_TRUE(c > cs);
    ASSERT_TRUE(g > a);
    ASSERT_TRUE(ef < d);
    ASSERT_FALSE(bf < b);
    ASSERT_TRUE(a2 > b);
}