#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function

import os
import sys
import shutil
import tempfile

VERSION = 'nightly'
API_URL = 'https://ampl.com/dl/API/future/{}/libampl.zip'.format(VERSION)

def updatelib(package):
    from zipfile import ZipFile
    try:
        from urllib import urlretrieve
    except Exception:
        from urllib.request import urlretrieve

    os.chdir(os.path.dirname(__file__) or os.curdir)

    tmpfile = tempfile.mktemp('.zip')
    tmpdir = os.path.join(os.curdir, 'tmp')
    libampldir = os.path.join(tmpdir, 'libampl')
    try:
        shutil.rmtree(tmpdir)
    except Exception:
        pass

    if package.startswith('http'):
        # Disable SSL verification
        import ssl
        ssl._create_default_https_context = ssl._create_unverified_context
        print("Downloading:", API_URL)
        urlretrieve(API_URL, tmpfile)
        with ZipFile(tmpfile) as zp:
            zp.extractall(tmpdir)
        try:
            os.remove(tmpfile)
        except Exception:
            pass
    else:
        with ZipFile(package) as zp:
            zp.extractall(tmpdir)

    include_dir = os.path.join(libampldir, 'include', 'ampl')
    rampl_include = os.path.join('src', 'include', 'ampl')
    try:
        shutil.rmtree(rampl_include)
    except Exception:
        pass
    shutil.copytree(include_dir, rampl_include)
    print(
        '*\n!.gitignore\n',
        file=open(os.path.join(rampl_include, '.gitignore'), 'w')
    )
    print('headers: {}'.format(rampl_include))

    dstbase = os.path.join('inst', 'libs')
    try:
        shutil.rmtree(dstbase)
        os.mkdir(dstbase)
    except Exception:
        pass
    print(
        '*\n!.gitignore\n',
        file=open(os.path.join(dstbase, '.gitignore'), 'w')
    )

    for lib, arch in [('intel32', 'i386'), ('amd64', 'x64')]:
        libdir = os.path.join(libampldir, lib)
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
        for filename in os.listdir(libdir):
            print('\t{}'.format(filename))
            shutil.copyfile(
                os.path.join(libdir, filename),
                os.path.join(dst, filename)
            )


if __name__ == '__main__':
    if len(sys.argv) == 2:
        updatelib(sys.argv[1])
    else:
        updatelib(API_URL)
