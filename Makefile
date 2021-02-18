venv/bin/python venv/bin/pip:
	python3 -m venv venv

venv/bin/pyserial-ports: venv/bin/pip
	venv/bin/pip install pyserial




clean:
	rm -rf venv