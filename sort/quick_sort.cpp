//2023.12.10

#include<stdio.h>

void swap(int* nums, int i, int j) {
	int tmp = nums[i];
	nums[i] = nums[j];
	nums[j] = tmp;
}


int Partition(int* nums, int left, int right) {
	int i = left, j = right;
	//��nums[left]Ϊ��׼�ڱ�
	while (i < j) {
		while (i < j && nums[left] <= nums[j]) {//�ҵ��ұ߿�ʼ��һ��С�ڻ�׼
			j--;
		}
		while (i < j && nums[left] >= nums[i]) {//�ҵ���߿�ʼ��һ�����ڻ�׼
			i++;
		}
		swap(nums, i, j);
	}
	swap(nums, left, i);
	return i;
}

int median(int* nums, int left, int mid, int right) {
	if (nums[left] > nums[mid] ^ nums[left] > nums[right])
		return left;
	else if (nums[mid] > nums[left] ^ nums[left] > nums[right])
		return mid;
	else
		return mid;
}


void quick_sort(int* nums, int left, int right) {
	if (left >= right)
		return;
	int i = median(nums, left, (left + right) / 2, right);
	swap(nums, left, i);
	int partition = Partition(nums, left, right);
	quick_sort(nums, left, partition - 1);
	quick_sort(nums, partition + 1, right);
}

int main()
{
	int arr[] = { 7,6,1,11,4,8,9,3,2,0 };
	int size = sizeof(arr) / sizeof(arr[0]);
	quick_sort(arr, 0, size - 1);
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}

}