#include <iostream>
#include <chrono>
#include <random>
#include <cassert>
#include <stdlib.h>

template <typename T>
class MyVector {
private:
    T* _array;
    std::size_t _size;
    std::size_t _allocated_memory;

    void resize_memory(size_t new_size) {
        if (_array == nullptr) {
            _allocated_memory = 1;
            _size = 1;
            _array = new T[_allocated_memory];
        }
        if ((new_size * 2 > _allocated_memory) && (new_size <= _allocated_memory))
            return;

        size_t new_allocated_memory = new_size + new_size / 2;
        T* new_array = new T[new_allocated_memory];
        for (int i = 0; (i < _size) && (i < new_allocated_memory); i++)
            new_array[i] = _array[i];

        delete[] _array;
        _array = new_array;
        _allocated_memory = new_allocated_memory;
        new_array = nullptr;
    };
public:
    MyVector() {
        _allocated_memory = 0;
        _size = 0;
        _array = nullptr;
    };
    MyVector(std::size_t size)
    {
        _allocated_memory = size + size / 2;
        _array = new T[_allocated_memory];
        _size = size;
    };
    MyVector(std::size_t size, T default_value)
    {
        for (int i = 0; i < _size; i++)
            _array[i] = default_value;
    };
    ~MyVector() {
        delete[] _array;
    };

    T& operator[] (std::size_t idx) { // доступ по индексу
       
        if (idx < 0) {
            std::cout << "Error, idx<0" << std::endl;
            exit;
        }
        if (idx > _size) {
            std::cout << "Error,1 index>size Myvector" << std::endl << idx << std::endl;
            exit;
        }
        return _array[idx];
    };
    std::size_t size() { // размерность
        return _size;
    };
    std::size_t allocated_memory_size() {
        return _allocated_memory;
    };
    void resize(std::size_t new_size) { // изменить размер
        resize(new_size, T());
    };
    void resize(std::size_t new_size, T default_value)
    {
        std::size_t old_size = _size;
        resize_memory(new_size);
        for (int i = old_size; i < new_size; i++)
            _array[i] = default_value;
        _size = new_size;
    };
    bool empty() { // пуст ли контейнер
        return _size == 0;
    };
    void push_back(T new_element) { // ƒобавить в конец
        resize(_size + 1, new_element);
    };
    T pop_back() { // ”далить с конца
        resize(_size - 1);
        return _array[_size];
    };
    void insert(T new_element) { // добавить в начало
        insert(0, 1, new_element);
    };
    void insert(std::size_t start_index, std::size_t count_elements, T default_element) { // вставить n элементов начина€ с позиции start index
        std::size_t old_size = _size;
        resize(_size + count_elements); 
        for (int i = old_size - 1; i >= 0; i--) {
            _array[i + count_elements] = _array[i];
        }
        for (int i = 0; i < count_elements; i++) {
            _array[start_index + i] = default_element;
        }
    };
    T front() {// перва€ €чейка вектора
        assert(_size > 0);
        return _array[0];
    };
    T back() { // последн€€ €чейка вектора
        assert(_size > 0);
        return _array[_size - 1];
    };
    T erase(std::size_t idx) { // ”далить дин элемент вектора
        assert((idx >= 0) && (idx < _size) && (_size > 0));
        resize(_size - 1);
        T deleted_element = _array[idx];
        for (int i = 0; i < _size; i++)
        {
            if (i >= idx)
                _array[i] = _array[i + 1];
        }
        return deleted_element;
    };
    void clear() { // удалить все элементы вектора
        _size = 0;
        _allocated_memory = 0;
        delete[] _array;
        _array = nullptr;
    };
    void swap_elements(std::size_t first_ind, std::size_t second_ind) {
        T temp = _array[first_ind];
        _array[first_ind] = _array[second_ind];
        _array[second_ind] = temp;
    };
    void print_data() {
        for (int i = 0; i < _size; i++)
        {
            std::cout << _array[i] << " ";
        }
        std::cout << std::endl;
    };
};

int randint(int max_size)
{
    return std::rand() % max_size;
}

void generateTest(MyVector<int>& vec, std::size_t vector_size, int max_integer = 100)
{
    vec.clear();
    vec.resize(vector_size);

    int randi;
    for (int i = 0; i < vector_size; i++) {
        randi = randint(max_integer);
        vec[i] = randi;
    }
}

void stupid_sort(MyVector<int>& vec, std::size_t vector_size, int n = 0) {
    int temp,i,j,l=0;
    for (j = 0; j<vector_size;j++){
        for (i = 0; i < vector_size-1; i++) {
            if (vec[i] > vec[i + 1]) {
                
                temp = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = temp;
                l++;
            }
        }
    }
    if (n == 1) {
        std::cout << "Count perestan stupid sort (count elements " << vec.size() << ") " << l << std::endl;
    }
}
void stupid_sort_reverse(MyVector<int>& vec, std::size_t vector_size) {
    int n, i, j,l=0;
    for (j = 0; j < vector_size; j++) {
        for (i = 0; i < vector_size - 1; i++) {
            if (vec[i] < vec[i + 1]) {
                n = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = n;
                
            }
        }
    }
    
}



