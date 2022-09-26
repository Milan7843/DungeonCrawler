#include "pch.h"
#include "CppUnitTest.h"

#include <Root/Gradient.h>
#include <Root/Gradient.cpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RootEngineTest
{
	TEST_CLASS(GradientTest)
	{
	public:
		
		TEST_METHOD(SimpleTest)
		{
			// Simple test: one point at 0,0, one at 1,1
			std::vector<GradientPoint<float>> points{
				{ 0.0f, 0.0f }, { 1.0f, 1.0f }
			};
			Gradient<float> gradient(points);

			Assert::AreEqual(0.0f, gradient.sample(0.0f));
			Assert::AreEqual(1.0f, gradient.sample(1.0f));
			Assert::AreEqual(0.5f, gradient.sample(0.5f));
		}

		TEST_METHOD(ThreePointTest)
		{
			// Three point test: one point at 0,0, one at 0.5,0.6 and last at 1,1
			std::vector<GradientPoint<float>> points{
				{ 0.0f, 0.0f }, { 0.5f, 0.6f }, { 1.0f, 1.0f }
			};
			Gradient<float> gradient(points);

			Assert::AreEqual(0.0f, gradient.sample(0.0f));
			Assert::AreEqual(1.0f, gradient.sample(1.0f));
			Assert::AreEqual(0.6f, gradient.sample(0.5f));
		}

		TEST_METHOD(LessThanSmallestTest)
		{
			std::vector<GradientPoint<float>> points{
				{ 0.1f, 0.3f }, { 1.0f, 0.7f }
			};
			Gradient<float> gradient(points);

			Assert::AreEqual(0.3f, gradient.sample(0.0f));
			Assert::AreEqual(0.3f, gradient.sample(-1.0f));
		}

		TEST_METHOD(GreaterThanGreatestTest)
		{
			std::vector<GradientPoint<float>> points{
				{ 0.1f, 0.3f }, { 1.2f, 0.7f }
			};
			Gradient<float> gradient(points);

			Assert::AreEqual(0.7f, gradient.sample(1.2f));
			Assert::AreEqual(0.7f, gradient.sample(1.3f));
			Assert::AreEqual(0.7f, gradient.sample(10.0f));
		}
	};
}
