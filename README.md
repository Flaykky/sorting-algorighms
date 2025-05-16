# Sorting Visualization Documentation

## Overview
This C program implements a visual demonstration of the Quicksort algorithm. It allows users to visualize the sorting process either as a numerical list or as a bar graph representation, with highlighted elements to show comparisons and swaps. The program supports both random and manual input and includes a delay to make the visualization process observable.

## Features
- **Input Modes**:
  - Random: Generates a list of random integers.
  - Manual: Allows users to input their own integers.
- **Display Modes**:
  - List: Shows the array as a comma-separated list of numbers.
  - Bars: Represents each element as a series of Unicode square characters (`□`), with the number of squares corresponding to the element's value.
- **Visualization**:
  - Highlights elements being compared or swapped using ANSI escape codes for underlining.
  - Updates the display after each significant operation (comparison or swap) with a configurable delay.
- **Configurable Parameters**:
  - Maximum array size (`MAXN = 100`).
  - Delay between visualization steps (`DELAY = 200000` microseconds).

## Dependencies
- Standard C libraries: `stdio.h`, `stdlib.h`, `time.h`, `string.h`.
- `unistd.h` for the `usleep` function (used for delays).
- A terminal that supports ANSI escape codes for clearing the screen, moving the cursor, and underlining text.

## Compilation and Execution
To compile and run the program:
```bash
gcc -o quicksort_visual main.c
./quicksort_visual
```
**Note**: The program uses `unistd.h`, which is typically available on Unix-like systems (Linux, macOS). For Windows, you may need to use a compatibility layer like Cygwin or modify the `pause_step` function to use `Sleep` from `windows.h`.

## Program Structure
### Global Variables
- `arr[MAXN]`: Integer array to store the elements to be sorted.
- `n`: Number of elements in the array.
- `mode`: Display mode (0 for list, 1 for bars).
- **Constants**:
  - `MAXN = 100`: Maximum number of elements.
  - `DELAY = 200000`: Delay in microseconds between visualization steps.
  - ANSI escape codes for terminal formatting:
    - `CLEAR_SCREEN`: Clears the terminal screen.
    - `MOVE_CURSOR_HOME`: Moves the cursor to the top-left corner.
    - `UNDERLINE_ON`/`UNDERLINE_OFF`: Enables/disables underlining.

### Functions
#### `pause_step()`
- **Purpose**: Introduces a delay to make the visualization steps observable.
- **Implementation**: Uses `usleep(DELAY)` to pause execution for `DELAY` microseconds.

#### `display()`
- **Purpose**: Displays the current state of the array without highlighting any elements.
- **Behavior**:
  - Clears the terminal and moves the cursor to the top.
  - Prints the algorithm name ("quicksort"), number of elements, and display mode.
  - If `mode == 0` (list):
    - Prints the array as `[a,b,c,...]`.
  - If `mode == 1` (bars):
    - Prints each element as a row of `□` characters, with the number of squares equal to the element's value.
  - Flushes the output buffer to ensure immediate display.



#### `display_highlight(int i, int j)`
- **Purpose**: Displays the array with elements at indices `i` and `j` highlighted (underlined).
- **Behavior**:
  - Similar to `display()`, but underlines the elements at indices `i` and `j` using ANSI escape codes.
  - Used to highlight elements being compared or swapped during sorting.

#### `partition(int low, int high)`
- **Purpose**: Partitions the array around a pivot (the element at `high`) as part of the Quicksort algorithm.
- **Algorithm**:
  - Selects `arr[high]` as the pivot.
  - Iterates through `low` to `high-1`, moving elements smaller than the pivot to the left of the partition index `i`.
  - Visualizes comparisons and swaps using `display_highlight` and `pause_step`.
  - Places the pivot in its final position and returns its index.
- **Visualization**:
  - Highlights the current element (`j`) and pivot (`high`) during comparisons.
  - Highlights swapped elements (`i` and `j`) during swaps.
  - Highlights the final pivot placement (`i+1` and `high`).

#### `quicksort(int low, int high)`
- **Purpose**: Recursively sorts the array using the Quicksort algorithm.
- **Algorithm**:
  - If `low < high`, partitions the array and recursively sorts the subarrays before and after the pivot.
  - Relies on `partition` for visualization and array manipulation.

#### `main()`
- **Purpose**: Program entry point, handles user input and initiates sorting.
- **Behavior**:
  - Seeds the random number generator with the current time.
  - Prompts the user to choose an input mode:
    - `1`: Random list (user specifies `n`, elements are random integers between 1 and 20).
    - `2`: Manual entry (user specifies `n` and enters `n` integers).
  - Prompts the user to choose a display mode (`0` for list, `1` for bars).
  - Displays the initial array state.
  - Calls `quicksort(0, n-1)` to sort the array.
  - Displays the final sorted array and prints "Sorting complete."


## sorting algorithms: 
- quick sort
- bubble sort
- merge sort
- buzu sort (comming soon)

## Usage Example
### Input
```plaintext
Choose input mode:
1 = random list
2 = manual entry
1
Enter number of elements (max 100): 5
Choose display mode:
0 = list
1 = bars
1
```

### Output (Bars Mode)
Initial display:
```plaintext
quicksort
elements: 5
mode: bars

□□□□□
□□
□□□□
□
□□□
```
During sorting, elements being compared or swapped are underlined, e.g.:
```plaintext
quicksort
elements: 5
mode: bars

□□□□□
□□
□□□□
□
□□□
```
Final display (sorted):
```plaintext
quicksort
elements: 5
mode: bars

□
□□
□□□
□□□□
□□□□□

Sorting complete.
```

## Limitations
- **Terminal Dependency**: Requires a terminal that supports ANSI escape codes. Some terminals (e.g., Windows CMD) may not render underlining or Unicode characters correctly.
- **Platform Dependency**: The `usleep` function is Unix-specific. For Windows, modifications are needed.
- **Fixed Range for Random Input**: Random elements are limited to 1–20 to keep bar visualizations manageable.
- **No Input Validation**: The program assumes valid user input (e.g., `n ≤ MAXN`, valid integers).

## Potential Improvements
- Add input validation to handle invalid inputs gracefully.
- Support additional sorting algorithms for comparison.
- Allow users to adjust the delay duration interactively.
- Implement a Windows-compatible version using `Sleep` or a cross-platform library.
- Add color highlighting for better visual distinction.
- Support larger ranges for random inputs with scaling for bar mode.

## Conclusion
This program provides an educational tool for visualizing the Quicksort algorithm. Its modular design and clear visualization make it suitable for learning about sorting algorithms, while its limitations highlight areas for further enhancement.
