#include <iostream>


class MyClass2 {
public:
    explicit MyClass2 (int i)
    :data_(i) {};
    template <typename T> T getAs () const;
private:
    int data_;
};

template<typename T>
T MyClass2::getAs() const {
    return {};
}

template<>
std::string MyClass2::getAs <std::string> () const{
    return "String";
}


template <typename T>
class MyClass {
public:
    void set (const T& t);
    const T& get () const;

    template <typename P> void print (const P& p);
    //Not possible to specialize template member function of templated class without also
    //specializing class
    template <typename P> P getAs () const {return helper ((P*)0);};
private:
    template <typename P> P helper (P*) const {return P{};}

    bool helper (bool*) const {return false;};
    std::string helper (std::string*) {return std::to_string(data_);}

    T data_;
};

template<typename T>
const T &MyClass<T>::get() const {
    return data_;
}

template<typename T>
void MyClass<T>::set(const T &t) {
    data_=t;
}

template<typename T>
template<typename P>
void MyClass<T>::print(const P &p) {
    std::cout<<p<<data_<<std::endl;
}

//Can specialise only if both class and function are specialized
template <>
template <>
void MyClass<int>::print(const std::string& s) {
    std::cout<<"Int string"<<std::endl;
}


int main() {
    MyClass <int> i;
    i.set (2);
    std::cout<<i.get ()<<std::endl;
    i.print(false); 
    i.print(std::string ("Hello"));
    std::cout<<i.getAs<std::string> ()<<std::endl;

    MyClass2 c2 (2);
    std::cout<<c2.getAs<std::string>()<<std::endl;
    return 0;
}
