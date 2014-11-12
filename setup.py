#!/usr/bin/env python3

import os
from setuptools import setup

def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

setup(
    name = "rc-clock",
    version = "0.1",
    author = "Brent Strysko",
    author_email = "bstrysko@andrew.cmu.edu",
    description = ("CMU Robotics Club Clock"),
    license = "MIT",
    keywords = "roboclub robotics club api cmu clock",
    packages=['clock/',],
    scripts = ["bin/rc-clock"],
    long_description=read('README.md'),
    install_dependencies = ['pyserial'],

    # TODO: make pyrc dependency
)