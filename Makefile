.DEFAULT_GOAL := help

.PHONY: help
help: ## Show help message
	@echo "Available targets:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

.PHONY: docs
docs: ## Generate documentation
	tinydocs-cli \
		-D tinydocs \
		--markers docs/tiny.markers.json \
		-o docs \
		--name tinydocs \
		--ignore .gitignore,.tinyignore

.PHONY: build
build: ## Build the package
	python -m build

.PHONY: install
install: build ## Install the package
	@latest=$$(ls dist/*.whl 2>/dev/null | sort -V | tail -n 1); \
	if [ -z "$$latest" ]; then \
		echo "Error: No wheel file found in dist/"; \
		exit 1; \
	fi; \
	echo "Installing: $$latest"; \
	pip install "$$latest" --break-system-packages --force-reinstall
