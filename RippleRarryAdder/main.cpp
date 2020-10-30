#include <iostream>
#include "reference/ripple_carry_adder.hpp"
#include <bitset>

size_t eval_num = 0;
size_t error_num = 0;
void addition(ripple_carry_adder*uut, unsigned int a, unsigned int b) {
    eval_num ++;
    uut->setSignalAsUInt("i_add_term1", a);
    uut->setSignalAsUInt("i_add_term2", b);
    hdl::SimMaster::getInstance()->eval();
    if (uut->getSignal("o_result")->toUInt() != a+b) {
        std::cout<<"Model error: "<<std::bitset<4>(a)<<" + "<<std::bitset<4>(b)<<" != ";
        std::cout<<*uut->getSignal("o_result")<<std::endl;
        std::cout<<"Result should be "<<std::bitset<5>(a+b)<<std::endl;
        std::cout<<*uut->getSignal("w_carry")<<std::endl;
        std::cout<<*uut->getSignal("w_sum")<<std::endl;
        error_num++;
    }
}

int main(int argc, char** argv) {
    ripple_carry_adder uut(0);

    std::cout<<"-------------------------------------------------"<<std::endl;

    for (unsigned int a = 0; a <= 0b1111; a++)
    for (unsigned int b = 0; b <= 0b1111; b++)
        addition(&uut, a, b);
    
    std::cout<<"Errors: "<<error_num<<std::endl;
    std::cout<<"Total: "<<eval_num<<std::endl;
}
