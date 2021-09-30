/*
 * for RenameCommand, which is a MacroCommand
 */

#include "RenameParsingStrategy.h"
#include "util.h"

/* RenameCommand is {copy, remove}
   this function transforms one input to a vector of two inputs.
     the first one for copy,
     the second one for remove */
vector<string> RenameParsingStrategy::parse(string raw_input)
{
  vector<string> splits = splitBySpace(raw_input);
  if (splits.size() != 2) return {};

  const string &existing_filename = splits[0];
  const string &new_filename = splits[1];

  return {
    existing_filename + " " + new_filename,  /* used by copy   */
    existing_filename                        /* used by remove */
  };
}
