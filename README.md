*This project has been created as part of the 42 curriculum by ngomez-v.*

> **DISCLAIMER:** This project was built **under the old curriculum subject (valid before March 2026)**. If you are working with the new subject, check that what you find here still matches the current requirements. 

## Description

**push_swap** is a project where the program receives a stack of integers (called stack **A**) in two possible ways: `./push_swap 1 2 3 4` or `./push_swap "1 2 3 4"` and the program must sort them in ascending order using a second empty stack (**B**) and a fixed set of operations: 
`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`.

The program prints the shortest sequence of instructions it can find. Performance is measured by operations amount count.

This implementation is using a three-phase pipeline:

1. **Index mapping** for converting values to ranks `from 0 to (n-1)`
2. **LIS** (LOngest Increasing Subsequence) keep the longest increasing subsequence in A, push the rest to B
2. **Inverted LIS** (Longest Decreasing Subsequence) pushing the longest decresasing subsequence to B and after that with the turkish algo. pushing it back to A.
3. **Turk algorithm** which push elements back from B to A using minimum-cost rotations (`rr` / `rrr` when possible). It requires always a one last rotation to sort them finally.

## Instructions

### Prerequisites

- `cc` (GCC or Clang)
- `make`
- Linux or macOS

### Compilation

```bash
make or make all
```
This will build `libft` from `ft_printf/libft/` and links the `push_swap` binary.

### Usage

```bash
./push_swap 2 1 3 6 5 8
./push_swap "4 67 3 87 23"
./push_swap 4 67 3 87 23
```

### Verify with the testers

File: `push_swap_test_linux.sh` 
File: `valgrind_tests.sh` 

### Clean everything:

```bash
make fclean
```

### Errors

The program prints `Error` followed by a newline on **stderr** (write 2) when:

- An argument is not a valid integer
- A value overflows `int` 
- There are duplicate values

- With no arguments, the program prints nothing and exits successfully.

## Benchmark results (this project)

Measured on random permutations (`./push_swap … | wc -l`). Efficiency = instruction count. Re-run with `python3 bench_stats.py 100 500 1000`.

| Size | Trials | Min | Max | Mean | Median | Stdev | CV % | P90 | P95 |
|------|--------|-----|-----|------|--------|-------|------|-----|-----|
| **100** | 1000 | 482 | 643 | **559.4** | **560.0** | 26.1 | **~4.7%** | 593 | 604 |
| **500** | 1000 | 4277 | 5166 | **4664.0** | **4664.0** | 133.9 | **~2.9%** | 4830 | 4876 |

**Moulinette grade band (from these runs):**

- **100 numbers:** max **643** &lt; 700 → **5/5**
- **500 numbers:** max **5166** &lt; 5500 → **5/5**

Mean ≈ Median + a low stdev means the solution is stable across random inputs (few outlier shuffles).

**Coefficient of variation (CV)** = `stdev / mean` (shown as **CV %** in the table):

- **~≤ 5%** → clearly stable / “low”
- **~5–10%** → still reasonably tight
- **≫ 10%** → more shuffle-dependent (more outlier cases)

Both sizes here sit under **5%** (~4.7% / ~2.9%), so the spread is low relative to the mean.

## Algorithm comparison: others vs this solution

