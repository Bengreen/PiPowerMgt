import setuptools
import os


def find_version():
    tag = os.environ.get("TAG", "0.0.0")
    return tag


setuptools.setup(
    name="wdactions",
    version=find_version(),
    description="Watchdog actions for RPI",
    author="Ben Greene",
    author_email="BenJGreene@gmail.com",
    url="https://www.undefined.com",
    packages=setuptools.find_packages(),
    include_package_data=True,
    # package_data={
    #     "gateway": [
    #         "templates/*",
    #         "static/*",
    #     ],
    # },
    zip_safe=False,
    install_requires=[
        "python-systemd",
        "click",
    ],
    extras_require={
        "dev": [
            "pytest-aiohttp",
        ]
    },
    entry_points={
        "console_scripts": ["wdactions = wdactions.cli:cli"],
    },
)