void quicksort(MyVector<int>& vector, int left, int right,int n=0) {
    int leftpoint=0, rightpoint=0, midpoint=0, piv=0;
    leftpoint = left;
    rightpoint = right;
    midpoint = left + (right - left) / 2;
    piv = vector[midpoint];
    int l = 0;
    
    int temp;
    while (leftpoint<right || rightpoint>left) {
        while (vector[leftpoint] < piv)
            leftpoint++;
        while (vector[rightpoint] > piv)
            rightpoint--;

        if (leftpoint <= rightpoint) {
            temp = vector[leftpoint];
            vector[leftpoint] = vector[rightpoint];
            vector[rightpoint] = temp;
            leftpoint++;
            rightpoint--;
            l++;
            
        }
        else {
            if (left < right)
                quicksort(vector, leftpoint, right);
            if (rightpoint > left)
                quicksort(vector, left, rightpoint);
            if (n == 1) {
                std::cout << "Count perestan quick sort (count elements " << vector.size() << ") " << l << std::endl;
            }
            return;
        }
    }
    
}



void quicksort_recursive(MyVector<int>& vector, int left, int right) {
    
    int temp,pivot=0,leftpoint=0,rightpoint=0;
    
    pivot = vector[right];
    leftpoint = left - 1;
    rightpoint = right;
    bool f = true;
    
    if (left < right) {
        while (f){
            while (vector[++leftpoint] > pivot) {
            }
            while (rightpoint > 0 && vector[--rightpoint] < pivot) {
            }
            if (leftpoint >= rightpoint) {
                f = false;
            }
            else {
                temp = vector[leftpoint];
                vector[leftpoint] = vector[rightpoint];
                vector[rightpoint] = temp;
            }
        }
       
        temp = vector[leftpoint];
        vector[leftpoint] = vector[right];
        vector[right] = temp;

        if (leftpoint>0){
        quicksort_recursive(vector, left, leftpoint-1);
        }
        quicksort_recursive(vector, leftpoint +1, right);
    }
}


void test_stupid_sort(int n,int k=0) {
    MyVector<int> vec_ideal;
    MyVector<int> vec_random;
    MyVector<int> vec_recursive;

    generateTest(vec_ideal, n);
    quicksort(vec_ideal, 0, n-1);
    generateTest(vec_random, n);
    generateTest(vec_recursive, n);
    quicksort_recursive(vec_recursive, 0, n-1);
  
    
    auto begin = std::chrono::steady_clock::now();
    stupid_sort(vec_ideal, n,k);
    auto end = std::chrono::steady_clock::now();
    auto time_ideal = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::cout << "Stupid sort ideal (count elements " << n << ") " << time_ideal.count() << std::endl<<std::endl;

    begin = std::chrono::steady_clock::now();
    stupid_sort(vec_recursive, n, k);
    end = std::chrono::steady_clock::now();
    auto time_recursive = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::cout << "Stupid sort recursive (count elements " << n << ") " << time_recursive.count() << std::endl << std::endl;

    begin = std::chrono::steady_clock::now();
    stupid_sort(vec_random, n,k);
    end = std::chrono::steady_clock::now();
    auto time_random = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::cout << "Stupid sort random (count elements " << n << ") " << time_random.count() << std::endl << std::endl;
    std::cout << std::endl;
    
}
void test_quicksort(int n,int k=0) {
    MyVector<int> vec_ideal;
    MyVector<int> vec_random;
    MyVector<int> vec_recursive;

    generateTest(vec_ideal, n);
    quicksort(vec_ideal, 0, n - 1);
    generateTest(vec_random, n);
    generateTest(vec_recursive, n);
    quicksort_recursive(vec_recursive, 0, n -1);

    auto begin = std::chrono::steady_clock::now();
    quicksort(vec_ideal,0, n-1,k);
    auto end = std::chrono::steady_clock::now();
    auto time_ideal = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::cout << "Quick sort ideal (count elements " << n << ") " << time_ideal.count() << std::endl << std::endl;

    begin = std::chrono::steady_clock::now();
    quicksort(vec_recursive, 0, n - 1, k);
    end = std::chrono::steady_clock::now();
    auto time_recursive = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::cout << "Quick sort recursive (count elements " << n << ") " << time_recursive.count() << std::endl << std::endl;

    begin = std::chrono::steady_clock::now();
    quicksort(vec_random,0, n-1,k);
    end = std::chrono::steady_clock::now();
    auto time_random = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::cout << "Quick sort random (count elements " << n << ") " << time_random.count() << std::endl << std::endl;
    std::cout << std::endl;

}

int main() {
   
    
    
    test_stupid_sort(100,1);
    test_stupid_sort(1000,1);
    test_stupid_sort(10000,1);
    //test_stupid_sort(20000);
    test_quicksort(100,1);
    test_quicksort(1000,1);
    test_quicksort(10000,1);
    //test_quicksort(20000);
    /*
    test_quicksort(50000);
    test_quicksort(100000);
    test_quicksort(200000);
    test_quicksort(1000000);
   */
   
}