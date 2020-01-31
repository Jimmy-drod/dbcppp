
#include "MakeSignal.h"
#include "../dbcppp/Network.h"

using namespace dbcppp;

#if BOOST_ENDIAN_LITTLE_BYTE
inline void native_to_big_inplace_64(uint64_t data[8]) noexcept
{
	boost::endian::native_to_big_inplace(data[0]);
	boost::endian::native_to_big_inplace(data[1]);
	boost::endian::native_to_big_inplace(data[2]);
	boost::endian::native_to_big_inplace(data[3]);
	boost::endian::native_to_big_inplace(data[4]);
	boost::endian::native_to_big_inplace(data[5]);
	boost::endian::native_to_big_inplace(data[6]);
	boost::endian::native_to_big_inplace(data[7]);
	std::swap(data[0], data[7]);
	std::swap(data[1], data[6]);
	std::swap(data[2], data[5]);
	std::swap(data[3], data[4]);
}
#else
inline void native_to_big_inplace_64(uint64_t data[8]) noexcept
{
}
#endif
#if BOOST_ENDIAN_BIG_BYTE
inline void native_to_little_inplace_64(uint64_t data[8]) noexcept
{
	boost::endian::native_to_little_inplace(data[0]);
	boost::endian::native_to_little_inplace(data[1]);
	boost::endian::native_to_little_inplace(data[2]);
	boost::endian::native_to_little_inplace(data[3]);
	boost::endian::native_to_little_inplace(data[4]);
	boost::endian::native_to_little_inplace(data[5]);
	boost::endian::native_to_little_inplace(data[6]);
	boost::endian::native_to_little_inplace(data[7]);
	std::swap(data[0], data[7]);
	std::swap(data[1], data[6]);
	std::swap(data[2], data[5]);
	std::swap(data[3], data[4]);
}
#else
inline void native_to_little_inplace_64(uint64_t data[8]) noexcept
{
}
#endif

template <dbcppp::Signal::ByteOrder aByteOrder, dbcppp::Signal::ValueType aValueType>
Signal::raw_t decode8(const Signal& sig, const void* _8byte) noexcept
{
	uint64_t data = *reinterpret_cast<const uint64_t*>(_8byte);
	if constexpr (aByteOrder == Signal::ByteOrder::BigEndian)
	{
		// only reverse byte order when native byte order isn't big endian
		boost::endian::native_to_big_inplace(data);
	}
	else
	{
		// only reverse byte order when native byte order isn't little endian
		boost::endian::native_to_little_inplace(data);
	}
	data >>= sig.fixed_start_bit;
	if constexpr (aValueType == Signal::ValueType::Signed)
	{
		// bit extending
		data |= ~((data & sig.mask_signed) - 1);
	}
	else
	{
		data &= sig.mask;
	}
	// ignore the case when bit size == 64 and ValueType == Unsigned
	return data;
}
template <dbcppp::Signal::ByteOrder aByteOrder, dbcppp::Signal::ValueType aValueType>
Signal::raw_t decode64(const Signal& sig, const void* _64byte) noexcept
{
	uint64_t data64[8];
	std::memcpy(data64, _64byte, 64);
	if constexpr (aByteOrder == Signal::ByteOrder::BigEndian)
	{
		// only reverse byte order when native byte order isn't big endian
		native_to_big_inplace_64(data64);
	}
	else
	{
		// only reverse byte order when native byte order isn't little endian
		native_to_little_inplace_64(data64);
	}
	uint64_t data = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(data64)[sig.big_endian_byte_pos_fd]);
	data >>= sig.fixed_start_bit_fd;
	if constexpr (aValueType == Signal::ValueType::Signed)
	{
		// bit extending
		data |= ~((data & sig.mask_signed) - 1);
	}
	else
	{
		data &= sig.mask;
	}
	// ignore the case when bit size == 64 and ValueType == Unsigned
	return data;
}

std::shared_ptr<dbcppp::Signal> make_signal(Signal::ByteOrder byte_order, Signal::ValueType value_type)
{
	auto sig = std::make_shared<Signal>();
	if (byte_order == Signal::ByteOrder::BigEndian &&
		value_type == Signal::ValueType::Signed)
	{
		sig->_decode8 = decode8<Signal::ByteOrder::BigEndian, Signal::ValueType::Signed>;
		sig->_decode64 = decode64<Signal::ByteOrder::BigEndian, Signal::ValueType::Signed>;
	}
	else if (byte_order == dbcppp::Signal::ByteOrder::BigEndian &&
		value_type == dbcppp::Signal::ValueType::Unsigned)
	{
		sig->_decode8 = decode8<Signal::ByteOrder::BigEndian, Signal::ValueType::Unsigned>;
		sig->_decode64 = decode64<Signal::ByteOrder::BigEndian, Signal::ValueType::Unsigned>;
	}
	else if (byte_order == Signal::ByteOrder::LittleEndian &&
		value_type == Signal::ValueType::Signed)
	{
		sig->_decode8 = decode8<Signal::ByteOrder::LittleEndian, Signal::ValueType::Signed>;
		sig->_decode64 = decode64<Signal::ByteOrder::LittleEndian, Signal::ValueType::Signed>;
	}
	else if (byte_order == Signal::ByteOrder::LittleEndian &&
		value_type == Signal::ValueType::Unsigned)
	{
		sig->_decode8 = decode8<Signal::ByteOrder::LittleEndian, Signal::ValueType::Unsigned>;
		sig->_decode64 = decode64<Signal::ByteOrder::LittleEndian, Signal::ValueType::Unsigned>;
	}
	else
	{
		// can't be reached
		throw std::runtime_error("Couldn't determine Signal!");
	}
	return sig;
}
