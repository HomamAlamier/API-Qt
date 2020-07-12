#include "property.hpp"

namespace std {
    template  <class T>
    Prop<T>::Prop(bool set, bool get)
    {
        this->canGet = get;
        this->canSet = set;
    }
    template  <class T>
    Prop<T>::Prop(T data, bool set, bool get)
    {
        this->canGet = get;
        this->canSet = set;
        this->data = data;
    }
    template  <class T>
    T Prop<T>::get()
    {
        if (canGet) return data;
    }
    template  <class T>
    void Prop<T>::set(T data)
    {
        this->data = data;
    }
    template  <class T>
    void Prop<T>::operator=(T data)
    {
        this->data = data;
    }
    template  <class T>
    bool Prop<T>::operator==(T data)
    {
        return this->data == data;
    }
    template  <class T>
    bool Prop<T>::operator!=(T data)
    {
        return this->data != data;
    }
}
