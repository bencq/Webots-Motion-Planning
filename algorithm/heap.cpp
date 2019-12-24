#include<iostream>
using namespace std;
template<typename T>
class MaxHeap
{
	T* head;
	int size;
	int maxSize;
	bool isLeaf(int pos)
	{
		if(pos >= size / 2 && pos < size)
		{
			return 1;
		}
		return 0;
	}
	int leftChild(int pos)
	{
		return 2 * pos + 1;
	}
	int rightChild(int pos)
	{
		return 2 * pos + 2;
	}
	int parent(int pos)
	{
		return (pos - 1) / 2;
	}
	void siftDown(int pos)
	{
		while(!isLeaf(pos))
		{
			int bigger = leftChild(pos);
			int rc = rightChild(pos);
			if(rc < size)
			{
				if(head[rc] > head[bigger])
				{
					bigger = rc;
				}
			}
			if(head[pos] >= head[bigger])
			{
				return;
			}
			swap(head[pos],head[bigger]);
			pos = bigger;
		}
	}
	void buildHeap()
	{
		for(int i = parent(size - 1);i >= 0;--i)
		{
			siftDown(i);
		}
	}
	public:
		MaxHeap(T* head,int size,int maxSize)
		{
			this->head = head;
			this->size = size;
			this->maxSize = maxSize;
			buildHeap();
		}
		~MaxHeap()
		{
			this->head = NULL;
			this->size = 0;
			this->maxSize = 0;
		}
		bool insert(const T& elem)
		{
			if(size >= maxSize)
			{
				return 0;
			}
			head[size] = elem;
			int pos = size;
			++size;
			while(pos > 0)
			{
				if(head[pos] > head[parent(pos)])
				{
					swap(head[pos],head[parent(pos)]);
					pos = parent(pos);
				}
				else
				{
					break;
				}
			}
			return 1;
		}
		bool removeMax(T& elem)
		{
			if(size <= 0)
			{
				return 0;
			}
			elem = head[0];
			swap(head[0],head[--size]);
			if(size > 0)
			{
				siftDown(0);
			}
			return 1;
		}
        bool removeMax()
		{
			if(size <= 0)
			{
				return 0;
			}
			swap(head[0],head[--size]);
			if(size > 0)
			{
				siftDown(0);
			}
			return 1;
		}
		int getSize()
		{
			return size;
		}
};
template<typename T>
class MinHeap
{
    public:
	T* head;
	int size;
	int maxSize;
	bool isLeaf(int pos)
	{
		if(pos >= size / 2 && pos < size)
		{
			return 1;
		}
		return 0;
	}
	int leftChild(int pos)
	{
		return 2 * pos + 1;
	}
	int rightChild(int pos)
	{
		return 2 * pos + 2;
	}
	int parent(int pos)
	{
		return (pos - 1) / 2;
	}
	void siftDown(int pos)
	{
		while(!isLeaf(pos))
		{
			int smaller = leftChild(pos);
			int rc = rightChild(pos);
			if(rc < size)
			{
				if(head[rc] < head[smaller])
				{
					smaller = rc;
				}
			}
			if(head[pos] <= head[smaller])
			{
				return;
			}
			swap(head[pos],head[smaller]);
			pos = smaller;
		}
	}
	void buildHeap()
	{
		for(int i = parent(size - 1);i >= 0;--i)
		{
			siftDown(i);
		}
	}
	public:
		MinHeap(T* head,int size,int maxSize)
		{
			this->head = head;
			this->size = size;
			this->maxSize = maxSize;
			buildHeap();
		}
		~MinHeap()
		{
			this->head = NULL;
			this->size = 0;
			this->maxSize = 0;
		}
		bool insert(const T& elem)
		{
			if(size >= maxSize)
			{
				return 0;
			}
			head[size] = elem;
			int pos = size;
			++size;
			while(pos > 0)
			{
				if(head[pos] < head[parent(pos)])
				{
					swap(head[pos],head[parent(pos)]);
					pos = parent(pos);
				}
				else
				{
					break;
				}
			}
			return 1;
		}
		bool removeMin(T& elem)
		{
			if(size <= 0)
			{
				return 0;
			}
			elem = head[0];
			swap(head[0],head[--size]);
			if(size > 0)
			{
				siftDown(0);
			}
			return 1;
		}
        bool removeMin()
		{
			if(size <= 0)
			{
				return 0;
			}
			swap(head[0],head[--size]);
			if(size > 0)
			{
				siftDown(0);
			}
			return 1;
		}
		int getSize()
		{
			return size;
		}
};
/*const int maxn = 1000;
int arr[maxn];
int main()
{
	int num;
	int i = 0;
	while(cin >> num && num >= 0)
	{
		arr[i++] = num;
	}
	MinHeap<int> heap(arr,i,maxn);
	for(int i = 0;i < heap.getSize();++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	while(cin >> num && num >= 0)
	{
		heap.insert(num);
	}
	for(int i = 0;i < heap.getSize();++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	while(cin >> num && num >= 0)
	{
		heap.removeMin(num);
		cout << num << "removed" << endl;
	}
	for(int i = 0;i < heap.getSize();++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}*/
