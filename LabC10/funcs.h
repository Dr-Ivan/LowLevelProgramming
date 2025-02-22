#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mem.h>


#define LEN(array) array[0] 
#define ELEM(array, i) array[i+1]
#define ELEM_TYPE int


// функция принимает массив,
// позволяет заполнить его случайными числами из заданного диапазона
void randomize_arr (ELEM_TYPE* arr, float mn, float mx){
	ELEM_TYPE len = LEN(arr);   											// длина поданного массива
	int i;
	for(i = 0; i<len; i++){													// цикл по всем элементам
		ELEM(arr, i) = (ELEM_TYPE) ((float)rand() / RAND_MAX * (mx - mn) + mn);	// случайный элемент в заданном диапазоне
	};
};

// функция принимает массив и изменяет его так,
// чтобы он состоял только из элеметов, стоявших на нечетных или четных индексах в зависимости от define-а DELETE_ODD_INDEXES
ELEM_TYPE* delete_indexes(ELEM_TYPE* arr){
	ELEM_TYPE len = LEN(arr); 							// длина поданного массива
	int i, j;
	ELEM_TYPE new_size = len;							// граница, до которой включительно будут рассматриваться элементы при сдвиге
		
	for (i = len; i >= 1; i--){  						// цикл по всем индексам
	#ifdef DELETE_ODD_INDEXES
		if (i % 2 != 0)
		{												// на каждом нечетном индексе
			for (j = i; j < new_size; j++){				// сдвинуть все элементы на один влево
				ELEM(arr, j-1) = ELEM(arr, j);
			};
			new_size--;									// не рассматривать далее лишние элементы
			LEN(arr)--;									// уменьшить нулевой индекс, который означает размер массива
		};	
	#else
		if (i % 2 == 0)
		{												// на каждом четном индексе
			for (j = i; j < new_size; j++){				// сдвинуть все элементы на один влево
				ELEM(arr, j-1) = ELEM(arr, j);
			};
			new_size--;									// не рассматривать далее лишние элементы
			LEN(arr)--;									// уменьшить нулевой индекс, который означает размер массива
		};	
	#endif
    }
    arr = (ELEM_TYPE*) realloc(arr, (LEN(arr))*sizeof(ELEM_TYPE));	// реаллокация массива - уменьшение занимаемой памяти
	if (!arr) exit(1);												// проверка на то, что память была выделена
	return arr;
};

// функция принимает массив, находит максимум и
// добавляет столько нулей в начало
ELEM_TYPE* add_zeros(ELEM_TYPE* arr){
	ELEM_TYPE len = LEN(arr), mx = ELEM(arr, 0); 						// длина поданного массива
	int i, j = 1;
	for(i = 0; i<len; i++){												// цикл по всем элементам
		mx = mx > ELEM(arr, i) ? mx : ELEM(arr, i);						// поиск максимума
	};
	mx = abs(mx); 														// модуль максимума
	arr = (ELEM_TYPE*) realloc(arr, (len+mx)*sizeof(ELEM_TYPE));		// реаллокация памяти
	if (!arr) exit(1);						    						// проверка на то, что память была выделена
	LEN(arr) = len+mx; 			 										// длина нового массива
	
	for(i = len-1; i >= 0; i--){										// передвинуть все элементы на mx индексов вправо
		ELEM(arr, i+mx) = ELEM(arr, i);
	};
	
	memset(arr+1, 0, (size_t)(mx * sizeof(ELEM_TYPE))); 				// занулить первые mx элементов
	 
	return arr;
};

// функция принимает массив, и переставляет все нули в начало 
ELEM_TYPE* relocate_zeros(ELEM_TYPE* arr){
	ELEM_TYPE len = LEN(arr);  							// длина поданного массива
	int zero_count = 0, i = 1;  						// счетчик нулей
	for(i = 0; i<len; i++){								// цикл по всем элементам
		zero_count += ELEM(arr, i) == 0 ? 1 : 0;		// подсчет нулей
	};
	int j = (int) len-1;	
	for (i = len-1; i >= 0; i--){						// передвинуть все ненулевые элементы в конец
		if (ELEM(arr, i) != 0){
			ELEM(arr, j) = ELEM(arr, i);
			j--;
		}
	}
	memset(arr+1, 0, (size_t)(zero_count * sizeof(ELEM_TYPE))); // занулить столько первых элементов, сколько было найдено нулей в исходном массиве
	return arr;
};

// функция принимает массив и заменяет все элементы, равные Х, на
// максимум, минимум или среднее арифметическое всех элементов массива в зависимости от define-ов REPLACE_WITH_MAX, REPLACE_WITH_MIN
ELEM_TYPE* replace(ELEM_TYPE* arr, const int x){
	ELEM_TYPE len = LEN(arr);			// длина поданного массива
	ELEM_TYPE replacement = ELEM(arr, 0);		// значение, на которое нужно будет заменить
	int i;
	
	#if REPLACE_WITH_MIN == 1
	for(i = 1; i<len; i++){				// цикл по всем элементам
		replacement = ELEM(arr, i) < replacement? ELEM(arr, i) : replacement ;	// поиск минимума
	};
	
	#elif REPLACE_WITH_MAX == 1
	for(i = 1; i<len; i++){				// цикл по всем элементам
		replacement = ELEM(arr, i) > replacement? ELEM(arr, i) : replacement ;	// поиск максимума
	};
	
	#else
	for(i = 1; i<len; i++){				// цикл по всем элементам
		replacement += ELEM(arr, i);	// подсчет суммы
	};
	replacement /= len;  				// подсчет среднего арифметического
	
	#endif
	
	for(i = 0; i<len; i++){				// цикл по всем элементам
		if (ELEM(arr, i) == x)			// замена требуемых элементов
			ELEM(arr, i) = replacement;			// на среднее арифметическое
	};
	return arr;
};


