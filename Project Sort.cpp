#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


//This class is dedicated to managing the vectors keeping it organized for use in other classes
class dataClass {
    private:
        //Generates completely random numbers up to the specified size
        void createList(int size) {

            srand((unsigned)time(0));

            for (int i = 0; i < size; i++)
            {
                dataList.push_back(rand());
            }

            updateSize(size);

        }

        //Updates the variable arrSize
        void updateSize(int size) {
            arrSize = dataList.size();
        }
    public:
        vector <int> dataList;
        vector <int> dataListSorted;
        int arrSize = dataList.size();

        //Defines the size of the new array calling all corresponding functions to create array
        void generateList(string size) {
            int intSize = 0;
            if (size == "Small") {
                intSize = 100;
            }

            else if(size == "Medium") {
                intSize = 1000;
            }

            else if (size == "Large") {
                intSize = 10000;
            }

            //XL size
            else{
                intSize = 100000;
            }

            createList(intSize);
            
        }

        //Displays any given vector
        void outputArray(vector <int> data) {
            for (int i = 0; i < arrSize; i++)
            {
                cout << data[i] << " ";
            }
            cout << endl;
        }

        //Displays the advantages and disadvantages for each sort 
        //Recommending different sort types for each size
        void bubbleSortInfo() {
            cout << endl << endl << "Recommended for: Small, Medium" << endl
                << "Advantages: Very simple and Resource light" << endl << endl
                << "Disadvantages: Very inefficient so not good for real life application" << endl
                << "Every time a element is added the time to sort is increased exponentionally." << endl << endl;

        }

        void mergeSortInfo() {
            cout << endl << endl << "Recommended for: Small, Medium, Large" << endl
                << "Advantages: Efficient fast due to divide and conquer strategy" << endl << endl
                << "Disadvantages: Less efficient than QuickSort" << endl << endl;

        }

        void quickSortInfo() {
            cout << endl << endl  << "Recommended for: Small, Medium, Large and Extra Large" << endl
                << "Advantages: The Most efficient and fast due to divide and conquer strategy. " << endl
                << "It sorts in place so doesnt use any temporary storage" << endl
                << "Very good with huge array's" << endl << endl
                << "Disadvantages: With its worst case sequence of numbers" << endl
                <<"its inefficiency can be similar to bubble sort" << endl << endl;

        }
};

//This class is dedicated to the reading and writing of files for the program
class fileClass {
    private:
        int tempCount;
    public:
        
        //Reads the file data.txt and returns all of the data as a vector
        vector <int> readList() {

            vector <int> tempList;
            string tempStr;
            tempCount = 0;
            ifstream fileRead;
            fileRead.open("data.txt");

            while (getline(fileRead, tempStr)) {
                tempCount++;
                int tempInt = stoi(tempStr);
                tempList.push_back(tempInt);
            }
            fileRead.close();
            
            return tempList;
        }

        //Takes a newly generated vector and puts each value from the vector on a new line
        void writeList(vector <int> data, int size) {
            ofstream fileWrite;
            fileWrite.open("data.txt");
            for (int i = 0; i < size; i++) {
                fileWrite << data[i] << endl;
            }

            fileWrite.close();
        }
        //Used to set new arrSize from readList
        int getTempCount() {
            return tempCount;
        }

};
//This class consists of all the sorting algorithms used
class sortClass {
    private:
        //This is apart of mergeSort used to compare values and edit accordingly
        vector <int> merge(vector <int> arrayOne, vector <int> arrayTwo)
        {
            vector <int> data;


            while (arrayOne.size() != 0 && arrayTwo.size() != 0)
            {
                if (arrayOne[0] > arrayTwo[0])
                {
                    data.push_back(arrayTwo[0]);
                    arrayTwo.erase(arrayTwo.begin());
                }
                else
                {
                    data.push_back(arrayOne[0]);
                    arrayOne.erase(arrayOne.begin());
                }
            }

            while (arrayTwo.size() != 0)
            {
                data.push_back(arrayTwo[0]);
                arrayTwo.erase(arrayTwo.begin());
            }
            while (arrayOne.size() != 0)
            {
                data.push_back(arrayOne[0]);
                arrayOne.erase(arrayOne.begin());
            }

            return data;
        }
        //This function is used in quickSort
        int quickSortPartition(vector <int>& data, int low, int high)
        {
            int pivot = data[high];
            int leftWall = low - 1;

            for (int i = low; i <= high - 1; i++)
            {
                if (data[i] < pivot)
                {
                    leftWall++;
                    swap(data[leftWall], data[i]);
                }
            }
            swap(data[leftWall + 1], data[high]);


            return (leftWall + 1);

        }
    public:
        //This is the bubblesort algorithm which returns a sorted vector
        vector <int> bubbleSort(vector <int> data, int arrSize)
        {
            bool sorted = true;
            while (sorted)
            {
                sorted = false;
                for (int index = 1; index <= arrSize - 1; index++)
                {
                    if (data[index - 1] > data[index])
                    {
                        swap(data[index - 1], data[index]);
                        sorted = true;
                    }
                }
            }

            return data;
        }


