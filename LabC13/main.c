#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "TriangleModule.h"
#include "ProductModule.h"


int main(int argc, char *argv[]) {
	system("color F0");  	// белый цвет консоли
	system("chcp 1251"); 	// кодовая страница русского языка
	
	// объявление переменных
	float ax, ay, bx, by, cx, cy;
	float dx, dy;
	float centx, centy;
	float angle;
	float k;
	float side;
	float X,Y;
	int cont = false;
	Triangle t;	
	Product* products = NULL;
    int size = 0;
	int type;
	int index;
	int command = 0;	  // команда пользователя
	
	while (true){	// основной цикл программы для ввода команд пользователя
        printf("\nМеню:\n");
        printf("1. Лабораторная 11: работа со структурой-треугольником\n");
        printf("2. Лабораторная 12: работа с массивом структур-продуктов\n");
        printf("3. Выход из программы\n");
		printf("Выберите действие (введите только цифру): ");

        int choice;
        scanf("%d", &choice);
        
    	bool created = false; // создан ли треугольник
		bool run = true;	  // продолжение работы в данном режиме

        switch (choice) 	
        {
        case 1: // Лабораторная 11: работа со структурой-треугольником
			while (run){
				printf("Введите команду (только цифру):\
							\n\t1 - Создание треугольника по координатам его вершин.\
							\n\t2 - Перемещение треугольника на заданное смещение относительно осей X и Y.\
							\n\t3 - Расчёт координат центроида треугольника.\
							\n\t4 - Поворот треугольника на заданный угол вокруг его центроида.\
							\n\t5 - Изменение размера треугольника на заданный коэффициент масштаба относительно его центроида.\
							\n\t6 - Создание равностороннего треугольника по заданному размеру стороны, центроид которого совпадает с точкой (0,0).\
							\n\t7 - Создание прямоугольного треугольника по двум заданным длинам катетов, совпадающих с положительными полуосями X и Y.\
							\n\t8 - Вывод треугольника в консоль.\
							\n\t9 - Выход из этого режима работы. \n\n");
							
				printf("Выбраная команда: ");
				scanf("%d", &command);
				printf("\n\n");
				
				switch (command)
			    {
			    case 1:  // создание тругольника по координатам вершин
			    	printf("Введите координаты точек тругольника\nв слудющем порядке ax, ay, bx, by, cx, cy: ");
			    	scanf("%f %f %f %f %f %f", &ax, &ay, &bx, &by, &cx, &cy);
			    	Triangle t = create_triangle(ax, ay, bx, by, cx, cy);
			    	created = true;
			    	printf("Создан новый треугольник. Для просмотра используйте команду 8.\n\n");
			    	break;
			    	
			    case 2:	// смещиение треугольника
			    	if (!created) {
						printf("Треугольник ещё не создан!\n\n");
						break;
					};
			        printf("Введите смещения dx, dy: ");
			    	scanf("%f %f", &dx, &dy);
			    	move_triangle(&t, dx, dy);
			    	printf("Треугольник перемещён. Для просмотра используйте команду 8.\n\n");
			    	break;
			
			    case 3:	// расчет координат ценитроида треугольника
			    	if (!created) {
						printf("Треугольник ещё не создан!\n\n");
						break;
					};
			    	center(&t, &centx, &centy);
			    	printf("\n\n");
			    	printf("Центроид данного треугольника находится в точке (%.2f, %.2f).\n\n", centx, centy);	
			        break;
			
			    case 4:	// поворот треугольника вокруг центроида на заданный угол в градусах 
			    	if (!created) {
						printf("Треугольник ещё не создан!\n\n");
						break;
					};
			        printf("Введите угол поворота в градусах: ");
			    	scanf("%f", &angle);
			    	rotate(&t, angle);
			    	printf("Треугольник повёрнут. Для просмотра используйте команду 8.\n\n");
			    	break;
			
			    case 5:	// масштабирование треугольника на заданный коэффициент
			    	if (!created) {
						printf("Треугольник ещё не создан!\n\n");
						break;
					};
			        printf("Введите коэффициент масштаба k: ");
			    	scanf("%f", &k);
			    	resize(&t, k);
			    	printf("Треугольник отмасштабирован. Для просмотра используйте команду 8.\n\n");
			    	break;
			
			    case 6:	// создание равностороннего треугольника с центроидом в начале координат
			        printf("Введите длину стороны равностороннего треугольника с центроидом в точке (0, 0): ");
			    	scanf("%f", &side);
			    	t = create_equilateral_triangle(side);
			    	created = true;
			    	printf("Создан новый треугольник. Для просмотра используйте команду 8.\n\n");
			    	break;
			
			    case 7: // создание прямоугольного треугольника
			        printf("Введите катеты X и Y: ");
			    	scanf("%f %f", &X, &Y);
			    	t = create_right_triangle(X,Y);
			    	created = true;
			    	printf("Создан новый треугольник. Для просмотра используйте команду 8.\n\n");
			    	break;
			    	
			    case 8:	// вывод треугольника в консоль по заданному шаблону
			    	if (!created) {
						printf("Треугольник ещё не создан!\n\n");
						break;
					};
			    	print_triangle(&t);
			    	break;
			    	
			    case 9: // завершение работы
			    	printf("Завершение работы со структурой-треугольником...\n\n");
			    	run = false;
			    	break;
			
			    default:
			        printf("Неизвестная команда!\n\n");
			        break;
			    };
			    
			if (run){ // вопрос о продолжении, чтобы не выводить сразу после результата большое меню
				printf("Продолжить? \n\t0 - нет, выйти.\n\t1 - да, продолжить.\n");
				printf("Выбраная команда: ");
				scanf("%d", &cont);
				printf("\n\n");
				if (!cont) run = false;
			};		
			};
			break;
			
        case 2: // Лабораторная 12: работа с массивом структур-продуктов
		        
			while (run) { 
		        printf("\n\nМеню:\n");
		        printf("1. Добавить продукт.\n");
		        printf("2. Удалить продукт.\n");
		        printf("3. Обновить информацию о существующем продукте.\n");
		        printf("4. Вывести на экран информацию обо всех продуктах.\n");
		        printf("5. Вывести на экран только информацию о продуктах с указанными свойствами.\n");
		        printf("6. Выход из этого режима работы.\n");
		        printf("Выберите действие (введите только цифру): ");
		
		        scanf("%d", &command);
		
		        switch (command)
		        {
		        case 1:
		            printf("Введите тип продкукта\n(%d - Новогодняя елка,\n%d - Елочная игрушка,\n%d - Новогодний подарок)\nВаш выбор: ",  CHRISTMAS_TREE_NUM, CHRISTMAS_TREE_DECORATION_NUM, NEW_YEAR_GIFT_NUM);
		            scanf("%d", &type);
		            ProductType new_porduct_type = (ProductType)type;
		            Product* new_product = create_product(new_porduct_type);
		            if (!new_product) break;            
		            add_product(&products, &size, new_product);
		            printf("Новый элемент добавлен в массив. Используйте команду 4 для просмотра.");
		            break;
		
		        case 2:
		            if (size == 0)
		            {
		                printf("Массив пуст.\n");
		                break;
		            }
		
		            printf("Введите номер элемента, который необходимо удалить (нумерация с единицы): ");
		            scanf("%d", &index);
		            remove_product(&products, &size, index - 1);
		            break;
		
		        case 3:
		            if (size == 0)
		            {
		                printf("Массив пуст.\n");
		                break;
		            }
		
		            printf("Введите индекс элемента, который необходимо обновить (нумерация с единицы): ");
		            scanf("%d", &index);
		            update_product(products, size, index - 1);
		            printf("Элемент обновлен. Используйте команду 4 для просмотра.");
		            break;
		
		        case 4:
		            if (size == 0)
		            {
		                printf("Массив пуст.\n");
		                break;
		            }
		            print_all_products(products, size);
		            break;
		
		        case 5:
		            if (size == 0)
		            {
		                printf("Массив пуст.\n");
		                break;
		            }
		            print_products_by_mask(products, size);
		            break;
		
		        case 6:
		            printf("Завершение работы с массивом структур-продуктов...\n\n");
		            free(products);
		            products = NULL;
		            run = false;
		            break;
		
		        default:
		            printf("Неизвестная команда!\n");
		        };
		    };
		    break;
		    
        case 3:
            printf("Выход из программы...\n");
            return 0;

        default:
            printf("Неизвестная команда!\n");
        }
    };
		
	system("pause");
	return 0;
}

