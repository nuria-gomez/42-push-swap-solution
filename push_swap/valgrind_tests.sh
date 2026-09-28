#!/bin/bash

# Valgrind suite for push_swap: leaks, invalid access, uninit values, fd leaks.
# Usage:
#   ./valgrind_tests.sh           # default (up to 100 random)
#   ./valgrind_tests.sh --full    # also 500 random (slow)

RED='\033[1;91m'
GREEN='\033[1;92m'
YELLOW='\033[0;93m'
BLUE='\033[0;94m'
CYAN='\033[0;96m'
DEF='\033[0;39m'

BIN="./push_swap"
LOGDIR="./valgrind_logs"
VALGRIND_OPTS=(
	--leak-check=full
	--show-leak-kinds=all
	--track-origins=yes
	--track-fds=yes
	--error-exitcode=42
)
FULL=0
PASS=0
FAIL=0
TOTAL=0

if [ "${1:-}" = "--full" ]; then
	FULL=1
fi

if ! command -v valgrind >/dev/null 2>&1; then
	printf "${RED}valgrind is not installed.${DEF}\n"
	exit 1
fi

if [ ! -x "$BIN" ]; then
	printf "${YELLOW}Building push_swap...${DEF}\n"
	make -s all || exit 1
fi

rm -rf "$LOGDIR"
mkdir -p "$LOGDIR"

print_header()
{
	printf "${BLUE}\n-------------------------------------------------------------\n${DEF}"
	printf "${CYAN}  %s\n${DEF}" "$1"
	printf "${BLUE}-------------------------------------------------------------\n${DEF}"
}

# Returns 0 if the valgrind log is clean.
log_is_clean()
{
	local log="$1"
	local errors lost_def lost_ind lost_pos still

	if ! grep -q "HEAP SUMMARY" "$log"; then
		return 1
	fi
	errors=$(grep "ERROR SUMMARY:" "$log" | tail -1 | awk '{print $4}')
	[ "${errors:-1}" = "0" ] || return 1
	if grep -Eq "Invalid (read|write)" "$log"; then
		return 1
	fi
	if grep -q "uninitialised" "$log"; then
		return 1
	fi
	if grep -q "All heap blocks were freed -- no leaks are possible" "$log"; then
		:
	else
		lost_def=$(grep "definitely lost:" "$log" | tail -1 | awk '{print $4}' | tr -d ',')
		lost_ind=$(grep "indirectly lost:" "$log" | tail -1 | awk '{print $4}' | tr -d ',')
		lost_pos=$(grep "possibly lost:" "$log" | tail -1 | awk '{print $4}' | tr -d ',')
		still=$(grep "still reachable:" "$log" | tail -1 | awk '{print $4}' | tr -d ',')
		[ "${lost_def:-1}" = "0" ] || return 1
		[ "${lost_ind:-1}" = "0" ] || return 1
		[ "${lost_pos:-1}" = "0" ] || return 1
		[ "${still:-1}" = "0" ] || return 1
	fi
	# Extra FDs inherited from Cursor/the shell are not leaks.
	if awk '
		/Open file descriptor|Open [^ ]+ socket/ {
			if ((getline nxt) > 0 && nxt !~ /inherited from parent/)
				found = 1
		}
		END { exit found ? 0 : 1 }
	' "$log"; then
		return 1
	fi
	return 0
}

run_vg()
{
	local name="$1"
	shift
	local safe_name log

	TOTAL=$((TOTAL + 1))
	safe_name=$(printf "%s" "$name" | tr ' ' '_')
	log="$LOGDIR/${TOTAL}_${safe_name}.log"

	valgrind "${VALGRIND_OPTS[@]}" --log-file="$log" "$BIN" "$@" \
		>/dev/null 2>/dev/null

	if log_is_clean "$log"; then
		PASS=$((PASS + 1))
		printf "${GREEN}[%02d][OK]${DEF} %s\n" "$TOTAL" "$name"
	else
		FAIL=$((FAIL + 1))
		printf "${RED}[%02d][KO]${DEF} %s  ${YELLOW}-> %s${DEF}\n" \
			"$TOTAL" "$name" "$log"
	fi
}

rand_args()
{
	local n="$1"
	local half=$((n / 2))

	seq -"$half" $((n - half - 1)) | shuf | tr '\n' ' '
}

# --------------------------------------------------------------------------- #
print_header "NO ARGS / EMPTY"

run_vg "no_args"
run_vg "empty_string" ""
run_vg "spaces_only" "     "
run_vg "tabs_only" $'\t\t'

# --------------------------------------------------------------------------- #
print_header "INVALID INPUT (must not leak on Error)"

