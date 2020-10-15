#include <iostream>
#include "reference/ripple_carry_adder.hpp"

void addition(ripple_carry_adder*uut, unsigned int a, unsigned int b) {
    uut->setSignalAsUInt("i_add_term1", a);
    uut->setSignalAsUInt("i_add_term2", b);
    hdl::SimMaster::getInstance()->eval();
    if (uut->getSignal("o_result")->toUInt() != a+b) {
        std::cout<<"Model error: "<<a<<" + "<<b<<" != ";
        std::cout<<*uut->getSignal("o_result")<<std::endl;
        std::cout<<*uut->getSignal("w_carry")<<std::endl;
        std::cout<<*uut->getSignal("w_sum")<<std::endl;
    }
}

int main(int argc, char** argv) {
    ripple_carry_adder uut(0);

    std::cout<<"-------------------------------------------------"<<std::endl;

    for (unsigned int a = 0; a <= 0b1111; a++)
    for (unsigned int b = 0; b <= 0b1111; b++)
        addition(&uut, a, b);
}