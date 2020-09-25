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
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "classProject.h"


void purpose()
{
    //Display Purpose
    cout << "\nThis program will analyze a file that contains random sequences,\
    \neach containing 10 numbers. The analysis will consist of normalizing\
    \nthe data, calculating the mean and standard deviation for each\
    \nsequence, and finding the smallest value between all sequences.\n" << endl;
    return;
}

void requestInputFilePath(ifstream& sourceFile) 
{
    //Declare Variables
    string filePath; //Will contain the file path input by the user
    string dummy;    //Dummy variable used during a test to see if the file is empty

    //Ask for file path
    cout << "Please input the path of the file containing the random sequences: ";
    cin >> filePath;

    //Open File
    sourceFile.open(filePath);

    //Check if file was opened successfully. 
    if(!(sourceFile.is_open()))
        {
            cout << "There was an error opening the file. Program closing." << endl;
            exit(EXIT_FAILURE);
        }

    //Check if file is empty
    if(sourceFile >> dummy)
    {
        cout << "File opened successfully." << endl;
    }
    else
    {
        cout << "The file is empty. Program closing" << endl;
        exit(EXIT_FAILURE);
    }
    
    //Reset cursor to the beginning
    sourceFile.seekg(0,ios::beg);
    return;
}

int requestNumSeq(int sequenceAmount)
{
    //Declare Variable
    int userInput;     //Will hold the amount of sequences the user wishes to analyze

    //Ask user how many sequences to analyze
    cout << "Please enter the amount of sequences you would like to analyze: ";
    cin >> userInput;
  
    //Verify that the amount of sequences to analyze is valid
    while (userInput > sequenceAmount || userInput <= 0)
    {
        if (userInput <= 0)
        {
            cout << "You have entered an invalid number of sequences to analyze,\n\
or a non-numerical string. Program closing.\n";
            exit(EXIT_FAILURE);
        }
        else
        {
            cout << "You have entered a number that is greater than the amount of\nsequences present in the file.\
            \nPlease enter a valid number of sequences to analyze: ";
        }
        cin >> userInput;
    }
    return userInput;
}

void fileToVector(vector<Sequences> &sequences,ifstream& sourceFile)
{
    //Declare variables 
    string clicks;   //Dummy variable to hold each sequences's clicks value while the file is read
    Sequences temp;  //Temporary variable to read each sequence

    //Read data and copy to vector, ignoring click values
    while(!sourceFile.eof())
    {
        sourceFile >> temp.sequenceID;
        for(int j = 0; j < 10; j++)
        {
            sourceFile >> temp.values[j]; 
        }
        sourceFile >> clicks;
        sourceFile >> temp.maxValue;
        sequences.push_back(temp);
    }
    sourceFile.close();
    
    //Deletes the last element of the vector, which is duplicate/invalid. 
    sequences.pop_back();

    //Display total amount of sequences in file 
    cout << "The file has " << sequences.size() << " sequences." << endl;
//    Excess code used during debugging, can be ignored.
//    for(int i = 0;i < 10; i++)
//    {
//            cout <<  sequences[i].sequenceID << endl;
//    }
    return;
}

void normalize(vector<Sequences> sequences,vector<NormalizedSequences> &normalizedSeq, int numSeq)
{
    //Declare Variable
    NormalizedSequences temp; //Temp value to hold the structure member values before transferring to the vectors
 
    //Normalize sequences, save normalized values in the normalized sequences vector 
    for(int i = 0; i < numSeq; i++)
    {
        temp.sequenceID = sequences[i].sequenceID;
        for(int j = 0; j < 10; j++)
        {
            temp.values[j] = static_cast<double>(sequences[i].values[j])/sequences[i].maxValue;
        }
        normalizedSeq.push_back(temp);
    }
//    Excess code used during debugging, can be ignored.
//    for(int i = 0; i < normalizedSeq.size(); i++)
//    {    
//         cout << setprecision(6) << normalizedSeq[i].values[9] << endl;
//    }
    return;
}

