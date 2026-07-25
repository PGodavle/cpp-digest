#include <iostream>


template<typename T>
class SharedPtr
{

private:

    T* ptr;

    int* count;



public:


    SharedPtr(T* p=nullptr)
    {
        ptr=p;

        count=new int(1);
    }



    // Copy constructor

    SharedPtr(const SharedPtr& other)
    {

        ptr=other.ptr;

        count=other.count;


        (*count)++;

    }



    // Assignment

    SharedPtr& operator=(const SharedPtr& other)
    {

        if(this!=&other)
        {

            release();


            ptr=other.ptr;

            count=other.count;


            (*count)++;
        }


        return *this;
    }




    void release()
    {

        (*count)--;


        if(*count==0)
        {
            delete ptr;

            delete count;

            std::cout<<"Memory deleted\n";
        }

    }



    ~SharedPtr()
    {
        release();
    }



    int use_count()
    {
        return *count;
    }



    T& operator*()
    {
        return *ptr;
    }


    T* operator->()
    {
        return ptr;
    }

};



int main()
{

    SharedPtr<int> p1(new int(100));


    std::cout<<"Count : "
             <<p1.use_count()
             <<std::endl;



    {

        SharedPtr<int> p2=p1;


        std::cout<<"Count : "
                 <<p1.use_count()
                 <<std::endl;


        std::cout<<*p2<<std::endl;

    }



    std::cout<<"Count : "
             <<p1.use_count()
             <<std::endl;


    return 0;
}
