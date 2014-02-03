#ifndef SMART_POINTER_H
#define SMART_POINTER_H


template <typename T>

class SmartPointer {
public:
	//constructor
	SmartPointer(T* p=0): _ptr(p), _reference_count(new size_t){
		if(p)
			*_reference_count = 1; 
		else
			*_reference_count = 0; 
	}
	//copy constructor
	SmartPointer(const SmartPointer& src) {
		if(this!=&src) {
			_ptr = src._ptr;
			_reference_count = src._reference_count;
			(*_reference_count)++;
		}
	}
	//overload operator =
	SmartPointer& operator=(const SmartPointer& src) {
		if(_ptr==src._ptr) {
			return *this;
		}
		releaseCount();
		_ptr = src._ptr;
		_reference_count = src._reference_count;
		(*_reference_count)++;
		return *this;
	}

	//overload operator *
	T& operator*() {
		if(ptr) {
			return *_ptr;
		}
		//throw exception
	}
	//overload operator ->
	T* operator->() {
		if(ptr) {
			return _ptr;
		}
		//throw exception
	}
	//desconstructor
	~SmartPointer() {
		if (--(*_reference_count) == 0) {
            delete _ptr;
            delete _reference_count;
        }
	}
private:
	T *_ptr;
    size_t *_reference_count;
    
    void releaseCount() {
		if(_ptr) {
			(*_reference_count)--;
    		if((*_reference_count)==0) {
    			delete _ptr;
    			delete _reference_count;
    		}
		}
    }
};

#endif
