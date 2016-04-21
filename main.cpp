#include <iostream>
#include <fstream>



using namespace std;
int quickSortComp = 0; int quickSortSwap = 0; int mergeSortComp = 0; int mergeSortSwap = 0;  //These are used to count the comparisons and swaps for
//quick sort and merge sort since they have a recursive function in them, I didn't know how to add a counter into the functions

int * MakeArray (int Array[], string FileName)  //Makes an array using the 4 different files
{
    int fileContents, j;
    j = 0;
    ifstream inFile;

    inFile.open(FileName);
    while (!inFile.eof())                       //Takes the ints in the file and puts them into an array (should be an array with 10000 ints)
    {
        inFile >> fileContents;

        Array[j] = fileContents;
        //cout << Array[j] << endl;
        j++;                                    //Next element in the array = next integer in the file being read

    }
    return Array;
    inFile.close();             //close the file
}
void BubbleSort (int Array[], int n)        //Bubble Sorts Arrays and keeps track of number of comparisons and swaps
{
    int i, j, temp, swaps, comps;
    swaps = comps = 0;
    for (i = 0; i < n; i++)   //Number of passes
    {
        for(j = 0; j < n-1; j++)
        {
            comps++;                //comparison occurs
            if (Array[j] > Array[j+1])  //Ascending order bubble sort
            {
                temp = Array[j];
                Array[j] = Array[j+1];  //swap ocurs
                Array[j+1] = temp;
                swaps++;                //Increment swap
            }
        }
    }
    cout << "     Comparisons: " << comps << endl;   //Function will write to console the number of comparisons and swaps
    cout << "     Swaps: " << swaps << endl;
}

void InsertionSort(int Array[], int n)          //Insertion sorts array and keeps track of number of comparisons and swaps
{
   int i, j, index, comps, swaps;
   comps = swaps = 0;

   for (i=1; i < n; i++)
   {
      index = Array[i];
      for (j=i-1;j >= 0 && Array[j] > index;j--)    //Move the elements of Array, that are greater than index to one position ahead of their ur
      {
         Array[j + 1] = Array[j];               //A comparison and swap are made, increment both
         comps++;
         swaps++;
      }
      Array[j+1] = index;
      comps++;                                  //Another comparison, increment comparison
   }
    cout << "     Comparisons: " << comps << endl;     //Function will write to console the number of comparisons and swaps
    cout << "     Swaps: " << swaps << endl;
}

void ShellSort (int Array[], int n)            //Shell sorts array and keeps track of number of comparisons and swaps
{
    int j, comps, swaps;
    comps = swaps = 0;
  //Narrow the array by 2 everytime
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        //Gapped insertion sort for the gap size
        //Keep adding an element until the entire array is gap sorted
        comps++;                            //increment comp for gap > 0 comparison
        for (int i = gap; i < n; ++i)
        {
            //add a[i] to the array
            //make temp and make room in the array for temp
            comps++;                        //increment comp for i < n comparison
            int temp = Array[i];
            for (j = i; j >= gap && temp < Array[j - gap]; j -= gap)
            {
                //put temp into correct location
                comps++;                    //increment comp for j>=gap comparison
                swaps++;                    //swap occurs, increment swap
                Array[j] = Array[j - gap];
            }
            Array[j] = temp;
        }
    }
    cout << "     Comparisons: " << comps << endl;      //Function will write to console the number of comparisons and swaps
    cout << "     Swaps: " << swaps << endl;
}

