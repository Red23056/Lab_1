#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <time.h>
#include <vector>
#include <math.h>
using namespace std;
const int previous = 1;
const int one_step = 1;
const int two_step = 2;
const int start = 1;
const int start_gap = 1;
const int undabling = 2;
const int shell_step = 2;
const int shell_step_pratt = 3;

void bubble_sort(vector <int> & mass, int size)
{
    int boffer;
    for (int i = size - one_step; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (mass[j] > mass[j + one_step])
            {
                boffer = mass[j + one_step];
                mass[j + one_step] = mass[j];
                mass[j] = boffer;
            }
        }
    }
}

void shell_sort(vector <int> & mass, int len)
{
    int element, i, j;
    for (int gap = len / shell_step; gap > 0; gap /= shell_step)
    {
        for (i = gap; i < len; i++)
        {
            element = mass[i];
            for (j = i; j >= gap and mass[j - gap] > element; j -= gap)
            {
                mass[j] = mass[j - gap];
            }
            mass[j] = element;
        }
    }
}

void selection_sort(vector <int> & mass, int size)
{
    for (int i = 0; i < size; i++)
    {
        int mn = i;
        for (int j = i; j < size; j++)
        {
            if (mass[mn] > mass[j])
            {
                mn = j;
            }
        }
        int buffer = mass[mn];
        mass[mn] = mass[i];
        mass[i] = buffer;
    }
}

vector <int> uniteVector_forQS(vector <int> vec1, vector <int> vec2) 
{
    for (int element : vec2) 
    {
        vec1.push_back(element);
    }
    return vec1;
}

vector <int> quick_sort(vector <int> mass) 
{
    if (mass.size() == 0) 
    {
        return mass;
    }
    else 
    {
        int pivot = mass[mass.size() / undabling]; // опорный элемент
        vector <int> left_element; // элементы меньше опорного
        vector <int> vecPivot; // элементы равные опорному
        vector <int> right_element; // элементы больше опорного
        for (int i = 0; i < mass.size(); i++) 
        {
            if (mass[i] < pivot) 
            {
                left_element.push_back(mass[i]);
            }
            else if (mass[i] == pivot) 
            {
                vecPivot.push_back(mass[i]);
            }
            else 
            {
                right_element.push_back(mass[i]);
            }
        }
        return uniteVector_forQS(uniteVector_forQS(quick_sort(left_element), vecPivot), quick_sort(right_element));
    }
}

void merge_sort(vector <int>& mass, int left, int mid, int right)
{
    int i = 0, j = 0, k = 0;
    int left_size = mid - left + one_step;
    int right_size = right - mid;
    vector <int> left_mass(left_size);
    vector <int> right_mass(right_size);
    for (i = 0; i < left_size; i++)
    {
        left_mass[i] = mass[left + i];
    }
    for (j = 0; j < right_size; j++)
    {
        right_mass[j] = mass[mid + j + one_step];
    }
    i = 0;
    j = 0;
    k = left;
    while (i < left_size and j < right_size)
    {
        if (left_mass[i] <= right_mass[j])
        {
            mass[k] = left_mass[i];
            k++;
            i++;
        }
        else
        {
            mass[k] = right_mass[j];
            k++;
            j++;
        }
    }
    while (i < left_size)
    {
        mass[k] = left_mass[i];
        k++;
        i++;
    }
    while (j < right_size)
    {
        mass[k] = right_mass[j];
        k++;
        j++;
    }
}

void recursive_merge(vector <int>& mass, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / undabling;
        recursive_merge(mass, left, mid);
        recursive_merge(mass, mid + one_step, right);
        merge_sort(mass, left, mid, right);
    }
}

void heapify(vector <int> & mass, int size, int i)
{
    int root = i;//Ставим наибольший элемент последним
    int left = undabling * i + one_step; // левый
    int right = undabling * i + two_step; // правый
    if (left < size and mass[left] > mass[root])
    {
        root = left;
    }
    if (right < size and mass[right] > mass[root])
    {
        root = right;
    }
    if (root != i)
    {
        swap(mass[i], mass[root]);
        heapify(mass, size, root);
    }
}

void heapSort(vector <int> & mass, int size)//heap sort
{
    for (int i = size / undabling - one_step; i >= 0; i--)
        heapify(mass, size, i);

    for (int i = size - one_step; i >= 0; i--)
    {
        swap(mass[0], mass[i]);

        heapify(mass, i, 0);
    }
}

void insertion_sort(vector <int> & mass, int len)
{
    int element, i, j;
    for (i = start; i < len; i++)
    {
        element = mass[i];
        for (j = i; j >= start and mass[j - one_step] > element; j -= one_step)
        {
            mass[j] = mass[j - one_step];
        }
        mass[j] = element;
    }
}

void shell_sort_pratt(vector <int> & mass, int len, vector <int> gaps)
{
    int element, i, j;
    int gap;
    for (int gaps_size = gaps.size() - one_step; gaps_size >= 0; gaps_size--)
    {
        gap = gaps[gaps_size];
        for (i = gap; i < len; i++)
        {
            element = mass[i];
            for (j = i; j >= gap and mass[j - gap] > element; j -= gap)
            {
                mass[j] = mass[j - gap];
            }
            mass[j] = element;
        }
    }
}

