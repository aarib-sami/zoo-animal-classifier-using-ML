    #include "givenA1.h"
    #include "helper.h"   
    

    // Function to read data from a file and populate an array of Animal structures
    int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES])
    {
        FILE *file = fopen(fName, "r");
        
        if(file == NULL)
        {
            return -1;
        }
        
        for (int i = 0; i < NUM_SAMPLES; i++)
        {
            fscanf(file, "%s", dataZoo[i].animalName);
            for (int j = 0; j < NUM_FEATURES; j++)
            {
                fscanf(file, "%d", &dataZoo[i].features[j]);
            }
            fscanf(file, "%d", &dataZoo[i].classLabel);
        }
        return 1;
    }

    // Function to read test data from a file and populate an array of Animal structures
    int readTestFromFile (char fName [30], struct Animal dataZoo [NUM_TEST_DATA])
    {
        FILE *file = fopen(fName, "r");
        
        if(file == NULL)
        {
            return -1;
        }
        
        for (int i = 0; i < NUM_TEST_DATA; i++) {
        fscanf(file, "%49[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                   dataZoo[i].animalName,
                   &dataZoo[i].features[0], &dataZoo[i].features[1], &dataZoo[i].features[2], &dataZoo[i].features[3],
                   &dataZoo[i].features[4], &dataZoo[i].features[5], &dataZoo[i].features[6], &dataZoo[i].features[7],
                   &dataZoo[i].features[8], &dataZoo[i].features[9], &dataZoo[i].features[10], &dataZoo[i].features[11],
                   &dataZoo[i].features[12], &dataZoo[i].features[13], &dataZoo[i].features[14], &dataZoo[i].features[15],
                   &dataZoo[i].classLabel); 
        }
        return 1;
    }

    // Function to generate statistics for a given feature in the dataset
    int generateStatisticsFeatureX (struct Animal dataZoo [NUM_SAMPLES], int whichFeature, float * mean, int * mode)
    {
        // Check if the feature index is valid
        if (!(whichFeature >= 1 && whichFeature <=16))
        {
            return -1;
        }

        int sum = 0;
        int count1 = 0;
        int count0 = 0;
        int counter = 0;
        int index;

        // Calculate mean and mode for non-special feature
        if (whichFeature!=13)
        {
            for (int i = 0; i < NUM_SAMPLES; i++)
            {
                sum = sum + dataZoo[i].features[whichFeature-1];
                if (dataZoo[i].features[whichFeature-1] == 1)
                {
                    count1++;
                }
                else
                {
                    count0++;
                }
            }
            *mean = (float)sum/NUM_SAMPLES;

            if (count1 >= count0)
            {
                *mode = 1;
            }
            else if (count1 < count0)
            {
                *mode = 0;
            }
            else if ((count1 == 0) || (count0 == 0))
            {
                *mode = -1;
            }
        }   
        else
        {
            // Calculate mean and mode for special feature 13
            int modeResult[6][2] = {{0,0},{0,2},{0,4},{0,5},{0,6},{0,8}};

            for (int i = 0; i < NUM_SAMPLES; i++)
            {
                sum += dataZoo[i].features[12];
                if (dataZoo[i].features[whichFeature-1] == 0)
                {
                    modeResult[0][0]++;
                }
                else if ((dataZoo[i].features[whichFeature-1] == 2))
                {
                    modeResult[1][0]++;
                }
                else if (dataZoo[i].features[whichFeature-1] == 4)
                {
                    modeResult[2][0]++;
                }
                else if (dataZoo[i].features[whichFeature-1] == 5)
                {
                    modeResult[3][0]++;
                }
                else if (dataZoo[i].features[whichFeature-1] == 6)
                {
                    modeResult[4][0]++;
                }
                else if (dataZoo[i].features[whichFeature-1] == 8)
                {
                    modeResult[5][0]++;
                }

                for (int i = 0; i < POSSIBLE_LEG_COMBINATIONS; i++)
                {
                    if (counter < modeResult[i][0])
                    {
                        counter = modeResult[i][0];
                        index = modeResult[i][1];
                    }
                }
                *mean = (float)sum/NUM_SAMPLES;
                *mode = index;    
                
            }
        }
        return 1;
    }

    // Function to display the class distribution in the dataset
    void classDistribution(struct Animal dataZoo[NUM_SAMPLES]) 
    {
        int mainClassCounter[NUM_CLASSES] = {0};
        int secondaryClassCounter[NUM_CLASSES] = {0};
        int maxiumumValue = 0;

        for (int i = 0; i < NUM_SAMPLES; i++) 
        {
            int label = dataZoo[i].classLabel;
            if (label >= 1 && label <= NUM_CLASSES) 
            {
                mainClassCounter[label - 1]++;
                secondaryClassCounter[label - 1]++;
            }
        }
        for (int i = 0; i < NUM_CLASSES; i++) 
        {
            if (mainClassCounter[i] > maxiumumValue) 
            {
                maxiumumValue = mainClassCounter[i];
            }
        }
        printf("   (%d) \n", secondaryClassCounter[0]);
        for (int i = maxiumumValue; i > 0; i--) 
        {
            for (int j = 0; j < NUM_CLASSES; j++) 
            {
                if(i == mainClassCounter[j]) 
                {   
                    printf("    *     ");
                    mainClassCounter[j]--;
                    if (i-1 == secondaryClassCounter[j+1])
                    {
                        printf("   (%d)",secondaryClassCounter[j+1]);
                    }
                } 
                else 
                {
                    
                    if (i-1 == secondaryClassCounter[j])
                    {
                        printf("    ");
                    }
                    else
                    {
                        printf("          ");
                    }
                    
                    if (i-1 == secondaryClassCounter[j+1])
                    {
                        printf("   (%d)",secondaryClassCounter[j+1]);
                    }
                }
            }
            printf("\n");
        }

        for (int i = 0; i < NUM_CLASSES; i++) 
        {
            printf("Class %d   ", i + 1);
        }

        printf("\n\n");
    }

    // Function to calculate Euclidean distance between two vectors
    float euclideanDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES])
    {
        float eucDistance = 0.00;

        for(int i = 0; i < NUM_FEATURES; i++)
        {
            eucDistance += (vector1[i] - vector2[i])*(vector1[i] - vector2[i]);
        }
        
        eucDistance = sqrt(eucDistance);
        
        return eucDistance;
    }

    // Function to calculate Hammind Distance between two vectors
    int hammingDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES])
    {
        int hamDistance = 0;

        for(int i = 0; i < NUM_FEATURES; i++)
        {
            if(!(vector1[i] == vector2[i]))
            {
                hamDistance++;
            }
        }
        
        return hamDistance;
    }

    // Function to calculate Jaccard similarity between two vectors
    float jaccardSimilarity (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES])
    {
        float jaccard;
        int onetoOne = 0;
        int zeroTozero = 0;

        for(int i = 0; i < NUM_FEATURES; i++)
        {
            if(vector1[i] == 1 && vector2[i] == 1)
            {
                onetoOne++;
            }
            else if (vector1[i] == 0 && vector2[i] == 0)
            {
                zeroTozero++;
            }
        }
        
        jaccard = (float)(onetoOne)/(NUM_FEATURES-zeroTozero);

        return jaccard;
    }

    // Function to find K-nearest neighbors using a specified distance function
    void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES])
    {
        float distanceData [NUM_SAMPLES][2];

        if (whichDistanceFunction == 1)
        {
            for (int i = 0; i < NUM_SAMPLES; i++)
            {
                float eucDistance;
                eucDistance = euclideanDistance(dataZoo[i].features, newSample);
                distanceData[i][0] = eucDistance;
                distanceData[i][1] = i;
            }
        }
        else if (whichDistanceFunction == 2)
        {
            for (int i = 0; i < NUM_SAMPLES; i++)
            {
                float hamDistance;
                hamDistance = hammingDistance(dataZoo[i].features, newSample);
                distanceData[i][0] = hamDistance;
                distanceData[i][1] = i;
            }
        }
        else if (whichDistanceFunction == 3)
        {
            for (int i = 0; i < NUM_SAMPLES; i++)
            {
                float jaccardSim;
                jaccardSim = jaccardSimilarity(dataZoo[i].features, newSample);
                distanceData[i][0] = jaccardSim;
                distanceData[i][1] = i;
            }
        }

        int arraySize = sizeof(distanceData) / sizeof(distanceData[0]);
        sort(distanceData, arraySize);
  
        for (int i = 0; i < k; i++)
        {
            kNearestNeighbors[i] = (int)distanceData[i][1];
        }
    }

    // Function to predict the class of a new sample based on K-nearest neighbors
    int predictClass (struct Animal dataZoo [NUM_SAMPLES], int neighborsForNewSample [NUM_SAMPLES], int newSample [NUM_FEATURES], int k)
    {
        int class [NUM_CLASSES] = {0,0,0,0,0,0,0};
        int finalClass = 0;
        int sum = 0;

        for (int i = 0; i < k; i++)
        {
            int classNum;
            classNum = dataZoo[neighborsForNewSample[i]].classLabel;
            class[classNum-1]++;
        }


        for (int i = 0; i < NUM_CLASSES; i++)
        {  
            if (class[i] > sum)
            {
                sum = class[i];
                finalClass = i+1;
            }
        }
        return finalClass;
    }

    // Function to find the accuracy of the prediction on test data
    float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], struct Animal testData [NUM_TEST_DATA], int k)
    {
        int prediction;
        int correctPrediction = 0;
        int totalPredictions = 0;
        float finalAccuracy;
        int neighborsForNewSample [NUM_SAMPLES];
        
        for (int j = 0; j < NUM_TEST_DATA; j++)
        {
            findKNearestNeighbors(dataZoo, testData[j].features, k, 1, neighborsForNewSample);
            prediction = predictClass(dataZoo, neighborsForNewSample, testData[j].features, k);
            printf("Actual: %d \nPredicted: %d\n",testData[j].classLabel, prediction);
            if (prediction == testData[j].classLabel)
            {   
                correctPrediction++;
                totalPredictions++;
            }
            else
            {
                totalPredictions++;
            }
        }

        printf("Total Prediciton: %d \nCorrect: %d\n", totalPredictions, correctPrediction);
        finalAccuracy = (float)correctPrediction/totalPredictions;
        
        return finalAccuracy;
    }


    // Function definiton obtained from ChatGPT
    int compare(const void *a, const void *b) {
    const float *fa = (const float *)a;
    const float *fb = (const float *)b;

    // Use < and > for ascending and descending order, respectively
    if (*fa < *fb) return -1;
    if (*fa > *fb) return 1;
    return 0;
}

    // Function definiton obtained from ChatGPT
    void sort (float array[NUM_SAMPLES][2], int size)
    {
        qsort(array, size, sizeof(array[0]), compare);
    }
