#include <iostream>
#include <cmath>
#include <ctime>
#include <ratio>
#include <chrono>
#include <algorithm>
#include <fstream>
using namespace std;

/*
 ************************************************
 *                MERGE SORT                    *
 ************************************************
 */

template <typename T>
void Merge(T *A, T *B, int L, int M, int R)
{
	int i = L;
	int j = M + 1;
	int k = L;

	while (i <= M && j <= R)
	{
		if (A[i] < A[j])
		{
			B[k] = A[i];
			i++;
		}
		else
		{
			B[k] = A[j];
			j++;
		}
		k++;
	}

	while (i <= M)
	{
		B[k] = A[i];
		i++;
		k++;
	}

	while (j <= R)
	{
		B[k] = A[j];
		j++;
		k++;
	}

	for(int i = L; i <= R; i++)
	{
		A[i] = B[i];		
	}
	
}


template <typename T>
void Merge_Sort(T *A, T *B, int L, int R)
{
	if (L < R)
	{
		int M = (L + R) / 2;
		Merge_Sort(A, B, L, M);
		Merge_Sort(A, B, M+1, R);
		Merge(A, B, L, M, R);
	}
}

/*
 ************************************************
 *                QUICK SORT                    *
 ************************************************
 */

template<typename T>
int Partition (T *A, int L, int R)
{
	int i = L;
	int j = R;
	int Pivot = A[(L + R)/2];	
	
	while(true)
	{
		while (A[j] > Pivot) 
			j--;
		while(A[i] < Pivot)
			i++;
		if (i<j)
			swap(A[i++],A[j--]);
		else
			return j;
	}
}

template <typename T>
void Quick_Sort(T *A, int L, int R)
{
	int Pivot = A[(L + R)/2];
	int i = L;
	int j = R;

	do 
	{
		while(A[i] < Pivot)
			i++;

		while(A[j] > Pivot)
			j--;
		
		if (i <= j)
		{
			swap(A[i++], A[j--]);
		}

	} while (i <= j);
	if (L < j)	Quick_Sort(A,L,j);
	if (R > i)	Quick_Sort(A,i,R);	
}
	

/*
 ************************************************
 *                INSERTION SORT                *
 ************************************************
 */



template<typename T>
void Insertion_Sort(T *A, int L, int R)
{
	for (int i = L + 1; i <= R; i++)
	{
		int k = A[i];
		int j = i;
		while(j > L && A[j-1] > k)
		{
			A[j] = A[j-1];
			j--; 
		}
		A[j] = k;
	}
}

/*
 ************************************************
 *                HEAP SORT                     *
 ************************************************
 */

template<typename T>
void Exchange(T A[], int i, int j)
{
	T tmp;
	tmp = A[i];
	A[i]=A[j];
	A[j]=tmp;
}

template <typename T>
void Heapify (T *A, int H_Size, int i)
{
	int Max_S; 
	int l = 2*i; 
	int r = (2*i)+1;

	if (l <= H_Size && A[l]>=A[i])
		Max_S = l;
	else 
		Max_S = i;
	if (r <= H_Size && A[r] >= A[Max_S])
		Max_S = r;
	if (Max_S != i)
	{
		Exchange(A, Max_S, i);
		Heapify(A,H_Size ,Max_S);
	}
}

template <typename T>
void Build_Heap(T *A, int H_Size)
{
	for (int i = H_Size/2; i >= 0; i--)
		Heapify(A, H_Size, i);
}
 

template<typename T>
void Hsort(T *A, int H_Size)
{
	Build_Heap(A, H_Size);
	for (int i = H_Size; i > 0 ; i--)
	{
		Exchange(A, i, 0);
		H_Size--;
		Heapify(A, H_Size ,0);
	}
}


/*
 ************************************************
 *              INTROSPECTIVE SORT              *
 ************************************************
 */


template<typename T>
void IntroSort(T *A, int N, int Max_Depth)
{
	if(Max_Depth <= 0)
		{
		Hsort(A, N);
		return;
		}
	int x = Partition(A, 0, N);
	if (x >= 16)
		IntroSort(A, x, Max_Depth-1);
	if(N-1-x >= 16)
		IntroSort(A+x+1, N-1-x, Max_Depth-1);
}

template<typename T>
void IntroSpective_Sort(T *A, int N)
{
	int Max_Depth = floor(2*log(N));
	IntroSort(A, N, Max_Depth);
	Insertion_Sort(A, 0 , N);
}


template<typename T>
void P_Intro(T *A, T *B, int L, int N)
{
	IntroSpective_Sort(A, N);
}

template<typename T>
void P_Quick(T *A, T *B, int L, int R)
{
	Quick_Sort(A, L, R);
}

template<typename T>
void P_Merge(T *A, T *B, int L, int R)
{
	Merge_Sort(A, B, L, R);
}

bool Compare(int a, int b)
{
	return a > b;
}

template<typename T>
void Reverse_Sort(T *A, int N)
{
	sort(A, A+N, Compare);
}




