// Copyright (C) 2025 Krock/SmallJoker <mk939@ymail.com>
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#pragma once

#include <type_traits> // is_base_of_v

// Shared pointer class for IReferenceCounted classes (RAII).

namespace irr
{

// https://www.geeksforgeeks.org/cpp/how-to-implement-user-defined-shared-pointers-in-c/

class IReferenceCounted;

template <typename T>
class RcPointer {
public:
	/// This does NOT increase the reference count!
	/// Use only when passing a newly constructed class.
	RcPointer(T *obj = nullptr) : Obj(obj) {}

	RcPointer(const RcPointer<T> &other)
	{
		Obj = other.Obj;
		if (Obj)
			Obj->grab();
	}

	RcPointer(RcPointer<T> &&other)
	{
		Obj = other.Obj;
		other.Obj = nullptr;
	}

	~RcPointer()
	{
		// In case of the compiler error 'non-constant condition for static assertion',
		// do define the constructor AND destructor if your class in the source file.
		static_assert(std::is_base_of_v<IReferenceCounted, T>, "");
		reset(nullptr);
	}

	RcPointer &operator=(const RcPointer<T> &other)
	{
		Obj = other.Obj;
		if (Obj)
			Obj->grab();
		return *this;
	}

	/// Does not grab `obj`
	void reset(T *obj = nullptr)
	{
		if (Obj)
			Obj->drop();
		Obj = obj;
	}

	/// Does not drop `obj`
	T *release()
	{
		T *val = get();
		Obj = nullptr;
		return val;
	}

	T *get() const { return Obj; }
	// Automatic type conversion
	explicit operator T*() const { return Obj; }
	// Member access
	T *operator->() const { return Obj; }

	operator bool() const { return Obj; }

private:
	T *Obj;
};

// Glue for backporting efforts
template <typename T>
using irr_ptr = RcPointer<T>;

}
