#include <iostream>


template<typename T>
class UniquePtr
{

private:

    T* ptr;


public:

    explicit UniquePtr(T* p=nullptr)
        : ptr(p)
    {

    }


    ~UniquePtr()
    {
        delete ptr;
    }



    // Copy disabled

    UniquePtr(const UniquePtr&) = delete;


    UniquePtr& operator=(const UniquePtr&) = delete;



    // Move constructor

    UniquePtr(UniquePtr&& other)
    {
        ptr = other.ptr;

        other.ptr = nullptr;
    }



    // Move assignment

    UniquePtr& operator=(UniquePtr&& other)
    {

        if(this != &other)
        {
            delete ptr;

            ptr = other.ptr;

            other.ptr=nullptr;
        }


        return *this;
    }



    T& operator*()
    {
        return *ptr;
    }



    T* operator->()
    {
        return ptr;
    }



    T* get()
    {
        return ptr;
    }


    T* release()
    {
        T* temp = ptr;

        ptr=nullptr;

        return temp;
    }


    void reset(T* p=nullptr)
    {
        delete ptr;

        ptr=p;
    }

};



int main()
{

    UniquePtr<int> p1(new int(50));


    std::cout<<*p1<<std::endl;



    UniquePtr<int> p2 = std::move(p1);



    std::cout<<*p2<<std::endl;



    return 0;
}
