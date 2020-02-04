import sys
from importlib import import_module
from json import load
from os import environ
from os.path import join as join_path
from pkgutil import walk_packages

from cqpy.cqp import get_app_directory

settings = {}


def import_recursive(name):
    modules = []
    mod = import_module(name)
    if hasattr(mod, '__path__'):
        for finder, mod_name, is_pkg in walk_packages(mod.__path__):
            sub_mod = import_module('.'.join([name, mod_name]))
            modules.append(sub_mod)
            if is_pkg:
                modules.extend(import_recursive('.'.join([name, mod_name]))[1])

    return mod, modules


def _bootstrap():
    """
    initialize interpreter environment

    :return:
    """
    global settings
    app_dir = get_app_directory()
    with open(join_path(app_dir, 'settings.json'), 'rb') as f:
        settings = load(f)

    env = settings.get('virtualenv', '')
    if env:
        sys.path.append(join_path(env, 'Lib', 'site-packages'))
        environ['VIRTUALENV'] = env

    extras = settings.get('extras', [])
    sys.path.extend(extras)

    # register callback functions
    for load_name in settings.get('plugins', []):
        import_recursive(load_name)


_bootstrap()
