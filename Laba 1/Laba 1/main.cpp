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
				//���������� ������� ��� ������ ���������� math.h
				while (x <= b)
				{
						f += sin(x) / (pow(x, 2) + 10);
						x += step;
				}
				end_math = clock();
				printf("���������� <math.h>\n");
				printf("�������� �������: %f\n", f);
				printf("�����: %f\n\n", (double)(end_math - start_math) / CLK_TCK);

				x = a;
				f = 0;
				start_asm = clock();
				_asm
				{
						finit		//������������� ������������

						fld b		//��������� � ST(0) ������� ������� ���������
						fld x		//��������� �������� �������
						loop_start :		//����� ������ �����
						fcom		//�������� ������� ���������
								fstsw ax
						    and ah, 01000101b
								jz loop_end

								fldz		//��������� ����
								fadd x	//���������� �
								fsin		//��������� �����

								fld x		//��������� �
								fmul x	//�������� x*x
								fiadd ten		//���������� 10

								fdiv		//�����
								fadd f	//���������� �������� �������
								fstp f	//��������� � ������ ��������

								fadd step		//���������� ���
								fst x			//��������� � � ������
								jmp loop_start	//��������� � �����

								loop_end :	//����� ��������� ������
						fwait
				}

				end_asm = clock();
				printf("������ ������������\n");
				printf("�������� �������: %f\n", f);
				printf("�����: %f\n\n", (double)(end_asm - start_asm) / CLK_TCK);
				printf("��� ������ ������� 0");
				char c = _getch();
				if (c == '0') break;
		}
		return 0;
}