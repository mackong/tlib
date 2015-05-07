#include <stdio.h>
#include <limits.h>

static void swap(int arr[], int i, int j)
{
	int tmp;

	tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

static void reverse(int arr[], int start, int end)
{
	while (start <= end) {
		swap(arr, start, end);
		start++;
		end--;
	}
}

static void print_arr(int arr[], int len)
{
	int i;
	for (i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

static void perm(int arr[], int start, int end)
{
	int i;

	if (end == start) {
		print_arr(arr, end + 1);
		return;
	}


	for (i = start; i <= end; i++) {
		swap(arr, start, i);
		perm(arr, start + 1, end);
		swap(arr, i, start);
	}
}

void permutation(int arr[], int len)
{
	perm(arr, 0, len - 1);
}

void permutation2(int arr[], int len)
{
	int i, j, min_r, min_i;

	print_arr(arr, len);

	while (1) {
		j = -1;

		for (i = len - 1; i > 0; i--) {
			if (arr[i - 1] < arr[i]) {
				j = i - 1;
				break;
			}
		}

		if (j == -1) {
			break;
		}

		min_r = INT_MAX;

		for (i = j + 1; i < len; i++) {
			if (arr[i] > arr[j] && arr[i] < min_r) {
				min_r = arr[i];
				min_i = i;
			}
		}

		swap(arr, j, min_i);

		reverse(arr, j + 1, len - 1);

		print_arr(arr, len);
	}
}
