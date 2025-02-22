#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*  Имя: Lab5
	Цель: 
				x1 = 4/3, xk = x_(k–1) ^ ((2*k^2) / (4*k^2 - 1))
				найти первое xn, такое что (x_(n)–x_(n–1)) < eps
	Дата: 12.10.2024
	Автор: Деревянко Иван Александрович, группа 3413
*/


// рекурсивная функция для вычисления нужного члена последовательности
double recursive_solution(double cur, int k, const double eps){
	float power = (2*k*k) / (float)(4*k*k - 1); // новая степень
	double nxt = pow(cur, power);				// возвести в эту степень
	double res = 0;
	if (cur - nxt >= eps)						// если этот член последовательности сильно отличается от предыдущего
		res = recursive_solution(nxt, ++k, eps); // рекурсивный вызов для следующего члена последовательности
	else										// иначе - найден нужный член последовательности
		res = nxt;								// возвращаем его значение
	return res;					
};


// итеративная функция для вычисления нужного члена последовательности
double iterative_solution(const double x1, const double eps){
	double cur = x1;		// текущий член последовательности
	float k = 2.0f;			// его номер
	float power; 			// новая степень
	double nxt = cur;		// следующий член последовательности
	do {
		cur = nxt;							  // перезаписать текущий член последовательности
		power = (2*k*k) / (float)(4*k*k - 1); // рассчитать новую степень
		nxt = pow(cur, power);				  // рассчитать номер члена последовательности
		k++;								  // увеличить счетчик - номер текущего члена последовательности
	} while (cur - nxt >= eps);				  // повтор, если новый член последовательности сильно отличается от предыдущего
	return nxt;								  // иначе - найден нужный член последовательности -> возвращаем его значение
};

int main(int argc, char *argv[]) {
	system("color F0");   	//	белый фон консоли
	system("chcp 1251");	// русский язык
	
	// обьявление переменных
	float eps;
	double res_iterative, res_recursive;
	// ввод, пока не будет данных, удовлетровяющих ОДЗ (eps > 0)
	do {
		printf("Введите значение минимальной разницы между членами последовательности: ");
		scanf("%f", &eps);
		printf("\n");
	} while (eps <= 0);
	
	const double x1 = 4.0f/3.0f; 					// первый член последовательности - константа
	res_iterative = iterative_solution(x1, eps);	// итеративное решение
	printf("Значение, полученное при итеративном подходе: %17.15f \n", res_iterative); // вывод результата

	res_recursive = recursive_solution(x1, 2, eps);	// рекурсивное решение
	printf("Значение, полученное при рекурсивном подходе: %17.15f \n", res_recursive); // вывод результата

	system("pause"); // не закрывать окно
	return 0;
}
