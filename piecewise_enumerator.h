#ifndef PIECEWISE_ENUMERATOR_H
#define PIECEWISE_ENUMERATOR_H

#include "segment.h"
#include "sequence.h"

class piecewise_enumerator {
private:
    sequence<segment>* segments_;
    int index_;

public:
    piecewise_enumerator(sequence<segment>* segs) : segments_(segs), index_(-1) {}

    bool move_next() {
        index_++;
        return index_ < segments_->get_length();
    }

    segment current() const {
        if (index_ < 0 || index_ >= segments_->get_length()) {
            throw index_out_of_range_exception("enumerator out of range");
        }
        return segments_->get(index_);
    }

    void reset() {
        index_ = -1;
    }
};

#endif