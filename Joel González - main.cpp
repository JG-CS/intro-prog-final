/*  Programmer: Joel González
    ID: 801-13-2812
    CCOM 3033-002
    File Name: Joel González - classProject.h
    Purpose: This program will read data from a file containing randomized sequences. 
             It will normalize the data, and calculate the mean and standard deviation 
             for each sequence, as well as identify the smallest value throughout all 
             the sequences.
*/

#include <vector>
#include <fstream>
#include "classProject.h"

int main()
{
    //Declare ifstream object for file reading
    ifstream sourceFile;

    //Display Purpose
    purpose();

    //Declare vector that will hold unmodified sequences
    vector<Sequences> sequences; 
    
    //Ask user for filename
    requestInputFilePath(sourceFile);
    
    //Reads file and saves information to vector 
    fileToVector(sequences,sourceFile);

    //Ask user for the number of sequences to analyze
    int numSeq = requestNumSeq(sequences.size());

    //Declare arrays used to store data
    vector<NormalizedSequences> normalizedSeq[3];   //Array of structure vectors that will hold sequence data after normalization, analysis and sorting
    int minPosition[2];                             //Holds the sequence and location numbers of the smallest value throughout all sequences
    double bubbleTime[2];                           //Holds time taken to Bubble Sort sequences by mean, and avg time taken to sort each sequence's values 
    double selectionTime[2];                        //Holds time taken to Selection Sort sequences by mean and avg time taken to sort each sequence's values
    
    //Normalizes data and saves it to the normalized sequences vector. 
    normalize(sequences,normalizedSeq[0], numSeq);

    //Calculate mean and standard deviation for each normalized sequence
    mean(normalizedSeq[0]);
    stdDev(normalizedSeq[0]);

    //Find the smallest value throughout all sequences
    min(normalizedSeq[0],minPosition);
    
    //Make copies of the normalized sequences vector to sort with the bubble sort and selection sort algorithms
    normalizedSeq[2] = normalizedSeq[1] = normalizedSeq[0];

    //Use bubble sort algorithm to sort the values in each normalized sequence, and sort all sequences by mean value 
    bubbleSort(normalizedSeq[1], bubbleTime);


    //Use selection sort algorithm to sort the values in each normalized sequence, and sort all sequences by mean value 
    selectionSort(normalizedSeq[2], selectionTime);

    //Request the output file's path
    string outputFilePath = requestOutputFilePath(sourceFile);

    //Write the information contained in the normalized sequences vectors(2 sorted) and information about the smallest element throughout all the sequences
    writeToFile(normalizedSeq, minPosition, sourceFile, outputFilePath);

    //Display table detailing the time it took for each sorting method to complete 
    displayTime(bubbleTime, selectionTime);

    return 0;
}

