#include "pch.h"
#include "CppUnitTest.h"
#include "../3.2b/3.2b.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int N = 2;
			Student* s = new Student[N];
			s[0].prizv = "Protsak";
			s[0].cours = (Cours)1;
			s[0].spec = (Spec)2;
			s[0].physic = 5;
			s[0].math = 5;
			s[0].prog = 5;
			s[1].prizv = "Prozzz";
			s[1].cours = (Cours)2;
			s[1].spec = (Spec)2;
			s[1].physic = 3;
			s[1].math = 3;
			s[1].prog = 3;

			Assert::IsTrue(BinSearch(s, N, "Prozzz", (Cours)2, 3) == 1);
		}
	};
}
