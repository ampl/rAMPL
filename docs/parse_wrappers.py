#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function
import sys
import os
import re


def parse_wrappers(path):
    rgx = re.compile(r'/\*(\.\..*?)\*/', re.DOTALL)
    for fname in os.listdir(path):
        if fname.endswith(('.cpp', '.h')):
            srcfile = os.path.join(path, fname)
            rstfile = os.path.join(
                'source', 'reference', fname.replace('.', '') + '.rst'
            )
            with open(srcfile, 'r') as src:
                text = src.read()
                entries = rgx.findall(text)
            if len(entries) > 0:
                with open(rstfile, 'w') as rst:
                    for entry in entries:
                        print(entry, file=rst)

if __name__ == '__main__':
    os.chdir(os.path.dirname(__file__) or os.curdir)
    parse_wrappers('../src/')
