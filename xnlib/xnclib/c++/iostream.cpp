

#include <iostream>

namespace std {

	istream cin(static_cast<streambuf *>(0));
	ostream cout(static_cast<streambuf *>(0));
	ostream cerr(static_cast<streambuf *>(0));
	ostream clog(static_cast<streambuf *>(0));
}

