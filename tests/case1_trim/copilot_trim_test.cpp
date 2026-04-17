#include <gtest/gtest.h>
#include <string>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <sstream>

// ============================================================================
// EQUIVALENCE PARTITIONING (EP) AND BOUNDARY VALUE ANALYSIS (BVA) TEST SUITE
// for boost::algorithm::trim functions
// ============================================================================

// ============================================================================
// TRIM_LEFT Tests
// ============================================================================

// EP: Valid input with leading whitespace (space characters)
// BVA: String with one leading space
TEST(TrimLeft, SingleLeadingSpace) {
    std::string input = " hello";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with leading whitespace (space characters)
// BVA: String with multiple leading spaces
TEST(TrimLeft, MultipleLeadingSpaces) {
    std::string input = "    hello";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with leading whitespace (tab characters)
// BVA: String with single leading tab
TEST(TrimLeft, SingleLeadingTab) {
    std::string input = "\thello";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with leading whitespace (multiple tab characters)
// BVA: String with multiple leading tabs
TEST(TrimLeft, MultipleLeadingTabs) {
    std::string input = "\t\t\thello";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with leading whitespace (newline characters)
// BVA: String with single leading newline
TEST(TrimLeft, SingleLeadingNewline) {
    std::string input = "\nhello";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with leading whitespace (mixed whitespace types)
// BVA: String with mixed leading whitespace
TEST(TrimLeft, MixedLeadingWhitespace) {
    std::string input = " \t\n hello";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("hello", input);
}

// EP: Boundary value - Empty string
// BVA: Minimum input length (empty)
TEST(TrimLeft, EmptyString) {
    std::string input = "";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("", input);
}

// EP: Boundary value - String with no leading whitespace
// BVA: No leading whitespace
TEST(TrimLeft, NoLeadingWhitespace) {
    std::string input = "hello";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("hello", input);
}

// EP: Boundary value - String with only whitespace
// BVA: Entire string is whitespace
TEST(TrimLeft, OnlyWhitespace) {
    std::string input = "   \t\n  ";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("", input);
}

// EP: Valid input with trailing whitespace (should not be trimmed)
// BVA: Leading and trailing whitespace present
TEST(TrimLeft, LeadingAndTrailingWhitespace) {
    std::string input = "  hello  ";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("hello  ", input);
}

// EP: Boundary value - Single character, no whitespace
// BVA: Minimum non-empty string without whitespace
TEST(TrimLeft, SingleCharacter) {
    std::string input = "a";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("a", input);
}

// EP: Boundary value - Single whitespace character only
// BVA: Minimum whitespace-only string
TEST(TrimLeft, SingleWhitespaceCharacter) {
    std::string input = " ";
    boost::algorithm::trim_left(input);
    EXPECT_EQ("", input);
}

// ============================================================================
// TRIM_RIGHT Tests
// ============================================================================

// EP: Valid input with trailing whitespace (space characters)
// BVA: String with one trailing space
TEST(TrimRight, SingleTrailingSpace) {
    std::string input = "hello ";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with trailing whitespace (space characters)
// BVA: String with multiple trailing spaces
TEST(TrimRight, MultipleTrailingSpaces) {
    std::string input = "hello    ";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with trailing whitespace (tab characters)
// BVA: String with single trailing tab
TEST(TrimRight, SingleTrailingTab) {
    std::string input = "hello\t";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with trailing whitespace (multiple tab characters)
// BVA: String with multiple trailing tabs
TEST(TrimRight, MultipleTrailingTabs) {
    std::string input = "hello\t\t\t";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with trailing whitespace (newline characters)
// BVA: String with single trailing newline
TEST(TrimRight, SingleTrailingNewline) {
    std::string input = "hello\n";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with trailing whitespace (mixed whitespace types)
// BVA: String with mixed trailing whitespace
TEST(TrimRight, MixedTrailingWhitespace) {
    std::string input = "hello \t\n ";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("hello", input);
}

// EP: Boundary value - Empty string
// BVA: Minimum input length (empty)
TEST(TrimRight, EmptyString) {
    std::string input = "";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("", input);
}

// EP: Boundary value - String with no trailing whitespace
// BVA: No trailing whitespace
TEST(TrimRight, NoTrailingWhitespace) {
    std::string input = "hello";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("hello", input);
}

// EP: Boundary value - String with only whitespace
// BVA: Entire string is whitespace
TEST(TrimRight, OnlyWhitespace) {
    std::string input = "   \t\n  ";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("", input);
}

// EP: Valid input with leading whitespace (should not be trimmed)
// BVA: Leading and trailing whitespace present
TEST(TrimRight, LeadingAndTrailingWhitespace) {
    std::string input = "  hello  ";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("  hello", input);
}

// EP: Boundary value - Single character, no whitespace
// BVA: Minimum non-empty string without whitespace
TEST(TrimRight, SingleCharacter) {
    std::string input = "a";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("a", input);
}

// EP: Boundary value - Single whitespace character only
// BVA: Minimum whitespace-only string
TEST(TrimRight, SingleWhitespaceCharacter) {
    std::string input = " ";
    boost::algorithm::trim_right(input);
    EXPECT_EQ("", input);
}

// ============================================================================
// TRIM (Both Sides) Tests
// ============================================================================

// EP: Valid input with leading and trailing whitespace (spaces)
// BVA: Symmetric whitespace on both ends
TEST(TrimBothSides, LeadingAndTrailingSpaces) {
    std::string input = "  hello  ";
    boost::algorithm::trim(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with leading and trailing whitespace (tabs)
// BVA: Mixed tabs on both sides
TEST(TrimBothSides, LeadingAndTrailingTabs) {
    std::string input = "\t\thello\t\t";
    boost::algorithm::trim(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with leading and trailing whitespace (newlines)
// BVA: Newlines on both sides
TEST(TrimBothSides, LeadingAndTrailingNewlines) {
    std::string input = "\n\nhello\n\n";
    boost::algorithm::trim(input);
    EXPECT_EQ("hello", input);
}

// EP: Valid input with mixed whitespace on both sides
// BVA: Asymmetric mixed whitespace
TEST(TrimBothSides, MixedWhitespaceBothSides) {
    std::string input = " \t\nhello\n\t ";
    boost::algorithm::trim(input);
    EXPECT_EQ("hello", input);
}

// EP: Boundary value - Empty string
// BVA: Minimum input length (empty)
TEST(TrimBothSides, EmptyString) {
    std::string input = "";
    boost::algorithm::trim(input);
    EXPECT_EQ("", input);
}

// EP: Boundary value - String with only whitespace
// BVA: Entire string is whitespace
TEST(TrimBothSides, OnlyWhitespace) {
    std::string input = "   \t\n  ";
    boost::algorithm::trim(input);
    EXPECT_EQ("", input);
}

// EP: Boundary value - String with no whitespace
// BVA: No leading or trailing whitespace
TEST(TrimBothSides, NoWhitespace) {
    std::string input = "hello";
    boost::algorithm::trim(input);
    EXPECT_EQ("hello", input);
}

// EP: Boundary value - Only leading whitespace
// BVA: Asymmetric case (only leading)
TEST(TrimBothSides, OnlyLeadingWhitespace) {
    std::string input = "  hello";
    boost::algorithm::trim(input);
    EXPECT_EQ("hello", input);
}

// EP: Boundary value - Only trailing whitespace
// BVA: Asymmetric case (only trailing)
TEST(TrimBothSides, OnlyTrailingWhitespace) {
    std::string input = "hello  ";
    boost::algorithm::trim(input);
    EXPECT_EQ("hello", input);
}

// EP: Boundary value - Single character, no whitespace
// BVA: Minimum non-empty string without whitespace
TEST(TrimBothSides, SingleCharacter) {
    std::string input = "a";
    boost::algorithm::trim(input);
    EXPECT_EQ("a", input);
}

// EP: Boundary value - Single whitespace character only
// BVA: Minimum whitespace-only string
TEST(TrimBothSides, SingleWhitespaceCharacter) {
    std::string input = " ";
    boost::algorithm::trim(input);
    EXPECT_EQ("", input);
}

// EP: Valid input with internal spaces (should be preserved)
// BVA: Multiple words with internal spacing
TEST(TrimBothSides, InternalSpaces) {
    std::string input = "  hello   world  ";
    boost::algorithm::trim(input);
    EXPECT_EQ("hello   world", input);
}

// ============================================================================
// TRIM_LEFT_COPY Tests
// ============================================================================

// EP: Valid input with leading whitespace
// BVA: Copy operation with leading spaces
TEST(TrimLeftCopy, WithLeadingSpaces) {
    std::string input = "  hello";
    std::string result = boost::algorithm::trim_left_copy(input);
    EXPECT_EQ("hello", result);
    EXPECT_EQ("  hello", input);  // Original unchanged
}

// EP: Boundary value - Empty string
// BVA: Copy of empty string
TEST(TrimLeftCopy, EmptyString) {
    std::string input = "";
    std::string result = boost::algorithm::trim_left_copy(input);
    EXPECT_EQ("", result);
}

// EP: Boundary value - String with only whitespace
// BVA: Copy of whitespace-only string
TEST(TrimLeftCopy, OnlyWhitespace) {
    std::string input = "   ";
    std::string result = boost::algorithm::trim_left_copy(input);
    EXPECT_EQ("", result);
}

// EP: Valid input with mixed leading whitespace
// BVA: Copy with mixed whitespace types
TEST(TrimLeftCopy, MixedLeadingWhitespace) {
    std::string input = " \t\nhello";
    std::string result = boost::algorithm::trim_left_copy(input);
    EXPECT_EQ("hello", result);
}

// ============================================================================
// TRIM_RIGHT_COPY Tests
// ============================================================================

// EP: Valid input with trailing whitespace
// BVA: Copy operation with trailing spaces
TEST(TrimRightCopy, WithTrailingSpaces) {
    std::string input = "hello  ";
    std::string result = boost::algorithm::trim_right_copy(input);
    EXPECT_EQ("hello", result);
    EXPECT_EQ("hello  ", input);  // Original unchanged
}

// EP: Boundary value - Empty string
// BVA: Copy of empty string
TEST(TrimRightCopy, EmptyString) {
    std::string input = "";
    std::string result = boost::algorithm::trim_right_copy(input);
    EXPECT_EQ("", result);
}

// EP: Boundary value - String with only whitespace
// BVA: Copy of whitespace-only string
TEST(TrimRightCopy, OnlyWhitespace) {
    std::string input = "   ";
    std::string result = boost::algorithm::trim_right_copy(input);
    EXPECT_EQ("", result);
}

// EP: Valid input with mixed trailing whitespace
// BVA: Copy with mixed whitespace types
TEST(TrimRightCopy, MixedTrailingWhitespace) {
    std::string input = "hello \t\n";
    std::string result = boost::algorithm::trim_right_copy(input);
    EXPECT_EQ("hello", result);
}

// ============================================================================
// TRIM_COPY Tests
// ============================================================================

// EP: Valid input with leading and trailing whitespace
// BVA: Copy operation with both-sided spaces
TEST(TrimCopy, WithLeadingAndTrailingSpaces) {
    std::string input = "  hello  ";
    std::string result = boost::algorithm::trim_copy(input);
    EXPECT_EQ("hello", result);
    EXPECT_EQ("  hello  ", input);  // Original unchanged
}

// EP: Boundary value - Empty string
// BVA: Copy of empty string
TEST(TrimCopy, EmptyString) {
    std::string input = "";
    std::string result = boost::algorithm::trim_copy(input);
    EXPECT_EQ("", result);
}

// EP: Boundary value - String with only whitespace
// BVA: Copy of whitespace-only string
TEST(TrimCopy, OnlyWhitespace) {
    std::string input = "     ";
    std::string result = boost::algorithm::trim_copy(input);
    EXPECT_EQ("", result);
}

// EP: Valid input with mixed whitespace on both sides
// BVA: Copy with mixed whitespace types
TEST(TrimCopy, MixedWhitespaceBothSides) {
    std::string input = "\t hello\n";
    std::string result = boost::algorithm::trim_copy(input);
    EXPECT_EQ("hello", result);
}

// EP: Valid input with internal spaces (should be preserved in copy)
// BVA: Multiple words preservation
TEST(TrimCopy, InternalSpaces) {
    std::string input = "  hello   world  ";
    std::string result = boost::algorithm::trim_copy(input);
    EXPECT_EQ("hello   world", result);
}

// ============================================================================
// TRIM_LEFT_IF Tests (with custom predicate)
// ============================================================================

// EP: Valid input with leading spaces, using is_space predicate
// BVA: Custom predicate with leading spaces
TEST(TrimLeftIf, CustomPredicateWithLeadingSpaces) {
    std::string input = "  hello";
    boost::algorithm::trim_left_if(input, boost::algorithm::is_space());
    EXPECT_EQ("hello", input);
}

// EP: Valid input with mixed leading whitespace, using is_space predicate
// BVA: Custom predicate with mixed whitespace
TEST(TrimLeftIf, CustomPredicateWithMixedWhitespace) {
    std::string input = " \t\nhello";
    boost::algorithm::trim_left_if(input, boost::algorithm::is_space());
    EXPECT_EQ("hello", input);
}

// ============================================================================
// TRIM_RIGHT_IF Tests (with custom predicate)
// ============================================================================

// EP: Valid input with trailing spaces, using is_space predicate
// BVA: Custom predicate with trailing spaces
TEST(TrimRightIf, CustomPredicateWithTrailingSpaces) {
    std::string input = "hello  ";
    boost::algorithm::trim_right_if(input, boost::algorithm::is_space());
    EXPECT_EQ("hello", input);
}

// EP: Valid input with mixed trailing whitespace, using is_space predicate
// BVA: Custom predicate with mixed whitespace
TEST(TrimRightIf, CustomPredicateWithMixedWhitespace) {
    std::string input = "hello \t\n";
    boost::algorithm::trim_right_if(input, boost::algorithm::is_space());
    EXPECT_EQ("hello", input);
}

// ============================================================================
// TRIM_IF Tests (with custom predicate)
// ============================================================================

// EP: Valid input with both-sided whitespace, using is_space predicate
// BVA: Custom predicate with both-sided whitespace
TEST(TrimIf, CustomPredicateWithBothSidedWhitespace) {
    std::string input = "  hello  ";
    boost::algorithm::trim_if(input, boost::algorithm::is_space());
    EXPECT_EQ("hello", input);
}

// EP: Valid input with mixed whitespace on both sides
// BVA: Custom predicate with mixed whitespace types
TEST(TrimIf, CustomPredicateWithMixedWhitespace) {
    std::string input = "\t hello\n";
    boost::algorithm::trim_if(input, boost::algorithm::is_space());
    EXPECT_EQ("hello", input);
}

// ============================================================================
// TRIM_LEFT_COPY_IF Tests (with custom predicate)
// ============================================================================

// EP: Valid input with leading spaces, copy with predicate
// BVA: Copy operation with custom predicate
TEST(TrimLeftCopyIf, CustomPredicateWithLeadingSpaces) {
    std::string input = "  hello";
    std::string result = boost::algorithm::trim_left_copy_if(input, boost::algorithm::is_space());
    EXPECT_EQ("hello", result);
    EXPECT_EQ("  hello", input);  // Original unchanged
}

// ============================================================================
// TRIM_RIGHT_COPY_IF Tests (with custom predicate)
// ============================================================================

// EP: Valid input with trailing spaces, copy with predicate
// BVA: Copy operation with custom predicate
TEST(TrimRightCopyIf, CustomPredicateWithTrailingSpaces) {
    std::string input = "hello  ";
    std::string result = boost::algorithm::trim_right_copy_if(input, boost::algorithm::is_space());
    EXPECT_EQ("hello", result);
    EXPECT_EQ("hello  ", input);  // Original unchanged
}

// ============================================================================
// TRIM_COPY_IF Tests (with custom predicate)
// ============================================================================

// EP: Valid input with both-sided whitespace, copy with predicate
// BVA: Copy operation with custom predicate on both sides
TEST(TrimCopyIf, CustomPredicateWithBothSidedWhitespace) {
    std::string input = "  hello  ";
    std::string result = boost::algorithm::trim_copy_if(input, boost::algorithm::is_space());
    EXPECT_EQ("hello", result);
    EXPECT_EQ("  hello  ", input);  // Original unchanged
}
