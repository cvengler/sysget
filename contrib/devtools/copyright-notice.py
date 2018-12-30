import sys, os, glob, time, datetime

NOTICE = """// Copyright (c) <YEAR> Emil Engler et al.
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
// file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>."""

FILES = ["*.hpp", "*.cpp"]

now = datetime.datetime.now()

if now.year == 2018:
    NOTICE = NOTICE.replace("<YEAR>", "2018")

else:
    NOTICE = NOTICE.replace("<YEAR>" , "2018-" + str(now.year))


NOTICE = NOTICE.split("\n")

for ext in FILES:
    for filename in glob.iglob("../../src/" + ext, recursive=True):
        file = open(filename, "r")
        file_str = file.readlines()
        file.close()
        # Check if the first line matches the NOTICE
        if file_str[0][0] != "/":
            file_str.insert(0, NOTICE[0] + "\n")
            file_str.insert(1, NOTICE[1] + "\n")
            file_str.insert(2, NOTICE[2] + "\n")
            file = open(filename, "w")
            for x in file_str:
                file.write(x)

            file.close()
            print("Done with " + filename + " - NEW")

        else:
            file_str = file_str[3:]
            file_str.insert(0, NOTICE[0] + "\n")
            file_str.insert(1, NOTICE[1] + "\n")
            file_str.insert(2, NOTICE[2] + "\n")
            file = open(filename, "w")
            for x in file_str:
                file.write(x)

            file.close()
            print("Done with " + filename + " - UPDATE")