run_vg "letter" a
run_vg "mixed_alnum" 111a11
run_vg "hello" hello
run_vg "plus_only" +
run_vg "minus_only" -
run_vg "double_sign" --1
run_vg "plus_minus" +-1
run_vg "leading_zero" 00
run_vg "leading_zero_pos" 01
run_vg "leading_zero_neg" -01
run_vg "plus_leading_zero" +01
run_vg "float" 1.5
run_vg "comma" 1,2
run_vg "spaces_in_arg" "1 2 3a"
run_vg "overflow" 2147483648
run_vg "underflow" -2147483649
run_vg "big_overflow" 999999999999
run_vg "dup_two" 1 1
run_vg "dup_later" 1 2 3 2
run_vg "dup_neg" -1 0 -1
run_vg "valid_then_empty" 1 ""
run_vg "valid_then_letter" 1 2 a
run_vg "quoted_dup" "1 2 1"
run_vg "quoted_letter" "1 2 a"
run_vg "quoted_overflow" "1 2147483648"

# --------------------------------------------------------------------------- #
print_header "QUOTED STRING VS ARGV"

run_vg "quoted_3" "3 2 1"
run_vg "argv_3" 3 2 1
run_vg "quoted_multi_space" "3   2    1"
run_vg "quoted_leading_space" "  4 3 2 1"
run_vg "quoted_trailing_space" "4 3 2 1  "
run_vg "plus_sign" +1 +2 +3
run_vg "quoted_plus" "+3 +1 +2"

# --------------------------------------------------------------------------- #
print_header "SMALL STACKS (1-5, hardcoded path)"

run_vg "one" 42
run_vg "one_neg" -42
run_vg "one_zero" 0
run_vg "two_sorted" 1 2
run_vg "two_unsorted" 2 1
run_vg "three_012" 0 1 2
run_vg "three_021" 0 2 1
run_vg "three_102" 1 0 2
run_vg "three_120" 1 2 0
run_vg "three_201" 2 0 1
run_vg "three_210" 2 1 0
run_vg "four" 4 3 2 1
run_vg "four_mixed" 2 4 1 3
run_vg "five" 5 4 3 2 1
run_vg "five_mixed" 3 1 5 2 4
run_vg "five_quoted" "5 1 4 2 3"

# --------------------------------------------------------------------------- #
print_header "ALREADY SORTED / REVERSE"

run_vg "sorted_6" 1 2 3 4 5 6
run_vg "sorted_10" 1 2 3 4 5 6 7 8 9 10
run_vg "reverse_6" 6 5 4 3 2 1
run_vg "reverse_10" 10 9 8 7 6 5 4 3 2 1
run_vg "almost_sorted" 1 2 3 4 6 5
run_vg "rotated" 3 4 5 6 1 2

# --------------------------------------------------------------------------- #
print_header "INT LIMITS AND NEGATIVES"

run_vg "int_max" 2147483647 0 1
run_vg "int_min" -2147483648 0 1
run_vg "int_min_max" -2147483648 2147483647 0
run_vg "negatives" -5 -1 -3 -2 -4
run_vg "mixed_signs" -2 0 5 -10 3
run_vg "zero_mix" 0 -0 +0
run_vg "quoted_limits" "-2147483648 42 2147483647"

# --------------------------------------------------------------------------- #
print_header "LIS / TURKISH PATH (>= 6)"

run_vg "six_random_fixed" 6 3 8 1 5 2
run_vg "seven" 7 1 6 2 5 3 4
run_vg "ten_fixed" 9 1 8 2 7 3 6 4 5 0
run_vg "desc_then_asc" 5 4 3 2 1 6 7 8 9 10
run_vg "asc_then_desc" 1 2 3 4 5 10 9 8 7 6

# --------------------------------------------------------------------------- #
print_header "RANDOM STACKS"

run_vg "rand_10" $(rand_args 10)
run_vg "rand_25" $(rand_args 25)
run_vg "rand_50" $(rand_args 50)
run_vg "rand_100" $(rand_args 100)

if [ "$FULL" -eq 1 ]; then
	print_header "FULL: 500 RANDOM (slow)"
	run_vg "rand_500" $(rand_args 500)
else
	printf "${YELLOW}\nSkipping 500 (pass --full to include it).${DEF}\n"
fi

# --------------------------------------------------------------------------- #
printf "${BLUE}\n-------------------------------------------------------------\n${DEF}"
printf "  Passed: ${GREEN}%d${DEF}   Failed: ${RED}%d${DEF}   Total: %d\n" \
	"$PASS" "$FAIL" "$TOTAL"
printf "${BLUE}-------------------------------------------------------------\n${DEF}"

if [ "$FAIL" -ne 0 ]; then
	printf "${YELLOW}Inspect KO logs in %s/${DEF}\n" "$LOGDIR"
	exit 1
fi
printf "${GREEN}All valgrind tests passed.${DEF}\n"
exit 0
