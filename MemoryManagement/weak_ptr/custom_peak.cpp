#include <iostream>


class ControlBlock
{

public:

    int sharedCount;
    int weakCount;


    ControlBlock()
    {
        sharedCount=1;
        weakCount=0;
    }

};



template<typename T>
class SharedPtr;


template<typename T>
class WeakPtr
{

private:

    T* ptr;

    ControlBlock* control;


public:


    WeakPtr()
    {
        ptr=nullptr;
        control=nullptr;
    }



    WeakPtr(const SharedPtr<T>& sp)
    {

        ptr=sp.ptr;

        control=sp.control;

        control->weakCount++;

    }



    bool expired()
    {
        return control->sharedCount==0;
    }



    int use_count()
    {
        return control->sharedCount;
    }

};




template<typename T>
class SharedPtr
{

private:

    T* ptr;

    ControlBlock* control;


public:


    SharedPtr(T* p)
    {

        ptr=p;

        control=new ControlBlock();

    }



    ~SharedPtr()
    {

        control->sharedCount--;


        if(control->sharedCount==0)
        {

            delete ptr;


            if(control->weakCount==0)
                delete control;
        }

    }



    friend class WeakPtr<T>;

};




int main()
{

    SharedPtr<int> sp(new int(100));


    WeakPtr<int> wp(sp);



    std::cout
    <<"Shared Count : "
    <<wp.use_count()
    <<std::endl;



    std::cout
    <<"Expired : "
    <<wp.expired()
    <<std::endl;



    return 0;
}
