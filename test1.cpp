#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;


const int Population_size = 100;
const int Chromosome_length = 6;
double rate_crossover = 0.5;
double rate_mutation = 0.001;
int iteration_num = 50;


//��Ⱦɫ�嶨��Ϊ�ṹ������
typedef struct Chromosome
{
    short int bit[Chromosome_length];
    double value;
    double fitness;
    double rate_fit;
    double cumu_fit;
}chromosome;

void population_initialize(chromosome (&population_current)[Population_size]);

void decode(chromosome &population_current) ;

double objective_function(double x);

void fresh_property(chromosome(&population_current)[Population_size]);

void seletc_prw(chromosome(&population_current)[Population_size], chromosome(&population_next_generation)[Population_size], chromosome &best_individual);

void crossover(chromosome (&population_next_generation)[Population_size]);

void mutation(chromosome (&population_next_generation)[Population_size]);


void main()
{

    clock_t start, end;//��ʼ��ʱ,��ȷ����
    start = clock();



    chromosome population_current[Population_size];                    //��ǰ��Ⱥ
    chromosome population_next_generation[Population_size];       //��������һ������Ⱥ
    chromosome best_individual;                                                 //��¼��Ӧ�ȵ����ֵ
    chromosome zeros_chromosome;                                                //����һ��ȫΪ0�ĸ��壬����Ⱥ����ĳ�����������


    int i = 0,j = 0;

    for (i = 0; i < Chromosome_length; i++)
        zeros_chromosome.bit[i] = 0;
    zeros_chromosome.fitness = 0.0;
    zeros_chromosome.value = 0.0;
    zeros_chromosome.rate_fit = 0.0;
    zeros_chromosome.cumu_fit = 0.0;

    best_individual = zeros_chromosome;
    for (i = 0; i < Population_size; i++)
    {
        population_current[i] = zeros_chromosome;
        population_next_generation[i] = zeros_chromosome;
    }



    printf("\nWelcome to the Genetic Algorithm��\n");  //
    printf("The Algorithm is based on the function y = -x^2 + 5 to find the maximum value of the function.\n");

    enter:printf("\nPlease enter the no. of iterations\n��������Ҫ�趨�ĵ����� : ");
    scanf_s("%d", &iteration_num);


    if (iteration_num <1)
        goto enter;



    population_initialize(population_current);

    fresh_property(population_current);

    for (i = 0; i< iteration_num; i++)
    {
        seletc_prw(population_current,population_next_generation,best_individual);
        crossover(population_next_generation);
        mutation(population_next_generation);
        fresh_property(population_next_generation);
        for (i = 0; i < Population_size; i++)
        {
            population_current[i] = population_next_generation[i];
            population_next_generation[i] = zeros_chromosome;
        }
        //����ʱ���Ƿ�90s
        end = clock();
        if (double(end - start) / CLK_TCK> 89)
            break;
    }
    //�������ʱ��
    printf("\n ����%d������ʱ��Ϊ�� %f\n", iteration_num, double(end - start) / CLK_TCK);

    //������
    printf("\n �����õ����ֵΪ�� %f ,��Ӧ��Ϊ��%f \n", best_individual.value, best_individual.fitness);

    for (i = 0; i<Population_size; i++)
    {
        printf(" population_current[%d]=", i);
        for (j = 0; j < Chromosome_length; j++)
            printf(" %d", population_current[i].bit[j]);
        printf("        value=%f    fitness = %f\n", population_current[i].value, population_current[i].fitness);
    }
    printf("\nPress any key to end ! ");


    system("pause");
}


void population_initialize(chromosome (&population_current)[Population_size])
{
    int i = 0, j = 0;

    srand((unsigned)time(NULL));

    for (j = 0; j<Population_size; j++)
    {
        for (i = 0; i<Chromosome_length; i++)
        {
            population_current[j].bit[i] = rand()% 2;
        }

    }

}


void decode(chromosome &population_current)
{//�˴���Ⱦɫ�峤��Ϊ�����и���ʾ����λ
    int i = 0;
    population_current.value = 0;
    //��λ��ǰ����λ�ٺ�
    for( i = 0 ; i < Chromosome_length -1; i++ )
        population_current.value += (double)pow(2, i) * (double)population_current.bit[i];    //����Ⱦɫ������Ʊ���,
    //���λΪ����λ�������1������
    if (population_current.bit[Chromosome_length - 1] == 1)
        population_current.value = 0 - population_current.value;

}

