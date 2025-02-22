#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <mem.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// функция принимает массив,
// позволяет заполнить его случайными числами из заданного диапазона
void randomize_arr (int* arr, float mn, float mx){
	int len = arr[0];   	// длина поданного массива
	int i;
	for(i = 1; i<=len; i++){										// цикл по всем элементам
		arr[i] = (int) ((float)rand() / RAND_MAX * (mx - mn) + mn);	// случайный элемент в заданном диапазоне
	};
};

// функция принимает массив и изменяет его так,
// чтобы он состоял только из элеметов, стоявших на нечетных индексах
int* delete_even_indexes(int* arr){
	int len = arr[0]; 			// длина поданного массива
	int i, j;
	int new_size = len;			// граница, до которой включительно будут рассматриваться элементы при сдвиге
		
	for (i = len; i >= 1; i--){  				// цикл по всем индексам
		if (i % 2 == 0){						// на каждом четном индексе
			for (j = i; j < new_size; j++){		// сдвинуть все элементы на один влево
				arr[j] = arr[j+1];
			};
			new_size--;							// не рассматривать далее лишние элементы
			arr[0]--;							// уменьшить нулевой индекс, который означает размер массива
		};
		
//		// отладочная печать массива на каждой итерации
//		int k = 1;
//		for (k =1;k<=len;k++){
//			printf(" %d ", arr[k]);
//		};
//		printf("\n");
		
    }
    arr = (int*) realloc(arr, (arr[0])*sizeof(int));	// реаллокация массива - уменьшение занимаемой памяти
	if (!arr) exit(1);									// проверка на то, что память была выделена
	return arr;
};

// функция принимает массив, находит максимум и
// добавляет столько нулей в начало
int* add_zeros(int* arr){
	int len = arr[0], mx = arr[1]; 						// длина поданного массива
	int i, j = 1;
	for(i = 1; i<=len; i++){							// цикл по всем элементам
		mx = mx > arr[i] ? mx : arr[i];					// поиск максимума
	};
	mx = abs(mx); 										// модуль максимума
	arr = (int*) realloc(arr, (len+mx)*sizeof(int));	// реаллокация памяти
	if (!arr) exit(1);						    		// проверка на то, что память была выделена
	arr[0] = len+mx; 			 						// длина нового массива
	
	for(i = len; i >= 1; i--){							// передвинуть все элементы на mx индексов вправо
		arr[i+mx] = arr[i];
	};
	
	memset(arr+1, 0, (size_t)(mx * sizeof(int))); 		// занулить первые mx элементов
	 
	return arr;
};

// функция принимает массив, и переставляет все нули в начало 
int* relocate_zeros(int* arr){
	int len = arr[0];  						// длина поданного массива
	int zero_count = 0, i = 1;  			// счетчик нулей
	for(i = 1; i<=len; i++){				// цикл по всем элементам
		zero_count += arr[i] == 0 ? 1 : 0;	// подсчет нулей
	};
	int j = len;	
	for (i = len; i >= 1; i--){				// передвинуть все ненулевые элементы в конец
		if (arr[i] != 0){
			arr[j--] = arr[i];
		}
	}
	memset(arr+1, 0, (size_t)(zero_count * sizeof(int))); // занулить столько первых элементов, сколько было найдено нулей в исходном массиве
	return arr;
};

// функция принимает массив и заменяет все элементы, равные Х, на
// среднее арифметическое всех элементов массива
int* replace_with_average(int* arr, const int x){
	int len = arr[0];	// длина поданного массива
	int avg = 0;		// среднее арифметическое
	int i;
	for(i = 1; i<=len; i++){	// цикл по всем элементам
		avg += arr[i];			// подсчет суммы
	};
	avg /= len;  				// подсчет среднего арифметического
	for(i = 1; i<=len; i++){	// цикл по всем элементам
		if (arr[i] == x)		// замена требуемых элементов
			arr[i] = avg;		// на среднее арифметическое
	};
	return arr;
};


int main(int argc, char *argv[]) {
	
	system("color F0");  // белый цвет консоли
	system("chcp 1251"); // кодовая страница русского языка
	srand(time(0)); 	 // инициализация псевдослучайной последовательности
	
	// объявление переменных
	int A_len = 11111;
	int B_len = 11111;
	int max_len = 10000;
	int i, j;
	int** A = NULL;

	// ввод размеров массива
	while (A_len < 1 || A_len >= max_len || B_len < 1 || B_len >= max_len){
		printf("Введите размеры массива: \n");
		printf("\tВведите количество строк А: ");
		scanf("%d", &A_len);
		printf("\tВведите количество столбцов B: ");
		scanf("%d", &B_len);
		printf("\n");
	};
	
	// ввод границ диапазона случайных чисел
	float mn, mx;
	printf("Введите минимум и максимум для случайных чисел: ");
	scanf("%f %f", &mn, &mx);							
	printf("\n");
	
	// при необходимости поменять границы местами
	if (mn > mx){										
		float t = mn;
		mn = mx;
		mx = t;
	};
	
    A = (int**) malloc(A_len * sizeof(int*));		// выделение памяти под двумерный массив А
	if (!A) exit(1);								// проверка на то, что память была выделена
	
 	//для каждого элемента-указателя создаётся свой массив
    for (i = 0; i < A_len; ++i){
        A[i] = (int*) calloc(B_len+1, sizeof(int)); // выделение памяти для подмассива
		if (!A[i]) exit(1);							// проверка на то, что память была выделена
		A[i][0] = B_len;							// начальная длина
 		randomize_arr(A[i], mn, mx);				// заполнение массива случайными числами
	};
	
	printf("Исходный массив: \n");
	
	// вывод двумерного массива
	for (i = 0; i < A_len; ++i) 
    {
    	int line_len = A[i][0];
        for (j = 1; j <= line_len; ++j) 
            printf("%6d ", A[i][j]);
        printf("\n");
    };
    
    printf("\n\n");
    
    // построчное применение операций над подмассивами
    for (i = 0; i < A_len; ++i) 
    {
    	if (i % 4 == 0)
    		A[i] = delete_even_indexes(A[i]);
    	if (i % 4 == 1)
        	A[i] = add_zeros(A[i]);
        if (i % 4 == 2)
        	A[i] = relocate_zeros(A[i]);
        if (i % 4 == 3){
	        int x;
			printf("Введите число, которое нужно заменить на среднее в строке номер %d: ", i+1);
			scanf("%d", &x);
        	A[i] = replace_with_average(A[i], x);
		};
    };
    
    
    printf("Полученный массив: \n");
    
    // вывод двумерного массива
	for (i = 0; i < A_len; ++i) 
    {
    	int line_len = A[i][0];
        for (j = 1; j <= line_len; ++j) 
            printf("%6d ", A[i][j]);
        printf("\n");
    };
    
    // очищаем подмассивы
    for (i = 0; i < A_len; ++i)  
		free(A[i]);
    
    // очищаем основной массив
	free(A); 
	A = NULL;
	
	return 0;
}
