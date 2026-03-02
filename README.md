# tinydocs

## Installation

```bash
# Build from source
pip install build
python -m build

# Install
pip install dist/tinydocs-*.whl
```

## Usage

```bash
tinydocs-cli \
    --dirs tinydocs \
    --markers docs/tiny.markers.json \
    --output docs \
    --name tinydocs \
    --ignore .gitignore,.tinyignore \
    --generate
```

## License

[MIT](./LICENSE)
