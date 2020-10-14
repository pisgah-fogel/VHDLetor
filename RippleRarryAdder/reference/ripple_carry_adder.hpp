#pragma once

/**
 * @file half_adder.hpp
 * This file is the cycle accurate equivalent to half_adder.vhd
 */

#include <iostream>
#include <ostream>
#include <vector>

#include "../../include/VHDLetor.hpp"
#include "full_adder.hpp"

#define SIGNALS_NUMBER 5
#define COMPONENTS_NUMBER 4

// For lisibility and performance index are here
#define i_add_term1 0
#define i_add_term2 1
#define o_result 2
#define w_carry 3
#define w_sum 4

class ripple_carry_adder : public hdl::VHDLComponent
{
    public:
        hdl::VHDLComponent* childs[COMPONENTS_NUMBER];

        hdl::Signal signals[SIGNALS_NUMBER] = {
            hdl::Signal("i_add_term1", hdl::SignalType::input, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X)),
            hdl::Signal("i_add_term2", hdl::SignalType::input, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X)),
            hdl::Signal("o_result", hdl::SignalType::output, hdl::SignalImpl::wire, hdl::SignalValue(5, hdl::TriState::X)),
            hdl::Signal("w_carry", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(5, hdl::TriState::X)),
            hdl::Signal("w_sum", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X))
        };
        hdl::SignalValue savedSignals[SIGNALS_NUMBER];

        ripple_carry_adder(size_t instance_num) {
            std::string name = "ripple_carry_adder_";
            name.append(std::to_string(instance_num));
            hdl::SimMaster::getInstance()->registerInstance(name, this);

            for (size_t ii = 0; ii<COMPONENTS_NUMBER; ii++) {
                childs[ii] = new full_adder(ii);
            }
        }

        ~ripple_carry_adder() {
            std::cout<<"~ripple_carry_adder() called"<<std::endl;
            for (size_t ii = 0; ii<COMPONENTS_NUMBER; ii++) {
                delete (childs[ii]);
            }
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
            signals[w_carry].value[0] = hdl::TriState::L;

            for (size_t ii = 0; ii<COMPONENTS_NUMBER; ii++) {
                childs[ii]->setSignal("i_a",signals[i_add_term1].getBits(ii, ii+1));
                childs[ii]->setSignal("i_b",signals[i_add_term2].getBits(ii, ii+1));
                childs[ii]->setSignal("i_carry",signals[w_carry].getBits(ii, ii+1));
                signals[w_sum].value[ii] = childs[ii]->getSignal("o_sum")->value[0]; // Can also use .getBits(0, 1)
                signals[w_carry].value[ii+1] = childs[ii]->getSignal("o_carry")->value[0];
            }

            signals[o_result].value = hdl::sig_concatenate(signals[w_carry].getBits(4, 5), signals[w_sum].value);
            // End of concurrent code
        }
};