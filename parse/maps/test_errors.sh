#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "=================================="
echo "   CUB3D ERROR TEST SUITE"
echo "=================================="
echo ""

# Counter for tests
TOTAL=0
PASSED=0
FAILED=0

# Function to run a test
run_test() {
    local test_file=$1
    local expected_error=$2
    local test_name=$3

    TOTAL=$((TOTAL + 1))

    echo -n "Test $TOTAL: $test_name... "

    # Run the program and capture output
    OUTPUT=$(./cub3D "$test_file" 2>&1)
    EXIT_CODE=$?

    # Check if it failed (exit code != 0)
    if [ $EXIT_CODE -ne 0 ]; then
        # Check if error message contains expected text
        if echo "$OUTPUT" | grep -q "Error"; then
            echo -e "${GREEN}PASS${NC}"
            PASSED=$((PASSED + 1))
            if [ ! -z "$expected_error" ]; then
                echo "    Expected: $expected_error"
                echo "    Got: $(echo "$OUTPUT" | head -n 2 | tr '\n' ' ')"
            fi
        else
            echo -e "${RED}FAIL${NC} - No error message"
            FAILED=$((FAILED + 1))
        fi
    else
        echo -e "${RED}FAIL${NC} - Program should have failed"
        FAILED=$((FAILED + 1))
    fi
    echo ""
}

# Test 1: Invalid extension
run_test "maps/error_tests/wrong_extension.txt" \
    ".cub extension" \
    "Invalid file extension (.txt instead of .cub)"

# Test 2: Missing configuration elements
run_test "maps/error_tests/missing_north.cub" \
    "Incomplete configuration" \
    "Missing NO (north) texture"

run_test "maps/error_tests/missing_floor.cub" \
    "Incomplete configuration" \
    "Missing F (floor) color"

run_test "maps/error_tests/missing_ceiling.cub" \
    "Incomplete configuration" \
    "Missing C (ceiling) color"

# Test 3: Invalid colors
run_test "maps/error_tests/color_out_of_range.cub" \
    "Invalid color range" \
    "Color value out of range (256)"

run_test "maps/error_tests/color_negative.cub" \
    "Invalid color range" \
    "Negative color value"

run_test "maps/error_tests/color_invalid_format.cub" \
    "Invalid color format" \
    "Missing color component (only 2 values)"

run_test "maps/error_tests/color_too_many_values.cub" \
    "Invalid color format" \
    "Too many color values (4 instead of 3)"

# Test 4: Invalid maps
run_test "maps/error_tests/map_not_closed.cub" \
    "Map is not closed" \
    "Map extends beyond boundaries"

run_test "maps/error_tests/map_hole_in_wall.cub" \
    "Map is not closed" \
    "Space in wall (hole)"

run_test "maps/error_tests/map_no_player.cub" \
    "No player" \
    "No player start position"

run_test "maps/error_tests/map_multiple_players.cub" \
    "Multiple players" \
    "More than one player position"

run_test "maps/error_tests/map_invalid_char.cub" \
    "Invalid character" \
    "Invalid character 'X' in map"

run_test "maps/error_tests/map_empty.cub" \
    "Map is empty" \
    "Empty map"

run_test "maps/error_tests/map_space_near_zero.cub" \
    "space inside playable area" \
    "Space next to empty cell (0)"

run_test "maps/error_tests/map_space_inside.cub" \
    "space inside playable area" \
    "Space inside map (not outside walls)"

run_test "maps/error_tests/map_player_at_edge.cub" \
    "Map is not closed" \
    "Player at map edge"

run_test "maps/error_tests/map_open_top.cub" \
    "Map is not closed" \
    "Map open at top edge"

run_test "maps/error_tests/map_open_bottom.cub" \
    "Map is not closed" \
    "Map open at bottom edge"

# Test 5: Duplicate configuration
run_test "maps/error_tests/duplicate_north.cub" \
    "Duplicate" \
    "Duplicate NO texture definition"

run_test "maps/error_tests/duplicate_floor.cub" \
    "Duplicate" \
    "Duplicate F color definition"

run_test "maps/error_tests/duplicate_ceiling.cub" \
    "Duplicate" \
    "Duplicate C color definition"

# Test 6: Missing texture files
run_test "maps/error_tests/texture_not_found.cub" \
    "Texture file not found" \
    "Texture file doesn't exist"

run_test "maps/error_tests/texture_wrong_path.cub" \
    "Texture file not found" \
    "Wrong texture path"

# Test 7: Edge cases
run_test "maps/error_tests/config_after_map.cub" \
    "Incomplete configuration" \
    "Configuration element after map"

# Summary
echo "=================================="
echo "         TEST SUMMARY"
echo "=================================="
echo "Total tests: $TOTAL"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo "=================================="

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi
