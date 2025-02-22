# %BANNER_BEGIN%
# ---------------------------------------------------------------------
# %COPYRIGHT_BEGIN%
#
# Copyright (c) 2018 Magic Leap, Inc. (COMPANY) All Rights Reserved.
# Magic Leap, Inc. Confidential and Proprietary
#
#  NOTICE:  All information contained herein is, and remains the property
#  of COMPANY. The intellectual and technical concepts contained herein
#  are proprietary to COMPANY and may be covered by U.S. and Foreign
#  Patents, patents in process, and are protected by trade secret or
#  copyright law.  Dissemination of this information or reproduction of
#  this material is strictly forbidden unless prior written permission is
#  obtained from COMPANY.  Access to the source code contained herein is
#  hereby forbidden to anyone except current COMPANY employees, managers
#  or contractors who have executed Confidentiality and Non-disclosure
#  agreements explicitly covering such access.
#
#  The copyright notice above does not evidence any actual or intended
#  publication or disclosure  of  this source code, which includes
#  information that is confidential and/or proprietary, and is a trade
#  secret, of  COMPANY.   ANY REPRODUCTION, MODIFICATION, DISTRIBUTION,
#  PUBLIC  PERFORMANCE, OR PUBLIC DISPLAY OF OR THROUGH USE  OF THIS
#  SOURCE CODE  WITHOUT THE EXPRESS WRITTEN CONSENT OF COMPANY IS
#  STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND
#  INTERNATIONAL TREATIES.  THE RECEIPT OR POSSESSION OF  THIS SOURCE
#  CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
#  TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE,
#  USE, OR SELL ANYTHING THAT IT  MAY DESCRIBE, IN WHOLE OR IN PART.
#
# %COPYRIGHT_END%
# ---------------------------------------------------------------------
# %BANNER_END%

import argparse
import os
import re
import subprocess
import sys
import tempfile

def main():
    assert os.name == 'nt', "The include dependency generator can only be used on Windows!"

    desc = "Resolve the include dependency hierarchy of a given input source file and convert it to a format " \
           "compatible with GNU make. This should only be run from mabu!"
    parser = argparse.ArgumentParser(
        prog="Include Dependency Generator",
        description=desc
    )

    parser.add_argument("src_file", action="store", help="Input source file to preprocess.")
    parser.add_argument("dep_file", action="store", help="Output dependency file for the resolved dependency information.")
    parser.add_argument("obj_file", action="store", help="Compiled object file the input source file is expected to have.")

    parser.add_argument("flags", nargs=argparse.REMAINDER, help="Other preprocessor flags")

    opt = parser.parse_args()
    temp_out_dir = tempfile.mkdtemp()
    tool = "cl.exe"
    input_arg = os.path.abspath(opt.src_file)
    output_arg = os.path.join(temp_out_dir, "out.i")

    cmd = [
        tool,
        "-nologo",
        "-showIncludes",
        "-W0",
        "-P",
        "-Fi{}".format(output_arg),
        input_arg,
    ]   + opt.flags

    deps = set()

    try:
        fd = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                              universal_newlines=True)
        output, _ = fd.communicate()

        # Only extract the includes if the compiler encountered no errors.
        if fd.returncode != 0:
            # show errors that don't appear to be from /showIncludes
            # (note: even if the locale is not English, this will print something...)
            non_note_match = re.compile(r"Note:.*\n", re.M)
            print("Failed to invoke " + " ".join(cmd) +
                  '\n' + non_note_match.sub('', output), file=sys.stderr)
            sys.exit(fd.returncode)

        includeMatch = re.compile(r"[^:]+:\s*[^:]+:\s*(.*)", re.M)
        matches = includeMatch.finditer(output)
        for match in matches:
            try:
                # Add the include file to the list of dependencies.
                path = match.group(1)

                # make only wants capitalized drive letters
                if len(path) > 2 and path[0].isalpha() and path[1] == ':':
                    path = path[0].upper() + path[1:]
                deps.add(path)
            except:
                pass
    finally:
        # Remove the preprocessed file generated by the compiler.
        if os.access(output_arg, os.F_OK):
            os.remove(output_arg)
        os.rmdir(temp_out_dir)

    deps = [input_arg] + sorted(deps)
    deps = [dep.replace("\\", "/").replace(" ", "\\ ") for dep in deps]
    dep_file = os.path.abspath(opt.dep_file)
    dep_file_dir = os.path.dirname(dep_file)

    # Create the directory hierarchy for the dependency file if it doesn't exist.
    if not os.access(dep_file_dir, os.F_OK):
        try:
            os.makedirs(dep_file_dir)
        except FileExistsError as e:
            pass  # someone raced us to it

    # Join the dependencies into a single string in the correct output format.
    deps_output = " \\\n ".join(deps)

    # note: the object file path must look exactly as it came in, modulo path separators,
    # else 'make' won't match the rules... defeating the purpose :)
    obj_file = opt.obj_file.replace("\\", "/")

    # Create a rule for every file mentioned, so make will not
    # complain if it is moved/renamed before the next build
    file_rules = ":\n".join(deps + [''])

    # Create and write the dependency file.
    with open(dep_file, "w") as f:
        f.write("{}: \\\n {}\n{}\n".format(obj_file, deps_output, file_rules))

if __name__ == "__main__":
    main()
