#ifndef PIECEWISE_FUNCTION_H
#define PIECEWISE_FUNCTION_H

#include "sequence.h"
#include "segment.h"
#include "array_sequence.h"
#include <cmath>

class piecewise_function {
protected:
    sequence<segment>* segments_;
    virtual piecewise_function* instance() = 0;

public:
    piecewise_function() : segments_(new mutable_array_sequence<segment>()) {}
    piecewise_function(sequence<segment>* segs) : segments_(segs) {}
    piecewise_function(const piecewise_function& other) : segments_(other.segments_ ? other.segments_->clone() : nullptr) {}
    virtual ~piecewise_function() {
        delete segments_;
    }

    double evaluate(double x) const {
        for (int i = 0; i < segments_->get_length(); ++i) {
            segment seg = segments_->get(i);
            if (x >= seg.start_x && x <= seg.end_x) return seg.evaluate(x);
        }
        throw index_out_of_range_exception("x out of function domain");
    }

    bool is_continuous(double epsilon = 1e-9) const {
        if (segments_->get_length() <= 1) return true;
        for (int i = 0; i < segments_->get_length() - 1; ++i) {
            segment curr = segments_->get(i);
            segment next = segments_->get(i + 1);
            if (std::abs(curr.evaluate(curr.end_x) - next.evaluate(next.start_x)) > epsilon) return false;
        }
        return true;
    }

    bool is_monotonic() const {
        if (segments_->get_length() <= 1) return true;
        bool inc = true, dec = true;
        for (int i = 0; i < segments_->get_length(); ++i) {
            if (segments_->get(i).k < 0) inc = false;
            if (segments_->get(i).k > 0) dec = false;
        }
        if (!inc && !dec) return false;
        for (int i = 0; i < segments_->get_length() - 1; ++i) {
            segment curr = segments_->get(i);
            segment next = segments_->get(i + 1);
            if (inc && curr.evaluate(curr.end_x) > next.evaluate(next.start_x)) return false;
            if (dec && curr.evaluate(curr.end_x) < next.evaluate(next.start_x)) return false;
        }
        return true;
    }

    virtual piecewise_function* redefine_on_interval(double start, double end, double k, double m) = 0;
    virtual piecewise_function* add_segment(double start, double end, double k, double m) = 0;
    virtual piecewise_function* remove_segment(int index) = 0;
    virtual piecewise_function* concat(const piecewise_function& other) = 0;

    int get_segment_count() const { return segments_ ? segments_->get_length() : 0; }
    segment get_segment(int index) const { return segments_->get(index); }
    sequence<segment>* get_segments() const { return segments_; }

    virtual piecewise_function* clone() const = 0;
};

#endif