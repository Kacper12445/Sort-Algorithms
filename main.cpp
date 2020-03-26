#include "Sorts.cpp"
using namespace chrono;
#define Type int

template<typename T>
using Sort_P = void (*)(T*,T*, int, int);

template <typename T>
void Merge(T *A, T *B, int L, int M, int R);

template <typename T>
void Merge_Sort(T *A, T *B, int L, int R);

template<typename T>
int Partition (T *A, int L, int R);

template <typename T>
void Quick_Sort(T *A, int L, int R);

template<typename T>
void Insertion_Sort(T *A, int L, int R);

template<typename T>
void Exchange(T A[], int i, int j);

template <typename T>
void Heapify (T *A, int H_Size, int i);

template <typename T>
void Build_Heap(T *A, int H_Size);

template<typename T>
void Hsort(T *A, int H_Size);

template<typename T>
void IntroSort(T *A, int N, int M);

template <typename T>
void IntroSpective_Sort(T *A, int N);

//Funkcja ukladajaca elementy tablicy malejaco
bool Compare(int a, int b);

//Funkcja tworzaca tablice odwrocona
template<typename T>
void Reverse_Sort(T *A, int N);


//Funkcja alokująca pamięć dla tablicy
template<typename T>
T *Create_Array(int N)
{
	return new T[N];
}

//Funkcja zwalniająca pamięc po tablicy poprzez usunięcie jej
template<typename T>
void kill_Array(T *A)
{
	delete[] A;
}

//Funkcja wypisująca tablice uzywana w testach aby sprawdzic czy zadany algorytm dziala poprawnie
template<typename T>
void Print_Array(T *A, int N)
{
	for(int i = 0; i < N;i++)
		cout << A[i]<<" ";
	cout << endl;
}


//Funkcja wypełniająca naszą tablice o rozmiarze N o wartości losowe z przedziału od 1 do 1000000
template<typename T>
void Fill_random(T *A, int N)
{
	for(int i=0; i<N; i++)
		A[i]=rand()% 1000000 + 1 ;
} 

/*
Funkcja sortująca tablice o rozmiarze N o zadany procent
Jesli procent jest rowny 100 to tablica zostaje posortowana malejąco zamiast rosnąco.
Dla procentu rownemu 0 , wszystkie elementy tablicy są losowe
*/
template <typename T>
void Percent_Sorted(T *A, int N, double Percent)
{
	if (Percent == 100)
	{
		Reverse_Sort(A, N);
	 	return;
	}	
	sort(A, A+(int)((N*Percent)/100));
}

// Funkcja sprawdzajaca czy tablica A o rozmiarze N jest posortowana poprawnie
template <typename T>
void If_Sorted(T *A, int N)
{
	for (int i = 0; i < N; i++)
 	{
		if(A[i] > A[i+1]){
	 		cout <<"Array is not sorted correctly"<<endl;
	 		cout<<endl;
		break;
		}
		else
	 	{
	 		cout<<"* Array sorted. Good Job !* "<<endl;
	 		cout<<endl;
	 	break;
	 	}
	}
}

//Funkcja sprawdzajaca czy plik w ktorym beda zapisywane wyniki otworzyl si
void If_open(fstream &plik){
	if(plik.good() == true)
	{
		cout<<"File open"<<endl;
	}
	else 
	{
		cout<<"Error ! Program Closing. "<<endl;
		exit(1);
	}
}


// Funkcja oliczająca najlepszy czas sortowania
duration<double> minTime(duration<double> time[], int size)
{
	duration<double> sumTime = time[0];
	for (int i = 0; i < size - 1; i++)
	{
		if (time[i + 1] < time[i]) sumTime = time[i + 1];
	}
	return sumTime;
}

// Funkcja oliczająca najgorszy czas sortowania
duration<double> maxTime(duration<double> time[], int size)
{
	duration<double> sumTime = time[0];
	for (int i = 0; i < size - 1; i++)
	{
		if (time[i + 1] > time[i]) sumTime = time[i + 1];
	}
	return sumTime;
}

// Funkcja obliczajaca sredni czas sortowania
duration<double> sumTime(duration<double> time[], int size)
{
	duration<double> sumTime = (duration<double>)0;
	for (int i = 0; i < size; i++)
	{
		sumTime += time[i];
	}
	return sumTime;
}


//******************************************************************************************************
int main()
{
	fstream plik;
	plik.open("Sort_time3.txt",ios::out | ios::app); 
	If_open(plik);									
	const int A_number = 100;
	srand(time(NULL));
	auto start = system_clock::now();
	auto end = system_clock::now();
	duration<double> elapsed_seconds[A_number];
	
	double Percent_tab[] = {0 25, 50, 75, 95, 99, 99.7, 100}; 
	int Size_tab[] = {10000, 50000, 100000, 500000, 1000000}; 
	
	string sorts[3] = {"Merge Sort","Quick Sort"," IntroSpective Sort"}; 
	Sort_P <Type> pM = &P_Merge, pQ = &P_Quick, pI = &P_Intro;			
	Sort_P <Type> ptable[3] = {pM, pQ, pI}; 							


	for(int j = 0; j<3; j++)
	{
		cout << sorts[j] << endl;

		for(double percent : Percent_tab)
		{
			for (int N : Size_tab)
			{
				int *tab = Create_Array<Type>(N);
				int *tab2 = Create_Array<Type>(N);

				for (int i = 0; i < A_number; i++)
				{
					
					Fill_random(tab, N);
					Print_Array(tab, N);
					Percent_Sorted(tab, N, percent);
					start = system_clock::now();
			
					ptable[j](tab, tab2, 0, N-1);
					
					end = system_clock::now();
					elapsed_seconds[i] = end - start;
					Print_Array(tab, N);

					If_Sorted(tab, N);

				}
				plik << sorts[j] <<endl;
				plik << "Dla tablicy o wielkości: " << N <<endl;
				
				if (percent == 100)
					plik <<"Dla sortowania w odwrotnej kolejności"<<endl;
				else if(percent == 0)
					plik <<"Sortowanie dla wszystkich elementów losowych"<<endl;
				else
					plik << percent<<"% posortowanych początkowych elementów tablicy"<<endl;
				plik << endl;
				plik << " Calkowity czas sortowania: " <<sumTime(elapsed_seconds, A_number).count() *1000 <<" ms"<<endl;
				plik << " Sredni czas sortowania: " <<(minTime(elapsed_seconds, A_number).count() + maxTime(elapsed_seconds, A_number).count())/2*1000 <<" ms"<<endl;
				plik << " Najszybszy czas sortowania: " <<minTime(elapsed_seconds, A_number).count() *1000 <<" ms"<<endl;
				plik << " Najwolniejszy czas sortowania: " <<maxTime(elapsed_seconds, A_number).count() *1000 <<" ms"<<endl;	
				plik << endl;
				kill_Array(tab);
				kill_Array(tab2);		

				cout << N <<" Arrays sorted"<<endl;
			}
			cout<<"While ";
			cout << percent << "% sorted !" << endl;
			cout << endl;
			cout<<"*********************************";
			cout<<endl;
		}
	}
	cout << " THE END";
	cout<<endl;
	plik.close();
	
	return 0 ;

}