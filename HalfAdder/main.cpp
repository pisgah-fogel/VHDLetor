#include <iostream>
#include "reference/half_adder.hpp"

int main(int argc, char** argv) {
    half_adder uut(0);
    uut.setSignalAsUInt("i_a", 0);
    uut.setSignalAsUInt("i_b", 0);
    uut.setSignalAsUInt("o_sum", 0);
    uut.setSignalAsUInt("o_carry", 0);

    hdl::SimMaster::getInstance()->eval();
    std::cout<<*uut.getSignal("o_sum")<<std::endl;
    std::cout<<*uut.getSignal("o_carry")<<std::endl;
    
    uut.setSignalAsUInt("i_a", 1);
    hdl::SimMaster::getInstance()->eval();
    std::cout<<*uut.getSignal("o_sum")<<std::endl;
    std::cout<<*uut.getSignal("o_carry")<<std::endl;

    uut.setSignalAsUInt("i_a", 0);
    uut.setSignalAsUInt("i_b", 1);
    hdl::SimMaster::getInstance()->eval();
    std::cout<<*uut.getSignal("o_sum")<<std::endl;
    std::cout<<*uut.getSignal("o_carry")<<std::endl;

    uut.setSignalAsUInt("i_a", 1);
    hdl::SimMaster::getInstance()->eval();
    std::cout<<*uut.getSignal("o_sum")<<std::endl;
    std::cout<<*uut.getSignal("o_carry")<<std::endl;
}