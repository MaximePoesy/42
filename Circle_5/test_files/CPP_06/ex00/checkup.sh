#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counter for tests
TOTAL=0
PASSED=0

# Function to print section header
print_section() {
    echo ""
    echo -e "${BLUE}======================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}======================================${NC}"
}

# Function to run a test
run_test() {
    TOTAL=$((TOTAL + 1))
    echo -e "\n${YELLOW}Test $TOTAL: ./convert $1${NC}"
    ./convert "$1"
    echo -e "${GREEN}---${NC}"
}

# Check if program exists
if [ ! -f "./convert" ]; then
    echo -e "${RED}Error: ./convert not found. Please compile first.${NC}"
    exit 1
fi

echo -e "${GREEN}Starting ScalarConverter Tests${NC}"
echo -e "${GREEN}======================================${NC}"

# ============================================
# CHAR TESTS
# ============================================
print_section "CHAR LITERAL TESTS"

run_test "a"
run_test "z"
run_test "0"
run_test "9"
run_test "+"
run_test "-"
run_test " "
run_test "~"

# ============================================
# INT TESTS
# ============================================
print_section "INT LITERAL TESTS"

# Basic integers
run_test "0"
run_test "42"
run_test "-42"
run_test "+42"
run_test "1"
run_test "-1"

# Edge cases
run_test "2147483647"    # INT_MAX
run_test "-2147483648"   # INT_MIN
run_test "2147483648"    # INT_MAX + 1 (overflow)
run_test "-2147483649"   # INT_MIN - 1 (underflow)

# ASCII boundary values
run_test "0"     # NULL char
run_test "31"    # Non-displayable
run_test "32"    # First displayable (space)
run_test "126"   # Last displayable (~)
run_test "127"   # DEL (non-displayable)
run_test "128"   # Beyond ASCII

# ============================================
# FLOAT TESTS
# ============================================
print_section "FLOAT LITERAL TESTS"

# Basic floats
run_test "0.0f"
run_test "42.0f"
run_test "-42.0f"
run_test "+42.0f"
run_test "4.2f"
run_test "-4.2f"
run_test "0.5f"
run_test "123.456f"

# Special float values
run_test "nanf"
run_test "+inff"
run_test "-inff"
run_test "inff"

# Edge cases
run_test "2147483647.0f"
run_test "-2147483648.0f"

# ============================================
# DOUBLE TESTS
# ============================================
print_section "DOUBLE LITERAL TESTS"

# Basic doubles
run_test "0.0"
run_test "42.0"
run_test "-42.0"
run_test "+42.0"
run_test "4.2"
run_test "-4.2"
run_test "0.5"
run_test "123.456"

# Special double values
run_test "nan"
run_test "+inf"
run_test "-inf"
run_test "inf"

# Edge cases
run_test "2147483647.0"
run_test "-2147483648.0"

# ============================================
# EDGE CASES & INVALID INPUT
# ============================================
print_section "EDGE CASES & INVALID INPUT"

# Invalid formats
run_test "abc"
run_test "42abc"
run_test "42.42.42"
run_test "42f"      # Missing decimal point
run_test "f"
run_test ""
run_test "."
run_test ".0"
run_test "0."
run_test "--42"
run_test "++42"
run_test "- 42"
run_test "4 2"

# Overflow strings
run_test "999999999999999999999"
run_test "-999999999999999999999"

# Mixed formats
run_test "42.0"     # Should be double, not float
run_test "42.0f"    # Should be float
run_test "'a'"      # Quoted char (may not work depending on shell)

# ============================================
# CONVERSION ACCURACY TESTS
# ============================================
print_section "CONVERSION ACCURACY TESTS"

# Values that test char boundaries
run_test "65"    # 'A'
run_test "97"    # 'a'
run_test "48"    # '0'
run_test "57"    # '9'

# Float precision
run_test "42.42f"
run_test "3.14159f"
run_test "-273.15f"

# Double precision
run_test "42.424242"
run_test "3.14159265"
run_test "-273.15"

# ============================================
# SPECIAL CONVERSIONS
# ============================================
print_section "SPECIAL CONVERSION TESTS"

# Values that should show "Non displayable" for char
run_test "0"     # NULL
run_test "31"    # Unit Separator
run_test "127"   # DEL

# Values that should show "impossible" for char
run_test "-1"
run_test "128"
run_test "1000"

# Values that test float/double boundaries
run_test "nan"
run_test "nanf"
run_test "+inf"
run_test "+inff"
run_test "-inf"
run_test "-inff"

# ============================================
# SUMMARY
# ============================================
echo ""
echo -e "${BLUE}======================================${NC}"
echo -e "${GREEN}Testing Complete!${NC}"
echo -e "${BLUE}======================================${NC}"
echo -e "Total tests run: ${YELLOW}$TOTAL${NC}"
echo ""
echo -e "${YELLOW}Note: Review the output above to verify correctness.${NC}"
echo -e "${YELLOW}Expected behaviors:${NC}"
echo -e "  - Char conversions should show 'impossible' or 'Non displayable' when appropriate"
echo -e "  - Int conversions should handle overflow gracefully"
echo -e "  - Special values (nan, inf) should propagate correctly"
echo -e "  - Precision should be maintained across conversions"
echo ""
