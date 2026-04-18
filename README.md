# Master Project Guide: AI Test Generation Evaluation (Boost vs. Copilot)

This document serves as the comprehensive guide for our **Software Verification & Validation** case study. We are standardizing on **Fedora Linux via Windows Subsystem for Linux (WSL)** to ensure a uniform compiler and code coverage (`gcov`) environment across the team.

---

## 1. System Setup (Fedora 43 on WSL)

### Step 1: Enable WSL & Install Fedora
1. Open **Windows PowerShell** as Administrator and run:
   ```powershell
   wsl --install
   ```
2. Restart your computer if prompted.
3. Open **Windows PowerShell** again and run the following command to install Fedora 43:
   ```powershell
   wsl --install --web-download -d FedoraLinux-43
   ```
4. Follow the prompts in the terminal to create your UNIX username and password.

### Step 2: Install Project Dependencies
Inside your new Fedora terminal, run these commands to install the required C++ toolchain, Boost headers, and coverage tools:

```bash
# Update the system
sudo dnf update -y

# Install compilers, build tools, and coverage metrics
sudo dnf groupinstall "Development Tools" -y
sudo dnf install cmake gcc-c++ boost-devel gcovr -y
```

---

## 2. VS Code Environment
To ensure your environment handles the Linux file system correctly, connect VS Code directly to your Fedora WSL instance.

1. Install the **WSL extension** in VS Code.
2. Click the **green icon** in the bottom-left corner and select **Connect to WSL**.
3. Once connected, install these required extensions **within the WSL instance**:
   * **C/C++ (Microsoft):** IntelliSense and debugging.
   * **CMake Tools (Microsoft):** Build process management.
   * **GitHub Copilot & GitHub Copilot Chat:** The AI tools under evaluation.
   * **Coverage Gutters (ryanluker):** Displays green/red highlights to visualize covered lines.

---

## 3. Project Structure
The workspace is structured to strictly separate the AI reference headers from our active tests to prevent "data leakage."

```text
github-copilot-qa-evaluation/
├── CMakeLists.txt          # Global build configuration
├── build.sh                # Root compilation script
├── generate_reports.sh     # Root automation script for coverage
├── boosthppfiles/          # AI Reference folder (Header logic only)
│   ├── trim.hpp
│   ├── replace.hpp
│   └── split.hpp
├── tests/                  # Test suites
│   ├── case1_trim/
│   │   ├── boost_trim_test.cpp
│   │   └── copilot_trim_test.cpp
│   ├── case2_replace/
│   │   ├── boost_replace_test.cpp
│   │   └── copilot_replace_test.cpp
│   └── case3_split/
│       ├── boost_split_test.cpp
│       └── copilot_split_test.cpp
└── reports/                # Output destination for HTML coverage
```

---

## 4. Execution Workflow (The "Clean Room" Protocol)
Because `.copilotignore` can be unreliable, use this physical isolation method to ensure scientific validity.

### Step A: Generate the AI Tests
1. **Remove Baselines:** Navigate to your assigned test folder and physically move the `boost_XYZ_test.cpp` file completely out of the workspace (e.g., to your Windows Desktop).
2. **Verify Isolation:** Ensure the only files visible in VS Code are the specific `.hpp` file from `boosthppfiles/` and your empty `copilot_XYZ_test.cpp` file.
3. **Prompt:** Open Copilot Chat. Use the `#file` tag to point to the header in `boosthppfiles/` and paste your assigned prompt from Section 5.
4. **Restore:** Once the AI generates the code, save it, then move the Boost baseline file back into its original folder.

### Step B: Build and Report
Open the integrated Fedora terminal in VS Code and run:

```bash
# Compile the project
build.sh

# Run tests and generate HTML reports
generate_reports.sh
```

> [!IMPORTANT]
> Open the HTML files in the `reports/` directory to extract **Statement** and **Branch** coverage percentages for the final presentation.

# GitHub Copilot QA Evaluation Prompts

## Case 1: Trim
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

## Case 2: Replace All
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

## Case 3: Split
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