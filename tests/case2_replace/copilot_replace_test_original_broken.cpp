#include <gtest/gtest.h>
#include <string>
#include <boost/algorithm/string/replace.hpp>

// ============================================================================
// BOUNDARY VALUE ANALYSIS (BVA) AND EDGE CASE TEST SUITE
// for boost::algorithm::replace_all function
// ============================================================================

// ============================================================================
// BOUNDARY CONDITION: Empty Input String
// ============================================================================

// BVA: Empty input string with non-empty search and replace
TEST(ReplaceAllEdgeCases, EmptyInputStringWithNonEmptySearchAndReplace) {
    std::string input = "";
    boost::algorithm::replace_all(input, "foo", "bar");
    EXPECT_EQ("", input);
}

// BVA: Empty input string copy variant
TEST(ReplaceAllEdgeCases, EmptyInputStringCopyVariant) {
    std::string input = "";
    std::string result = boost::algorithm::replace_all_copy(input, "foo", "bar");
    EXPECT_EQ("", result);
    EXPECT_EQ("", input);  // Original unchanged
}

// ============================================================================
// BOUNDARY CONDITION: Empty Target String (Search String)
// ============================================================================

// BVA: Empty target string with non-empty input and replacement
// This is a destructive edge case - behavior depends on implementation
TEST(ReplaceAllEdgeCases, EmptyTargetStringWithNonEmptyInput) {
    std::string input = "hello";
    boost::algorithm::replace_all(input, "", "X");
    // Empty search string may be treated as matching every position or not at all
    // Result depends on implementation; documenting actual behavior
    EXPECT_TRUE(input.length() > 0);  // Should not crash
}

// BVA: Empty target string with empty input
TEST(ReplaceAllEdgeCases, EmptyTargetAndEmptyInput) {
    std::string input = "";
    boost::algorithm::replace_all(input, "", "replacement");
    EXPECT_EQ("", input);  // No-op expected
}

// ============================================================================
// BOUNDARY CONDITION: Empty Replacement String
// ============================================================================

// BVA: Empty replacement string removes all occurrences of target
TEST(ReplaceAllEdgeCases, EmptyReplacementStringRemovesTarget) {
    std::string input = "hello world hello";
    boost::algorithm::replace_all(input, "hello", "");
    EXPECT_EQ(" world ", input);
}

// BVA: Empty replacement string with single occurrence
TEST(ReplaceAllEdgeCases, EmptyReplacementSingleOccurrence) {
    std::string input = "foobar";
    boost::algorithm::replace_all(input, "foo", "");
    EXPECT_EQ("bar", input);
}

// BVA: Empty replacement string at start of input
TEST(ReplaceAllEdgeCases, EmptyReplacementAtStartOfInput) {
    std::string input = "foobar";
    boost::algorithm::replace_all(input, "foo", "");
    EXPECT_EQ("bar", input);
}

// BVA: Empty replacement string at end of input
TEST(ReplaceAllEdgeCases, EmptyReplacementAtEndOfInput) {
    std::string input = "barfoo";
    boost::algorithm::replace_all(input, "foo", "");
    EXPECT_EQ("bar", input);
}

// BVA: Empty replacement string with consecutive occurrences
TEST(ReplaceAllEdgeCases, EmptyReplacementConsecutiveOccurrences) {
    std::string input = "foofoobar";
    boost::algorithm::replace_all(input, "foo", "");
    EXPECT_EQ("bar", input);
}

// BVA: Empty replacement with copy variant
TEST(ReplaceAllEdgeCases, EmptyReplacementCopyVariant) {
    std::string input = "hello world hello";
    std::string result = boost::algorithm::replace_all_copy(input, "hello", "");
    EXPECT_EQ(" world ", result);
    EXPECT_EQ("hello world hello", input);  // Original unchanged
}

// ============================================================================
// BOUNDARY CONDITION: Target String Not Found in Input
// ============================================================================

