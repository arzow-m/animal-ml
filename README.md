🐾 Animal Classifier Using K-Nearest Neighbors (KNN)

This project processes structured animal data from .txt and .csv files, extracting relevant details such as animal names, binary features, and class labels. It implements a K-Nearest Neighbors (KNN) classification system to categorize animal species based on feature similarity.

The program supports multiple distance metrics — Euclidean, Hamming, and Jaccard — to measure similarity between data points. Machine learning techniques are applied to determine feature similarities and predict classifications for unseen animal samples. Additionally, it evaluates prediction accuracy against labeled test data.

📁 Files Included

main.c — Main program file implementing the core logic.
givenA1.h — Header file defining the Animal struct and constants.
a1Data.txt — Dataset containing training data.
testData.csv — Dataset containing test samples and ground truth labels.

🧠 Core Functionality

📥 Data Processing: Reads and parses animal data from files.
📏 Distance Calculations: Computes Euclidean, Hamming, and Jaccard distances between feature vectors.
🔍 KNN Classification: Finds k nearest neighbors and predicts a class based on majority voting.
📊 Accuracy Evaluation: Tests model performance using labeled test data.
