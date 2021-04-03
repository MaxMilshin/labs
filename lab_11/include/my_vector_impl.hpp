namespace containers {

template<typename T>
std::size_t my_vector<T>::new_capacity(std::size_t n) {
	std::size_t new_capacity_ = 1;
	for (; new_capacity_ < n; new_capacity_ *= 2);
	return new_capacity_; 
}

template<typename T>
my_vector<T>::my_vector() : capacity_(2), size_(0) {
	array_ = reinterpret_cast<T*>(new char[capacity_ * sizeof(T)]);
}

template<typename T>
my_vector<T>::my_vector(std::size_t n) 
: capacity_(new_capacity(n)), size_(n) {
	array_ = reinterpret_cast<T*>(new char[capacity_ * sizeof(T)]);
	for (size_t i = 0; i < n; i++) {
		new(&array_[i]) T();
	}
}

template<typename T>
my_vector<T>::my_vector(const my_vector& other) 
: capacity_(other.capacity_), size_(other.size_) {
	array_ = reinterpret_cast<T*>(new char[capacity_ * sizeof(T)]);	
	for (std::size_t i = 0; i < size_; i++) {
		new(&array_[i]) T(other[i]);
	}
}

template<typename T>
my_vector<T> my_vector<T>::operator=(my_vector other) {
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
	std::swap(array_, other.array_);
	return *this;
}

template<typename T>
my_vector<T>::~my_vector() {
	for (std::size_t i = 0; i < size_; i++) {
		array_[i].~T();
	}
	delete [] reinterpret_cast<char*>(array_);
}


template<typename T>
std::size_t my_vector<T>::size() const {
	return size_;
}

template<typename T>
std::size_t my_vector<T>::capacity() const {
	return capacity_;
}
   
template<typename T> 
bool my_vector<T>::empty() const {
	return (size_ == 0);
}


template<typename T>
void my_vector<T>::resize(std::size_t n) {
	(n >= size_) ? resize_up(n) : resize_down(n);
}

template<typename T>
void my_vector<T>::resize_up(std::size_t n) {
	reserve(n);
	for (std::size_t i = size_; i < n; i++) {
		new(&array_[i]) T();
	}
	size_ = n;
}

template<typename T>
void my_vector<T>::resize_down(std::size_t n) {
	for (std::size_t i = n; i < size_; i++) {
		array_[i].~T();
	}
	size_ = n;
}
    
template<typename T>
void my_vector<T>::reserve(std::size_t n) {
	if (capacity_ >= n)
		return;
	capacity_ = new_capacity(n);

	T* temp_array = reinterpret_cast<T*> (new char[capacity_ * sizeof(T)]);
	for (std::size_t i = 0; i < size_; i++) {
		new(&temp_array[i]) T(array_[i]);
		array_[i].~T();
	}
	delete [] reinterpret_cast<char*>(array_);
	array_ = temp_array;
}


template<typename T>
void my_vector<T>::push_back(T t) {
	reserve(size_ + 1);
	new(&array_[size_++]) T(t);
}

template<typename T>
void my_vector<T>::pop_back() {
	array_[--size_].~T();
}

template<typename T>
void my_vector<T>::clear() {
	resize_down(0);
}


template<typename T>
T my_vector<T>::operator[](std::size_t index) const {
	return array_[index];
}

template<typename T>
T& my_vector<T>::operator[](std::size_t index) {
	return array_[index];
}

template<typename U>
std::ostream& operator<< (std::ostream& out, const my_vector<U>& v) {
	for (size_t i = 0; i < v.size_; i++) {
		out << v.array_[i] << " ";
	}
	return out;
}

}