/**QuickSort Functions**/
void quicksort(int arr[], int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++; quickSortComp++; //Comparison occrus, increment comparison
            while (arr[j] > pivot)
                  j--; quickSortComp++; //Comparison occrus, increment comparison
            if (i <= j) {
                quickSortComp++; //Comparison occrus, increment comparison
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
                j--; //increment swap
                quickSortSwap++;
            }
      };

      /* recursion */
      if (left < j)
            quicksort(arr, left, j);
      if (i < right)
            quicksort(arr, i, right);
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void Merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    // create temp arrays
    int L[n1], R[n2];

    //Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])           //comparison occurs, increment comp
        {
            //mergeSortComp++;        //swap occurs, increment swap
            arr[k] = L[i];
            i++;
            mergeSortSwap++;
        }
        else
        {
            mergeSortComp++;      //comparison occurs, increment comp
            arr[k] = R[j];
            j++;
            mergeSortSwap++;     //swap occurs, increment swap
        }
        mergeSortComp++;        //i<n1 comparison
        //mergeSortComp++;        //j<n2 comparison
        k++;
    }

    // Copy the remaining elements of L[], if there
      // are any
    while (i < n1)
    {                       //Should a comparison go here?

        arr[k] = L[i];
        i++;
        k++;
    }

     //Copy the remaining elements of R[], if there
       //are any
    while (j < n2)
    {                   //Should a comparison go here?
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves recursively
        mergeSort(arr, l, m);       //Sort the left subarray
        mergeSort(arr, m+1, r);     //Sort the right subarray

        Merge(arr, l, m, r);        //Merge both arrays into sorted
    }
}

