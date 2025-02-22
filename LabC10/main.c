
// объ€вленные ниже define'ы мен€ют поведение функций из файла funcs.h, но вынесены сюда дл€ удобства изменени€
// остальные макросы LEN, ELEM, ELEM_TYPE и необоходитмые системные заголовочные файлы указаны в файле funcs.h

// если убрать оба define'a ниже, то по умолчанию будет замена на среднее арифметическое (по ветке else)
// если объ€вить оба, то преимущество у REPLACE_WITH_MIN - он провер€етс€ первым
#define REPLACE_WITH_MAX 1
//#define REPLACE_WITH_MIN 1


#define DELETE_ODD_INDEXES // мен€ет поведение функции delete_indexes - с ним удал€ютс€ нечетные индексы, без него - четные

#include "funcs.h"



int main(int argc, char *argv[]) {
	
	system("color F0");  	// белый цвет консоли
	system("chcp 1251"); 	// кодова€ страница русского €зыка
	srand(time(0)); 	 	// инициализаци€ псевдослучайной последовательности
	
	// объ€вление переменных
	int A_len = 11111;
	int B_len = 11111;
	int max_len = 10000;
	int i, j;
	ELEM_TYPE** A = NULL;

	// ввод размеров массива
	while (A_len < 1 || A_len >= max_len || B_len < 1 || B_len >= max_len){
		printf("¬ведите размеры массива: \n");
		printf("\t¬ведите количество строк ј: ");
		scanf("%d", &A_len);
		printf("\t¬ведите количество столбцов B: ");
		scanf("%d", &B_len);
		printf("\n");
	};
	
	// ввод границ диапазона случайных чисел
	float mn, mx;
	printf("¬ведите минимум и максимум дл€ случайных чисел: ");
	scanf("%f %f", &mn, &mx);							
	printf("\n");
	
	// при необходимости помен€ть границы местами
	if (mn > mx){										
		float t = mn;
		mn = mx;
		mx = t;
	};
	
    A = (ELEM_TYPE**) malloc(A_len * sizeof(ELEM_TYPE*));		// выделение пам€ти под двумерный массив ј
	if (!A) exit(1);											// проверка на то, что пам€ть была выделена
	
 	//дл€ каждого элемента-указател€ создаЄтс€ свой массив
    for (i = 0; i < A_len; ++i){
        A[i] = (ELEM_TYPE*) calloc(B_len+1, sizeof(ELEM_TYPE)); // выделение пам€ти дл€ подмассива
		if (!A[i]) exit(1);										// проверка на то, что пам€ть была выделена
		A[i][0] = B_len;										// начальна€ длина
 		randomize_arr(A[i], mn, mx);							// заполнение массива случайными числами
	};
	
	printf("»сходный массив: \n");
	
	// вывод двумерного массива
	for (i = 0; i < A_len; ++i) 
    {
    	ELEM_TYPE line_len = A[i][0];
        for (j = 1; j <= line_len; ++j) 
            printf("%6d ", A[i][j]);
        printf("\n");
    };
    
    printf("\n\n");
    
    // построчное применение операций над подмассивами
    for (i = 0; i < A_len; ++i) 
    {
    	if (i % 4 == 0)
    		A[i] = delete_indexes(A[i]);
    	if (i % 4 == 1)
        	A[i] = add_zeros(A[i]);
        if (i % 4 == 2)
        	A[i] = relocate_zeros(A[i]);
        if (i % 4 == 3){
	        int x;
	        
	        #if REPLACE_WITH_MIN == 1
	        printf("¬ведите число, которое нужно заменить на минимум в строке номер %d: ", i+1);
			#elif REPLACE_WITH_MAX == 1
			printf("¬ведите число, которое нужно заменить на максимум в строке номер %d: ", i+1);
			#else
			printf("¬ведите число, которое нужно заменить на среднее в строке номер %d: ", i+1);
			#endif
	        
			scanf("%d", &x);
        	A[i] = replace(A[i], x);
		};
    };
    
    
    printf("\nѕолученный массив: \n");
    
    // вывод двумерного массива
	for (i = 0; i < A_len; ++i) 
    {
    	ELEM_TYPE line_len = LEN(A[i]);
        for (j = 0; j < line_len; ++j) 
            printf("%6d ", ELEM(A[i], j));
        printf("\n");
    };
    printf("\n");
    
    // очищаем подмассивы
    for (i = 0; i < A_len; i++)  
		free(A[i]);
    
    // очищаем основной массив
	free(A); 
	A = NULL;
	
	system("pause");
	return 0;
};
