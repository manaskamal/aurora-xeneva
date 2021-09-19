
#include <iostream>

namespace std {

	int ios_base::Init::refCount;


	ios_base::Init::Init()
	{
		if (refCount <= 0)
		{
			streambuf sb;

			cin = istream(&sb);
			cout = ostream(&sb);
			cerr = ostream(&sb);
			clog = ostream(&sb);
		}

		refCount += 1;
	}


	ios_base::Init::~Init()
	{
		if (refCount <= 0)
		{
		}

		refCount -= 1;
	}


	ios_base::ios_base()
	{
	}


	template <class charT, class traits>
	basic_ios<charT, traits>::basic_ios()
	{
	}


	template class basic_ios<char, char_traits<char> >;
}

