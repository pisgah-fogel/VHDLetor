#pragma once

/**
 * @file half_adder.hpp
 * This file is the cycle accurate equivalent to half_adder.vhd
 */

#include <iostream>
#include <ostream>
#include <vector>

#include "../../include/VHDLetor.hpp"

#define SIGNALS_NUMBER 8

// For lisibility and performance index are here
#define i_a 0
#define i_b 1
#define i_carry 2
#define o_sum 3
#define o_carry 4
#define w_wire_1 5
#define w_wire_2 6
#define w_wire_3 7

class full_adder : public hdl::VHDLComponent
{
    public:
        hdl::Signal signals[SIGNALS_NUMBER] = {
            hdl::Signal("i_a", hdl::SignalType::input, hdl::SignalImpl::wire, {{hdl::TriState::X}}),
            hdl::Signal("i_b", hdl::SignalType::input, hdl::SignalImpl::wire, {{hdl::TriState::X}}),
            hdl::Signal("i_carry", hdl::SignalType::input, hdl::SignalImpl::wire, {{hdl::TriState::X}}),
            hdl::Signal("o_sum", hdl::SignalType::output, hdl::SignalImpl::wire, {{hdl::TriState::X}}),
            hdl::Signal("o_carry", hdl::SignalType::output, hdl::SignalImpl::wire, {{hdl::TriState::X}}),
            hdl::Signal("w_wire_1", hdl::SignalType::local, hdl::SignalImpl::wire, {{hdl::TriState::X}}),
            hdl::Signal("w_wire_2", hdl::SignalType::local, hdl::SignalImpl::wire, {{hdl::TriState::X}}),
            hdl::Signal("w_wire_3", hdl::SignalType::local, hdl::SignalImpl::wire, {{hdl::TriState::X}})
        };
        hdl::SignalValue savedSignals[SIGNALS_NUMBER];

        full_adder(size_t instance_num) {
            std::string name = "full_adder_";
            name.append(std::to_string(instance_num));
            hdl::SimMaster::getInstance()->registerInstance(name, this);
        }

        hdl::Signal* getSignals() {
            return signals;
        }
        hdl::SignalValue* getSavedSignals() {
            return savedSignals;
        }
        size_t getSignalsCount() {
            return SIGNALS_NUMBER;
        }
        void eval_sequential() {

        }
        void eval_concurrent()  {
            // Concurrent code below:
            signals[w_wire_1].value = hdl::sig_xor(signals[i_a].value, signals[i_b].value);
            signals[w_wire_2].value = hdl::sig_and(signals[w_wire_1].value, signals[i_carry].value);
            signals[w_wire_3].value = hdl::sig_and(signals[i_a].value, signals[i_b].value);

            signals[o_sum].value = hdl::sig_xor(signals[w_wire_1].value, signals[i_carry].value);
            signals[o_carry].value = hdl::sig_or(signals[w_wire_2].value, signals[w_wire_3].value);
            // End of concurrent code
        }
};