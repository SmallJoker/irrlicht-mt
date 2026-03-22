#include "test_helper.h"
#include "test_rcpointer.h"
#include <IReferenceCounted.h>
#include <irrPtr.h>

using namespace irr;

#if 0
	#define DBG_TEST(...) printf(__VA_ARGS__)
#else
	#define DBG_TEST(...) do {} while(0)
#endif

static int instance_count = 0;

class TestObject : public virtual IReferenceCounted {
public:
	TestObject() {
		instance_count++;
		DBG_TEST("%s -> %d\n", __func__, instance_count);
	}
	~TestObject() {
		instance_count--;
		DBG_TEST("%s -> %d\n", __func__, instance_count);
	}
	void quack() {
		// Check whether the memory is still OK.
		for (size_t i = 0; i < sizeof(m_quacks); ++i)
			m_quacks[i] = i;
	}
private:
	char m_quacks[100];
};

RefCountedFwdDeclarationTest::RefCountedFwdDeclarationTest() :
	value(new TestObject()) {}
RefCountedFwdDeclarationTest::~RefCountedFwdDeclarationTest() {}

static void do_something_copy(RcPointer<TestObject> obj)
{
	UASSERTEQ(instance_count, 1);
	obj->quack();
}

static void do_something_move(RcPointer<TestObject> &&obj)
{
	UASSERTEQ(instance_count, 1);
	obj->quack();
}

void test_irr_rcpointer()
{
	UASSERTEQ(instance_count, 0);
	{
		RcPointer<TestObject> what;
	}
	UASSERTEQ(instance_count, 0);
	{
		RcPointer<TestObject> what(new TestObject());
	}
	UASSERTEQ(instance_count, 0);
	{
		RcPointer<TestObject> what(new TestObject());
		do_something_copy(what);
	}
	UASSERTEQ(instance_count, 0);
	{
		RcPointer<TestObject> what(new TestObject());
		do_something_move(std::move(what));
	}
	UASSERTEQ(instance_count, 0);
	std::cout << "    " << __func__ << " PASSED" << std::endl;
}
