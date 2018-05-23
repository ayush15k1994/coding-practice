/*
	BINARY HEAP:
		A Complete Binary Tree
		Either Min Heap or Max Heap 

		Heap Operations: -getMin(), -extractMin(), -heapify(), -decreaseKey(), -insert(), -delete()
*/

#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<map>
#include<cmath>
#include<climits>

#define ld long int
#define lld long long int
#define uld unsigned long int
#define ulld unsigned long long int

#define HEAD 1
#define LEFT(i) (2*i)
#define RIGHT(i) (2*i+1)
#define PARENT(i) (int(i/2))

using namespace std;

template <class T>
void printVector(vector<T> arr, char separator=' '){
	for(ld i=1; i<arr.size(); ++i){
		cout<<arr[i]<<separator;
	}
	cout<<endl;
}

class Heap {	// This is a MinHeap
private:
	int heap[10000];
	int nodes;	// size of heap

public:
	Heap(){
		nodes = 0;
	}

	int num_nodes(){
		return nodes;
	}

	int height(){
		if (nodes<=0){
			return -1;
		}
		return floor(log2(nodes));
	}

	int get_node(int i){
		if(i>nodes || i<HEAD)
			return -1;
		return heap[i];
	}

	int left_child(int i){
		int left = LEFT(i);
		if (left>nodes)
		{
			return -1;
		}

		else
			return heap[left];
	}

	int right_child(int i){
		int right = RIGHT(i);
		if (right>nodes)
		{
			return -1;
		}

		else
			return heap[right];
	}	

	int parent(int i){
		int parent_index = PARENT(i);
		if (parent_index < HEAD)
		{
			return -1;
		}
		return parent_index;
	}

	int get_parent(int i){
		int parent_index = PARENT(i);
		if (parent_index < HEAD)
		{
			return -1;
		}
		return parent_index;
	}

//		HEAP OPERATIONS

	int get_min(){
		if (nodes<1)
		{
			return -1;
		}
		return heap[HEAD];
	}

	void insert(int val){
		nodes++;
		heap[nodes] = val;

		int i=nodes, temp;
		while(i>1 && heap[parent(i)]>heap[i]){
			temp = heap[i];
			heap[i]=heap[parent(i)];
			heap[parent(i)] = temp;

			i=parent(i);
		}
	}

	void decreaseKey(int index, int new_val){
		if (heap[index] < new_val){
			return;
		}
		heap[index] = new_val;
		int temp;
		while(index>1 && heap[parent(index)]>heap[index]){
			temp = heap[index];
			heap[index] = heap[parent(index)];
			heap[parent(index)] = temp;

			index = parent(index);
		}
	}

	void minHeapify(int index){
		int smallest = index;
		int l = LEFT(index), r = RIGHT(index);

		if(l<=nodes && heap[l]<heap[smallest])
			smallest = l;
		if(r<=nodes && heap[r]<heap[smallest])
			smallest = r;

		if(smallest!=index){
			swap(heap[smallest], heap[index]);
			minHeapify(smallest);
		}
	}

	int extractMin(){
		if(nodes<=0){
			return -1;
		}

		if(nodes==1){
			nodes = 0;
			return heap[HEAD];
		}
		
		int tmp = heap[HEAD];
		swap(heap[HEAD], heap[nodes]);
		nodes--;
		minHeapify(HEAD);
		return tmp;
	}

	int deleteKey(int index){
		int temp = heap[index];
		decreaseKey(index, INT_MIN);
		extractMin();
		return temp;
	}

};

void print_bfs_heap(Heap heap){
	int h = heap.height(), num = heap.num_nodes();
	int i=1,j=1,size=1;
	
	if(num<=0){
		cout<<"Heap is Empty.\n";
		return;
	}

	while(i<=num){
		for(j=i; j<i+size && j<=num;++j){
			cout<<heap.get_node(j)<<" ";
		}
		cout<<"\n";
		i=i+size;
		size = size*2;
	}
}

void print_bfs_heap(vector<int> heap){
	int num = heap.size();
	
	int i=1,j=1,size=1;
	
	if(num<=0){
		cout<<"Heap is Empty.\n";
		return;
	}

	while(i<num){
		for(j=i; j<i+size && j<num;++j){
			cout<<heap[j]<<" ";
		}
		cout<<"\n";
		i=i+size;
		size = size*2;
	}
}

// For Max-Heapify in bottom-up way
void maxHeapify(vector<int> &v, int size, int index){

	if (size==0 || index<1){
		return;
	}

	int largest = index;
	int l = LEFT(index), r = RIGHT(index);

	if(l<size && v[l]>v[largest])
		largest = l;
	if(r<size && v[r]>v[largest])
		largest = r;

	if(largest!=index){
		swap(v[largest], v[index]);
		maxHeapify(v, size, largest);
	}
}

// Method required for Heapsort - Build MaxHeap from input array for ascending sort
vector<int> build_heap(vector<int> a){
	for(int i = a.size()/2 - 1; i>=1; --i){
		maxHeapify(a, a.size(), i);	
	}

	cout<<"\nHeapified array: \n";
	print_bfs_heap(a);

	for(int i=a.size()-1; i>=1; --i){
		/*
			Swap Max root with the last element
			Reduce the size of heap and heapify
		*/
		swap(a[1], a[i]);
		maxHeapify(a, i, 1);	
	}

	cout<<"\nSorted Array: ";
	printVector(a);

	return a;
}

int main(){
	int a[16] = {-1,10,1,9,3,5,19,15,7,20,13,17,16,11,2,4};
	vector<int> v = vector<int>(a, a+16);
	
	print_bfs_heap(v);

	build_heap(v);

	return 0;
}