// 16. F(x) = sin(x)/(x^2+10)

#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

int main()
{
		setlocale(LC_ALL, "Russian");
		double a, b, step;
		double f, x;
		int ten = 10;
		clock_t start_asm, end_asm;
		clock_t start_math, end_math;

		while (1)
		{
				system("cls");
				scanf("%lf %lf %lf", &a, &b, &step);
				x = a;
				f = 0;
				printf("F = sin(x)/(x^2+10)\n");
				start_math = clock();
				//Вычисление функции при помощи библиотеки math.h
				while (x <= b)
				{
						f += sin(x) / (pow(x, 2) + 10);
						x += step;
				}
				end_math = clock();
				printf("Библиотека <math.h>\n");
				printf("Значение функции: %f\n", f);
				printf("Время: %f\n\n", (double)(end_math - start_math) / CLK_TCK);

				x = a;
				f = 0;
				start_asm = clock();
				_asm
				{
						finit		//Инициализация сопроцессора

						fld b		//Загружаем в ST(0) верхнюю границу интервала
						fld x		//Загружаем значение функции
						loop_start :		//метка начала цикла
						fcom		//проверка границы интервала
								fstsw ax
						    and ah, 01000101b
								jz loop_end

								fldz		//Загружаем ноль
								fadd x	//Прибавляем х
								fsin		//Вычисляем синус

								fld x		//Загружаем х
								fmul x	//Умножаем x*x
								fiadd ten		//Прибавляем 10

								fdiv		//Делим
								fadd f	//Прибавляем значение функции
								fstp f	//Сохраняем в памяти значение

								fadd step		//Прибавляем шаг
								fst x			//Сохраняем х в памяти
								jmp loop_start	//Переходим к метке

								loop_end :	//Метка окончания работы
						fwait
				}

				end_asm = clock();
				printf("Работа сопроцессора\n");
				printf("Значение функции: %f\n", f);
				printf("Время: %f\n\n", (double)(end_asm - start_asm) / CLK_TCK);
				printf("Для выхода нажмите 0");
				char c = _getch();
				if (c == '0') break;
		}
		return 0;
}