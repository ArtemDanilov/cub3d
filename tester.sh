#!/bin/bash

# Configuration
EXE="./cub3D"
BAD_DIR="maps/bad"
GOOD_DIR="maps/good"

# Colors
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
RED="\033[0;31m"
WHITE="\033[0;37m"
RESET="\033[0m"

# If executable file doesn't exist
if [ ! -f $EXE ]; then
	printf "${RED}Missing executable file${RESET}\n"
	exit
fi
# Function to run the test
# $1: file path, $2: expected exit code, $3: test number
run_test() {
    local file=$1
    local expected=$2
    local index=$3
    
    # Run the program. Redirect stdout/stderr to /dev/null to keep it clean.
    output=$($EXE "$file" 2>&1)
    local actual=$?

    printf "%d.file: %s\n" "$index" "$(basename "$file")"

    if [ $actual -eq 139 ]; then
        printf "   test: ${RED}fail (SEGFAULT)${RESET}\n"
    elif [ $actual -eq $expected ]; then
        printf "   test: ${GREEN}ok${RESET}\n"
    else
        printf "   test: ${RED}fail${RESET}\n"
    fi

	# 3. Print the output/error message indented
    if [ -z "$output" ]; then
        printf "   output: ${YELLOW}[no output]${RESET}\n"
    else
        # This pipes the output and adds spaces to the start of every line for formatting
        clean_output=$(echo "$output" | sed 's/\x1b\[[0-9;]*m//g')
        
        printf "   output: ${WHITE}"
        echo "$clean_output" | sed 's/^/           /' | sed '1s/^ *//'
        printf "${RESET}"
    fi
    echo "-----------------------"
}

# --- Bad maps ---
# We expect these to return 1 (error caught)
echo " "
echo "----------------"
echo "--- Bad maps ---"
echo "----------------"
echo " "
i=1
# This will loop through every file in the maps/bad directory
for map in "$BAD_DIR"/*; do
    if [ -f "$map" ]; then
        run_test "$map" 1 $i
        ((i++))
    fi
done

# --- Good maps ---
# We expect these to return 0 (success)
echo " "
echo "-----------------"
echo "--- Good maps ---"
echo "-----------------"
echo " "
j=1
for map in "$GOOD_DIR"/*; do
    if [ -f "$map" ]; then
        run_test "$map" 0 $j
        ((j++))
    fi
done