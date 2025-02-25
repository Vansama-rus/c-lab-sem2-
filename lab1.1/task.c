#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 100

struct Student {
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent(const char* name, int math, int phy, int inf) {
    struct Student newStudent;
    strncpy(newStudent.name, name, sizeof(newStudent.name) - 1);
    newStudent.name[sizeof(newStudent.name) - 1] = '\0';
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}

void printStudentInfo(struct Student student) {
    printf("Имя: %s, Математика: %d, Физика: %d, Информатика: %d, Общий балл: %d\n",
           student.name, student.math, student.phy, student.inf, student.total);
}

void shellSort(struct Student arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            struct Student temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].total < temp.total; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
void countingSort(struct Student arr[], int n) {
    // Находим максимальное значение total
    int maxTotal = arr[0].total;
    for (int i = 1; i < n; i++) {
        if (arr[i].total > maxTotal) {
            maxTotal = arr[i].total;
        }
    }

    // Массив для подсчета
    int count[maxTotal + 1];
    struct Student output[n]; // Выходной массив

    // Инициализация массива подсчета
    for (int i = 0; i <= maxTotal; i++) {
        count[i] = 0;
    }

    // Заполняем массив подсчета
    for (int i = 0; i < n; i++) {
        count[arr[i].total]++;
    }

    // Преобразуем массив подсчета в массив индексов
    for (int i = 1; i <= maxTotal; i++) {
        count[i] += count[i - 1];
    }

    // Строим выходной массив
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i].total] - 1] = arr[i];
        count[arr[i].total]--;
    }

    // Копируем отсортированный массив обратно
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}


int main() {
    struct Student students[N];
    const char* names[] = {"Алексей", "Мария", "Дмитрий", "Вовчик", "Сергей", "Елена"};
    
    srand(time(NULL));
    
    for (int i = 0; i < N; i++) {
        const char* name = names[rand() % (sizeof(names)/sizeof(names[0]))];
        int math = rand() % 101;
        int phy = rand() % 101;
        int inf = rand() % 101;
        students[i] = addStudent(name, math, phy, inf);
    }

    printf("Список студентов до сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    clock_t start = clock();
    shellSort(students, N);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nСписок студентов после сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    printf("\nВремя работы сортировки: %f секунд\n", time_spent);
    
    system("cat /proc/cpuinfo | grep 'model name' | head -n 1");
    
    return 0;
}