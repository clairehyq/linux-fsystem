/*
 * for RenameCommand, which is a MacroCommand
 */

#pragma once
#include "AbstractParsingStrategy.h"

class RenameParsingStrategy : public AbstractParsingStrategy
{
public:
  vector<string> parse(string) override;
};
