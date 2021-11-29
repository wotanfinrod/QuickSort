//Mustafa Yilmaz Cakici

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>	
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>

using namespace std;

class Tweet //Tweet class for holding tweet attributes
{
    public:
    int tweet_id;
    int tweet_unixtime;
    string track_title;
    string tweet_datetime;
    string artist_name;
    string country;
};

int RandomInRange(int lowIndex, int highIndex) //To calculate random pivots
{
    int rangeLength = highIndex - lowIndex + 1;
    int x = (rand() % rangeLength) + lowIndex;
    return x;
}

int partition(Tweet arr[], int lowIndex, int highIndex, bool randomPivot)
{
    int pivotIndex;

    if(randomPivot) //If the pivot is randomly selected
    {
        pivotIndex = RandomInRange(lowIndex, highIndex); //Select a random index for pivot
        swap(arr[highIndex], arr[pivotIndex]); //Swap the pivot element with the rightmost element
        pivotIndex = highIndex; //Rightmost element is the pivot
    }
    else
    {
        pivotIndex = highIndex; //Rightmost element is the pivot        
    }

    int i = lowIndex; //Index for unsorted leftmost element and correct location for pivot


    for (int j = lowIndex; j <= highIndex-1 ; j++)
    {
        bool swapAcknow = false; //Determining if swap will happen or not  
        
        //Checking swap condition
        if (arr[j].country < arr[pivotIndex].country) swapAcknow = true; //Check for country
        else if(arr[j].country == arr[pivotIndex].country && arr[j].artist_name < arr[pivotIndex].artist_name) swapAcknow = true; //Check for artist_name
        else if(arr[j].country == arr[pivotIndex].country && arr[j].artist_name == arr[pivotIndex].artist_name && arr[j].tweet_unixtime < arr[pivotIndex].tweet_unixtime) swapAcknow = true; //Check for unixtime
        
        if (swapAcknow) 
        {
            swap(arr[j], arr[i]);
            i++;
        }
    }

    swap(arr[i], arr[highIndex]); //Replace the pivot to its correct position.
    return i; //Return the pivot index
}



void QuickSort(Tweet arr[], int lowIndex, int highIndex,bool isRandomized)
{
    if(lowIndex < highIndex) // Stop condition
    {
        int pivot = partition(arr, lowIndex, highIndex, isRandomized); //Calling the partition function to find the next pivot

        //Recursive calls
        QuickSort(arr, lowIndex, pivot - 1,isRandomized); 
        QuickSort(arr, pivot + 1, highIndex, isRandomized);

    }
}





int main(int argc, char* argv[])
{
    srand(time(NULL)); //Randomized seed

    const int N = atoi(argv[1]); //Number of tweets to be sorted
    const string A = argv[2]; //Type of pivot selection (randomized or deterministic)
    const string I = argv[3]; //Input file path
    const string O = argv[4]; // Output file path
    bool isRandomPivot;
    
    //Assigning Pivot selection method
    if(A == "randomized" || A == "Randomized") isRandomPivot = true;
    else if (A == "deterministic" || A == "Deterministic") isRandomPivot = false;
    else
    {
        cerr << "Please enter a valid pivot selection method";
        exit(1);
    }

    //File Open
    ifstream file;
    file.open(I);
    if(!file)  //File check
    {
        cerr << "File not found!";
        exit(1);
    }    

    //File Read
    string inputLine;
    Tweet* tweetArr = new Tweet[N]; //Memory allocated for Tweet array with N elements
    getline(file, inputLine);  //Header inputLine is read

    for (int i = 0; i < N; i++)
    {
        //file >> tweetArr[i].tweet_id; //Tweet id imported

        getline(file, inputLine, '\t');
        tweetArr[i].tweet_id = stoi(inputLine);

        getline(file, inputLine, '\t'); //Tweet Datetime imported
		tweetArr[i].tweet_datetime=inputLine; //Tweet Datetime assigned

		//file >> tweetArr[i].tweet_unixtime; //Unixtime imported
        getline(file, inputLine, '\t');
        tweetArr[i].tweet_unixtime = stoi(inputLine);


        getline(file, inputLine, '\t'); //Artist Name imported
		tweetArr[i].artist_name=inputLine; //Artist Name assigned
		
		getline(file, inputLine, '\t'); //Track Title imported
        tweetArr[i].track_title=inputLine; //Track Title assigned
		

		getline(file, inputLine, '\n'); //Country Name imported
		tweetArr[i].country=inputLine; //Country Name assigned    
    }

    file.close(); //Close the file

    clock_t t; //Calculating the the runtime for quicksort spesifically 
    t = clock();
    
        QuickSort(tweetArr, 0, N-1, isRandomPivot);// Executing QuickSort with given parameters. 
    
    t = clock() - t;
   	
    cout << "Quicksort took "<< ((float)t)/CLOCKS_PER_SEC << "second to execute." << endl; //Print the run-time

    //Writing the output file
    ofstream newFile;
    newFile.open(O);
    
    newFile << "tweet_id" << "\t" << "tweet_datetime" << "\t" << "tweet_unixtime" << "\t" << "artist_name" << "\t" << "track_title" << "\t" "country" << endl; // Header Line

    for(int i = 0; i < N; i++)    ///  Writing to the csv file	
    {		
        newFile << tweetArr[i].tweet_id<< "\t" << tweetArr[i].tweet_datetime << "\t" << tweetArr[i].tweet_unixtime<< "\t" <<tweetArr[i].artist_name<< "\t" <<tweetArr[i].track_title<< "\t" <<tweetArr[i].country <<endl;
	}
}
