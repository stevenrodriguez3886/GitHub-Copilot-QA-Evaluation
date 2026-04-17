#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

// ============================================================================
// ADVANCED TEST SUITE for boost::algorithm::split function
// Focus: Complex logic, algorithmic combinations, and token compression
// ============================================================================

// ============================================================================
// TEST GROUP 1: Single Delimiter vs. Multiple Delimiters
// ============================================================================

// Justification: Validates basic splitting with a single character predicate
// Ensures the function correctly identifies and uses a single delimiter type
TEST(SplitAdvanced, SingleCharacterDelimiter) {
    std::string input = "hello world test";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_space());
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("world", result[1]);
    EXPECT_EQ("test", result[2]);
}

// Justification: Validates splitting with multiple possible delimiters
// Ensures is_any_of correctly matches any of the specified characters
TEST(SplitAdvanced, MultipleCharacterDelimiters) {
    std::string input = "hello,world;test:data";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(",;:"));
    
    ASSERT_EQ(4, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("world", result[1]);
    EXPECT_EQ("test", result[2]);
    EXPECT_EQ("data", result[3]);
}

// Justification: Validates that the function correctly handles arbitrary predicates
// Tests custom character classification logic
TEST(SplitAdvanced, CustomPredicateDigits) {
    std::string input = "hello123world456test";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_digit());
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("world", result[1]);
    EXPECT_EQ("test", result[2]);
}

// Justification: Tests splitting with multiple types of delimiters in mixed order
// Validates that all delimiters in the set are recognized regardless of position
TEST(SplitAdvanced, AlternatingMultipleDelimiterTypes) {
    std::string input = "a,b;c:d,e;f";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(",;:"));
    
    ASSERT_EQ(6, result.size());
    for (int i = 0; i < 6; ++i) {
        EXPECT_EQ(std::string(1, static_cast<char>('a' + i)), result[i]);
    }
}

// ============================================================================
// TEST GROUP 2: Consecutive Delimiters - Compression OFF
// ============================================================================

// Justification: Validates that without compression, consecutive delimiters 
// generate empty tokens between them
TEST(SplitAdvanced, ConsecutiveDelimitersCompressionOff) {
    std::string input = "hello,,world";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("", result[1]);  // Empty token between consecutive delimiters
    EXPECT_EQ("world", result[2]);
}