void shell_sort_hibbord(vector <int> & mass, int len, vector <int> gaps)
{
    int element, i, j, gap;
    for (int gaps_size = gaps.size() - one_step; gaps_size >= 0; gaps_size--)
    {
        gap = gaps[gaps_size];
        for (i = gap; i < len; i++)
        {
            element = mass[i];
            for (j = i; j >= gap and mass[j - gap] > element; j -= gap)
            {
                mass[j] = mass[j - gap];
            }
            mass[j] = element;
        }
    }
}

// Генерация отсортированного массива
void generate_sorted_mass(vector <int> & mass, int size)
{
    for (int i = 0; i < size; i++)
    {
        mass[i] = i; // Отсортированный по возрастанию
    }
}

// Генерация почти отсортированного массива (90/10)
void generate_nearly_sorted_mass(vector <int>& mass, int size, int seed)
{
    srand(seed);
    int numSwaps = size / 10;
    int booffer;
    for (int i = 0; i < numSwaps; i++)
    {
        int idx1 = rand() % size;
        int idx2 = rand() % size;
        booffer = mass[idx1];
        mass[idx1] = mass[idx2];
        mass[idx2] = booffer;
    }
}

// Генерация массива, отсортированного в обратном порядке
void generate_reversed_mass(vector <int>& mass, int size)
{
    for (int i = 0; i < size; i++)
    {
        mass[i] = size - i; // Отсортированный по убыванию
    }
}

// Генерация случайного массива с заданным сидом
void generate_random_mass(vector <int>& mass, int size, int seed)
{
    srand(seed);
    for (int i = 0; i < size; ++i)
    {
        mass[i] = rand() % 100; // Заполняем случайными числами от 0 до 99
    }
}

double tested(vector <int>& mass, int size, int sorted)
{
    clock_t start = 0;
    clock_t end = 0;
    vector <int> gaps;
    switch (sorted)
    {
    case 1:start = clock();
        insertion_sort(mass, size);
        end = clock();
        break;
    case 2:start = clock();
        heapSort(mass, size);
        end = clock();
        break;
    case 3:start = clock();
        recursive_merge(mass, 0, size - one_step);
        end = clock();
        break;
    case 4:start = clock();
        quick_sort(mass);
        end = clock();
        break;
    case 5:start = clock();
        selection_sort(mass, size);
        end = clock();
        break;
    case 6:start = clock();
        shell_sort(mass, size);
        end = clock();
        break;
    case 7:start = clock();
        bubble_sort(mass, size);
        end = clock();
        break;
    case 8:
        for (int i = start_gap; i <= size; i *= shell_step)
        {
            for (int j = i; j <= size; j *= shell_step_pratt)
            {
                gaps.push_back(j);
            }
        }
        heapSort(gaps, gaps.size());
        start = clock();
        shell_sort_pratt(mass, size, gaps);
        end = clock();
        break;
    case 9:
        for (int i = start_gap; pow(shell_step, i) <= size; i ++)
        {
            gaps.push_back(pow(shell_step, i) - one_step);
        }
        start = clock();
        shell_sort_hibbord(mass, size, gaps);
        end = clock();
        break;
    default:break;
    }
    double second = (double)(end - start) / CLOCKS_PER_SEC;
    return(second);
}

void test(vector <int>& mass, int size, int seed, int command, int sorted, ofstream & out, ofstream & dat)
{
    if (command == 1)
    {
        generate_sorted_mass(mass, size);
        double second = tested(mass, size, sorted);
        cout << "Время выполнения сортировки отсортированного массива: " << second << endl;
        out << "Shell_sort_pratt,Отсортированный," << size << "," << second << endl;
        dat << second << endl;
    }
    else if (command == 2)
    {
        generate_nearly_sorted_mass(mass, size, seed);
        double second = tested(mass, size, sorted);
        cout << "Время выполнения сортировки отсортированного массива 90/10: " << second << endl;
        out << "Shell_sort_pratt,Почти отсортированный (90/10)," << size << "," << second << endl;
        dat << second << endl;
    }
    else if (command == 3)
    {
        generate_reversed_mass(mass, size);
        double second = tested(mass, size, sorted);
        cout << "Время выполнения сортировки отсортированного массива в обратном порядке: " << second << endl;
        out << "Shell_sort_pratt,Отсортированный в обратном порядке," << size << "," << second << endl;
        dat << second << endl;
    }
    else if (command == 4)
    {
        generate_random_mass(mass, size, seed);
        double second = tested(mass, size, sorted);
        cout << "Время выполнения сортировки случайного массива: " << second << endl;
        out << "Shell_sort_pratt,Случайный," << size << "," << second << endl;
        dat << second << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    ofstream out;
    ofstream dat;
    dat.open("dat.txt");
    out.open("data.txt");
    int seed;
    int command;
    int i;
    int sorted;
    cout << "seed: ";
    cin >> seed;
    cout << "command: ";
    cout << "Выберите сортировку" << endl << "1 - insertion_sort" << endl << "2 - heap_sort" << endl
        << "3 - merge_sort" << endl << "4 - quick" << endl << "5 - selection_sort" << endl
        << "6 - shell_sort" << endl << "7 - bubble_sort" << endl << "8 - shell_sort_hibbord" << endl
        << "9 - shell_sort_pratt" << endl;
    cin >> sorted;
    i = 1000;
    vector <int> mass(i);
    for (command = 1; command < 5; command++)
    {
        i = 1000;
        mass.resize(i);
        test(mass, i, seed, command, sorted, out, dat);
        for (i = 10000; i <= 100000; i += 10000)
        {
            mass.resize(i);
            test(mass, i, seed, command, sorted, out, dat);
        }
    }
}