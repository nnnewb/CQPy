from json import loads
from cqpy.cqp import get_app_directory
import sys
from os.path import join as join_path

# initialize interpreter environment
def _bootstrap():
    app_dir = get_app_directory()
    settings = loads(join_path(app_dir, 'settings.json'))

    venv = settings.get('VIRTUALENV', '')
    if venv:
        sys.path.append(join_path(venv, 'Lib', 'site-packages'))

    extras = settings.get('EXTRAS_PATH', [])
    sys.path.extend(extras)

