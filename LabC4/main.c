#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// функция принимает двумерный массив координат и его первую размерность - количество точек,
// позволяет пользователю заполнить его вручную
void arr_by_hand(float arr[][2], const int len){
	int i = 0;
	for(;i<len; i++){ 												// цикл по всем точкам
		printf("Введите координату X точки номер %d: ", i);
		scanf("%f", &arr[i][0]);									// ввод Х
		
		printf("Введите координату Y точки номер %d: ", i);
		scanf("%f", &arr[i][1]); 									// ввод Y

	};
}

// функция принимает двумерный массив координат и его первую размерность - количество точек,
// позволяет заполнить его случайными числами из заданного диапазона
void randomize_arr (float arr[][2], const int len){
	float mn, mx;
	printf("Введите минимум и максимум для случайных координат: ");
	scanf("%f %f", &mn, &mx);										 // ввод границ диапазона случайных координат
	printf("\n");
	
	if (mn > mx){													// при необходимости поменять границы местами
		float t = mn;
		mn = mx;
		mx = t;
	};
	srand(time(0)); 												// инициализация псевдослучайной последовательности
	int i = 0;
	for(;i<len; i++){												// цикл по всем точкам
		arr[i][0] = (float)rand() / RAND_MAX * (mx - mn) + mn;		// случайный Х
		arr[i][1] = (float)rand() / RAND_MAX * (mx - mn) + mn;		// случайный Y

	};
}

// фунция позволяет определить принадлежность точки к заданной области
// на вход принимает одномерный массив - координаты одной точки и параметр А, задающий область
bool belongs_to_area(float point[2], const float A){
	float x = point[0];											// координата Х точки
	float y = point[1];											// координата Y точки
	
	bool left_half = (x <= 0) && (y >= x) && (y <= -x);			// лежит между прямыми при Х <= 0
	bool right_half = (x >= 0) && (y >= -x) && (y <= x);		// лежит между прямыми при Х >= 0
	bool in_parabola = (y <= -1 * x * x + A);					// лежит внутри параболы
	return (left_half || right_half) && in_parabola;			// принадлежит области
}

// функция принимает двумерный массив координат, его первую размерность - количество точек и 
// параметр А, задающий область для оценки принадлежности точки к области через другую функцию
// выводит каждую точку в массиве на отдельной строке с координатами и информацией о принадлежности к области
void print_arr(float arr[][2], const int len, const float A){
	int i = 0;
	for(;i<len; i++){																		// цикл по всем точкам
		printf("Точка %3d имеет координаты (%10f, %10f). ", i+1, arr[i][0], arr[i][1]);		// вывод координат
		bool belongs = belongs_to_area(arr[i], A);								// оценка принадлежности
		
		if (belongs)															// вывод информации о принадлежности
			printf("Она принадлежит заданной области. ");
		else
			printf("Она не принадлежит заданной области. ");
		
		printf("\n");		// новая строка
	};
}

int main(int argc, char *argv[]) {
	system("color F0");  // белый цвет консоли
	system("chcp 1251"); // кодовая страница русского языка
	
	// объявление переменных
	int points_num;
	int arr_fill = 0;
	float A_parametr;
	
	// ввод количества точек
	printf("Введите количество рассматривамых точек: ");
	scanf("%d", &points_num);
	printf("\n");
	
	// выбор способа заполнения с защитой от ошибки
	while (arr_fill != 1 && arr_fill != 2){
		printf("Выберите способ заполнения массива координат:\n\t1 - ручной ввод координат,\n\t2 - заполнение случайными числами.\nВариант - ");
		scanf("%d", &arr_fill);
		printf("\n");
	};
	
	// объявление двумерного массива
	float points[points_num][2];
	
	// заполнение его выбранным способом
	if (arr_fill == 1)
		arr_by_hand(points, points_num);
	else
		randomize_arr(points, points_num);
		
	// ввод параметра А, задающего область
	printf("Введите параметр А, задающий область: ");
	scanf("%f", &A_parametr);
	printf("\n");
				
	// вывод оценки принадлежности к области для кажой точки 
	print_arr(points, points_num, A_parametr);
	
	system("pause"); // не закрывать окно
	return 0;
}