// BVA: Search string completely absent from input
TEST(ReplaceAllEdgeCases, TargetNotFoundInInput) {
    std::string input = "hello world";
    boost::algorithm::replace_all(input, "xyz", "abc");
    EXPECT_EQ("hello world", input);  // No change
}

// BVA: Case-sensitive search - case mismatch
TEST(ReplaceAllEdgeCases, TargetNotFoundCaseMismatch) {
    std::string input = "Hello World";
    boost::algorithm::replace_all(input, "hello", "hi");
    EXPECT_EQ("Hello World", input);  // No change
}

// BVA: Partial match should not replace
TEST(ReplaceAllEdgeCases, PartialMatchNotReplaced) {
    std::string input = "foobar";
    boost::algorithm::replace_all(input, "food", "meal");
    EXPECT_EQ("foobar", input);  // No change
}

// BVA: Search string longer than input
TEST(ReplaceAllEdgeCases, SearchStringLongerThanInput) {
    std::string input = "hi";
    boost::algorithm::replace_all(input, "hello", "goodbye");
    EXPECT_EQ("hi", input);  // No change
}

// ============================================================================
// BOUNDARY CONDITION: Overlapping Replacements
// ============================================================================

// BVA: Overlapping pattern "aba" in "ababa" 
// After replacing first "aba" with "X", the string becomes "Xba"
// The remaining "ba" should not match "aba"
TEST(ReplaceAllEdgeCases, OverlappingPatternAbaInAbaba) {
    std::string input = "ababa";
    boost::algorithm::replace_all(input, "aba", "X");
    EXPECT_EQ("Xba", input);  // First occurrence replaced, second prevented by replacement
}

// BVA: Multiple overlapping occurrences "aa" in "aaaa"
TEST(ReplaceAllEdgeCases, OverlappingPairAaInAaaa) {
    std::string input = "aaaa";
    boost::algorithm::replace_all(input, "aa", "X");
    EXPECT_EQ("XX", input);  // Non-overlapping replacements
}

// BVA: Self-referential pattern - replacement contains search string
TEST(ReplaceAllEdgeCases, SelfReferentialReplacementAvoidInfiniteLoop) {
    std::string input = "aaa";
    boost::algorithm::replace_all(input, "a", "aa");
    // This tests that replace_all doesn't infinitely expand
    EXPECT_GT(input.length(), 3);  // Should expand but not infinitely
    EXPECT_LE(input.length(), 10);  // Reasonable upper bound
}

// BVA: Overlapping three-character pattern
TEST(ReplaceAllEdgeCases, OverlappingThreeCharPattern) {
    std::string input = "abababa";
    boost::algorithm::replace_all(input, "aba", "X");
    EXPECT_EQ("XbX", input);  // Two non-overlapping replacements
}

// ============================================================================
// BOUNDARY CONDITION: Target String Equals Entire Input
// ============================================================================

// BVA: Input string identical to search string
TEST(ReplaceAllEdgeCases, InputIdenticalToSearchString) {
    std::string input = "hello";
    boost::algorithm::replace_all(input, "hello", "world");
    EXPECT_EQ("world", input);
}

// BVA: Input identical to search string, empty replacement
TEST(ReplaceAllEdgeCases, InputIdenticalToSearchStringEmptyReplacement) {
    std::string input = "hello";
    boost::algorithm::replace_all(input, "hello", "");
    EXPECT_EQ("", input);
}

// BVA: Copy variant - input identical to search string
TEST(ReplaceAllEdgeCases, InputIdenticalToSearchStringCopy) {
    std::string input = "hello";
    std::string result = boost::algorithm::replace_all_copy(input, "hello", "world");
    EXPECT_EQ("world", result);
    EXPECT_EQ("hello", input);  // Original unchanged
}

// ============================================================================
// BOUNDARY CONDITION: Single Character Inputs and Searches
// ============================================================================

