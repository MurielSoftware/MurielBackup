#include "stdafx.h"
#include "ReInterpreter.h"
#include "ReInstructionGenerator.h"
#include "ReParser.h"
#include "ReInputStream.h"
#include "ReExpression.h"
#include "ReVirtualMachine.h"

namespace Redneck
{
	Interpreter::Interpreter()
	{
		//_parser = new Parser();
		_instructionGenerator = new InstructionGenerator();
		_virtualMachine = new VirtualMachine();
	}

	Interpreter::~Interpreter()
	{
		//delete _parser;
		delete _instructionGenerator;
		delete _virtualMachine;
	}

	void Interpreter::Interpret(const string& path)
	{
		InputStream* inputStream = new InputStream(path);
		Parser* parser = new Parser(*inputStream);
		Expression* expression = parser->Parse();
		list<Instruction*> instructions = _instructionGenerator->Generate(expression);
		_virtualMachine->Execute(instructions);
	}
}