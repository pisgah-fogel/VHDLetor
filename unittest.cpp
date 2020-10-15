#define BOOST_TEST_MODULE VHDLetor
#include <boost/test/included/unit_test.hpp>
#include <iostream>

#include "include/VHDLetor.hpp"

BOOST_AUTO_TEST_SUITE( ts_vhdletor )

BOOST_AUTO_TEST_CASE( tc_sig_uint_conv )
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X));
  sig.setAsUInt(0b1011);
  BOOST_TEST_REQUIRE( sig.toUInt() == 0b1011 );
}

BOOST_AUTO_TEST_CASE( tc_sig_getBits_lsb )
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X));
  sig.setAsUInt(0b1110);
  BOOST_TEST_REQUIRE( sig.getBits(0, 1) == hdl::SignalValue(1, hdl::TriState::L) );
}

BOOST_AUTO_TEST_CASE( tc_sig_getBits_msb )
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(4, hdl::TriState::X));
  sig.setAsUInt(0b1000);
  BOOST_TEST_REQUIRE( sig.getBits(3, 4) == hdl::SignalValue(1, hdl::TriState::H) );
}

BOOST_AUTO_TEST_CASE( tc_sig_getBits_long_lsb )
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(8, hdl::TriState::X));
  sig.setAsUInt(0b00001110);
  BOOST_TEST_REQUIRE( sig.getBits(0, 4) == hdl::SignalValue({hdl::TriState::H, hdl::TriState::H, hdl::TriState::H, hdl::TriState::L}) );
}

BOOST_AUTO_TEST_CASE( tc_sig_getBits_long_msb_1 )
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(8, hdl::TriState::X));
  sig.setAsUInt(0b01101010);
  BOOST_TEST_REQUIRE( sig.getBits(3, 7) == hdl::SignalValue({hdl::TriState::H, hdl::TriState::H, hdl::TriState::L, hdl::TriState::H}) );
}
BOOST_AUTO_TEST_CASE( tc_sig_getBits_long_msb_2 )
{
  hdl::Signal sig = hdl::Signal("test_signal", hdl::SignalType::local, hdl::SignalImpl::wire, hdl::SignalValue(8, hdl::TriState::X));
  sig.setAsUInt(0b01101010);
  BOOST_TEST_REQUIRE( sig.getBits(4, 8) == hdl::SignalValue({hdl::TriState::L, hdl::TriState::H, hdl::TriState::H, hdl::TriState::L}) );
}

BOOST_AUTO_TEST_SUITE_END()