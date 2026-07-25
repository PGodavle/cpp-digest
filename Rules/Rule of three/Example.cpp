class MyString {
    char* data;

public:
    MyString(const char* s) {
        data = new char[strlen(s)+1];
        strcpy(data, s);
    }

    ~MyString() {
        delete[] data;
    }

    MyString(const MyString& other) {
        data = new char[strlen(other.data)+1];
        strcpy(data, other.data);
    }

    MyString& operator=(const MyString& other) {
        if(this != &other) {
            delete[] data;

            data = new char[strlen(other.data)+1];
            strcpy(data, other.data);
        }

        return *this;
    }
};