int main()
{
    int a[10000], b[10000], c[10000], d[10000];                     //Make four arrays of size 10000 for the four files to be put into

    MakeArray (a, "/Users/Perseus/Documents/C++/HW_5/Reversed.txt");        //use MakeArray function to make the four files
    MakeArray (b, "/Users/Perseus/Documents/C++/HW_5/FewUnique.txt");       //I didn't make the arrays with pointers so this is really bad memory usage
    MakeArray (c, "/Users/Perseus/Documents/C++/HW_5/Random.txt");
    MakeArray (d, "/Users/Perseus/Documents/C++/HW_5/NearlySorted.txt");

    ///Insertion Sort///
    cout << "/////INSERTION SORT/////" << endl;       //Takes each file and sorts them via insertion, tells the number of comparisons and swaps for each file
    cout << "Reversed: \n"; InsertionSort(a, 10000);
    cout << "\nFew unique: \n"; InsertionSort(b, 10000);
    cout << "\nRandom: \n"; InsertionSort(c, 10000);
    cout << "\nNearlySorted: \n"; InsertionSort(d, 10000);

    //Reset the Arrays back to the original files

    MakeArray (a, "/Users/Perseus/Documents/C++/HW_5/Reversed.txt");
    MakeArray (b, "/Users/Perseus/Documents/C++/HW_5/FewUnique.txt");
    MakeArray (c, "/Users/Perseus/Documents/C++/HW_5/Random.txt");
    MakeArray (d, "/Users/Perseus/Documents/C++/HW_5/NearlySorted.txt");

    ///Bubble Sort///
    cout << "\n/////BUBBLE SORT/////" << endl;          //Takes each file and sorts them via bubble sort, tells the number of comparisons and swaps for each file
    cout << "Reversed: \n"; BubbleSort(a, 10000);
    cout << "\nFew unique: \n"; BubbleSort(b, 10000);
    cout << "\nRandom: \n"; BubbleSort(c, 10000);
    cout << "\nNearly sorted: \n"; BubbleSort(d, 10000);

    //Reset the Array

    MakeArray (a, "/Users/Perseus/Documents/C++/HW_5/Reversed.txt");
    MakeArray (b, "/Users/Perseus/Documents/C++/HW_5/FewUnique.txt");
    MakeArray (c, "/Users/Perseus/Documents/C++/HW_5/Random.txt");
    MakeArray (d, "/Users/Perseus/Documents/C++/HW_5/NearlySorted.txt");

    ///Shell Sort ///
    cout << "/////SHELL SORT/////" << endl;            //Takes each file and sorts them via shell sort, tells the number of comparisons and swaps for each file
    cout << "Reversed: \n"; ShellSort(a, 10000);
    cout << "\nFew unique: \n"; ShellSort(b, 10000);
    cout << "\nRandom: \n"; ShellSort(c, 10000);
    cout << "\nNearly sorted: \n"; ShellSort(d, 10000);

    //Reset the Arrays
    MakeArray (a, "/Users/Perseus/Documents/C++/HW_5/Reversed.txt");
    MakeArray (b, "/Users/Perseus/Documents/C++/HW_5/FewUnique.txt");
    MakeArray (c, "/Users/Perseus/Documents/C++/HW_5/Random.txt");
    MakeArray (d, "/Users/Perseus/Documents/C++/HW_5/NearlySorted.txt");

    ///Merge Sort///            //Takes each file and sorts them via merge sort, tells the number of comparisons and swaps for each file
    //mergeSortComp and mergeSortSwap are reset to 0 for the other arrays to be counted
    cout << "\n/////MERGE SORT/////" << endl;
    cout << "Reversed: \n"; mergeSort(a, 0, 10000); cout << "     Comparisons: " << mergeSortComp << endl; cout << "     Swaps: " << mergeSortSwap << endl;
    mergeSortComp = 0; mergeSortSwap = 0;
    cout << "\nFew unique: \n"; mergeSort(b, 0, 10000); cout << "     Comparisons: " << mergeSortComp << endl; cout << "     Swaps: " << mergeSortSwap << endl;
    mergeSortComp = 0; mergeSortSwap = 0;
    cout << "\nRandom: \n"; mergeSort(c, 0, 10000); cout << "     Comparisons: " << mergeSortComp << endl; cout << "     Swaps: " << mergeSortSwap << endl;
    mergeSortComp = 0; mergeSortSwap = 0;
    cout << "\nNearly sorted: \n"; mergeSort(d, 0, 10000); cout << "     Comparisons: " << mergeSortComp << endl; cout << "     Swaps: " << mergeSortSwap << endl;
    mergeSortComp = 0; mergeSortSwap = 0;

    //Reset the Arrays

    MakeArray (a, "/Users/Perseus/Documents/C++/HW_5/Reversed.txt");
    MakeArray (b, "/Users/Perseus/Documents/C++/HW_5/FewUnique.txt");
    MakeArray (c, "/Users/Perseus/Documents/C++/HW_5/Random.txt");
    MakeArray (d, "/Users/Perseus/Documents/C++/HW_5/NearlySorted.txt");

    ///Quick Sort ///           //Takes each file and sorts them via quick sort, tells the number of comparisons and swaps for each file

    //quickSortComp and quickSortSwap are reset to 0 for the other arrays to be counted, since I made them out of the function
    //How would I add the counters to the recursive functions?

    cout << "\n/////QUICK SORT/////" << endl;
    cout << "Reversed: \n"; quicksort(a, 0, 10000); cout << "     Comparisons: " << quickSortComp << endl; cout << "     Swaps: " << quickSortSwap << endl;
    quickSortComp = 0; quickSortSwap = 0;
    cout << "\nFew unique: \n"; quicksort(b, 0, 10000); cout << "     Comparisons: " << quickSortComp << endl; cout << "     Swaps: " << quickSortSwap << endl;
    quickSortComp = 0; quickSortSwap = 0;
    cout << "\nRandom: \n"; quicksort(c, 0, 10000); cout << "     Comparisons: " << quickSortComp << endl; cout << "     Swaps: " << quickSortSwap << endl;
    quickSortComp = 0; quickSortSwap = 0;
    cout << "\nNearly sorted: \n"; quicksort(d, 0, 10000); cout << "     Comparisons: " << quickSortComp << endl; cout << "     Swaps: " << quickSortSwap << endl;
    quickSortComp = 0; quickSortSwap = 0;

//I just printed out the first 50 ints from each array because 10000 is WAAAAAY too much
/**For some reason the sorting doesn't sort all the way, it worked before I commented the code
After I commented the code, the sorting got messed up for merge sort and quick sort**/

    cout << "Reversed Array: " << endl;
    for (int i = 0; i < 50; i++)
    {
        cout << a[i] << endl;
    }
    cout << "\n\nFew Unique Array: " << endl;
    for (int i = 0; i < 50; i++)
    {
        cout << b[i] << endl;
    }
    cout << "\n\nRandom: " << endl;
    for (int i = 0; i < 50; i++)
    {
        cout << c[i] << endl;
    }
    cout << "\n\nNearly Sorted: " << endl;
    for (int i = 0; i < 50; i++)
    {
        cout << d[i] << endl;
    }
}


