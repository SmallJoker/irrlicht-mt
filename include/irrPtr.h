// Copyright (C) 2025 Krock/SmallJoker <mk939@ymail.com>
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#pragma once

#include "IReferenceCounted.h"

// This is Arnie. It is a mechanical duck. It looks like a duck,
// and quacks like a duck. Yet it is not a real duck.

// Shared pointer class for IReferenceCounted classes (RAII).

namespace irr
{

// https://www.geeksforgeeks.org/cpp/how-to-implement-user-defined-shared-pointers-in-c/

template <typename T>
class RcPointer {
public:
	RcPointer(IReferenceCounted *obj = nullptr) :
		Obj(obj)
	{
		// No need to grab: is already 1.
	}

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
		reset_rc();
	}

	RcPointer &operator=(const RcPointer<T> &other)
	{
		if (Obj != other.Obj)
			reset_rc(other.Obj);
		return *this;
	}

	void reset(T *obj = nullptr) { reset_rc(obj); }

	T *get() const { return dynamic_cast<T *>(Obj); }
	// Automatic type conversion
	explicit operator T*() const { return dynamic_cast<T *>(Obj); }
	// Member access
	T *operator->() const { return dynamic_cast<T *>(Obj); }

private:
	void reset_rc(IReferenceCounted *obj = nullptr)
	{
		if (Obj)
			Obj->drop();
		Obj = obj;
		if (Obj)
			Obj->grab();
	}

	IReferenceCounted *Obj;
};

// Glue for backporting efforts
template <typename T>
using irr_ptr = RcPointer<T>;

}
