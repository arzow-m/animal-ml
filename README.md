# 🐾 Animal Classifier Using K-Nearest Neighbors (KNN)

This project processes structured animal data from `.txt` and `.csv` files, extracting relevant details such as animal names, binary features, and class labels. It implements a K-Nearest Neighbors (KNN) classification system to categorize animal species based on feature similarity.

The program supports multiple distance metrics — **Euclidean**, **Hamming**, and **Jaccard** — to measure similarity between data points. Machine learning techniques are applied to determine feature similarities and predict classifications for unseen animal samples. Additionally, it evaluates prediction accuracy against labeled test data.

---

## Files Included

- `main.c` — Main program file implementing the core logic.
- `givenA1.h` — Header file defining the `Animal` struct and constants.
- `a1Data.txt` — Dataset containing training data.
- `testData.csv` — Dataset containing test samples and ground truth labels.

---

## Core Functionality

- **Data Processing**: Reads and parses animal data from files.
- **Distance Calculations**: Computes Euclidean, Hamming, and Jaccard distances between feature vectors.
- **KNN Classification**: Finds `k` nearest neighbors and predicts a class based on majority voting.
- **Accuracy Evaluation**: Tests model performance using labeled test data.

---

## Compilation

```bash
make
```
---

## Running the Program

```bash
./maksumArzowA1 a1Data.txt
```

Once started, the program provides a menu with five tasks:

```
1. Display dataset
2. Calculate distances between two feature vectors
3. Find k nearest neighbors
4. Predict class of a new animal
5. Evaluate accuracy on test dataset
```

> Error handling: Task 1 must be completed before running other tasks.

---

## Distance Metrics

- **Euclidean Distance** – Measures geometric distance in n-dimensional space.
- **Hamming Distance** – Counts the number of differing bits.
- **Jaccard Similarity** – Measures similarity by comparing overlapping features (ignoring common zeros).

---

## Sample Data Format

Each line in `a1Data.txt` contains:

```
animal_name f1 f2 ... f16 class_label
```

Example:
```
lion 1 0 1 0 1 0 1 0 1 1 0 1 0 1 1 0 3
```

The `testData.csv` file follows a similar structure but uses comma separators.

---

## Output

Task 5 evaluates predictions on the test dataset and prints:

- Predicted class labels
- Number of correct predictions
- Total test cases
- Overall accuracy as a decimal value

---