void mean(vector<NormalizedSequences> &normalizedSeq)
{
    //Declare variable
    double sum;         //Will hold the sum of all values, used during mean calculation

    //Calculate mean, save to each of the structure vector element's mean member variable 
    for(int i = 0;i< normalizedSeq.size();i++)
    {
        sum = 0;
        for(int j = 0; j < 10; j++)
        {
        sum += normalizedSeq[i].values[j]; 
        }
        normalizedSeq[i].mean = sum/10;
        // Excess code used during debugging, can be ignored.
        // cout << normalizedSeq[i].mean << endl;
    }
    return;
}

void stdDev(vector<NormalizedSequences> &normalizedSeq)
{
    //Declare Variable
    double sum;         //Will hold a sum used during standard deviation calculation

    //Calculate standard deviation, save to each of the structure vector element's stdDev member variable 
    for (int i = 0; i < normalizedSeq.size(); i++)
    {
        sum = 0;
        for(int j = 0; j < 10; j++)
        {
            sum += pow(normalizedSeq[i].values[j] - normalizedSeq[i].mean,2);
        }
        normalizedSeq[i].stdDev = sqrt(sum/10);
    }
//    Excess code used during debugging, can be ignored.
//    for (int i = 0; i < normalizedSeq.size(); i++)
//    {
//        cout << normalizedSeq[i].stdDev << endl;
//    }
    return;
}

void min(vector<NormalizedSequences> &normalizedSeq, int minPosition[])
{
    //Declare Variable
    double min = 2;     //Will hold the smallest value found throughout all sequences. Starts at 2 because all values will be lower than 2

    //Search through the values in all sequences to find the smallest value, save it's position information to the minPosition array
    for(int i = 0; i < normalizedSeq.size(); i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(min > normalizedSeq[i].values[j])
            {
                min = normalizedSeq[i].values[j];
                minPosition[0] = i;
                minPosition[1] = j;
            }
        }
    }
//    Excess code used during debugging, can be ignored.
//    cout << fixed << min << " " << minPosition[0] + 1 << " " << minPosition[1] + 1<< endl;
    return;
}

void bubbleSort(vector<NormalizedSequences> &sequenceToSort, double bubbleTime[])
{
    //Declare Variable
    clock_t clicks;    //Will hold information related to how much time it takes the computer to perform the sorting tasks
    
    //Save current CPU time 
    clicks = clock();

    //Sort values within each sequence
    for(int y = 0; y < sequenceToSort.size(); y++)
    {    
        for(int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if(sequenceToSort[y].values[j] > sequenceToSort[y].values[j+1])
                {
                    swap(sequenceToSort[y].values[j],sequenceToSort[y].values[j+1]);
                }
            }
        }
    }

    //Save average amount of time taken to sort values within sequences
    bubbleTime[0] = (static_cast<double>((clock() - clicks)) / CLOCKS_PER_SEC) / sequenceToSort.size();
    //Excess code used during debugging, can be ignored.
    // cout << fixed << setprecision(10) << bubbleTime[0] << endl;
    // for(int i = 0; i < sequenceToSort.size(); i++)
    // {
    //     cout << sequenceToSort[i].values[9] << endl;
    // }

    //Sort sequences based on their mean values
    clicks = clock();
    for(int i = 0; i < sequenceToSort.size(); i++)
    {
        for (int j = 0; j < sequenceToSort.size() - 1; j++)
        {
            if(sequenceToSort[j].mean > sequenceToSort[j+1].mean)
            {
                swap(sequenceToSort[j],sequenceToSort[j+1]);
            }
        }
    }
    //Save amount of time taken to sort sequences by mean value
    bubbleTime[1] = static_cast<double>((clock() - clicks)) / CLOCKS_PER_SEC;
    // Excess code used during debugging, can be ignored.
    // cout << bubbleTime[1] << endl;
    // for(int i = 0; i < sequenceToSort.size(); i++)
    // {
    //     cout << sequenceToSort[i].mean << endl;
    // }
    return;
}

