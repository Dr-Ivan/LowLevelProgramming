#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main() {
	system("color F0");
	system("chcp 1251"); // кодовая страница русского языка
	
	// Объявление переменных
	float x0, xh, xn;
	float y0, yh, yn;
	float x, y;
	double result;
	double max;
	double min;
	int nm1, nm2;
	
	// Ввод переменных
	printf("Введите [x0 (xh) xn]: ");
	scanf("%f %f %f", &x0, &xh, &xn);
	
	printf("Введите [y0 (yh) yn]: ");
	scanf("%f %f %f", &y0, &yh, &yn);
	
	printf("Введите целые значения: nm1, nm2: ");
	scanf("%d %d", &nm1, &nm2);
	
	// Проверка 
	bool correctData = (nm1 >= 2.0f && nm1 <= 6.0f && nm2 >= 2.0f && nm2 <= 6.0f && x0 <= xn && y0 <= yn && yh > 0 && xh > 0);
	if (!correctData) {
		printf("Введены неверные данные."); 	// если данные неверны
		return 1;	// вернуть код ошибки 1
	};
	
	// Вычисления
	x = x0; // начальное значение Х
	result = 0; // переменная для хранения результата
	max = -2147483647; // переменная для максимума (значение обязательно перезапишется)
	min = 2147483647; // переменная для минимума (значение обязательно перезапишется)
	
	// вывод шапки таблицы
	printf("|-------|-------|--------------|\n");
	printf("|   x   |   y   |    Result    |\n");
	printf("|-------|-------|--------------|\n");
	
	// вложенные циклы для табулирования функции двух переменных
	while(x < xn + xh/3) {
		y = y0;  // сброс значения у
		while(y < yn + yh/3) {
			result = 0; 
			// вычисление значения фунции в данной точке
			{
				double result1 = 0; //слагаемое 1
				double result2 = 0; // слагаемое 2
				int n = 1; //счетчик
				for (; n <= nm1; n++){ // цикл накопления суммы первого слагаемого
					double pw = pow(x, n);
					result1 += 1 + y * log(pw);
				};
				n = 1;	// сброс счетчика
				for (; n <= nm2; n++){ // цикл накопления суммы второго слагаемого
					result2 += (7*x + pow(y, n-1)) / (sqrt(2*n + y));
				};
				result = result1 + ((x+1) / (3*y)) * result2; // конечный результат
			};
			
			printf("| %5.2f | %5.2f | %.5le | \n", x, y, result); // вывод строки таблицы
			printf("|-------|-------|--------------|\n"); // вывод разделителя строк таблицы
			if (max < result) {	// обновление максимума
				max = result;
			};
			
			if (min > result) {	// обновление минимума
				min = result;
			};
				y += yh; // шаг по у
			};
		x += xh; // шаг по х
	};
	
	printf("Минимальное значение = %le \n", min); // вывод минимума
	printf("Максимальное значение = %le \n", max); // вывод максимума
	
	system("pause"); // пауза, чтобы окно не закрывалось само
	return 0;
}