//����:������Ӧ��
double objective_function(double x)
{
    double y;
    // Ŀ�꺯����y= - ( (x-1)^ 2 ) +5
    y = -((x - 1) *(x - 1)) + 5;
    return(y);
}

void fresh_property(chromosome (&population_current)[Population_size])
{
    int j = 0;
    double sum = 0;

    for (j = 0; j < Population_size; j++)
    {
        decode(population_current[j]);
        population_current[j].fitness = objective_function(population_current[j].value);
        sum = sum + population_current[j].fitness;

    }

    population_current[0].rate_fit = population_current[0].fitness / sum;
    population_current[0].cumu_fit = population_current[0].rate_fit;
    for (j = 1; j < Population_size; j++)
    {
        population_current[j].rate_fit = population_current[j].fitness / sum;
        population_current[j].cumu_fit = population_current[j].rate_fit + population_current[j-1].cumu_fit;
    }


}

void seletc_prw(chromosome (&population_current)[Population_size],chromosome (&population_next_generation)[Population_size],chromosome &best_individual)
{

    int i = 0, j = 0;
    double rate_rand = 0.0;
    best_individual = population_current[0];
    //�������������
    srand((unsigned)time(NULL));
    for (i = 0; i < Population_size; i++)
    {
        rate_rand = (float)rand() / (RAND_MAX);
        if (rate_rand < population_current[0].cumu_fit)
            population_next_generation[i] = population_current[0];
        else
        {
            for (j = 0; j < Population_size; j++)
            {
                if (population_current[j].cumu_fit <= rate_rand && rate_rand < population_current[j + 1].cumu_fit)
                {
                    population_next_generation[i] = population_current[j + 1];
                    break;
                }
            }
        }

        //�����ǰ�����Ŀǰ�����и��廹Ҫ���㣬�򽫵�ǰ������Ϊ���Ÿ���
        if(population_current[i].fitness > best_individual.fitness)
            best_individual = population_current[i];
    }

}


void crossover(chromosome (&population_next_generation)[Population_size])
{
    int i = 0,j = 0;
    double rate_rand = 0.0;
    short int bit_temp = 0;
    int num1_rand = 0, num2_rand = 0, position_rand = 0;
    //�������������
    srand((unsigned)time(NULL));
    //Ӧ�����������ٴ��أ����趨Ϊ��Ⱥ����
    for (j = 0; j<Population_size; j++)
    {
        rate_rand = (float)rand()/(RAND_MAX);
        //������ڽ�����ʾͽ��н������
        if(rate_rand <= rate_crossover)
        {
            //�����������Ⱦɫ��
            num1_rand = (int)rand()%(Population_size);
            num2_rand = (int)rand()%(Population_size);
            //�����������Ⱦɫ��Ľ���λ��
            position_rand = (int)rand()%(Chromosome_length - 1);
            //���õ��㽻�棬�����֮���λ������
            for (i = position_rand; i<Chromosome_length; i++)
            {
                bit_temp = population_next_generation[num1_rand].bit[i];
                population_next_generation[num1_rand].bit[i] = population_next_generation[num2_rand].bit[i];
                population_next_generation[num2_rand].bit[i] = bit_temp;
            }

        }
    }

}

// �������������
void mutation(chromosome (&population_next_generation)[Population_size])
{
    int position_rand = 0;
    int i = 0;
    double rate_rand = 0.0;
    //�������������
    srand((unsigned)time(NULL));
    //��������趨Ϊ��Ⱥ����
    for (i = 0; i<Population_size; i++)
    {
        rate_rand = (float)rand()/(RAND_MAX);
        //������ڽ�����ʾͽ��б������
        if(rate_rand <= rate_mutation)
        {
            //�������ͻ��λ��
            position_rand = (int)rand()%(Chromosome_length);
            //ͻ��
            if (population_next_generation[i].bit[position_rand] == 0)
                population_next_generation[i].bit[position_rand] = 1;
            else
                population_next_generation[i].bit[position_rand] = 0;

        }

    }
}
