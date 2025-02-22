#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "TriangleModule.h"


// проверка равенства вещественных чисел
bool equal_float(float a, float b){
	return (abs(a - b) < EPS);
}


// создание тругольника по координатам вершин
Triangle create_triangle(float ax, float ay, float bx, float by, float cx, float cy){
	Triangle t;
	t.ax = ax;
	t.ay = ay;
	t.bx = bx;
	t.by = by;
	t.cx = cx;
	t.cy = cy;
	t.equilateral = (bool) (equal_float(pow((bx-ax), 2) + pow((by-ay), 2), pow((cx-ax), 2) + pow((cy-ay), 2)) &&
							equal_float(pow((bx-cx), 2) + pow((by-cy), 2), pow((cx-ax), 2) + pow((cy-ay), 2)));                     
	return t;
};


// смещиение треугольника
void move_triangle(Triangle* t, float dx, float dy){
	t->ax += dx;
	t->ay += dy;
	t->bx += dx;
	t->by += dy;
	t->cx += dx;
	t->cy += dy;
};


// расчет координат ценитроида треугольника
void center(const Triangle* t, float* resx, float* resy){
	*resx = (float)(t->ax + t->bx + t->cx)/3;
	*resy = (float)(t->ay + t->by + t->cy)/3;
};


// поворот треугольника на заданный угол в градусах вокруг центроида
void rotate(Triangle* t, float alpha_deg){
	float center_x, center_y;
	center(t, &center_x, &center_y);
	
	float alpha_rad = alpha_deg * M_PI / 180;
	
	float ax = center_x + (t->ax - center_x) * cos(alpha_rad) - (t->ay - center_y) * sin(alpha_rad);
	float ay = center_y + (t->ax - center_x) * sin(alpha_rad) + (t->ay - center_y) * cos(alpha_rad);
	float bx = center_x + (t->bx - center_x) * cos(alpha_rad) - (t->by - center_y) * sin(alpha_rad);
	float by = center_y + (t->bx - center_x) * sin(alpha_rad) + (t->by - center_y) * cos(alpha_rad);
	float cx = center_x + (t->cx - center_x) * cos(alpha_rad) - (t->cy - center_y) * sin(alpha_rad);
	float cy = center_y + (t->cx - center_x) * sin(alpha_rad) + (t->cy - center_y) * cos(alpha_rad);
	
	t->ax = ax;
	t->ay = ay;
	t->bx = bx;
	t->by = by;
	t->cx = cx;
	t->cy = cy;	
};


// масштабирование треугольника на заданный коэффициент
void resize(Triangle* t, float k){
	t->ax *= k;
	t->ay *= k;
	t->bx *= k;
	t->by *= k;
	t->cx *= k;
	t->cy *= k;
};


// создание равностороннего треугольника с центроидом в начале координат
Triangle create_equilateral_triangle(float side){
	Triangle t; 
	float ax = -side/2;
	float ay = -side*sqrt(3)/6;
	float bx = side/2;
	float by = -side*sqrt(3)/6;
	float cx = 0;
	float cy = side*sqrt(3)/3;
	
	t.ax = ax;
	t.ay = ay;
	t.bx = bx;
	t.by = by;
	t.cx = cx;
	t.cy = cy;
	
	t.equilateral = true;
	return t;
};


// создание прямоугольного треугольника
Triangle create_right_triangle(float sidex, float sidey){
	Triangle t;
	t.ax = 0;
	t.ay = 0;
	t.bx = sidex;
	t.by = 0;
	t.cx = 0;
	t.cy = sidey;
	t.equilateral = false; 
	return t;
};


// вывод треугольника в консоль по заданному шаблону
void print_triangle(const Triangle* t){
	float px1, py1, px2, py2, px3, py3;
	
	if (t->ay > t->by){
		if (t->ay > t->cy){
			px1 = t->ax;
			py1 = t->ay;
			if (t->bx < t->cx){
				px2 = t->bx;
				py2 = t->by;
				px3 = t->cx;
				py3 = t->cy;
			} else{
				px2 = t->cx;
				py2 = t->cy;
				px3 = t->bx;
				py3 = t->by;
			};
		} else {
			px1 = t->cx;
			py1 = t->cy;
			
			if (t->bx < t->ax){
				px2 = t->bx;
				py2 = t->by;
				px3 = t->ax;
				py3 = t->ay;
			} else{
				px2 = t->ax;
				py2 = t->ay;
				px3 = t->bx;
				py3 = t->by;
			};
			
		};	
	}else{
		if (t->by > t->cy){
			px1 = t->bx;
			py1 = t->by;
			if (t->ax < t->cx){
				px2 = t->ax;
				py2 = t->ay;
				px3 = t->cx;
				py3 = t->cy;
			} else{
				px2 = t->cx;
				py2 = t->cy;
				px3 = t->ax;
				py3 = t->ay;	
			};
		} else {
			px1 = t->cx;
			py1 = t->cy;
			
			if (t->bx < t->ax){
				px2 = t->bx;
				py2 = t->by;
				px3 = t->ax;
				py3 = t->ay;
			} else{
				px2 = t->ax;
				py2 = t->ay;
				px3 = t->bx;
				py3 = t->by;	
			};
			
		};	
		
	}
	
	
	printf("\t(%.2f, %.2f)\n", px1, py1);
	printf("(%.2f, %.2f)\t(%.2f, %.2f)\n", px2, py2,px3, py3);
	printf("[%s]", t->equilateral? "Равносторонний": "Неравносторонний");
	printf("\n\n");
}

