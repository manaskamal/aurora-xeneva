

#include <memory>
#include <cstdlib>

namespace std {

	template <class T>
	allocator<T>::allocator()
	{
	}


	template <class T>
	allocator<T>::allocator(const allocator<T>&) throw()
	{
	}


	template <class T>
	allocator<T>::~allocator()
	{
	}


	template <class T>
	typename allocator<T>::pointer allocator<T>::address(reference ref) const
	{
		return (&ref);
	}


	template <class T>
	typename allocator<T>::const_pointer allocator<T>::address(
		const_reference ref) const
	{
		return (&ref);
	}


	template <class T>
	typename allocator<T>::pointer allocator<T>::allocate(size_type size,
		allocator<void>::const_pointer hint) const
	{
		if (hint) { /* not implemented */ }

		return (new T[size]);
	}


	template <class T>
	void allocator<T>::deallocate(pointer ptr, size_type size) const
	{
		if (size)
			return (delete[] ptr);
	}


	template <class T>
	typename allocator<T>::size_type allocator<T>::max_size() const throw()
	{
		return (static_cast<size_type>(-1));
	}


	template class allocator<char>;
}