        //The main function for the recursive mergesort algorithm returning a sorted vector
        vector <int> mergeSort(vector <int> data)
        {
            double arrSize = data.size();

            if (arrSize == 1)
            {
                return data;
            }

            vector <int> arrayOne;
            vector <int> arrayTwo;

            //Used for slicing the vectors to only have a certain range of the vector
            //The two below lines were sourced on Stackoverflow. Details in declaration of ownsership.
            arrayOne = vector<int>(data.begin(), data.begin() + arrSize / 2);
            arrayTwo = vector<int>(data.begin() + arrSize / 2, data.end());
            //------------------------------------------------------------------------------

            arrayOne = mergeSort(arrayOne);
            arrayTwo = mergeSort(arrayTwo);


            return merge(arrayOne, arrayTwo);
        }

        

        //Main quickSort function used to sort an unsorted array using the quicksort alogrithm
        void quickSort(vector <int> &data, int low, int high)
        {
            if (low < high)
            {
                int pivotLocation = quickSortPartition(data, low, high);
                quickSort(data, low, pivotLocation - 1);
                quickSort(data, pivotLocation + 1, high);
            }
        }

};


//Containing everything used for the programs Navigational Menu.
int main()
{   
    int option = -1;
    string size;

    //Defines each object of each class so they can be called.
    dataClass D;
    fileClass F;
    sortClass S;

    //Reads the file to set the unsorted list and its size on 
    //startup if user does not want to create new vector
    D.dataList = F.readList();
    D.arrSize = F.getTempCount();
    
    //This section of code is for the MENU used to navigate the program
    while (option != 0)
    {
        cout << "Option : 0 - Exit the program" << endl
            << "Option : 1 - Generate new array" << endl
            << "Option : 2 - Display unsorted array" << endl
            << "Option : 3 - Sort using BubbleSort" << endl
            << "Option : 4 - Sort using MergeSort" << endl
            << "Option : 5 - Sort using QuickSort" << endl
            << "Option : 6 - Display Info on sorting algorithm" << endl << endl;

        cout << "Select an option:" << endl;
        cin >> option;
        switch (option) {
                //exit
            case 0:
                cout << "Exiting program...." << endl;
                break;
                //Generate new list
            case 1:
                cout << "What size would you like the list:" << endl
                    << "1 - Small [100]" << endl
                    << "2 - Medium [1000]" << endl
                    << "3 - Large [10000]" << endl
                    << "4 - XLarge [100000]" << endl;
                cin >> option;
                //User picks the size that they want to try
                switch (option) {
                    case 1:
                        size = "Small";
                        break;
                    case 2:
                        size = "Medium";
                        break;
                    case 3:
                        size = "Large";
                        break;
                    case 4:
                        size = "XL";
                        break;
                    default:
                        cout << endl << "Invalid Input Default Size set to Small."<< endl << "Returning to main menu..." << endl;
                        size = "Small";
                        break;
                }
                D.dataList = {};
                cout << "Generating new array.." << endl;
                D.generateList(size);
                F.writeList(D.dataList,D.arrSize);
                
                cout << "New array generated." << endl;
                break;
                //Outputs the unsorted vector
            case 2:
                cout << "Displaying Unsorted array." << endl;
                D.outputArray(D.dataList);
                break;
                //Outputs the sorted vector using bubbleSort
            case 3:
                D.dataListSorted = {};
                cout << "Sorting using Bubble Sort..." << endl;
                D.dataListSorted = S.bubbleSort(D.dataList, D.arrSize);
                D.outputArray(D.dataListSorted);
                D.bubbleSortInfo();
                break;
                //Outputs the sorted vector using mergeSort
            case 4:
                D.dataListSorted = {};
                cout << "Sorting using Merge Sort..." << endl;
                D.dataListSorted = S.mergeSort(D.dataList);
                D.outputArray(D.dataListSorted);
                D.mergeSortInfo();
                break;
                //Outputs the sorted vector using quickSort
            case 5:
                D.dataListSorted = D.dataList;
                cout << "Sorting using Quick Sort..." << endl;
                S.quickSort(D.dataListSorted,0,D.arrSize-1);//Quicksort done with Pivot being last element
                D.outputArray(D.dataListSorted);
                D.quickSortInfo();
                break;

                //This is used to get the information on each sort
            case 6:

                cout << "What sort would you like more information on?" << endl
                    << "1 - BubbleSort" << endl
                    << "2 - MergeSort" << endl
                    << "3 - QuickSort" << endl << endl;

                cin >> option;
                switch (option) {
                    case 1:
                        D.bubbleSortInfo();
                        break;
                    case 2:
                        D.mergeSortInfo();
                        break;
                    case 3:
                        D.quickSortInfo();
                        break;
                    default:
                        cout << endl << "Invalid Input." << endl << "Returning to main menu..." << endl;
                        break;
                }       


        }
    }   
    
}
