#pragma once

/**
 * @file half_adder.hpp
 * This file is the cycle accurate equivalent to half_adder.vhd
 */

#include <iostream>
#include <ostream>
#include <vector>

#include "VHDLetor.hpp"

class half_adder : public VHDLComponent
{
    public:
        Signal signals[4] = {
            Signal("i_a", SignalType::input, SignalImpl::wire, {{TriState::X}}),
            Signal("i_b", SignalType::input, SignalImpl::wire, {{TriState::X}}),
            Signal("o_sum", SignalType::output, SignalImpl::wire, {{TriState::X}}),
            Signal("o_carry", SignalType::output, SignalImpl::wire, {{TriState::X}})
        };

        Signal* getSignals() {
            return signals;
        }
        size_t getSignalsCount() {
            return 4;
        }
        void eval_sequential() {

        }
        void eval_concurrent()  {
            // Concurrent code below:
            signals[2].value = sig_xor(signals[0].value, signals[1].value);
            signals[3].value = sig_and(signals[0].value, signals[1].value);
            // End of concurrent code
        }
};