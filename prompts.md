# GitHub Copilot QA Evaluation Prompts

## Case 1: Trim (Person 1)
**Focus:** Equivalence Partitioning (EP) and Boundary Value Analysis (BVA)  
**Target File:** `trim.hpp`

### Prompt
Act as a QA Automation Engineer. I need you to generate a comprehensive Google Test (GTest) suite for the `boost::algorithm::trim` function found in #file:trim.hpp. 

Testing Requirements:
1. Apply Equivalence Partitioning (EP) to identify valid and invalid input classes.
2. Apply Boundary Value Analysis (BVA) for standard string boundaries (e.g., empty strings, strings that are entirely whitespace, strings with only leading or only trailing whitespace).
3. Test various types of whitespace characters (spaces, tabs, newlines).

Constraints:
- Output ONLY the GTest TEST() blocks and necessary #include statements. 
- Do not generate a main() function. 
- Above each test case, include a brief comment explaining which EP or BVA partition this test satisfies.

---

## Case 2: Replace All (Person 2)
**Focus:** Tricky Edge Cases and Strict Boundaries  
**Target File:** `replace.hpp`

### Prompt
Act as a QA Automation Engineer. I need you to generate a highly rigorous Google Test (GTest) suite for the `boost::algorithm::replace_all` function found in #file:replace.hpp. 

Testing Requirements:
Focus heavily on Boundary Value Analysis (BVA) and destructive edge cases. You must explicitly generate tests for the following scenarios:
1. The input string is completely empty.
2. The target string to replace is completely empty.
3. The replacement string is completely empty.
4. The target string does not exist anywhere in the input.
5. Overlapping replacements (e.g., replacing "aba" in "ababa").

Constraints:
- Output ONLY the GTest TEST() blocks and necessary #include statements.
- Do not generate a main() function.
- Above each test case, explicitly state the boundary condition being tested.

---

## Case 3: Split (Person 3)
**Focus:** Complex Logic and Combinations  
**Target File:** `split.hpp`

### Prompt
Act as a QA Automation Engineer. I need you to generate an advanced Google Test (GTest) suite for the `boost::algorithm::split` function found in #file:split.hpp. 

Testing Requirements:
Focus on complex logic, algorithmic combinations, and token compression. Generate tests that validate:
1. Splitting using a single delimiter vs. multiple different delimiters.
2. Handling consecutive delimiters (are empty tokens generated, or are they compressed if token_compress_on is used?).
3. Splitting a string where the delimiters are at the absolute beginning or the absolute end of the string.
4. Splitting a string that contains absolutely no delimiters.

Constraints:
- Output ONLY the GTest TEST() blocks and necessary #include statements.
- Ensure you include the necessary Boost predicate headers (like boost/algorithm/string/classification.hpp) for the is_any_of logic.
- Do not generate a main() function.
- Comment the logical justification for each test case.