// BVA: Single character input, single character search and replace
TEST(ReplaceAllEdgeCases, SingleCharacterInputAndSearch) {
    std::string input = "a";
    boost::algorithm::replace_all(input, "a", "b");
    EXPECT_EQ("b", input);
}

// BVA: Single character repeated in input
TEST(ReplaceAllEdgeCases, SingleCharacterRepeatedInInput) {
    std::string input = "aaaa";
    boost::algorithm::replace_all(input, "a", "b");
    EXPECT_EQ("bbbb", input);
}

// BVA: Single character input, no match
TEST(ReplaceAllEdgeCases, SingleCharacterInputNoMatch) {
    std::string input = "a";
    boost::algorithm::replace_all(input, "b", "c");
    EXPECT_EQ("a", input);
}

// ============================================================================
// BOUNDARY CONDITION: Whitespace Handling
// ============================================================================

// BVA: Replace spaces with non-spaces
TEST(ReplaceAllEdgeCases, ReplaceSpacesWithNonSpaces) {
    std::string input = "hello world test";
    boost::algorithm::replace_all(input, " ", "_");
    EXPECT_EQ("hello_world_test", input);
}

// BVA: Replace non-spaces with spaces
TEST(ReplaceAllEdgeCases, ReplaceNonSpacesWithSpaces) {
    std::string input = "hello";
    boost::algorithm::replace_all(input, "o", " ");
    EXPECT_EQ("hell  ", input);
}

// BVA: Input with only whitespace
TEST(ReplaceAllEdgeCases, InputOnlyWhitespace) {
    std::string input = "   ";
    boost::algorithm::replace_all(input, " ", "X");
    EXPECT_EQ("XXX", input);
}

// BVA: Search for whitespace in input without whitespace
TEST(ReplaceAllEdgeCases, SearchWhitespaceInNonWhitespaceInput) {
    std::string input = "helloworld";
    boost::algorithm::replace_all(input, " ", "");
    EXPECT_EQ("helloworld", input);
}

// ============================================================================
// BOUNDARY CONDITION: Consecutive Occurrences
// ============================================================================

// BVA: Multiple consecutive identical patterns
TEST(ReplaceAllEdgeCases, MultipleConsecutivePatterns) {
    std::string input = "foofoofoo";
    boost::algorithm::replace_all(input, "foo", "bar");
    EXPECT_EQ("barbarbar", input);
}

// BVA: Patterns at alternating positions
TEST(ReplaceAllEdgeCases, AlternatingPatterns) {
    std::string input = "fooXfooXfoo";
    boost::algorithm::replace_all(input, "foo", "bar");
    EXPECT_EQ("barXbarXbar", input);
}

// ============================================================================
// BOUNDARY CONDITION: Case-Insensitive Replace (ireplace_all)
// ============================================================================

// BVA: Case-insensitive search with mixed case input
TEST(ReplaceAllEdgeCases, CaseInsensitiveSearchMixedCase) {
    std::string input = "Hello hello HELLO";
    boost::algorithm::ireplace_all(input, "hello", "hi");
    EXPECT_EQ("hi hi hi", input);
}

// BVA: Case-insensitive with empty replacement
TEST(ReplaceAllEdgeCases, CaseInsensitiveEmptyReplacement) {
    std::string input = "Hello WORLD hello";
    boost::algorithm::ireplace_all(input, "hello", "");
    EXPECT_EQ(" WORLD ", input);
}

// BVA: Case-insensitive copy variant
TEST(ReplaceAllEdgeCases, CaseInsensitiveCopyVariant) {
    std::string input = "Hello WORLD hello";
    std::string result = boost::algorithm::ireplace_all_copy(input, "hello", "hi");
    EXPECT_EQ("hi WORLD hi", result);
    EXPECT_EQ("Hello WORLD hello", input);  // Original unchanged
}

// ============================================================================
// BOUNDARY CONDITION: Large Expansion
// ============================================================================

