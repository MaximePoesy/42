import random
import sys

def generate_numbers(count, min_val, max_val, order):
    if count > 500:
        print("Error: Maximum limit is 500 numbers.")
        sys.exit(1)

    if min_val > max_val:
        print("Error: Min value cannot be greater than max value.")
        sys.exit(1)

    if max_val - min_val + 1 < count:
        print("Error: Range is too small to generate unique numbers.")
        sys.exit(1)

    numbers = random.sample(range(min_val, max_val + 1), count)  # Unique numbers

    if order == "sorted":
        numbers.sort()
    elif order == "reverse":
        numbers.sort(reverse=True)

    print(" ".join(map(str, numbers)))  # Print space-separated numbers

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("Usage: python script.py <count> <min> <max> <order>")
        print("order: sorted | unsorted | reverse")
        sys.exit(1)

    count = int(sys.argv[1])
    min_val = int(sys.argv[2])
    max_val = int(sys.argv[3])
    order = sys.argv[4]

    if order not in ["sorted", "unsorted", "reverse"]:
        print("Invalid order. Use 'sorted', 'unsorted', or 'reverse'.")
        sys.exit(1)

    generate_numbers(count, min_val, max_val, order)