void selectionSort(vector<NormalizedSequences> &sequenceToSort, double selectionTime[])
{
    //Declare Variable
    double smallestValue; //Will the smallest value found during that iteration through the array
    int smallestIndex;    //Will hold the subscript of the smallest value found during that iteration through the array
    clock_t clicks;       //Will hold information related to how much time it takes the computer to perform the sorting tasks

    //Save current CPU time 
    clicks = clock();

    //Sort values within each sequence
    for(int y = 0; y < sequenceToSort.size();y++)
    {
        for (int i = 0; i < 9; i++)
        {
            smallestValue = sequenceToSort[y].values[i];
            smallestIndex= i;
            for (int j = i+1; j < 10; j++)
            {
                if (sequenceToSort[y].values[j]< smallestValue)
                {
                    smallestValue = sequenceToSort[y].values[j];
                    smallestIndex = j;
                }
            }
            swap(sequenceToSort[y].values[i], sequenceToSort[y].values[smallestIndex]);
        }
    }

    //Save average amount of time taken to sort values within sequences
    selectionTime[0] = (static_cast<double>((clock() - clicks)) / CLOCKS_PER_SEC) / sequenceToSort.size();
    // Excess code used during debugging, can be ignored.
    // cout << selectionTime[0] << endl;
    // for(int i = 0; i < sequenceToSort.size(); i++)
    // {
    //     cout << sequenceToSort[i].values[9] << endl;
    // }
    
    //Sort sequences based on their mean values
    clicks = clock();
    for(int i = 0; i < sequenceToSort.size() - 1; i++)
    {
        smallestValue = sequenceToSort[i].mean;
        smallestIndex = i;
        for(int j = i+1; j < sequenceToSort.size(); j++)
        {
            if(sequenceToSort[j].mean < smallestValue)
            {
                smallestValue = sequenceToSort[j].mean;
                smallestIndex = j;
            }
        }
        swap(sequenceToSort[i],sequenceToSort[smallestIndex]);
    }
    //Save amount of time taken to sort sequences by mean value
    selectionTime[1] = static_cast<double>((clock() - clicks)) / CLOCKS_PER_SEC;
    // Excess code used during debugging, can be ignored.
    // cout << selectionTime[1] << endl;
    // for(int i = 0; i < sequenceToSort.size(); i++)
    // {
    //     cout << sequenceToSort[i].mean << endl;
    // }
    return;
}

void displayTime(double bubbleTime[], double selectionTime[])
{
    //Display a table containing information on how much time it took to perform the sorting tasks with each algorithm
    cout << '\n' << string(19,' ') << "***ALGORITHM EFFICIENCY***" << '\n'
         << fixed << setprecision(10) <<  string(64, '-') << '\n'
         << '|' << " ALGORITHM " << '|' << " Time taken to sort " << '|' << " Average time taken to sort  " << '|' << '\n'
         << '|' << string(11,' ') << '|' << " sequences by mean  " << '|' << " the values in each sequence " << '|' << '\n'
         << '|' << string(11,' ') << '|' << "     (seconds)      " << '|' << "          (seconds)          " << '|' << '\n'
         << string(64, '-') << '\n'
         << '|' << " BUBBLE    " << '|' << string(8,' ') <<  bubbleTime[1] << '|' << string(17,' ') << bubbleTime[0] 
         << '|' << '\n'
         << string(64, '-') << '\n'
         << '|' << " SELECTION " << '|' << string(8,' ')  << selectionTime[1] << '|' << string(17,' ') << selectionTime[0] 
         << '|' << endl
         << string(64, '-') <<  '\n' << endl;
    return;
}

string requestOutputFilePath(ifstream& sourceFile)
{
    //Declare Variables
    string filePath;    //Will hold the file path specifid by user
    string prompt;        //Will hold the answer to a prompt regarding whether or not to overwrite an already existing file

    //Ask user to enter the output file's path
    cout << "Please enter the output filepath: ";
    cin >> filePath;

    //Check if another file with that name exists. If true, ask user if they wish to overwrite
    sourceFile.open(filePath);
    while (sourceFile.is_open())
    {
        cout << "There exists a file with this path. Enter \"y\" or \"yes\" if you wish to overwrite: ";
        cin >> prompt;

        //Convert string to lowercase
        for(char &letter: prompt)
        {
            letter = tolower(letter);
        }

        if (!(prompt == "y" || prompt == "yes"))
        {
            cout << "Please enter another path for the output file: ";
            cin >> filePath;
            sourceFile.close();
            sourceFile.open(filePath);
        }
        else
        {
             sourceFile.close();
        }
    }
    return filePath;
}

