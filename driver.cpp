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
		A[i]=rand()% 100 + 1 ;
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
//***************************************************************************************************************************************************************8
int main()
{
	int N;
	double P;
	cout<<"Ilosc elementow tablicy : "<<endl;
	cin >> N;
	cout<<"Procent posortowanych elementów tablicy: "<<endl;
	cin>>P;
	int *tab = Create_Array<Type>(N);
	int *tab2 = Create_Array<Type>(N);



/*
Przyklad sortowania przez scalanie
*/
	cout<<"MERGE SORT"<<endl;
	Fill_random(tab, N);
	cout<<"Tablica elementow losowych"<<endl;
	Print_Array(tab,N);
	cout<<"Tablica posortowana w : "<<P<<"%"<<endl;
	Percent_Sorted(tab, N, P);
	Print_Array(tab,N);
	Merge_Sort(tab, tab2, 0, N-1);
	cout<<"Tablica posortowana"<<endl;
	Print_Array(tab,N);
	If_Sorted(tab,N);



	/*
Przyklad sortowania szybkiego
*/
	cout<<"QUICK SORT"<<endl;
	Fill_random(tab, N);
	cout<<"Tablica elementow losowych"<<endl;
	Print_Array(tab,N);
	cout<<"Tablica posortowana w : "<<P<<"%"<<endl;
	Percent_Sorted(tab, N, P);
	Print_Array(tab,N);
	Quick_Sort(tab, 0, N-1);
	cout<<"Tablica posortowana"<<endl;
	Print_Array(tab,N);
	If_Sorted(tab,N);
	
	


	/*
Przyklad sortowania introspektywnego
*/
	cout<<"INTRO SORT"<<endl;
	Fill_random(tab, N);
	cout<<"Tablica elementow losowych"<<endl;
	Print_Array(tab,N);
	cout<<"Tablica posortowana w : "<<P<<"%"<<endl;
	Percent_Sorted(tab, N, P);
	Print_Array(tab,N);
	IntroSpective_Sort(tab, N-1);
	cout<<"Tablica posortowana"<<endl;
	Print_Array(tab,N);
	If_Sorted(tab,N);
	



	kill_Array(tab);
	kill_Array(tab2);





	return 0 ;

}