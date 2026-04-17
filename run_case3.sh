#!/bin/bash
# ==========================================
# Run Coverage Workflow for Case 3: Split
# ==========================================

if [ ! -d "build" ]; then
    echo "Error: 'build' directory not found. Please compile the project first."
    exit 1
fi

mkdir -p reports/case3/
cd build

echo "1/6: Cleaning old coverage data..."
find . -type f -name "*.gcda" -delete

echo "2/6: Running Boost Baseline..."
./case3_boost_baseline

echo "3/6: Generating Boost Baseline Report..."
gcovr -r .. --filter '.*/split\.hpp' --html --html-details -o ../reports/case3/case3_boost_report.html -b

echo "4/6: Cleaning coverage data for AI run..."
find . -type f -name "*.gcda" -delete

echo "5/6: Running Copilot Tests..."
./case3_copilot_tests

echo "6/6: Generating Copilot Report..."
gcovr -r .. --filter '.*/split\.hpp' --html --html-details -o ../reports/case3/case3_copilot_report.html -b

echo "Success! Your reports are saved in the 'reports' folder."