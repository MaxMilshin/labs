#include <iostream>
#include <stdexcept>
#include <stdint.h>

namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
public:
	my_array();
	~my_array();

  	T const &  at(std::size_t index) const;
  	T & at(std::size_t index);
 	T const & operator[](std::size_t index) const noexcept;
 	T & operator[](std::size_t index) noexcept;

	bool empty() const;
	std::size_t size() const;

	void fill(T val);

private:
	T* data;
};



//__________________________________________________________________________________________________________
//____________________Implementation___________________________________________________________________________
//__________________________________________________________________________________________________________



template<typename T, std::size_t N>
my_array<T, N>::my_array() : data(new T[N]) {}

template<typename T, std::size_t N>
my_array<T, N>::~my_array() {
	delete [] data;
}

template<typename T, std::size_t N>
T const & my_array<T, N>::at(std::size_t index) const {
	if (index >= N)
		throw std::out_of_range("index out of range");	
	return data[index];
}

template<typename T, std::size_t N>
T & my_array<T, N>::at(std::size_t index) {
	if (index >= N)
		throw std::out_of_range("index out of range");
	return data[index];
}

template<typename T, std::size_t N>
T const & my_array<T, N>::operator[](std::size_t index) const noexcept {
	return data[index];
}

template<typename T, std::size_t N>
T & my_array<T, N>::operator[](std::size_t index) noexcept {
	return data[index];
}

template<typename T, std::size_t N>
std::size_t my_array<T, N>::size() const {
	return N;
}

template<typename T, std::size_t N>
bool my_array<T, N>::empty() const {
	return (size() == 0);
}

template<typename T, std::size_t N>
void my_array<T, N>::fill(T val) {
	for (std::size_t i = 0; i < N; i++) {
		data[i] = val;
	}
}


//__________________________________________________________________________________________________________
//____________________my_array<bool, N>_specialization__________________________________________________________________________
//__________________________________________________________________________________________________________



template<std::size_t N>
class my_array<bool, N> {
public:
	class bool_reference {
 	public:
 		bool_reference(std::size_t index, uint8_t &data) 
 			: index(index), data(data) {}
 		bool_reference() = default;

 		operator bool() {
 			return data & (1 << (index % 8));
 		}

 		bool operator=(bool value) {
 			if (value == true) {
 				data |= (1 << (index % 8));
 			}
 			else {
 				data &= ((1 << 8) - 1) ^ (1 << index);
 			}
 			return value;
 		}

 		bool_reference operator=(bool_reference ref) {
 			*this = (bool)ref;
 			return ref;
 		}

 	private:
 		std::size_t index;
 		uint8_t &data;
 	};

	my_array() : data(new uint8_t[(N + 7) / 8]) {}
	~my_array() {
		delete [] data;
	}


	bool operator[](std::size_t index) const noexcept {
 		return (data[index / 8] & (1 << (index % 8))) ? true : false;
 	}
	bool_reference operator[](std::size_t index) noexcept {
		return bool_reference(index % 8, data[index / 8]);
	}

 	bool at(std::size_t index) const {
 		if (index >= N)
			throw std::out_of_range("index out of range");
		return (*this)[index];
 	}
  	bool_reference at(std::size_t index) {
  		if (index >= N)
			throw std::out_of_range("index out of range");
		return (*this)[index];
  	}

 	void fill(bool value) {
 		uint8_t val = value ? ((1 << 8) - 1) : 0;
 		for (std::size_t i = 0; i < (N + 7) / 8; i++) {
			data[i] = val;
		}
 	}

 	bool empty() const {
 		return (size() == 0);
 	}
	std::size_t size() const {
		return N;
	}

private:
	uint8_t* data;
};

}
