#ifndef INTERVAL_H
#define INTERVAL_H

//мат интервал/отрезок left, right
struct interval {
    double left;   // лев граница
    double right;  // прав граница

    interval() : left(0), right(0) {}
    interval(double l, double r) : left(l), right(r) {}

    //проверка содержит ли интервал точку
    bool contains(double x) const {
        return x >= left && x <= right;
    }

    //проверка, пересекается ли с другим интервалом
    bool overlaps(const interval& other) const {
        return !(right < other.left || left > other.right);
    }

    //длина интервала
    double length() const {
        return right - left;
    }
};

#endif