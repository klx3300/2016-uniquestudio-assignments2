#!env python
# usage :
# ./replacer.py old_word new_word <origin.c >newfile.c

# e.g.
# ./replacer.py vector list
# vector->list
# Vector->List
# VECTOR->LIST

import sys
import re
import fileinput
if len(sys.argv)!=3:
    print("argv error")
    exit

fr = sys.argv[1]
to = sys.argv[2]
Aaafr, Aaato = fr.capitalize(), to.capitalize()
AAAfr, AAAto = fr.upper(), to.upper()
import re
rep = ((fr, to), (Aaafr, Aaato), (AAAfr, AAAto))
def multiple_replacer(*key_values):
    replace_dict = dict(key_values)
    replacement_function = lambda match: replace_dict[match.group(0)]
    pattern = re.compile("|".join([re.escape(k) for k, v in key_values]), re.M )
    return lambda string: pattern.sub(replacement_function, string)
mr = multiple_replacer(*rep)

for line in sys.stdin:
    print(mr(line), end="")
