#pragma once

#include "test_helper.h"
#include <irrPtr.h>

class TestObject;

struct RefCountedFwdDeclarationTest {
	RefCountedFwdDeclarationTest();
	~RefCountedFwdDeclarationTest();

	irr::RcPointer<TestObject> value;
};
