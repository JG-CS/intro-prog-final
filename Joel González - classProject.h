/*  Programmer: Joel González
    ID: 801-13-2812
    CCOM 3033-002
    File Name: Joel González - classProject.h
    Purpose: This program will read data from a file containing randomized sequences. 
             It will normalize the data, and calculate the mean and standard deviation 
             for each sequence, as well as identify the smallest value throughout all 
             the sequences.
*/

using namespace std;

struct Sequences
{
    string sequenceID;
    int values[10],
        maxValue;
};

struct NormalizedSequences
{
    string sequenceID;
    double values[10],
           stdDev,
           mean;
};

void purpose();
void requestInputFilePath(ifstream&);
void fileToVector(vector<Sequences>&, ifstream&);
int requestNumSeq(int);
void normalize(vector<Sequences>, vector<NormalizedSequences>&, int);
void mean(vector<NormalizedSequences>&);
void stdDev(vector<NormalizedSequences>&);
void min(vector<NormalizedSequences> &, int[]);
void bubbleSort(vector<NormalizedSequences>&, double[]);
void selectionSort(vector<NormalizedSequences>&, double[]);
void displayTime(double[], double[]);
string requestOutputFilePath(ifstream&);
void writeToFile(vector<NormalizedSequences>[], int[], ifstream&, string);
/*
GLOSSARY
    VARIABLES
        main()
            ifstream sourceFile object
                Used to access file.
            string filename
                Contains the file path of the file to be analyzed

            int numSeq
                Contains the amount of sequences to be analyzed by the program

            vector<Sequences> sequences 
                Made to contain the unmodified sequences read from the file

            vector<NormalizedSequences> normalizedSeq[3]
                Made to contain the normalized sequences.
                Element 0 contains the unsorted normalized sequences.
                Element 1 is a copy of element 0, to be sorted with the bubble sort algorithm.
                Element 2 is a copy of element 0, to be sorted with the selection sort algorithm.

            int minPosition[2]
                Made to contain the position information for the smallest value throughout all sequences

            double bubbleTime[2]
                Made to contain the information related to how much time the bubble sort algorithm took to complete

            double selectionTime[2]
                Made to contain the information related to how much time the selection sort algorithm took to complete

            string outputFilePath
                Holds the output file path specified by user

        requestInputFilePath()
            string filePath
                Holds the file path input by the user.
            string dummy
                Placeholder used during the test to verify if the file is empty
            EXIT_FAILURE
                Constant used within the exit() function that sends an error message to the OS
        
        requestNumSeq()
            int userInput
                Holds the amount of sequences to be analyzed, input by user
            EXIT_FAILURE
                Constant used within the exit() function that sends an error message to the OS

        fileToVector()
            string clicks
                Dummy variable made to contain the clicks value in each sequence. 
            Sequences temp
                Temporary variable that holds the values for a sequence, before being added to the vector of unmodified sequences

        normalize()
            NormalizedSequences temp
                Temporary variable that holds the values for a sequence, before being added to the vector of unmodified sequences           

        mean()
            double sum
                Accumulator variable. Made to hold the sum of all normalized sequences for the mean calculation process. 
        
        stdDev()
            double sum
                Accumulator variable. Made to hold a sum used during the standard deviation calculation 
        
        min()
            double min
                Meant to hold the smallest value throughout all sequences. Initialized to 2, as it is larger than any 
                present in the sequences and will always be changed during the search. 
        
        bubblesort()
            clock_t clicks
                Meant to hold the "click" values during execution, to record the time taken by the algorithm to complete.
            CLOCKS_PER_SEC
                Constant used to convert from clicks to real time.
        
        selectionSort()
            double smallestValue
                Holds the smallest value during each iteration. Used to identify the smallest element 
            int smallestIndex
                Subscript for the smallest value during each iteration. Used to keep track of the position of the 
                smallest element.
            clock_t clicks 
                Meant to hold the "click" values during execution, to record the time taken by the algorithm to complete.
            CLOCKS_PER_SEC
                Constant used to convert from clicks to real time.
        
        requestOutputFileName()
            string filePath
                Meant to hold the path of the output file
            string prompt
                Holds the user's answer when asked if they wish to overwrite an already existing file.

        writeToFile()
            ofstream outputFile object
                Used to write data to the output file

    
        struct Sequences //Structure designed to hold each unmodified sequence's information. 
            string SequenceID
                Holds the ID name of each individual sequence.
            int values[10]
                Array that holds the individual values for each sequence.
            int maxValue
                Holds the maximum value in each individual sequence.
        
        struct NormalizedSequences //Structure designed to hold each normalized sequence's information.
            string sequenceID
                Holds the ID name of each individual sequence.
            int values[10]
                Array that holds the individual values for each normalized sequence.
            double values[10]
                Array that holds the individual values for each sequence.
            double stdDev
                Holds the standard deviation value for each individual sequence.
            double mean
                Holds the mean value for each individual sequence. 

    FUNCTIONS 
        ====================================================================================
        Name ====> purpose
        Input ===> None
        Process => Displays program's purpose
        Output ==> none
        ====================================================================================
        Name ====> requestInputFilePath
        Input ===> ifstream object 
        Process => Requests a file path from the user, and verifies that the file exists
                   and is not empty
        Output ==> None
        ====================================================================================
        Name ====> requestNumSeq
        Input ===> Integer value for the total amount of sequences in the file
        Process => Asks the user how many sequences they wish to analyze. Verifies that the
                   user wishes to analyze a valid amount of sequences. 
        Output ==> Integer value for the number of sequences to analyze
        ====================================================================================
        Name ====> fileToVector
        Input ===> Vector that will contain randomized sequences, ifstream object
        Process => Reads the file and saves the randomized sequences to a vector
        Output ==> None
        ====================================================================================
        Name ====> normalize
        Input ===> Vector containing sequences, Vector that will contain the normalized
                   sequences, integer value for the amount of sequences to be analyzed
        Process => Normalizes the sequences in the sequences vector and places the values
                   in the normalized sequences vector
        Output ==> None
        ====================================================================================
        Name ====> mean
        Input ===> Vector containing normalized sequences
        Process => Saves the sequence mean information each sequence to each structure vector 
                   element's mean member
        Output ==> None
        ====================================================================================
        Name ====> stdDev
        Input ===> Vector containing normalized sequences
        Process => Saves the sequence standard deviation information to each structure vector
                   element's stdDev member
        Output ==> None
        ====================================================================================
        Name ====> min
        Input ===> Vector containing normalized sequences, array that will contain the 
                   minimum element's location information
        Process => Finds the smallest value throughout all sequences and saves it's location
                   information to the minimum position array
        Output ==> None
        ====================================================================================
        Name ====> bubbleSort
        Input ===> Vector containing normalized sequences, array that will hold information 
                   related to how much time the bubble sort algorithm took to complete
        Process => Sorts the individual values in each sequences, and sorts all sequences
                   according to their mean values. Measures the time taken to sort both. 
        Output ==> None
        ====================================================================================
        Name ====> selectionSort
        Input ===> Vector containing normalized sequences, array that will hold information 
                   related to how much time the selection sort algorithm took to complete
        Process => Sorts the individual values in each sequences, and sorts all sequences
                   according to their mean values. Measures the time taken to sort both. 
        Output ==> None
        ====================================================================================
        Name ====> displayTime
        Input ===> Array containing information related to how much time the bubble sort 
                   algorithm took to complete, array containing information related to how 
                   much time the selection sort algorithm took to complete
        Process => Prints a table detailing how much time each algorithm took to complete
                   the sorting tasks
        Output ==> None
        ====================================================================================
        Name ====> requestOutputFilePath
        Input ===> ifstream object
        Process => Asks the user the output file's path. Checks to see if a file already
                   exists with that file path, asks user if they wish to overwrite. 
        Output ==> string for the output file path
        ====================================================================================
        Name ====> writeToFile
        Input ===> Array of vectors containing normalized sequences(2 are sorted),
                   array with the minimum value's position information, ifstream object
        Process => Creates a file containing the 3 sets of normalized sequences(2 are sorted),
                   and writes the smallest value and location of said value to the file.
        Output ==> None
        ====================================================================================

    FUNCTIONS USED FROM EXTERNAL HEADERS
        requestInputFilePath()
            ifstreamObject.open()
                Used to open a file.
            ifstreamObject.is_open()
                Used to verify that a file is currently open
            exit()
                Used to stop the program's execution
            ifstreamObject.seekg()
                Used to navigate through an open file
        
        requestNumSeq()
            exit()
                Used to stop the program's execution

        fileToArray()
            ifstreamObject.eof()
                Used to detect whether or not the end of the file has been reached.
            ifstreamObject.close()
                Used to close the input file after the necessary information has been extracted.
            vectorObject.push_back()
                Used to increase the vector's size and add a new element dynamically. 
            vectorObject.pop_back()
                Used to decrease the size of a vector by 1. Information stored in that spot is lost.
            vectorObject.size()
                Returns the size of the vector object

        normalize()
            static_cast<double>()
                Used to convert integer or clock_t type values to double type values.
            vectorObject.push_back()
                Used to increase the vector's size and add a new element dynamically. 

        mean()
            vectorObject.size()
                Returns the size of the vector object            

        stdDev()
            vectorObject.size()
                Returns the size of the vector object  
            pow()
                Used to calculate the power of a value.
            sqrt()
                Used to calculate the square root of a value.
            
        min()
            vectorObject.size()
                Returns the size of the vector object  

        bubbleSort()
            static_cast<double>()
                Used to convert integer or clock_t type values to double type values.
            vectorObject.size()
                Returns the size of the vector object  
            clock()
                Used to store the current "CPU time" taken at the time of invocation.
            swap()
                Used to exchange the positions of two array elements. 

        selectionSort()
            static_cast<double>()
                Used to convert integer or clock_t type values to double type values.
            vectorObject.size()
                Returns the size of the vector object
            clock()
                Used to store the current "CPU time" taken at the time of invocation.
            swap()
                Used to exchange the positions of two array elements. 
        
        displayTime()
            setprecision()
                Used to set how many decimal positions should be printed when displaying decimal values
            string()
                Used to create strings that allow for a more viewer-friendly output.

        requestOutputFilePath()
            ifstreamObject.open()
                Used to open a file.
            ifstreamObject.is_open()
                Used to determine whether or not another file with the specified filename already exists,
                by checking to see if it is possible to open a file with that name.
            ifstreamObject.close()
                Used to close the file after the user has chosen whether or not to overwrite it.
            tolower()
                Converts an uppercase character to a lowercase character
            
        writeToFile()
            vectorObject.size()
                Returns the size of the vector object
            ofstreamObject.open()
                Creates/overwrites a file with the specified filename
            setw()
                Used to determine the amount of character spaces a printable element will take when written to the file. 
            string()
                Used to create strings that allow for a more viewer-friendly output.
            setprecision()
                Used to set how many decimal positions should be printed when displaying decimal values
            ofstreamObject.close()
                Closes the newly-created file after writing all the necessary information.
*/