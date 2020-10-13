#pragma once

/**
 * @file <<<ComponentName>>>.hpp
 * This file is the cycle accurate equivalent to <<<ComponentName>>>.vhd
 */

#include <iostream>
#include <ostream>
#include <vector>

#include "<<<VHDLetorDirectory>>>/include/VHDLetor.hpp"

class <<<ComponentName>>> : public hdl::VHDLComponent
{
    public:
        hdl::Signal signals[<<<SignalsCounts>>>] = {
            <<<Signals>>>
        };

        hdl::Signal* getSignals() {
            return signals;
        }
        size_t getSignalsCount() {
            return <<<SignalsCounts>>>;
        }
        void eval_sequential() {
            <<<SequentialCode>>>
        }
        void eval_concurrent()  {
            <<<ConcurrentCode>>>
        }
};
