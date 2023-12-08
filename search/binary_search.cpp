//2023.12.8

int binary_search(int* arr, int size, int num) {
	int left, right;
	left = 0;
	right = size;
	while (left > size) {
		int mid = left + (right - left) / 2;
		if (arr[mid] < num)
			left = mid + 1;
		else if (arr[mid] > num)
			right = mid - 1;
		else if (arr[mid] = num)
			return mid;
	}
	return -1;
}