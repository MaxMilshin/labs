#include <iostream>
#include <cassert>

#include "my_vector.hpp"
#include "my_vector_impl.hpp"

namespace product {

class Product {
public:
    Product(const char* name, int quantity, double price)
    : quantity_(quantity), price_(price) {
    	name_ = new char[strlen(name)];
    	strcpy(name_, name);
    }

    Product(const Product & other)
    : quantity_(other.quantity_), price_(other.price_)  {
    	name_ = new char[strlen(other.name_)];
    	strcpy(name_, other.name_);
    }

    ~Product() {
    	delete [] name_;
    }

    friend std::ostream& operator<< (std::ostream& out, const Product& p) {
    	out << p.name_ << " " << p.quantity_ << " " << p.price_;
    	return out;
    }

private:
    char *name_;  // Указатель владеет C-style строкой, на которую указывает.
    int quantity_;
    double price_;
};

void print(const containers::my_vector<Product>& v) {
    std::cout << v << std::endl;
}

}  // namespace product

template<typename T>
void test_my_vector(T t1, T t2) {
    // constructor check
    containers::my_vector<T> v;
    assert(v.size() == 0 && v.capacity() == 2); 
    
    // push_back && pop_back check 
    v.push_back(t1); 
    v.push_back(t2);
    assert(v.size() == 2 && v.capacity() == 2); 
    v.pop_back();
    assert(v.size() == 1 && v.capacity() == 2);
    v.push_back(t1);
    assert(v.size() == 2 && v.capacity() == 2);

    // reserve check
    v.push_back(t2);
    assert(v.size() == 3 && v.capacity() == 4); 
    v.reserve(4);
    assert(v.capacity() == 4);
    v.reserve(5);
    assert(v.capacity() == 8); 

    // copy constructor check
    containers::my_vector<T> w(v);
    assert(v.size() == w.size() && v.capacity() == w.capacity());

    // clear && empty check
    v.clear();
    assert(v.empty() && v.size() == 0 && v.capacity() == 8);

    // operator == check
    v = w;
    assert(v.size() == w.size() && v.capacity() == w.capacity());
    
    std::cout << "test_my_vector has passed!" << std::endl;
}

template<typename T>
void test_my_vector_default_constructible(T t1, T t2) {
    // default constuctable constructor check 
    containers::my_vector<T> v(5);
    assert(v.size() == 5 && v.capacity() == 8);

    // resize check
    v.clear();
    assert(v.empty() && v.size() == 0 && v.capacity() == 8);
    v.push_back(t1);
    v.push_back(t2);
    assert(v.size() == 2 && v.capacity() == 8);
    v.resize(0);
    assert(v.empty() && v.size() == 0 && v.capacity() == 8);
    v.resize(13);
    assert(v.size() == 13 && v.capacity() == 16);

    std::cout << "test_my_vector_default_constructible has passed!" << std::endl;
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
    test_my_vector_default_constructible<int>(5, 10);
    return 0;
}