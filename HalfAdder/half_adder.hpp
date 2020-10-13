#pragma once

/**
 * @file half_adder.hpp
 * This file is the cycle accurate equivalent to half_adder.vhd
 */

#include <iostream>
#include <ostream>
#include <vector>

#include "../include/VHDLetor.hpp"

class half_adder : public hdl::VHDLComponent
{
    public:
        hdl::Signal signals[4] = {
            hdl::Signal("i_a", hdl::SignalType::input, hdl::SignalImpl::wire, {{hdl::TriState::X}}),
            hdl::Signal("i_b", hdl::SignalType::input, hdl::SignalImpl::wire, {{hdl::TriState::X}}),
            hdl::Signal("o_sum", hdl::SignalType::output, hdl::SignalImpl::wire, {{hdl::TriState::X}}),
            hdl::Signal("o_carry", hdl::SignalType::output, hdl::SignalImpl::wire, {{hdl::TriState::X}})
        };

        hdl::Signal* getSignals() {
            return signals;
        }
        size_t getSignalsCount() {
            return 4;
        }
        void eval_sequential() {

        }
        void eval_concurrent()  {
            // Concurrent code below:
            signals[2].value = hdl::sig_xor(signals[0].value, signals[1].value);
            signals[3].value = hdl::sig_and(signals[0].value, signals[1].value);
            // End of concurrent code
        }
};