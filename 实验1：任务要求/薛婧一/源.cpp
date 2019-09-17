#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

typedef struct
{
	char name[10];         //����
	char number[10];       //ѧ��
	float Usualgrades;     //ƽʱ�ɼ�
	float Experimentalscore;//ʵ��ɼ�
	float Finalgrade;      //��ĩ�ɼ�
	float Overallresult;    //�ܳɼ�
}SS;

SS* stu;

void sortScore(SS stu[], int N);
SS* readdatafromthefile(int *N);        //��ȡѧ����������
void Calculatinggrades(SS stu[], int N);//����N��ѧ�������ܳɼ�
void Ranking(SS stu[], int N);          //���������ɼ�����
void Putout(SS stu[], int N);           //����һ���ĸ�ʽ���N��ѧ����������Ϣ

int main()
{
	cout << "       Student achievement management analysis system      " << endl;
	cout << "-----------------------------------------------------------" << endl;
	int N = 0;
	SS  *mate = NULL;
	mate = readdatafromthefile(&N);
	Calculatinggrades(mate, N);
	sortScore(mate, N);
	Putout(mate, N);
	free(mate);
	system("pause");
	return 0;
}

SS* readdatafromthefile(int *N)
{
	int n = 0;
	cout << "\nStep 1: Read the student's grade information from the file\n" << endl;
	SS *stu;
	FILE *fp = NULL;
	fp = fopen("C:\\Users\\Administrator\\Desktop\\��ҵ1\\score.txt", "r");
	stu = (SS*)malloc(sizeof(SS));
	while ((!feof(fp)))//��ȡÿ��ѧ������Ϣ,����feof��������:�ļ����������ط�0ֵ���ļ�δ����������0ֵ
	{
		fscanf(fp, "%s%s%f%f%f\n", (stu[n].name), (stu[n].number), &stu[n].Usualgrades, &stu[n].Experimentalscore, &stu[n].Finalgrade);
		printf("name:%s number:%s   Usual grades:%4.2f  Experimental score:%4.2f    Final grade:%4.2f \n", (stu[n].name), (stu[n].number), stu[n].Usualgrades, (stu[n].Experimentalscore), stu[n].Finalgrade);
		n++;
	}
	*N = n;
	printf("The number of the students are %d\n", n);
	fclose(fp);
	return stu;
}

void Calculatinggrades(SS stu[], int N)//����N��ѧ�����Ե������ɼ�
{
	int i;
	cout << "\nStep 2: Calculate the total score of each student\n" << endl;
	for (i = 0; i < N; i++)
	{
		stu[i].Overallresult = 0.2*stu[i].Usualgrades + 0.2*stu[i].Experimentalscore + 0.6*stu[i].Finalgrade;
		printf("name:%s     number:%s     Overall result:%4.2f\n", (stu[i].name), (stu[i].number), stu[i].Overallresult);
	}
}

int Ranking(const void *a, const void *b)//���������ɼ�����
{

	SS *aa = (SS *)(a);
	SS *bb = (SS *)(b);
	if ((*aa).Overallresult < (*bb).Overallresult)
	{
		return 1;
	}
	else if ((*aa).Overallresult > (*bb).Overallresult)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void sortScore(SS stu[], int N)
{

	qsort(&(stu[0]), N, sizeof(stu[0]), Ranking);

}

void Putout(SS stu[], int N)
{
	int i;
	cout << "\nStep 3: Output student ranking information based on the total score!\n" << endl;
	for (i = 0; i < N; i++)
	{
		printf("The number of the student:%d    number:%s   name:%s Overall result:%4.2f \n", i + 1, &(stu[i].number), &(stu[i].name), stu[i].Overallresult);
	}
	getchar();
}