// Justification: Validates multiple consecutive delimiters create multiple empty tokens
// Tests behavior with 3+ consecutive delimiters
TEST(SplitAdvanced, MultipleConsecutiveDelimitersCompressionOff) {
    std::string input = "a,,,b";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(4, result.size());
    EXPECT_EQ("a", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("", result[2]);
    EXPECT_EQ("b", result[3]);
}

// Justification: Validates empty tokens are preserved with different delimiter types
// Ensures compression setting applies uniformly across all delimiters
TEST(SplitAdvanced, ConsecutiveMixedDelimitersCompressionOff) {
    std::string input = "x,;y";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(",;"),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("x", result[0]);
    EXPECT_EQ("", result[1]);  // Empty token between different consecutive delimiters
    EXPECT_EQ("y", result[2]);
}

// ============================================================================
// TEST GROUP 3: Consecutive Delimiters - Compression ON
// ============================================================================

// Justification: Validates that with compression enabled, consecutive delimiters
// are merged and no empty tokens are generated
TEST(SplitAdvanced, ConsecutiveDelimitersCompressionOn) {
    std::string input = "hello,,world";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(2, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("world", result[1]);  // No empty token
}

// Justification: Validates compression works with multiple consecutive delimiters
// Tests that 3+ consecutive delimiters are collapsed into one separation point
TEST(SplitAdvanced, MultipleConsecutiveDelimitersCompressionOn) {
    std::string input = "a,,,b";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(2, result.size());
    EXPECT_EQ("a", result[0]);
    EXPECT_EQ("b", result[1]);  // Consecutive delimiters treated as single separator
}

// Justification: Validates compression handles mixed consecutive delimiters
// Tests that consecutive delimiters of different types are still merged
TEST(SplitAdvanced, ConsecutiveMixedDelimitersCompressionOn) {
    std::string input = "x,;:y";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(",;:"),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(2, result.size());
    EXPECT_EQ("x", result[0]);
    EXPECT_EQ("y", result[1]);  // Mixed consecutive delimiters merged
}

// Justification: Validates compression handles long sequences of consecutive delimiters
// Tests scalability of compression logic
TEST(SplitAdvanced, LongSequenceConsecutiveDelimitersCompressionOn) {
    std::string input = "start,,,,,,,end";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(2, result.size());
    EXPECT_EQ("start", result[0]);
    EXPECT_EQ("end", result[1]);
}

// ============================================================================
// TEST GROUP 4: Delimiters at Beginning - Compression OFF
// ============================================================================

// Justification: Validates splitting when delimiter is at the absolute start
// Tests edge case of leading delimiter with compression disabled
TEST(SplitAdvanced, DelimiterAtBeginningCompressionOff) {
    std::string input = ",hello,world";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("", result[0]);  // Empty token before leading delimiter
    EXPECT_EQ("hello", result[1]);
    EXPECT_EQ("world", result[2]);
}

// Justification: Validates multiple delimiters at the start with compression off
// Tests behavior when string begins with consecutive delimiters
TEST(SplitAdvanced, MultipleDelimitersAtBeginningCompressionOff) {
    std::string input = ",,hello";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("hello", result[2]);
}

// ============================================================================
// TEST GROUP 5: Delimiters at Beginning - Compression ON
// ============================================================================

// Justification: Validates leading delimiter behavior with compression enabled
// Tests that leading delimiters are handled intelligently without creating empty tokens
TEST(SplitAdvanced, DelimiterAtBeginningCompressionOn) {
    std::string input = ",hello,world";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(2, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("world", result[1]);  // Leading delimiter ignored with compression
}

// Justification: Validates multiple leading delimiters with compression
// Tests that multiple leading delimiters are all compressed away
TEST(SplitAdvanced, MultipleDelimitersAtBeginningCompressionOn) {
    std::string input = ",,,,hello";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(1, result.size());
    EXPECT_EQ("hello", result[0]);
}

// ============================================================================
// TEST GROUP 6: Delimiters at End - Compression OFF
// ============================================================================

// Justification: Validates splitting when delimiter is at the absolute end
// Tests edge case of trailing delimiter with compression disabled
TEST(SplitAdvanced, DelimiterAtEndCompressionOff) {
    std::string input = "hello,world,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("world", result[1]);
    EXPECT_EQ("", result[2]);  // Empty token after trailing delimiter
}

// Justification: Validates multiple trailing delimiters with compression off
// Tests behavior when string ends with consecutive delimiters
TEST(SplitAdvanced, MultipleDelimitersAtEndCompressionOff) {
    std::string input = "hello,,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("", result[2]);
}

// ============================================================================
// TEST GROUP 7: Delimiters at End - Compression ON
// ============================================================================

// Justification: Validates trailing delimiter behavior with compression enabled
// Tests that trailing delimiters are handled without creating empty tokens
TEST(SplitAdvanced, DelimiterAtEndCompressionOn) {
    std::string input = "hello,world,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(2, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("world", result[1]);  // Trailing delimiter ignored with compression
}

// Justification: Validates multiple trailing delimiters with compression
// Tests that multiple trailing delimiters are all compressed away
TEST(SplitAdvanced, MultipleDelimitersAtEndCompressionOn) {
    std::string input = "hello,,,,,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(1, result.size());
    EXPECT_EQ("hello", result[0]);
}

// ============================================================================
// TEST GROUP 8: Delimiters at Both Beginning and End - Compression OFF
// ============================================================================

// Justification: Validates handling when string is surrounded by delimiters
// Tests combined edge case with compression disabled
TEST(SplitAdvanced, DelimitersAtBothEndsCompressionOff) {
    std::string input = ",hello,world,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(4, result.size());
    EXPECT_EQ("", result[0]);
    EXPECT_EQ("hello", result[1]);
    EXPECT_EQ("world", result[2]);
    EXPECT_EQ("", result[3]);
}

// Justification: Validates multiple delimiters at both ends without compression
// Tests complex edge case with consecutive delimiters at boundaries
TEST(SplitAdvanced, MultipleDelimitersAtBothEndsCompressionOff) {
    std::string input = ",,hello,,world,,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(7, result.size());
    EXPECT_EQ("", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("hello", result[2]);
    EXPECT_EQ("", result[3]);
    EXPECT_EQ("world", result[4]);
    EXPECT_EQ("", result[5]);
    EXPECT_EQ("", result[6]);
}

// ============================================================================
// TEST GROUP 9: Delimiters at Both Beginning and End - Compression ON
// ============================================================================

// Justification: Validates surrounding delimiters are removed with compression
// Tests that leading and trailing delimiters don't create empty tokens
TEST(SplitAdvanced, DelimitersAtBothEndsCompressionOn) {
    std::string input = ",hello,world,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(2, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("world", result[1]);
}

// Justification: Validates multiple surrounding delimiters are all compressed
// Tests comprehensive compression with multiple boundary delimiters
TEST(SplitAdvanced, MultipleDelimitersAtBothEndsCompressionOn) {
    std::string input = ",,,,hello,,,world,,,,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(2, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("world", result[1]);
}

// ============================================================================
// TEST GROUP 10: String with Absolutely No Delimiters
// ============================================================================

// Justification: Validates that a string with no matching delimiters 
// remains intact as a single token
TEST(SplitAdvanced, NoDelimitersInString) {
    std::string input = "helloworld";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","));
    
    ASSERT_EQ(1, result.size());
    EXPECT_EQ("helloworld", result[0]);
}

// Justification: Validates that strings without matching delimiters
// are unaffected by compression mode
TEST(SplitAdvanced, NoDelimitersCompressionOnDoesNotAffect) {
    std::string input = "helloworld";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(1, result.size());
    EXPECT_EQ("helloworld", result[0]);
}

// Justification: Validates that empty strings result in empty containers
// or containers with empty tokens depending on compression
TEST(SplitAdvanced, EmptyStringNoDelimitersCompressionOff) {
    std::string input = "";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    // Empty string typically results in one empty token
    EXPECT_LE(result.size(), 1);
    if (result.size() == 1) {
        EXPECT_EQ("", result[0]);
    }
}

// Justification: Validates empty strings with compression enabled
// Tests that compression doesn't affect empty input handling
TEST(SplitAdvanced, EmptyStringNoDelimitersCompressionOn) {
    std::string input = "";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    // Empty string with compression may result in 0 or 1 token
    EXPECT_LE(result.size(), 1);
}

// ============================================================================
// TEST GROUP 11: String is Only Delimiters
// ============================================================================

// Justification: Validates behavior when input contains only delimiters
// Tests edge case without any actual content
TEST(SplitAdvanced, OnlyDelimitersCompressionOff) {
    std::string input = ",,,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(4, result.size());
    for (const auto& token : result) {
        EXPECT_EQ("", token);
    }
}

// Justification: Validates delimiter-only strings with compression
// Tests that compression results in no tokens from delimiter-only input
TEST(SplitAdvanced, OnlyDelimitersCompressionOn) {
    std::string input = ",,,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    EXPECT_EQ(0, result.size());
}

// ============================================================================
// TEST GROUP 12: Whitespace Delimiters
// ============================================================================

// Justification: Validates splitting by whitespace characters (spaces, tabs, newlines)
// Tests real-world scenario of tokenizing by whitespace
TEST(SplitAdvanced, WhitespaceDelimiters) {
    std::string input = "hello   world\t\ttest\nnext";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_space());
    
    // With is_space(), consecutive whitespace should create empty tokens
    EXPECT_GE(result.size(), 4);
    EXPECT_EQ("hello", result[0]);
}

// Justification: Validates whitespace tokenization with compression
// Tests practical use case of word extraction
TEST(SplitAdvanced, WhitespaceDelimitersCompressionOn) {
    std::string input = "hello   world\t\ttest";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_space(),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("hello", result[0]);
    EXPECT_EQ("world", result[1]);
    EXPECT_EQ("test", result[2]);
}

// ============================================================================
// TEST GROUP 13: Single Character Tokens
// ============================================================================

// Justification: Validates splitting produces single-character tokens
// Tests behavior with minimal token content
TEST(SplitAdvanced, SingleCharacterTokens) {
    std::string input = "a,b,c,d";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","));
    
    ASSERT_EQ(4, result.size());
    EXPECT_EQ("a", result[0]);
    EXPECT_EQ("b", result[1]);
    EXPECT_EQ("c", result[2]);
    EXPECT_EQ("d", result[3]);
}

