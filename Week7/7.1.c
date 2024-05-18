#include <stdio.h>
#include <stdlib.h>

// Hàm tính khoảng cách trung bình giữa các giá trị trong mảng
double averageDistance(int arr[], int n) {
    if (n < 2) return 0.0;

    int sum = 0;
    for (int i = 1; i < n; ++i) {
        sum += abs(arr[i] - arr[i-1]);
    }
    return (double)sum / (n - 1);
}

// Hàm xóa các phần tử trùng nhau trong một mảng
int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;

    int temp[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        int k;
        for (k = 0; k < j; k++) {
            if (arr[i] == temp[k])
                break;
        }
        if (k == j)
            temp[j++] = arr[i];
    }
    for (int i = 0; i < j; i++) {
        arr[i] = temp[i];
    }
    return j;
}

// Hàm tìm mảng con có tổng bằng M
int findSubArrayWithSum(int arr[], int n, int M) {
    int currentSum = arr[0], start = 0;
    for (int i = 1; i <= n; i++) {
        while (currentSum > M && start < i-1) {
            currentSum = currentSum - arr[start];
            start++;
        }
        if (currentSum == M) {
            printf("Mang con voi tong bang %d la nhung phan tu %d and %d\n", M, start, i-1);
            return 1;
        }
        if (i < n)
            currentSum = currentSum + arr[i];
    }
    printf("No subarray with given sum found.\n");
    return 0;
}

// Hàm tìm dãy con toàn dương có tổng lớn nhất
int maxSubArraySum(int arr[], int n) {
    int maxSoFar = 0, maxEndingHere = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0)
            maxEndingHere += arr[i];
        else
            maxEndingHere = 0;
        if (maxSoFar < maxEndingHere)
            maxSoFar = maxEndingHere;
    }
    return maxSoFar;
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 2, 5, 6, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    // Tính khoảng cách trung bình giữa các giá trị trong mảng
    double avgDist = averageDistance(arr, n);
    printf("Khoang cach trung binh giua cac gia tri trong mang la: %f\n", avgDist);

    // Xóa các phần tử trùng nhau
    n = removeDuplicates(arr, n);
    printf("Xoa phan tu trung nhau: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // Tìm mảng con có tổng bằng M
    int M = 10;
    findSubArrayWithSum(arr, n, M);

    // Tìm dãy con toàn dương có tổng lớn nhất
    int maxSum = maxSubArraySum(arr, n);
    printf("Day con toan duong co tong lon nhat: %d\n", maxSum);

    return 0;
}