void writeToFile(vector<NormalizedSequences> normalizedSeq[],int minPosition[],ifstream& sourceFile, string filePath)
{
    //Declare ofstream object 
    ofstream outputFile;        //Used to write to the output file
    
    //Created new file at the path specified by user
    outputFile.open(filePath); 

    //Write normalized sequences to file
    outputFile << setw(12) << "dataID" << setw(12) << "Value_1" << setw(12) << "Value_2" << setw(12) << "Value_3" << setw(12) << "Value_4" \
               << setw(12) << "Value_5" << setw(12) << "Value_6" << setw(12) << "Value_7" << setw(12) << "Value_8" << setw(12) << "Value_9" \
               << setw(12) << "Value_10" << setw(12) << "Mean" << setw(12) << "StdDev" << '\n' 
               << string(156,'-') << endl;
    for (int i = 0; i < normalizedSeq[0].size(); i++)
    {
        outputFile << setw(12) << normalizedSeq[0][i].sequenceID;
        for (int j = 0; j < 10; j++)
        {
            outputFile << fixed << setw(12) << setprecision(6) << normalizedSeq[0][i].values[j];
        }
        outputFile << setw(12) << setprecision(6) << normalizedSeq[0][i].mean 
        << setw(12) << setprecision(6) << normalizedSeq[0][i].stdDev << endl;
    }

    //Write information about the smallest element through the sequences
    outputFile << "\nMinimum value of all sequences is: " << fixed << normalizedSeq[0][minPosition[0]].values[minPosition[1]] << ", found on column " \
               << minPosition[1] + 1 << " of sequence number " << minPosition[0] + 1 << ".\n" << endl;

    //Write sequences sorted with the bubblesort algorithm
    //Write Header
    outputFile << string(156,'=') << "\n\nSorting with BUBBLE we got:\n\n"
               << setw(12) << "dataID" << setw(12) << "Value_1" << setw(12) << "Value_2" << setw(12) << "Value_3" << setw(12) << "Value_4" \
               << setw(12) << "Value_5" << setw(12) << "Value_6" << setw(12) << "Value_7" << setw(12) << "Value_8" << setw(12) << "Value_9" \
               << setw(12) << "Value_10" << setw(12) << "Mean" << setw(12) << '\n' 
               << string(144,'-') << endl;
    //Write sequences
    for (int i = 0; i < normalizedSeq[1].size(); i++)
    {
        outputFile << setw(12) << normalizedSeq[1][i].sequenceID;
        for (int j = 0; j < 10; j++)
        {
            outputFile << fixed << setw(12) << setprecision(6) << normalizedSeq[1][i].values[j];
        }
        outputFile << setw(12) << setprecision(6) << normalizedSeq[1][i].mean << endl;
    }

    //Write sequences sorted with the selection sort algorithm

    //Write header
    outputFile << '\n' << string(156,'=') << "\n\nSorting with SELECTION we got:\n\n"
               << setw(12) << "dataID" << setw(12) << "Value_1" << setw(12) << "Value_2" << setw(12) << "Value_3" << setw(12) << "Value_4" \
               << setw(12) << "Value_5" << setw(12) << "Value_6" << setw(12) << "Value_7" << setw(12) << "Value_8" << setw(12) << "Value_9" \
               << setw(12) << "Value_10" << setw(12) << "Mean" << setw(12) << '\n' 
               << string(144,'-') << endl;
    //Write Sequences
    for (int i = 0; i < normalizedSeq[2].size(); i++)
    {
        outputFile << setw(12) << normalizedSeq[2][i].sequenceID;
        for (int j = 0; j < 10; j++)
        {
            outputFile << fixed << setw(12) << setprecision(6) << normalizedSeq[2][i].values[j];
        }
        outputFile << setw(12) << setprecision(6) << normalizedSeq[2][i].mean << endl;
    }

    //Close output file
    outputFile.close();
    cout << "Created file \"" << filePath << "\"." << endl;
    return;
}

