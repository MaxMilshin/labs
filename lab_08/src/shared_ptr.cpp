#include "shared_ptr.hpp"

shared_ptr::shared_ptr(Matrix* obj) {
	storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
	storage_ = other.storage_;
	storage_->incr();
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
	std::swap(storage_, other.storage_);
	return *this;
}

shared_ptr::~shared_ptr() {
	storage_->decr();
}

Matrix* shared_ptr::ptr() const {
	return storage_->getObject();
}

bool shared_ptr::isNull() const {
	return (storage_->getObject() == nullptr);
}

void shared_ptr::reset(Matrix* obj) {
	storage_->decr();
	storage_ = new Storage(obj);
}

Matrix* shared_ptr::operator->() const {
	return ptr();
}

Matrix& shared_ptr::operator*() const {
	return *(ptr());
}



//------------------------------------------------------------------------



shared_ptr::Storage::Storage(Matrix* mtx) {
    data_ = mtx;
    incr();
}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ref_count_++;    
}

void shared_ptr::Storage::decr() {
    if (--ref_count_ == 0)
        delete data_;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}