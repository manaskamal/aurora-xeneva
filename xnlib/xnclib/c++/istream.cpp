//
//  Visopsys
//  Copyright (C) 1998-2020 J. Andrew McLaughlin
//
//  This library is free software; you can redistribute it and/or modify it
//  under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation; either version 2.1 of the License, or (at
//  your option) any later version.
//
//  This library is distributed in the hope that it will be useful, but
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
//  General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this library; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
//  istream.cpp
//

// This is the standard "istream" definition, as found in standard C++
// libraries

#include <istream>
#include <cctype>

using namespace std;



namespace std {

	template <class charT, class traits>
	basic_istream<charT, traits>::basic_istream(
		basic_streambuf<charT, traits> *)
	{
	}


	template <class charT, class traits>
	basic_istream<charT, traits>::~basic_istream()
	{
	}


	template <>
	istream& istream::operator>>(char& c)
	{
		unsigned unicode = 0;

		//visopsys::textInputGetc(&unicode);

		c = (char) unicode;

		return (*this);
	}


	template <>
	istream& istream::operator>>(char *s)
	{
		int count = 0;

		do
		{
			unsigned unicode = 0;

			//visopsys::textInputGetc(&unicode);

			s[count] = (char) unicode;

		} while (!isspace(s[count++]));

		s[count] = 0;

		return (*this);
	}


	template class basic_istream<char, char_traits<char> >;
}

