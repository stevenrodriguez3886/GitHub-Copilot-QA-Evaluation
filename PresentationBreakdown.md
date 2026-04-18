## Steven Rodriguez: The Intro (Slides 1–5)

**Goal:** Quickly get through the introductory boilerplate and establish exactly what AI tool the team evaluated.

**Repo Files to Use:** Use the [README.md](README.md) to pull the project goal and the AI tool descriptions.

**Slide Assignments (5 Slides):**
* **Slide 1 (Title):** Names, Course, Date.
* **Slide 2 (Project Overview):** State the testing problem (Unit Test Boilerplate) and your main takeaway sentence on "automation complacency."
* **Slide 3 (Team Members):** Briefly list the four roles.
* **Slide 4 (Section Divider):** "Tool, Context, and Testing Goal."
* **Slide 5 (AI Tool Selection):** Introduce GitHub Copilot. Explain its key features and why the team chose it for generating C++ tests.

**Speaking Notes:** Do not linger on Slides 1–4. Your main speaking task is Slide 5. Hook the audience and hand it off.

---

## Team Member 2: The Context & Method (Slides 6–9)

**Goal:** Explain the specific C++ code you tested, the testing metrics you used to judge the AI, and how the team ran the scripts.

**Repo Files to Use:** [README.md](README.md), [CMakeLists.txt](CMakeLists.txt), [build.sh](build.sh), and [generate_reports.sh](generate_reports.sh).

**Slide Assignments (4 Slides):**
* **Slide 6 (Application Under Test):** Introduce the Boost C++ String Algorithms (trim, replace, split). Explain why you used an industry-standard baseline for comparison.
* **Slide 7 (Testing Concepts):** Define the metrics: Equivalence Partitioning (EP), Boundary Value Analysis (BVA), and Statement/Branch Coverage.
* **Slide 8 (Section Divider):** "Method and Demonstration."
* **Slide 9 (Workflow / Method):** Talk the audience through the execution: "We generated tests, built them with CMake, and ran gcovr/lcov to generate HTML coverage reports." Discuss the environment, language (C++), and platform used.

---

## Team Member 3: The Case Studies & Output (Slides 10–12)

**Goal:** Show the actual code, the AI's prompts, and the generated tests.

**Repo Files to Use:** [README.md](README.md), [trim.hpp](boosthppfiles/trim.hpp), [split.hpp](boosthppfiles/split.hpp),[replace.hpp](boosthppfiles/replace.hpp), [copilot_trim_test.cpp](tests/case1_trim/copilot_trim_test.cpp), [boost_trim_test.cpp](tests/case1_trim/boost_trim_test.cpp), [copilot_replace_test.cpp](tests/case2_replace/copilot_replace_test.cpp), [boost_replace_test.cpp](tests/case2_replace/boost_replace_test.cpp), [copilot_split_test.cpp](tests/case3_split/copilot_split_test.cpp), and [boost_split_test.cpp](tests/case3_split/boost_split_test.cpp).

**Slide Assignments (4 Slides):**
* **Slide 10 (Setup and Inputs):** Show the exact constraints and prompts you fed into GitHub Copilot.
* **Slide 11 (Example Code):** Take screenshots of the original Boost functions. Briefly explain their logic.
* **Slide 11 continued (Extra Screenshots):** add extra slides if need for the screenshots.
* **Slide 12 (Tool Output and Demo):** Take screenshots of the Copilot-generated test cases.
* **Crucial:** Point out a success (e.g., it tested the basic happy path) and a failure (e.g., it missed a null input or a specific edge-case boundary). Apply the EP/BVA concepts here.
* **Slide 12 continued (Extra Screenshots):** add extra slides if need for the screenshots.

---

## Team Member 4: The TV&V Evaluator (Slides 13–16)

**Goal:** Aggregate the data from all the case studies, prove the tool's limitations with hard numbers, and close the presentation.

**Repo Files to Use:** Open the HTML reports in [reports/case1](reports/case1), [reports/case2](reports/case2), and [reports/case3](reports/case3). 

> [!IMPORTANT]
> Compare the Boost reports against the Copilot reports. IE [case1_boost_report](reports/case1/case1_boost_report.html) vs [case1_copilot_report](reports/case1/case1_copilot_report.html).

**Slide Assignments (3 Slides, Heavy Speaking):**
* **Slide 13 (Section Divider):** "Evaluation and Recommendations."
* **Slide 14 (Strengths and Value):** What did Copilot do well? (e.g., It generated GoogleTest boilerplate instantly, saving setup time).
* **Slide 15 (Limitations & Risks):** Put your comparison table here. Show a simple chart of Copilot's Coverage % vs. Boost's Official Coverage %. Highlight the gaps where Copilot failed to achieve the same coverage. Discuss the risk of false confidence.
* **Slide 16 (Conclusion):** Deliver the final verdict. Reiterate that Copilot is an excellent assistant for speed, but human oversight using TV&V principles is mandatory.