#include "UnitTest.hpp"
#include "include/VHDLetor.hpp"

// Test the convertion from uint to hdl::Signal and back (4 bits, not symetric))
int tc_sig_uint_conv(void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X));
  sig.setAsUInt(0b1011);
  if(sig.toUInt() == 0b1011 )
	  return 0;
  return 1;
}
START_TEST(tc_sig_uint_conv);

int tc_sig_xor(void)
{
  hdl::SignalValue r = hdl::SignalValue(5, hdl::TriState::X);
  hdl::SignalValue a = hdl::SignalValue({hdl::TriState::H, hdl::TriState::L, hdl::TriState::H, hdl::TriState::L, hdl::TriState::L});
  hdl::SignalValue b = hdl::SignalValue({hdl::TriState::H, hdl::TriState::H, hdl::TriState::L, hdl::TriState::L, hdl::TriState::L});
  r = hdl::sig_xor(a, b);
  if (r == hdl::SignalValue({hdl::TriState::L, hdl::TriState::H, hdl::TriState::H, hdl::TriState::L, hdl::TriState::L}))
	return 0;
  return 1;
}
START_TEST(tc_sig_xor);

int tc_sig_getBitsLSB_lsb(void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X));
  sig.setAsUInt(0b1110);
  if ( sig.getBitsLSB(0, 1) == hdl::SignalValue(1, hdl::TriState::L) ) return 0; else return 1;
}
START_TEST(tc_sig_getBitsLSB_lsb);

int  tc_sig_getBitsLSB_msb  (void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X));
  sig.setAsUInt(0b1000);
  if ( sig.getBitsLSB(3, 4) == hdl::SignalValue(1, hdl::TriState::H) ) return 0; else return 1;
}
START_TEST(tc_sig_getBitsLSB_msb);

int  tc_sig_getBitsLSB_long_lsb  (void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(8, hdl::TriState::X));
  sig.setAsUInt(0b00001110);
  if ( sig.getBitsLSB(0, 4) == hdl::SignalValue({hdl::TriState::H, hdl::TriState::H, hdl::TriState::H, hdl::TriState::L}) ) return 0; else return 1;
}
START_TEST(tc_sig_getBitsLSB_long_lsb);

int  tc_sig_getBitsLSB_long_msb_1  (void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(8, hdl::TriState::X));
  sig.setAsUInt(0b01101010);
  if ( sig.getBitsLSB(3, 7) == hdl::SignalValue({hdl::TriState::H, hdl::TriState::H, hdl::TriState::L, hdl::TriState::H}) ) return 0; else return 1;
}
START_TEST(tc_sig_getBitsLSB_long_msb_1);

int  tc_sig_getBitsLSB_long_msb_2  (void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(8, hdl::TriState::X));
  sig.setAsUInt(0b01101010);
  if ( sig.getBitsLSB(4, 8) == hdl::SignalValue({hdl::TriState::L, hdl::TriState::H, hdl::TriState::H, hdl::TriState::L}) ) return 0; else return 1;
}
START_TEST(tc_sig_getBitsLSB_long_msb_2);

int  tc_sig_getBitsMSB_lsb  (void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X));
  sig.setAsUInt(0b0111);
  if ( sig.getBitsMSB(0, 1) == hdl::SignalValue(1, hdl::TriState::L) ) return 0; else return 1;
}
START_TEST(tc_sig_getBitsMSB_lsb);

int  tc_sig_getBitsMSB_msb  (void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X));
  sig.setAsUInt(0b0001);
  if ( sig.getBitsMSB(3, 4) == hdl::SignalValue(1, hdl::TriState::H) ) return 0; else return 1;
}
START_TEST(tc_sig_getBitsMSB_msb);

int  tc_sig_getBitsMSB_long_lsb  (void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(8, hdl::TriState::X));
  sig.setAsUInt(0b11100000);
  if ( sig.getBitsMSB(0, 4) == hdl::SignalValue({hdl::TriState::H, hdl::TriState::H, hdl::TriState::H, hdl::TriState::L}) ) return 0; else return 1;
}
START_TEST(tc_sig_getBitsMSB_long_lsb);

int  tc_sig_getBitsMSB_long_msb_1  (void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(8, hdl::TriState::X));
  sig.setAsUInt(0b00011010);
  if ( sig.getBitsMSB(3, 7) == hdl::SignalValue({hdl::TriState::H, hdl::TriState::H, hdl::TriState::L, hdl::TriState::H}) ) return 0; else return 1;
}
START_TEST(tc_sig_getBitsMSB_long_msb_1);

int  tc_sig_getBitsMSB_long_msb_2  (void)
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(8, hdl::TriState::X));
  sig.setAsUInt(0b10110110);
  if ( sig.getBitsMSB(4, 8) == hdl::SignalValue({hdl::TriState::L, hdl::TriState::H, hdl::TriState::H, hdl::TriState::L}) ) return 0; else return 1;
}
START_TEST(tc_sig_getBitsMSB_long_msb_2);

int main(int argc, char** argv)
{
	return 0;
}

