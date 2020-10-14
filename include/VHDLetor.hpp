#pragma once

#include <iostream>
#include <ostream>
#include <vector>
#include <map>

namespace hdl {

typedef enum TriState
{
    L = 0, // Binary 0
    H = 1, // Binary 1
    Z, // High impedance
    X // Error
} TriState;

typedef std::vector<TriState> SignalValue;

std::ostream& operator<<(std::ostream& os, const SignalValue& dt) {
    for (const TriState &v : dt) {
        switch (v) {
            case TriState::H:
                os <<'1';
                break;
            case TriState::L:
                os <<'0';
                break;
            case TriState::X:
                os <<'X';
                break;
            case TriState::Z:
                os <<'Z';
                break;
            default:
                os <<'?';
        }
    }
    return os;
}

typedef enum SignalType
{
    input,
    output,
    local,
    variable
} SignalType;

typedef enum SignalImpl
{
    wire,
    reg // This signal is a register (initial value and/or sequential operation)
} SignalImpl;

class Signal
{
    public:
        std::string name;
        SignalType signalType;
        SignalImpl signalImpl;
        SignalValue value;
        Signal(const std::string& sigName, SignalType sigType, SignalImpl sigImpl, SignalValue sigValue):
            name(sigName), signalType(sigType), signalImpl(sigImpl), value(sigValue)
        {
        }
    friend std::ostream& operator<<(std::ostream& os, const Signal& dt) {
        os << dt.name << ": " << dt.value;
        return os;
    }
};

SignalValue sig_xor(SignalValue a, SignalValue b)
{
    SignalValue output;
    if (a.size() != b.size()) {
        std::cout<<"xor: Error: Signals do not have the same width"<<std::endl;
        return output;
    }
    SignalValue::iterator ita = a.begin();
    SignalValue::iterator itb = b.begin();
    while(ita != a.end() && itb != b.end()) {
        if (*ita == TriState::X || *itb == TriState::X) {
            output.push_back(TriState::X);
        }
        else if (*ita == TriState::Z || *itb == TriState::Z) {
            // TODO: Is it the correct results ?
            output.push_back(TriState::Z);
        }
        else {
            output.push_back((TriState)(*ita ^ *itb));
        }
        ita ++; itb ++;
    }
    return output;
}

SignalValue sig_and(SignalValue a, SignalValue b)
{
    SignalValue output;
    if (a.size() != b.size()) {
        std::cout<<"and: Error: Signals do not have the same width"<<std::endl;
        return output;
    }
    SignalValue::iterator ita = a.begin();
    SignalValue::iterator itb = b.begin();
    while(ita != a.end() && itb != b.end()) {
        if (*ita == TriState::X || *itb == TriState::X) {
            output.push_back(TriState::X);
        }
        else if (*ita == TriState::Z || *itb == TriState::Z) {
            // TODO: Is it the correct results ?
            output.push_back(TriState::Z);
        }
        else {
            output.push_back((TriState)(*ita & *itb));
        }
        ita ++; itb ++;
    }
    return output;
}

SignalValue sig_or(SignalValue a, SignalValue b)
{
    SignalValue output;
    if (a.size() != b.size()) {
        std::cout<<"or: Error: Signals do not have the same width"<<std::endl;
        return output;
    }
    SignalValue::iterator ita = a.begin();
    SignalValue::iterator itb = b.begin();
    while(ita != a.end() && itb != b.end()) {
        if (*ita == TriState::X || *itb == TriState::X) {
            output.push_back(TriState::X);
        }
        else if (*ita == TriState::Z || *itb == TriState::Z) {
            // TODO: Is it the correct results ?
            output.push_back(TriState::Z);
        }
        else {
            output.push_back((TriState)(*ita | *itb));
        }
        ita ++; itb ++;
    }
    return output;
}

class VHDLComponent
{
    public:
        virtual Signal* getSignals() = 0;
        virtual size_t getSignalsCount() = 0;
        virtual void eval_concurrent() = 0;
        virtual void eval_sequential() = 0;
        void eval() {
            bool outputdiff = true;
            size_t count_eval = 0;
            SignalValue outputs[getSignalsCount()];

            // While the output is different from the one before the eval call we run all concurrent operations
            do {
                eval_concurrent();

                if (count_eval > 0) {
                    outputdiff = false;
                    for (size_t i = 0; i<getSignalsCount(); i++) {
                        if (getSignals()[i].value != outputs[i]){
                            outputdiff = true;
                            break;
                        }
                    }
                }
                for (size_t i = 0; i<getSignalsCount(); i++) {
                    outputs[i] = getSignals()[i].value;
                }
                count_eval += 1;

                if (count_eval > 100) {
                    std::cout<<"Error: half_adder::eval(): You have a loop in your concurrent code"<<std::endl;
                    return;
                }

            } while (outputdiff);
            std::cout<<"Concurrent code tool "<<count_eval<<" evaluations to complete"<<std::endl;
            eval_sequential();
        }
        Signal* getSignal(const std::string& sigName) {
            for (size_t i = 0; i < getSignalsCount(); i++) {
                if (getSignals()[i].name == sigName)
                    return &(getSignals()[i]);
            }
            return nullptr;
        }
        void setSignal(const std::string& sigName, SignalValue sigValue) {
            Signal* ptr = getSignal(sigName);
            if (ptr != nullptr) {
                // TODO: check that the signals have the same size...
                ptr->value = sigValue;
            }
            else {
                std::cout<<"half_adder::setSignal(): Error: Cannot find signal: "<<sigName<<std::endl;
            }
        }
        void setSignalAsUInt(const std::string& sigName, unsigned int sigValue) {
            Signal* ptr = getSignal(sigName);
            if (ptr != nullptr) {
                size_t sigSize = ptr->value.size();
                if (sigSize > sizeof(sigValue)*8) {
                    std::cout<<"half_adder::setSignalAsUInt(): Error: Signal "<<sigName<<" is "<<sigSize<<" bits wide and on your system 'setSignalAsUInt' only support "<<sizeof(sigValue)*8<<" bits"<<std::endl;
                    std::cout<<"Abording the operation on this signal"<<std::endl;
                    return;
                }

                SignalValue tmp;
                for (int z = sigSize-1; z>=0; z--) {
                    if (sigValue & (0b1<<z))
                        tmp.push_back(TriState::H);
                    else
                        tmp.push_back(TriState::L);
                }
                ptr->value = tmp;
                std::cout<<"Debug: setSignalAsUInt: Uint "<<sigValue<<" result in "<<*ptr<<" (size="<<sigSize<<")"<<std::endl;
            }
            else {
                std::cout<<"half_adder::setSignalAsUInt(): Error: Cannot find signal: "<<sigName<<std::endl;
            }
        }
};

class SimMaster
{
    public:
        std::map<std::string, VHDLComponent*> HDLInstances;

        static SimMaster* getInstance() {
            static SimMaster instance;
            return &instance;
        }

        void registerInstance(const std::string &name, VHDLComponent* ptr) {
            if (HDLInstances.find(name) != HDLInstances.end()) {
                std::cout<<"SimMaster::registerInstance: Error: Instance: "<<name<<" already exist"<<std::endl;
                return;
            }
            HDLInstances[name] = ptr;
            std::cout<<"Instance "<<name<<" registered in SimMaster"<<std::endl;
        }

    private:
        SimMaster() {
            std::cout<<"SimMaster created"<<std::endl;
        }
};

}
