#pragma once

#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <deque>

namespace hdl {

typedef enum TriState
{
    L = 0, // Binary 0
    H = 1, // Binary 1
    Z, // High impedance
    X // Error
} TriState;

typedef std::deque<TriState> SignalValue;

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
            std::cout<<"Signal "<<name<<" created: "<<value.size()<<"bits = "<<value<<std::endl;
        }
        SignalValue getBits(size_t start, size_t end)
        {
            SignalValue output;
            if (start > end || end > value.size()) {
                std::cout<<"Signal::getBits: Error: Invalid range "<<start<<" to "<<end<<" for signal "<<name<<" (size="<<value.size()<<")"<<std::endl;
                return value;
            }
            
            for (size_t i = start; i < end; i++)
                output.push_back(value[i]);// TODO: Do not use [] operator
            std::cout<<"getBit "<<start<<":"<<end<<" of "<<value<<" = "<<output<<std::endl;
            return output;
        }
        friend std::ostream& operator<<(std::ostream& os, const Signal& dt) {
            os << dt.name << ": " << dt.value;
            return os;
        }
        void setAsUInt(unsigned int sigValue) {
            if (value.size() > sizeof(sigValue)*8) {
                std::cout<<"half_adder::setSignalAsUInt(): Error: Signal "<<name<<" is "<<value.size()<<" bits wide and on your system 'setSignalAsUInt' only support "<<sizeof(sigValue)*8<<" bits"<<std::endl;
                std::cout<<"Abording the operation on this signal"<<std::endl;
                return;
            }
            size_t s = value.size();
            value.clear();
            for (int z = s-1; z>=0; z--) {
                if (sigValue & (0b1<<z))
                    value.push_back(TriState::H);
                else
                    value.push_back(TriState::L);
            }
            std::cout<<"Debug: setSignalAsUInt: Uint "<<sigValue<<" result in "<<value<<" (size="<<value.size()<<")"<<std::endl;
        }
        unsigned int toUInt() {
            if (value.size() > sizeof(unsigned int)*8) {
                std::cout<<"half_adder::toUInt(): Error: Signal "<<name<<" is "<<value.size()<<" bits wide and on your system 'toUInt' only support "<<sizeof(unsigned int)*8<<" bits"<<std::endl;
                return 0;
            }
            unsigned int sum = 0;
            unsigned int top = 0b1 << (value.size()-1);
            size_t i = 0;
            for (const TriState &val : value) {
                switch (val) {
                    case TriState::H:
                        sum += top >> i;
                        break;
                    case TriState::L:
                        break;
                    default:
                        std::cout<<"half_adder::toUInt(): Error: Signal "<<name<<", value: "<<value<<" cannot be converted to integer"<<std::endl;
                }
                i++;
            }
            std::cout<<"Debug: toUInt: "<<value<<" = "<<sum<<std::endl;
            return sum;
        }
};

SignalValue sig_xor(SignalValue a, SignalValue b)
{
    SignalValue output;
    if (a.size() != b.size()) {
        std::cout<<"xor: Error: Signals do not have the same width"<<std::endl;
        std::cout<<a<<" xor "<<b<<std::endl;
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
        std::cout<<a<<" and "<<b<<std::endl;
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
        std::cout<<a<<" or "<<b<<std::endl;
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

SignalValue sig_concatenate(SignalValue a, SignalValue b)
{
    SignalValue output = a;
    output.insert(output.end(), b.begin(), b.end());
#ifdef DEBUG
    std::cout<<"Concatenate "<<a<<" & "<<b<<" = "<<output<<std::endl;
#endif
    return output;
}

class VHDLComponent
{
    public:
        virtual Signal* getSignals() = 0;
        virtual SignalValue* getSavedSignals() = 0;
        virtual size_t getSignalsCount() = 0;
        // Is called by SimMaster, do not call directly
        virtual void eval_concurrent() = 0;
        // Is called by SimMaster, do not call directly
        virtual void eval_sequential() = 0;

        virtual ~VHDLComponent() {}

        void saveSignals() {
            for (size_t i = 0; i<getSignalsCount(); i++) {
                getSavedSignals()[i] = getSignals()[i].value;
            }
        }

        bool isAnySignalsChanged() {
            for (size_t i = 0; i<getSignalsCount(); i++) {
                if (getSignals()[i].value != getSavedSignals()[i]){
                    return true;
                }
            }
            return false;
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
                ptr->setAsUInt(sigValue);
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

        void eval() {
            size_t count_eval = 0;
            const size_t max_eval = 100;

            while (count_eval < max_eval) {
                count_eval ++;

                for (std::map<std::string, VHDLComponent*>::iterator it = HDLInstances.begin(); it != HDLInstances.end(); it++) {
                    it->second->saveSignals();
                }
                
                for (std::map<std::string, VHDLComponent*>::iterator it = HDLInstances.begin(); it != HDLInstances.end(); it++) {
                    it->second->eval_concurrent();
                }

                bool outputdiff = false;
                for (std::map<std::string, VHDLComponent*>::iterator it = HDLInstances.begin(); it != HDLInstances.end(); it++) {
                    if (it->second->isAnySignalsChanged()) {
                        outputdiff = true;
#ifdef DEBUG
                        std::cout<<"SimMaster::eval: Instance "<<it->first<<" require a new evaluation iteration"<<std::endl;
#endif
                        break;
                    }
                }
                if (!outputdiff)
                    break;
            }
            std::cout<<"Concurrent code took "<<count_eval<<" evaluations to complete"<<std::endl;
            for (std::map<std::string, VHDLComponent*>::iterator it = HDLInstances.begin(); it != HDLInstances.end(); it++) {
                it->second->eval_sequential();
            }
        }

    private:
        SimMaster() {
            std::cout<<"SimMaster created"<<std::endl;
        }
};

}
