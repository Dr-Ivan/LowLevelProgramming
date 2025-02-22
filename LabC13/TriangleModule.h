#ifndef LAB11_HEADER
#define LAB11_HEADER

#define EPS 1e-6

// структура для треугольника
typedef struct
{
	float ax;
	float ay;
	float bx;
	float by;
	float cx;
	float cy;
	bool equilateral;
} Triangle;

// создание тругольника по координатам вершин
Triangle create_triangle(float ax, float ay, float bx, float by, float cx, float cy);


// смещиение треугольника
void move_triangle(Triangle* , float, float);


// расчет координат ценитроида треугольника
void center(const Triangle*, float*, float*);


// поворот треугольника на заданный угол в градусах вокруг центроида
void rotate(Triangle*, float);


// масштабирование треугольника на заданный коэффициент
void resize(Triangle*, float);


// создание равностороннего треугольника с центроидом в начале координат
Triangle create_equilateral_triangle(float);


// создание прямоугольного треугольника
Triangle create_right_triangle(float, float);


// вывод треугольника в консоль по заданному шаблону
void print_triangle(const Triangle*);


#endif // LAB11_HEADER
