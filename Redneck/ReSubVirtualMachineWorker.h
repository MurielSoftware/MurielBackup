#pragma once

#include "ReVirtualMachineWorker.h"

namespace Redneck
{
	class SubVirtualMachineWorker : public VirtualMachineWorker
	{
	public:
		void ProcessInstruction(stack<DataType*>& stack, Memory& memory, Instruction* instruction);
	};
}