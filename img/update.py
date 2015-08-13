#!/usr/bin/python

import glob, os
for src in glob.glob("*.png"):
    dst = src.replace(".png", ".bmp")
    update = False

    if os.path.exists(dst):
        srcStat = os.stat(src)
        dstStat = os.stat(dst)
        if srcStat.st_mtime > dstStat.st_mtime:
            update = True
    else:
        update = True
    if update:
        print "Updating", dst
        os.system("convert %s %s" % (src, dst))

