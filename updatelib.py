#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function

import os
import shutil
import tempfile

VERSION = 'nightly'
API_URL = 'http://ampl.com/dl/API/future/{}/libampl.zip'.format(VERSION)


def updatelib():
    from zipfile import ZipFile
    try:
        from urllib import urlretrieve
    except Exception:
        from urllib.request import urlretrieve

    os.chdir(os.path.dirname(__file__) or os.curdir)

    tmpfile = tempfile.mktemp('.zip')
    tmpdir = os.path.join(os.curdir, 'tmp', 'libampl')
    try:
        shutil.rmtree(tmpdir)
    except Exception:
        pass

    print("Downloading:", API_URL)
    urlretrieve(API_URL, tmpfile)
    with ZipFile(tmpfile) as zp:
        zp.extractall(tmpdir)
    try:
        os.remove(tmpfile)
    except Exception:
        pass

    include_folder = os.path.join(tmpdir, 'include', 'ampl')
    lib32 = os.path.join(tmpdir, 'lib32')
    lib64 = os.path.join(tmpdir, 'lib64')

    ampl_include = os.path.join('src', 'include', 'ampl')
    try:
        shutil.rmtree(ampl_include)
    except Exception:
        pass
    shutil.copytree(include_folder, ampl_include)
    print(
        '*\n!.gitignore\n',
        file=open(os.path.join(ampl_include, '.gitignore'), 'w')
    )
    print('headers: {}'.format(ampl_include))

    for lib, arch in [(lib32, 'i386'), (lib64, 'x64')]:
        dst = os.path.join('inst', 'libs', arch)
        print('{} ({}):'.format(arch, dst))
        try:
            shutil.rmtree(dst)
        except Exception:
            pass
        if not os.path.exists(dst):
            os.makedirs(dst)
        print(
            '*\n!.gitignore\n',
            file=open(os.path.join(dst, '.gitignore'), 'w')
        )
        for filename in os.listdir(lib):
            if filename.endswith('.jar'):
                continue
            if 'java' in filename:
                continue
            if 'csharp' in filename:
                continue
            print('\t{}'.format(filename))
            shutil.copyfile(
                os.path.join(lib, filename),
                os.path.join(dst, filename)
            )


if __name__ == '__main__':
    updatelib()