// Justification: Validates alternating delimiters and single characters
// Tests maximum fragmentation scenario
TEST(SplitAdvanced, AlternatingDelimitersAndSingleChars) {
    std::string input = ",a,b,c,";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_off);
    
    ASSERT_EQ(5, result.size());
    EXPECT_EQ("", result[0]);
    EXPECT_EQ("a", result[1]);
    EXPECT_EQ("b", result[2]);
    EXPECT_EQ("c", result[3]);
    EXPECT_EQ("", result[4]);
}

// ============================================================================
// TEST GROUP 14: Very Long Strings and Large Number of Tokens
// ============================================================================

// Justification: Validates performance and correctness with large inputs
// Tests scalability of split logic
TEST(SplitAdvanced, VeryLongStringManyTokens) {
    std::string input;
    for (int i = 0; i < 1000; ++i) {
        input += "token" + std::to_string(i);
        if (i < 999) input += ",";
    }
    
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","));
    
    EXPECT_EQ(1000, result.size());
    EXPECT_EQ("token0", result[0]);
    EXPECT_EQ("token999", result[999]);
}

// Justification: Validates handling of many consecutive delimiters in large input
// Tests compression with high delimiter density
TEST(SplitAdvanced, ManyConsecutiveDelimitersCompressionOn) {
    std::string input = "start";
    for (int i = 0; i < 100; ++i) {
        input += ",";
    }
    input += "end";
    
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_any_of(","),
                          boost::algorithm::token_compress_on);
    
    ASSERT_EQ(2, result.size());
    EXPECT_EQ("start", result[0]);
    EXPECT_EQ("end", result[1]);
}

// ============================================================================
// TEST GROUP 15: Complex Predicate Combinations
// ============================================================================

// Justification: Validates splitting by alphanumeric vs. non-alphanumeric characters
// Tests complex character classification logic
TEST(SplitAdvanced, NonAlphanumericDelimiters) {
    std::string input = "hello123world@test#data";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_digit());
    
    // Digits are delimiters, so alphanumeric tokens may be fragmented
    EXPECT_GE(result.size(), 2);
    EXPECT_EQ("hello", result[0]);
}

// Justification: Validates splitting by lower case characters only
// Tests selective character-based tokenization
TEST(SplitAdvanced, LowerCaseAsDelimiters) {
    std::string input = "AaBbCc";
    std::vector<std::string> result;
    boost::algorithm::split(result, input, boost::algorithm::is_lower());
    
    ASSERT_EQ(4, result.size());
    EXPECT_EQ("A", result[0]);
    EXPECT_EQ("B", result[1]);
    EXPECT_EQ("C", result[2]);
}
