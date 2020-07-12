#ifndef PROPERTY_HPP
#define PROPERTY_HPP

namespace std {
template <class T>
    class Prop
    {
    private:
        T data;
        bool canSet;
        bool canGet;
    public:
        /*Prop(bool get = true, bool set = true);
        Prop(T data, bool get = true, bool set = true);
        void set(T data);
        T get();
        void operator =(T data);
        bool operator ==(T data);
        bool operator !=(T data);*/
        Prop(bool set = true, bool get = true)
        {
            this->canGet = get;
            this->canSet = set;
        }
        Prop(T data, bool set = true, bool get = true)
        {
            this->canGet = get;
            this->canSet = set;
            this->data = data;
        }
        T get()
        {
            if (canGet) return data;
            else return (T)0;
        }
        void set(T data)
        {
            this->data = data;
        }
        template  <class T>
        bool operator==(T data)
        {
            return this->data == data;
        }
        bool operator!=(T data)
        {
            return this->data != data;
        }
    };
}

#endif // PROPERTY_HPP
