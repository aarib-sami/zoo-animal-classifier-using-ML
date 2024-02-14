#include "givenA1.h"
#include "helper.h"

int main()
{
    struct Animal dataZoo [NUM_SAMPLES];
    struct Animal testData [NUM_TEST_DATA];
    int task1;
    int task2;
    int task5;
    int mode;
    int whichFeature = 13;
    int kNearestNeighbors [NUM_SAMPLES];
    int task8;
    int k;
    int d;

    int choice;

    // Aardvark
    int sample1 [NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1};
    // Antelope
    int sample2 [NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 4, 1, 0, 1};
    // termite
    int sample3 [NUM_FEATURES] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 6, 0, 0, 0};

    //gorilla
    int sample4 [NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 2, 0, 0, 1};

    // test
    int sample5 [NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};

    float task4;
    float mean;
    float task6;
    float task9;
    
    char fName[30] = "a1Data.txt";

    // task 1
    task1 = readFromFile (fName, dataZoo);
    printf("Test 1 Result: %d\n\n", task1);

    strcpy(fName,"testData.csv");
    task1 = readTestFromFile (fName, testData);
    printf("Test 1 Result: %d\n\n", task1);


    do 
    {
        printf ("\nHere is the menu - enter a number between 1 and 9 \n\n");
        printf ("1. Task 2 – generate stats\n");
        printf ("2. Task 3 – print class distribution\n");
        printf ("3. Task 4 – eculdidan distance\n");
        printf ("4. Task 5 – hamming distance \n");
        printf ("5. Task 6 – jaccardSimilarity \n");
        printf ("6. Task 7 – findKNearestNeighbours\n");
        printf ("7. Task 8 – predictClass\n");
        printf ("8. Task 9 – find accuracy\n");
        
        printf ("9. Exit\n");
        
        printf ("Enter your choice: ");
        scanf ("%d", &choice);
        printf ("\n\n");
        
        if (choice < 1 || choice > 8) {
            break;
        }
        
        switch (choice) {
            case 1:
                printf("Please enter feature #: \n");
                scanf("%d", &whichFeature);
                task2 = generateStatisticsFeatureX(dataZoo, whichFeature, &mean, &mode);
                printf("Task 2 Mean: %f\n", mean);
                printf("Task 2 Mode: %d\n", mode);
                printf("Task 2 Result: %d\n\n", task2);
                break;
            case 2:
                classDistribution (dataZoo);
                break;
            case 3:
                task4 = euclideanDistance(sample3, sample4);
                printf("Task 4 Result: %f\n\n", task4);
                break;
            case 4:
                task5 = hammingDistance(sample1, sample2);
                printf("Task 5 Result: %d\n\n", task5);
                break;

            case 5:
                task6 = jaccardSimilarity(sample1, sample2);
                printf("Task 6 Result: %f\n\n", task6); 
                break;
            case 6:
                printf("Please enter k: \n");
                scanf("%d", &k);
                printf("Please enter which distance formula: \n");
                scanf("%d", &d);
                findKNearestNeighbors(dataZoo, sample1, k, d, kNearestNeighbors);
                printf("KNearestNeighbors: \n");
                for (int i = 0; i < k; i++)
                {
                    printf("%d \n", kNearestNeighbors[i]);
                }
                break;
            case 7:
                printf("Please enter k: \n");
                scanf("%d", &k);
                printf("\n");
                findKNearestNeighbors(dataZoo, sample1, k, 1, kNearestNeighbors);
                task8 = predictClass(dataZoo, kNearestNeighbors, sample1, k);
                printf("Predicted class: %d \n\n", task8);
                break;
            case 8:
                printf("Please enter k: \n");
                scanf("%d", &k);
                task9 = findAccuracy(dataZoo, testData, k);
                printf("Accuracy: %f \n", task9);
                break;

            default: printf ("Invalid, will exit\n");                
        }
    }while (choice >= 1 || choice <= 8);
    return 0;
}