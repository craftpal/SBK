#pragma once

#include "cutout.h"
#include "entities.h"

using namespace cutout;

namespace PazzleClacDll
{
	class CInterfaceRectance :CCoreRectance {
	public:
		static CDxfRectangle toDxfRectangle(CFrame _frame);
		static CDxfContinuum toDxfContinuum(std::vector<CFrame> _frame);
	};
}