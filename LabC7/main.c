#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



// функция принимает массив и количество его элементов,
// позволяет заполнить его случайными числами из заданного диапазона
void randomize_arr (int* arr, const int len){
	float mn, mx;
	printf("Введите минимум и максимум для случайных чисел: ");
	scanf("%f %f", &mn, &mx);									// ввод границ диапазона случайных чисел
	printf("\n");
	
	if (mn > mx){												// при необходимости поменять границы местами
		float t = mn;
		mn = mx;
		mx = t;
	};
	srand(time(0)); 											// инициализация псевдослучайной последовательности
	int i;
	for(i = 0;i<len; i++){										// цикл по всем элементам
		arr[i] = (int) ((float)rand() / RAND_MAX * (mx - mn) + mn);		// случайный элемент в заданном диапазоне
	};
}

// функция принимает массив и количество его элементов, выводит его на экран
void print_arr(const int* const arr, const int len){
	if (len == 0)
		printf("Массив пуст. \n");
	int i;
	for(i = 0;i<len; i++){												// цикл по всем элементам
		printf("Элемент массива номер %4d равен %5d. ", i+1, arr[i]);	// вывод элемента
		printf("\n");		// новая строка
	};
}

// функция принимает массив и количество его элементов, сортирует его на месте (в порядке возрастания)
void sort_arr(int* arr, const int len){
	int i = 0;
	int j;
	for (; i < len; i++){  	// сортировка простым выбором
		// поиск индекса минимального элемента неотсортированной части
		int min_ind = i;	
		for (j = i+1; j < len; j++){
			min_ind = arr[min_ind] > arr[j] ? j : min_ind;
		};
		
		// найденный индекс ставим в начало неотсортированной части
		int temp = arr[i];
		arr[i] = arr[min_ind];
		arr[min_ind] = temp;
	};
}

// функция создает и выводит массив В из массива А по условию задачи
void make_arr_B(const int* const arr_A, const int A_len){
	int len_B = 0;						// количество подходящих чисел
	int i;
	for(i = 0;i<A_len; i++){
		int current = arr_A[i];			// цикл по всем элементам
		if ((current%3 == 0) || (current%5 == 0)){
			len_B++;					// подсчет количества подходящих чисел
		};
	};
	
	// выделение памяти под массив В
	int* arr_B = (int*) malloc(sizeof(int) * len_B);
	if (!arr_B) exit(1);				// проверка на то, что память была выделена
	int k = 0;
	for(i = 0;i<A_len; i++){
		int current = arr_A[i];			// цикл по всем элементам массива А
		if ((current%3 == 0) || (current%5 == 0)){
			arr_B[k++] = current; 		// заполнение массива В нужными числами
		};

	};

	printf("\nПолученный отсортированный массив B: \n");
	sort_arr(arr_B, len_B); 	// сортировка массива В
	print_arr(arr_B, len_B);	// вывод массива В
	free(arr_B);				// освободить памать, занимаемую массивом В
	arr_B = NULL;
}


int main(int argc, char *argv[]) {
	system("color F0");  // белый цвет консоли
	system("chcp 1251"); // кодовая страница русского языка
	
	// объявление переменных
	int A_len = 11111;
	int max_len = 10000;
	int* A = NULL;

	
	while (A_len <= 1 || A_len >= max_len){
		// ввод количества точек
		printf("Введите количество чисел в массиве А: ");
		scanf("%d", &A_len);
		printf("\n");
	};
	
	A = (int*) malloc(sizeof(int) * A_len); 	// выделение памяти под массив А
	if (!A) exit(1);							// проверка на то, что память была выделена
	randomize_arr(A, A_len);					// заполнение массива А случайными числами
	
	
	printf("\nИсходныи массив А: \n"); 			// вывод массива А
	print_arr(A, A_len);

	make_arr_B(A, A_len); 						// все дальнейшие действия, связанные с массивом В
	
	free(A); 									// освободить памать, занимаемую массивом А
	A = NULL;
	system("pause");							// не закрывать окно
	return 0;
}