Benchmarks from public READMEs and from [pjtunstall's multi-algorithm survey](https://github.com/pjtunstall/push-swap). Sample sizes and reported stats vary — see the notes column and caveats below.

| Algorithm | Repo | 100 numbers | 500 numbers | Test size / notes |
|-----------|------|-------------|-------------|-------------------|
| Radix sort (base 2) | [Leo Fu](https://github.com/LeoFu9487/push_swap_tutorial) / restray tester | 1084 (mean = min = max) | 6756 (his figure) | Deterministic, so mean = median by construction. pjtunstall calculates 6784 for 500 and can't reproduce 6756. |
| Radix sort | [madebypixel02](https://github.com/madebypixel02/push_swap) | 1025 | 6756 | Same deterministic behavior. |
| Chunk / bucket sort (Jamie Dawson style) | [pjtunstall](https://github.com/pjtunstall/push-swap) reimplementation ([Jamie Dawson](https://github.com/JamieDawson/push_swap_final)) | 867 (713 with optimizations) | not given | 10,000 trials |
| Chunk sort (YYBer) | [pjtunstall](https://github.com/pjtunstall/push-swap) reimplementation ([YYBer](https://github.com/YYBer/push_swap)) | 631 | 4814 | 10,000 trials for 100 |
| Chunk sort | [duarte3333](https://github.com/duarte3333/Push_Swap) | 595 | 4806 | 1000 tests each |
| Median split + cheapest insertion | [benjaminmerchin](https://github.com/benjaminmerchin/push_swap) | 660 | 5010 | Average only |
| Turkish / Turk (Ali Yigit Ogun) | [pjtunstall](https://github.com/pjtunstall/push-swap) reimplementation ([article](https://medium.com/@ayogun/push-swap-c1f5d2d41e97)) | 561 (std 23) | 5105 | 10,000 trials for 100. The 500 figure comes from a 100-trial test. |
| Turk + LIS + 2 buckets (Dan Sylvain) | [pjtunstall](https://github.com/pjtunstall/push-swap) reimplementation ([Dan Sylvain](https://github.com/dansylvain/42_pushswap)) | 566 | not given | 10,000 trials |
| 3-bucket triage + Turk-style cost check (Fred Orion) | [pjtunstall](https://github.com/pjtunstall/push-swap) reimplementation | 555 (std 25, max 699) | 4216 (std 121) | 10,000 trials for 100. The 500 figure comes from a 100-trial test. |
| Advanced cost-based insertion | [ulsgks](https://github.com/ulsgks/push_swap) | not published | mean 3784, best 3680, worst 3871, std 27 | 10,000 samples |
| Chunks + insertion with queue optimizations | [aaron-22766](https://github.com/aaron-22766/42_push_swap) | not published | mean 3971, min 3663, max 4277 | 1000 tests |
| Quick/insertion hybrid | aurelien-brabant | min 588, max 725 | min 6334, max 7045 | 1000 tests, no mean given |
| **This: Turkish + LIS + Inverted LIS** | **this project** | **mean ~559 / median ~560** | **mean ~4664 / median ~4664** | **1000 trials each** |

**Caveats:**

- Median is rarely published. Repos like ulsgks and aaron-22766 give mean + min/max; pjtunstall gives mean + stdev. Those spreads are tight, so the median is probably close to the mean — but that is an inference, not published data.
- Sample sizes are inconsistent: 100-number results range from 1,000 to 10,000 trials; some 500-number figures come from only 100 trials. That limits how fair a direct ranking is.

**Takeaways:**

- **100 numbers:** mean ~559 is essentially on par with Turk (561), Turk + LIS (566), and Fred Orion's 3-bucket version (555).
- **500 numbers:** mid-pack. ~4664 beats plain Turk (5105) and the chunk variants, but [ulsgks](https://github.com/ulsgks/push_swap) (~3784) and [aaron-22766](https://github.com/aaron-22766/42_push_swap) (~3971) do considerably better.
- Several LIS-based repos (fdiaz-ca, RaulCasado, rfs-hybrid, hafid-ops, JessicaRouillon) publish no benchmark numbers in their READMEs.
- Inverted LIS mainly helps on reverse-ish / highly decreasing inputs; on fully random stacks the mean stays near classic Turkish+LIS (~560 / ~4660), still safely inside the **5/5** thresholds.

## Why Index Mapping + LIS + Inverted LIS + Turkish Alg.

- **Index mapping** turns any integer input (including negatives) into ranks `0 … n-1` that will be used for all the rest of algorithims. 
- **LIS (Longest Increasing Subsequence)** finds the largest subset of A that is already in ascending order. Those elements stay in A; only the rest move to B. A longer LIS means fewer `pb` operations upfront.
- **INverted LIS (Longest Decreasing Subsequence)** finds the largest subset of A that is already in descending order. The inverted LIS will be considered only if it is bigger than the normal LIS and contains at least the 75% of the numbers in the stack A.
- **Turk** picks the cheapest element in the stack at each step: compute how many rotations bring both the self stack top element and its target position in the other stasck to the top. It basically calculates how much movements takes to bring the node X to self-top and to the target-top, additions both of them and compare the total between all possible nodes and takes the cheapests. 
- **Auxiliary algorithms**: for a sequence between 1 and 5 I'm using hardcoded functions. I'm also using the binary search algo. for being able to extract both the LIS and the inverted LIS. 

## Resources

| Topic | Link |
|-------|------|
| 42 push_swap subject | https://42-cursus.gitbook.io/guide/rank-02/push_swap |
| Algorithm choice (Radix vs Turk) | https://github.com/jgrigorjeva/push_swap/wiki/Push-swap%3A-which-algorithm-to-choose%3F |
| Turk algorithm, the original article | https://medium.com/@ayogun/push-swap-c1f5d2d41e97 |
| Turk algorithm, a 6-step walkthrough | https://pure-forest.medium.com/push-swap-turk-algorithm-explained-in-6-steps-4c6650a458c0 |
| Turk vs Radix: developer notes | https://dev.to/i_moh/pushswap-paralysis-and-why-i-finally-chose-the-turk-algorithm-3a2p |
| LIS: a dynamic programming | https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/ |
| LIS on O(n log n) | https://www.geeksforgeeks.org/longest-increasing-subsequence-on-log-n/ |
| Radix sort by Wikipedia | https://en.wikipedia.org/wiki/Radix_sort |
| Radix sort push_swap example | https://github.com/abbastoof/Push_Swap |
| Multi Algorithm Survey | https://github.com/pjtunstall/push-swap |
| LIS + Turk reference | https://github.com/rfs-hybrid-42-common-core/push_swap |
| Visualizer | https://codepen.io/ahkoh/full/bGWxmVz |
| **TESTER** used | https://github.com/gemartin99/Push-Swap-Tester |

### AI usage

- AI was used as a teacher: for algorithm research and for deeply understanding their logic.
- It was also used to create the bash file for the Valgrim test checker:
```bash
./valgrind_tests.sh          # default, up to 100 random
./valgrind_tests.sh --full   # also 500 random (really slow)
```

## Project structure

```
├── Makefile
├── push_swap.h
├── main.c
├── *.c
├── ft_printf
```
