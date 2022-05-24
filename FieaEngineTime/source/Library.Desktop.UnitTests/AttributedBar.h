#pragma once
#include <gsl/pointers>
#include "Attributed.h"

namespace LibraryDesktopUnitTests
{
	class AttributedBar final : public FieaGameEngine::Attributed
	{
		RTTI_DECLARATIONS(AttributedBar, FieaGameEngine::Attributed)

	public:
		static const std::size_t ArraySize = 5;

		AttributedBar();
		AttributedBar(const AttributedBar&) = default;
		AttributedBar(AttributedBar&&) = default;
		AttributedBar& operator=(const AttributedBar&) = default;
		AttributedBar& operator=(AttributedBar&&) = default;
		~AttributedBar() = default;

		int ExternalInteger = 0;
		float ExternalFloat = 0;
		std::string ExternalString;
		glm::vec4 ExternalVector;
		glm::mat4 ExternalMatrix;

		int ExternalIntegerArray[ArraySize];
		float ExternalFloatArray[ArraySize];
		std::string ExternalStringArray[ArraySize];
		glm::vec4 ExternalVectorArray[ArraySize];
		glm::mat4 ExternalMatrixArray[ArraySize];

		gsl::owner<AttributedBar*> Clone() const override;
		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;

		static const FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();
	};
}


