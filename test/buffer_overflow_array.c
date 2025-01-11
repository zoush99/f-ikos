#include <stdio.h>

#define SIZE 100

// 函数声明
void initialize_array(float arr[], int size);
void process_array(float arr[], int size);
void access_out_of_bounds(float arr[], int index);

int main() {
    // 定义一个浮点数组
    float arr[SIZE];

    // 初始化数组
    initialize_array(arr, SIZE);

    // 处理数组（不越界）
    process_array(arr, SIZE);

    // 越界访问
    printf("\nAttempting out-of-bounds access:\n");
    access_out_of_bounds(arr, SIZE);  // 越界访问，应该访问 arr[100]，但 arr 最大索引为 99

    return 0;
}

// 初始化数组的值
void initialize_array(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i * 1.1f;  // 给数组元素赋值
    }

    printf("Array initialized:\n");
    for (int i = 0; i < size; i++) {
        printf("arr[%d] = %.2f\n", i, arr[i]);
    }
}

// 处理数组中的元素（这里模拟一些复杂的数组操作）
void process_array(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        // 这里假设数组处理是基于某些复杂的规则
        if (arr[i] > 50.0f) {
            arr[i] *= 1.5f;  // 将大于 50 的元素乘以 1.5
        } else {
            arr[i] -= 1.0f;  // 将小于等于 50 的元素减去 1.0
        }
        printf("Processed arr[%d] = %.2f\n", i, arr[i]);
    }
}

// 模拟越界访问（这里故意尝试访问一个越界的元素）
void access_out_of_bounds(float arr[], int index) {


    // 越界访问，模拟访问 `arr[100]`，这会超出数组的实际范围
    printf("Accessing arr[] = %.2f\n",arr[SIZE]);
}
