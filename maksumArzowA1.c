// extra c file

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "givenA1.h" // include header file

/* Task 1: reads data from txt file, stores in an array of struct Animal called dataZoo, return 1 if successful, -1 if not */
int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES]){
    char animalInfo[100];
    int i = 0;

    FILE *file; // declare variable of type FILE*
    file = fopen(fName, "r"); // open file for reading 

    if (file == NULL) { // check if the file was successfully opened
        printf("Could not open %s\n", fName);
        return -1;
    }

    while (!(feof(file))){
        fgets(animalInfo, 100, file);
        sscanf(animalInfo,"%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
        dataZoo[i].animalName,
        &dataZoo[i].features[0], &dataZoo[i].features[1], &dataZoo[i].features[2], &dataZoo[i].features[3],
        &dataZoo[i].features[4], &dataZoo[i].features[5], &dataZoo[i].features[6], &dataZoo[i].features[7],
        &dataZoo[i].features[8], &dataZoo[i].features[9], &dataZoo[i].features[10], &dataZoo[i].features[11],
        &dataZoo[i].features[12], &dataZoo[i].features[13], &dataZoo[i].features[14], &dataZoo[i].features[15],
        &dataZoo[i].classLabel
        );
        i++;
    }
    fclose(file);
    return i;
}

/* Task 2 */
void distanceFunctions(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES], float *euclideanDistance, int *hammingDistance, float *jaccardSimilarity) {
    *euclideanDistance = 0.0f;
    *hammingDistance = 0;
    *jaccardSimilarity = 0.0f;
    
    float sumSquaredDifferences = 0.0f;
    int oneOneCount = 0;
    int zeroZeroCount = 0;

    for (int i = 0; i < NUM_FEATURES; i++) {
        // euclidean Distance: sum of squared differences
        float diff = (float)(vector1[i] - vector2[i]);
        sumSquaredDifferences += diff * diff;

        // hamming Distance: count of differing positions
        if (vector1[i] != vector2[i]) {
            (*hammingDistance)++;
        }

        // aaccard similarity: count (1,1) matches and (0,0) matches
        if (vector1[i] == 1 && vector2[i] == 1) {
            oneOneCount++;
        }
        if (vector1[i] == 0 && vector2[i] == 0) {
            zeroZeroCount++;
        }
    }
    
    // compute final values
    *euclideanDistance = sqrt(sumSquaredDifferences);
    *jaccardSimilarity = ((float)oneOneCount / (16 - zeroZeroCount));
}

/* Task 3: compare newSample (some new animal defined by 16 ints) to the 100 samples in task 1, find the closest match */
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]){
    float distances[NUM_SAMPLES];
    int indices[NUM_SAMPLES];
    float euclideanDistance = 0;
    int hammingDistance = 0;
    float jaccardSimilarity = 0;

    // calucating distances
    for (int i = 0; i < NUM_SAMPLES; i++){
        distanceFunctions(newSample, dataZoo[i].features, &euclideanDistance, &hammingDistance, &jaccardSimilarity);

        if (whichDistanceFunction == 1){
            distances[i] = (euclideanDistance);
        }
        else if (whichDistanceFunction == 2){
            distances[i] = (hammingDistance);
        }
        else {
            distances[i] = (jaccardSimilarity);
        }
        indices[i] = i;
    }

    // sorting distances + keep track of indices (bubble sort algorithm was obtained from chatgpt)
    for (int i = 0; i < NUM_SAMPLES - 1; i++){
        for (int j = i + 1; j < NUM_SAMPLES; j++){

            // sorting condition, ascending for eud/ham + descending for jac
            if ((whichDistanceFunction != 3 && distances[i] > distances[j]) || 
            (whichDistanceFunction == 3 && distances[i] < distances[j]) ||
            (distances[i] == distances[j] && indices[i] > indices[j])) {
                // swap distances 
                float temp = distances[i];
                distances[i] = distances[j];
                distances[j] = temp;

                // swap indices
                int tempIndex = indices[i];
                indices[i] = indices[j];
                indices[j] = tempIndex;
            }
        }
    }

    // store the top k nearest neighbours 
    for (int i = 0; i < k; i++){
        kNearestNeighbors[i] = indices[i];
    }
}

int predictClass (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int whichDistanceFunction, int k){
    int nearestNeighbors[NUM_SAMPLES];
    int neighborLabels[NUM_SAMPLES] = {0};
    int labelCount = 0;
    int highestFrequency = 0;
    int mostFrequentLabel = neighborLabels[0];

    // find k nearest neighbors using helper function
    findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, nearestNeighbors);

    // store class labels of nearest neighbors
    for (int i = 0; i < k; i++) {
        neighborLabels[i] = dataZoo[nearestNeighbors[i]].classLabel;
    }

    // determine the most frequent class label
    for (int i = 0; i < k; i++){
        labelCount = 0;

        // count occurrences of each label
        for (int j = 0; j < k; j++){
            if (neighborLabels[i] == neighborLabels[j]){
                labelCount++;
            }
        }

        // update most frequent label if a higher count is found
        if (labelCount > highestFrequency){
            highestFrequency = labelCount;
            mostFrequentLabel = neighborLabels[i];
        }
        // if tie, choose the smaller label
        else if (labelCount == highestFrequency && neighborLabels[i] < mostFrequentLabel){
            mostFrequentLabel = neighborLabels[i];
        }
    }
    return mostFrequentLabel;
}

float findAccuracy(struct Animal dataZoo[NUM_SAMPLES], int whichDistanceFunction, struct Animal testData[NUM_TEST_DATA], int k) {
    char buffer[1000];
    int i = 0;

    // attempt to open file, throw error if cannot
    FILE *file = fopen("testData.csv", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return -1.0;
    }

    while (!(feof(file))) {
        fgets(buffer, sizeof(buffer), file);

        // initialize token with strtok
        char *token = strtok(buffer, ",");

        // store animal name as first token
        if (token != NULL) {
            strcpy(testData[i].animalName, token);
        }

        // store all feature values
        for (int j = 0; j < NUM_FEATURES; j++) {
            token = strtok(NULL, ",");
            if (token != NULL) {
                sscanf(token, "%d", &testData[i].features[j]);
            }
        }

        // store class label
        token = strtok(NULL, ",");
        if (token != NULL) {
            sscanf(token, "%d", &testData[i].classLabel);
        }

        i++;
    }


    fclose(file);

    // comparing predictions vs actual class label 
    int correctPredictions = 0;

    for (int i = 0; i < NUM_TEST_DATA; i++) {
        int prediction = predictClass(dataZoo, testData[i].features, whichDistanceFunction, k);
        
        // print only the predicted class labels
        printf("%d ", prediction);

        if (prediction == testData[i].classLabel) {
            correctPredictions++;
        }
    }
    printf("\n"); 

    // print number of correct predictions and total test cases
    printf("%d\n", correctPredictions);
    printf("%d", NUM_TEST_DATA);

    // calculating and printing accuracy 
    float accuracy = ((float)correctPredictions / NUM_TEST_DATA);

    return accuracy;
}
