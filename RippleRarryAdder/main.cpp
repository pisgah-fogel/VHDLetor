#include <iostream>
#include "reference/ripple_carry_adder.hpp"

int main(int argc, char** argv) {
    ripple_carry_adder uut(0);

    uut.setSignalAsUInt("i_add_term1", 0);
    uut.setSignalAsUInt("i_add_term2", 0);
    hdl::SimMaster::getInstance()->eval();
    std::cout<<*uut.getSignal("o_result")<<std::endl;
    std::cout<<*uut.getSignal("w_carry")<<std::endl;
    std::cout<<*uut.getSignal("w_sum")<<std::endl;

    uut.setSignalAsUInt("i_add_term1", 0b0110);
    uut.setSignalAsUInt("i_add_term2", 0b1101);
    hdl::SimMaster::getInstance()->eval();
    std::cout<<*uut.getSignal("o_result")<<std::endl;
    std::cout<<*uut.getSignal("w_carry")<<std::endl;
    std::cout<<*uut.getSignal("w_sum")<<std::endl;

    uut.setSignalAsUInt("i_add_term1", 0b1010);
    uut.setSignalAsUInt("i_add_term2", 0b0101);
    hdl::SimMaster::getInstance()->eval();
    std::cout<<*uut.getSignal("o_result")<<std::endl;
    std::cout<<*uut.getSignal("w_carry")<<std::endl;
    std::cout<<*uut.getSignal("w_sum")<<std::endl;
}