#define NUM_FEATURES 16   // not including animal name and class label
#define NUM_SAMPLES 100      // total number of samples / rows in the given zoo dataset
#define NUM_CLASSES 7        // total number of class labels in zoo dataset
#define NUM_TEST_DATA 20     // total number of samples / rows in the test dataset - you need this for task 9
#define MAX_LENGTH_ANIMAL_NAME 50
#define POSSIBLE_LEG_COMBINATIONS 5

int compare(const void *a, const void *b);

void sort (float [NUM_SAMPLES][2], int size);

int readTestFromFile (char fName [30], struct Animal dataZoo [NUM_TEST_DATA]);