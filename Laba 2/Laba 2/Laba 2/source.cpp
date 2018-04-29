#include <iostream>
#include <random>
#include <time.h>

const int COUNT_CYCLE = 10000000; //���������� �������� �����
const int SIZE = 4; //������ ������
const int RAND = 10000; //������� �������
using namespace std;

/*����� ������� �� �����*/
void output(int ms[SIZE][SIZE])
{
		for (int i = 0; i < SIZE; i++)
		{
				for (int j = 0; j < SIZE; j++)
				{
						cout << ms[i][j] << ' ';
				}
				cout << endl;
		}
}

void null(int ms[SIZE][SIZE])
{
		for (int i = 0; i < SIZE; i++)
		{
				for (int j = 0; j < SIZE; j++)
				{
						ms[i][j]=0;
				}
		}
}

/*���������� ������� ���������� �������*/
void rand(int ms[SIZE][SIZE])
{
		for (int i = 0; i < SIZE; i++)
		{
				for (int j = 0; j < SIZE; j++)
				{
						ms[i][j] = rand() % RAND;
				}
		}
}

int main()
{
		srand(time(NULL));
		clock_t start;
		clock_t end;
		int ms1[SIZE][SIZE];
		int ms2[SIZE][SIZE];
		int result_ms[SIZE][SIZE] = { 0 };
		
		rand(ms1);
		rand(ms2);

		cout << "Number of iterations: " << COUNT_CYCLE << endl;
		cout << "Random area: " << RAND << endl << endl;
		/*Pure C*/
		start = clock();
		for (int i = 0; i < COUNT_CYCLE; i++)
		{
				for (int i = 0; i < 4; i++)
				{
						for (int j = 0; j < 4; j++)
						{
								result_ms[i][j] = ms1[i][j] - ms2[i][j];
						}
				}
		}
		end = clock();
		//output(result_ms);
		cout << "Pure C: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

		null(result_ms);
		/*Asm*/
		start = clock();
		for (int i = 0; i < COUNT_CYCLE; i++)
		{
				_asm {
						xor esi, esi  //�������� ������
						xor eax, eax	//�������� ��������
						mov ebx, 16 //������ 4�4


						cycleAsm:
								mov eax, ms1[esi]
								sub eax, ms2[esi]
								mov result_ms[esi], eax
								add esi, 4

								dec ebx //����������� ���������� ��������
								cmp ebx, 0 //���������� � ����
								jne cycleAsm
				}
		}
		end = clock();
		//output(result_ms);
		cout << "ASM: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

		/*MMX*/
		null(result_ms);
		start = clock();
		for (int i = 0; i < COUNT_CYCLE; i++)
		{
				_asm {
						pusha
						xor esi, esi //�������� ������
						mov ebx, 8  //���������� �������� �� ����� (������� 4x4)

						cycleMMX:
								movq MM0, ms1[esi]  //������� �������� � ������� MM0
								psubq MM0, ms2[esi] // �������� �������� ������� �������
								movq result_ms[esi], MM0  //���������� �������� � ������ ��������
								add esi, 8  //����������� ��������� �� int*2

								dec ebx  //����������� ���������� ��������
								cmp ebx, 0 //���������� � 0
								jne cycleMMX
								emms
								popa
				}
		}
		//output(result_ms);
		end = clock();
		cout << "MMX: " << (double)(end - start) / CLOCKS_PER_SEC << endl << endl;
		system("pause");
		return 0;
}