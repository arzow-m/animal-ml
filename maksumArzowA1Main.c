#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "givenA1.h" // include header file 

int main(int argc, char *argv[]) {

    int numRead = 0;
    int choice;
    float accuracy = 0.0;
    struct Animal dataZoo[NUM_SAMPLES];
    struct Animal testData[NUM_TEST_DATA];
    char file[30] = "a1Data.txt";
    float euclideanDistance = 0;
    int hammingDistance = 0;
    float jaccardSimilarity = 0;
    int k = 5;
    int eucClass = 0;
    int hamClass = 0;
    int jacClass = 0;
    int task1Completed = 0; // flag to ensure task 1 is done first

    int vector1[16] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int vector2[16] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1};
    int newSample[16] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int kNearestNeighbors[NUM_SAMPLES];

    // bonus: make sure the file name is provided, else exit
    if (argc > 1) {
        // verify the length of the file name is within the limit
        if (strlen(argv[1]) < 30) {
            strcpy(file, argv[1]);
        } else {
            printf("Error: The provided file name exceeds the allowed length.\n");
            return 1;
        }
    } else {
        printf("Error: No file name provided. Please specify a valid data file.\n");
        return 1;
    }

    // read from file first 
    numRead = readFromFile(file, dataZoo);

    do {
        printf("\nHere is the menu - enter a number between 1 and 5\n\n");
        printf("Enter your choice: ");

        // check if input is valid
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 1 and 5.\n");
            while (getchar() != '\n'); // clear input buffer
            continue; 
        }

        // ensure task 1 is completed first
        if (choice != 1 && (task1Completed == 0)) {
            printf("Error: You must complete task 1 before proceeding to other tasks.\n");
            continue; // restart loop
        }

        switch (choice) {
            case 1: 
                // task 1: display dataset
                for (int i = 0; i < numRead; i++) {  
                    printf("%s ", dataZoo[i].animalName); 
                    for (int j = 0; j < NUM_FEATURES; j++) { 
                        printf("%d ", dataZoo[i].features[j]);
                    }
                    printf("%d\n", dataZoo[i].classLabel);
                }
                task1Completed = 1; // mark task 1 as completed
                break;

            case 2:
                // task 2: calculate distances
                distanceFunctions(vector1, vector2, &euclideanDistance, &hammingDistance, &jaccardSimilarity);
                printf("Euclidean Distance: %f", euclideanDistance);
                printf("\nHamming Distance: %d", hammingDistance);
                printf("\nJaccard Similarity: %f\n", jaccardSimilarity);
                break;

            case 3:
                // task 3: find k nearest neighbors
                findKNearestNeighbors(dataZoo, newSample, k, 1, kNearestNeighbors);
                printf("Nearest neighbors for new sample with Euclidean Distance: ");
                for (int i = 0; i < k; i++) {
                    printf("%d ", kNearestNeighbors[i]);
                }
                printf("\n");

                findKNearestNeighbors(dataZoo, newSample, k, 2, kNearestNeighbors);
                printf("Nearest neighbors for new sample with Hamming Distance: ");
                for (int i = 0; i < k; i++) {
                    printf("%d ", kNearestNeighbors[i]);
                }
                printf("\n");

                findKNearestNeighbors(dataZoo, newSample, k, 3, kNearestNeighbors);
                printf("Nearest neighbors for new sample with Jaccard Similarity: ");
                for (int i = 0; i < k; i++) {
                    printf("%d ", kNearestNeighbors[i]);
                }
                printf("\n");
                break;

            case 4:
                // task 4: predict class
                eucClass = predictClass(dataZoo, newSample, 1, k);
                printf("\nThe predicted class is: %d\n\n", eucClass);

                hamClass = predictClass(dataZoo, newSample, 2, k);
                printf("The predicted class is: %d\n\n", hamClass);

                jacClass = predictClass(dataZoo, newSample, 3, k);
                printf("The predicted class is: %d\n", jacClass);
                break;

            case 5: 
                // task 5: compute accuracy
                accuracy = findAccuracy(dataZoo, 1, testData, k);
                printf("\nThe accuracy for the test data is %lf\n", accuracy);
                accuracy = findAccuracy(dataZoo, 2, testData, k);
                printf("\nThe accuracy for the test data is %lf\n", accuracy);
                accuracy = findAccuracy(dataZoo, 3, testData, k);
                printf("\nThe accuracy for the test data is %lf\n", accuracy);
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }

    } while (1); // infinite loop until user manually exits

    return 0;
}
