#ifndef OPTION_H
#define OPTION_H

//не выбрасываем искл, а возвращаем спец.контейнер
template<class T>
class option {
private:
    T value_; //всегда сущ., но мб none
    bool has_value_; //флаг валидности
public:
    option() : has_value_(false) {}
    explicit option(const T& val) : value_(val), has_value_(true) {} //const& 

    bool is_some() const { return has_value_; }
    bool is_none() const { return !has_value_; }
    const T& value() const { return value_; } //const& для безопасности

    static option<T> none() { return option<T>(); }
    static option<T> some(const T& val) { return option<T>(val); } //const&
};

#endif