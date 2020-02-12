from setuptools import setup, find_packages

with open('README.md', 'r', encoding='utf-8') as f:
    README = f.read()

setup(
    name="CQPy",
    version="0.1.2",
    author="weak_ptr",
    author_email="weak_ptr@outlook.com",
    description='CQPy is lightweight CoolQ Python SDK for Python 3.7+',
    long_description=README,
    long_description_content_type='text/markdown',
    packages=find_packages(),
)