#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std; 
mutex m; 
/*
implementar un algoritmo de ordenamiento de la siguiente manera: 

el tamaño del array se divide en el tamaño de la cantidad de nucleos, por ejemplo:
- si su computadora tine 4 nucleos el array tendra 4 sub-arrays procesdose en paralelo 
- si su computadora tine 8 nucleos el array tendra 8 sub-arrays procesdose en paralelo 

supongamos que el computador tiene 4 nucleos:
arraya_desordenado[n] = {n1, n2, n3, ....} // el array puede ser de cualquier tamaño 

se pasara el array de tamaño n y se dividira en 4 sub arrays, y cada uno se ordenara de forma paralela 
con el algoritmo quicksort: 

{array 1}  // se ordena con quicksort de forma paralela 
{array 2}  // se ordena con quicksort de forma paralela 
{array 3}  // se ordena con quicksort de forma paralela 
{array 4}  // se ordena con quicksort de forma paralela 

luego se juntara el array 1 con el array 2 y el array 3 con el 4. para luego ordenarlos utilizando 
el mergue sort de forma paralela 
{arra 1 y 2 concatenados} // se ordena con merge sort de forma paralela 
{arra 3 y 4 concatenados} // se ordena con merge sort de forma paralela 

luego se concatena los dos sub-arrays. para luego ordenarlos utilizando el mergue sort de forma 
secuencial 

{array concatenado} //ordenarlo de forma secuencial utilizando el merge sort 

nota el numero de elementos de cada sub-array depende de la cantidad de elementos del array 
es decir, si el tamaño es 12 entonces en cada sub array habra 3 elemntos, pero si el numero de 
elementos no es multiplo al numero de nucleos entonces se sugiere usar esta formula 
numero de elementos de cada sub array = (tamaño del array)-((tamañño del array/numero de nucleos)*(numero de nucleos -1))

el codigo para determinar el numero de nucleos es: int nucleos = thread::hardware_concurrency(); 
*/

/*
input: {6,9,2,8,1,3,6,4,7,5,24,20};

output: 
su computadorea tiene: 4 nucleos  (depende de que computador use)
se divide en 4 sub-arrays
{6,9,2} {8,1,3} {6,4,7} {5,24,20}

se ordena usando quicksort de forma paralela 
{2,6,9} {1,3,8} {4,6,7} {5,20,24}

se concatena
{2,6,9,1,3,8} {4,6,7,5,20,24}

se ordena usando merge sort de forma paralela 
{1,2,3,6,8,9} {4,5,6,7,20,24}

se concatena 
{1,2,3,6,8,9,4,5,6,6,7,20,24}

se ordena usando merge sort de forma secuencial 
{1,2,3,4,5,6,7,8,9,20,24}

*/

	
	/*
	Member functions
	(constructor) ->  Construct thread (public member function )
	(destructor)  ->  Thread destructor (public member function )
	operator=	  ->  Move-assign thread (public member function )
	get_id	      ->  Get thread id (public member function )
	joinable      ->  Check if joinable (public member function )
	join          ->  Join thread (public member function )
	detach        ->  Detach thread (public member function )
	swap          ->  Swap threads (public member function )
	native_handle ->  Get native handle (public member function )
	hardware_concurrency -> [static] Detect hardware concurrency (public static member function )
	*/  

/////////////////////////MERGE SORT ALGORITHM /////////////////////////////////
// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
  
    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
  
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
  
    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array
  
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}
// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively
  
    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}
// UTILITY FUNCTIONS
// Function to print an array
void printArray(int A[], int size)
{
    for (auto i = 0; i < size; i++)
    	//if(A[i] != 0)
        	cout << A[i] << "-";

   	cout << "\n\n";
}
/////////////////////////////////////////////////////////////////////////////////

///////////////////////////// QUICKSORT ALGORITHM ////////////////////////////////

// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
/* This function takes last element as pivot, places 
the pivot element at its correct position in sorted 
array, and places all smaller (smaller than pivot) 
to left of pivot and all greater elements to right 
of pivot */
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++; // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
/* Function to print an array */
void printArray2(int arr[], int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) 
        cout << arr[i] << " "; 
    cout << endl; 
} 
/////////////////////////////////////////////////////////////////////////////////

///////////////////////////// THREAD ALGORITHM ////////////////////////////////

//code here 
void F1(int* ar, int n)
{	
	//m.lock();	
	//printArray(ar, n); cout << "\n"; //muestra sub-arrays originales 

    //for ( int i = 0; i < n; i++ ) //muestra sub arrays ordenados con quicksort 
        quickSort(ar, 0, n - 1);  

    //printArray(ar, n);   
    /*for ( int i = 0; i < n; i++ )        
        cout << ar[i] << "-";
    cout << "\n\n"; */

    //m.unlock();
}

void F2(int* ar, int n)
{	
	//m.lock();	
	//printArray(ar, n); cout << "\n"; //muestra sub-arrays originales 

    //for ( int i = 0; i < n; i++ ) //muestra sub arrays ordenados con quicksort 
        mergeSort(ar, 0, n - 1);  

    //printArray(ar, n);   
    /*for ( int i = 0; i < n; i++ )        
        cout << ar[i] << "-";
    cout << "\n\n"; */

    //m.unlock();
}


int main(){
	
    int arr[] = {6,9,2,8,1,3,6,4,7,5,24,20};   
    int nucleos = thread::hardware_concurrency();
    auto arr_size = sizeof(arr) / sizeof(arr[0]);
    //cout << nucleos << endl; //numero de nucleos  
    //cout << arr_size; //tamaño del array 
    cout << "array original \n";
    printArray(arr, arr_size); 

    //int asignar_size = (arr_size)-((arr_size/nucleos)*(nucleos-1));
    int asignar_size =arr_size/nucleos ;
    vector<thread> ths(nucleos);
    for ( int i = 0; i < nucleos; i++ )
        ths[i] = thread(quickSort,&arr[i*asignar_size], 0, asignar_size - 1);
        //ths[i] = thread(F1, &arr[i*asignar_size], asignar_size);

    for ( int i = 0; i < nucleos; i++ )
        ths[i].join();

    cout << "primera pasada con quickSort paralelo \n";
    printArray(arr, arr_size); 

    vector<thread> ths2(nucleos/2);
    for ( int i = 0; i < nucleos/2; i++ )
        ths2[i] = thread(mergeSort,&arr[i*asignar_size*2], 0, asignar_size-1);
        //ths2[i] = thread(F2, &arr[i*asignar_size*2], asignar_size*2);

    for ( int i = 0; i < nucleos/2; i++ )
        ths2[i].join();

    cout << "segunda pasada con merge sort paralelo\n";
    printArray(arr, arr_size); 

    mergeSort(arr, 0, arr_size - 1);
    cout << "tercera pasada con merge sort secuencial \n";
	printArray(arr, arr_size);     
}

 