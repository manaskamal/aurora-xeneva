

#include <ostream>

using namespace std;


namespace std {

	template <class charT, class traits>
	basic_ostream<charT, traits>::basic_ostream(
		basic_streambuf<charT, traits> *)
	{
	}


	template <class charT, class traits>
	basic_ostream<charT, traits>::~basic_ostream()
	{
	}


	template <class charT, class traits>
	basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(
		basic_ostream<charT, traits>& (*pf)(basic_ostream<charT, traits>&))
	{
		return (pf(*this));
	}


	template <>
	ostream& ostream::operator<<(char c)
	{
		//visopsys::textPutc(static_cast<int>(c));
		return (*this);
	}


	template <>
	ostream& ostream::operator<<(const char *s)
	{
		//visopsys::textPrint(s);
		return (*this);
	}


	ostream& endl(ostream& os)
	{
		//visopsys::textNewline();
		return (os);
	}


	template class basic_ostream<char, char_traits<char> >;
}