// BVA: Replacement much longer than search string
TEST(ReplaceAllEdgeCases, LargeExpansionReplacement) {
    std::string input = "a";
    boost::algorithm::replace_all(input, "a", "this is a long replacement string");
    EXPECT_EQ("this is a long replacement string", input);
}

// BVA: Multiple replacements with large expansions
TEST(ReplaceAllEdgeCases, MultipleExpansionReplacements) {
    std::string input = "x x x";
    boost::algorithm::replace_all(input, "x", "longword");
    EXPECT_EQ("longword longword longword", input);
}

// ============================================================================
// BOUNDARY CONDITION: Large Contraction
// ============================================================================

// BVA: Replacement much shorter than search string
TEST(ReplaceAllEdgeCases, LargeContractionReplacement) {
    std::string input = "verylongword";
    boost::algorithm::replace_all(input, "verylongword", "x");
    EXPECT_EQ("x", input);
}

// BVA: Multiple replacements with large contractions
TEST(ReplaceAllEdgeCases, MultipleContractionReplacements) {
    std::string input = "longword longword longword";
    boost::algorithm::replace_all(input, "longword", "x");
    EXPECT_EQ("x x x", input);
}

// ============================================================================
// BOUNDARY CONDITION: Special Characters
// ============================================================================

// BVA: Special characters in search and replace
TEST(ReplaceAllEdgeCases, SpecialCharactersInSearch) {
    std::string input = "hello@world@test";
    boost::algorithm::replace_all(input, "@", "#");
    EXPECT_EQ("hello#world#test", input);
}

// BVA: Newline characters in replacement
TEST(ReplaceAllEdgeCases, NewlineInReplacement) {
    std::string input = "hello world";
    boost::algorithm::replace_all(input, " ", "\n");
    EXPECT_EQ("hello\nworld", input);
}

// BVA: Tab characters in search
TEST(ReplaceAllEdgeCases, TabCharacterInSearch) {
    std::string input = "hello\tworld\ttest";
    boost::algorithm::replace_all(input, "\t", " ");
    EXPECT_EQ("hello world test", input);
}

// ============================================================================
// BOUNDARY CONDITION: Original String Preservation (Copy Variants)
// ============================================================================

// BVA: Copy variant leaves original completely unchanged
TEST(ReplaceAllEdgeCases, CopyVariantOriginalUnchanged) {
    std::string original = "hello world hello";
    std::string input = original;
    std::string result = boost::algorithm::replace_all_copy(input, "hello", "hi");
    EXPECT_EQ("hi world hi", result);
    EXPECT_EQ(original, input);  // Original must be completely unchanged
}

// BVA: Case-insensitive copy variant leaves original unchanged
TEST(ReplaceAllEdgeCases, CaseInsensitiveCopyOriginalUnchanged) {
    std::string original = "HELLO world HELLO";
    std::string input = original;
    std::string result = boost::algorithm::ireplace_all_copy(input, "hello", "hi");
    EXPECT_EQ("hi world hi", result);
    EXPECT_EQ(original, input);  // Original must be completely unchanged
}

// ============================================================================
// BOUNDARY CONDITION: Very Long Strings
// ============================================================================

// BVA: Very long input string
TEST(ReplaceAllEdgeCases, VeryLongInputString) {
    std::string input(10000, 'a');
    boost::algorithm::replace_all(input, "a", "b");
    EXPECT_EQ(10000, input.length());
    EXPECT_TRUE(input.find('a') == std::string::npos);  // All 'a's replaced
}

// BVA: Long pattern repeated many times
TEST(ReplaceAllEdgeCases, LongPatternRepeatedManyTimes) {
    std::string input = "";
    for (int i = 0; i < 100; ++i) {
        input += "pattern";
    }
    boost::algorithm::replace_all(input, "pattern", "X");
    EXPECT_EQ(100, input.length());  // 100 'X's
}
