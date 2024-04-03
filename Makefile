help:
	@echo "Available targets:"
	@grep -E "^[a-zA-Z0-9_-]+:.*?## .*$$" $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: ## "Nothing to see here..."
	@echo "I told you..."

.PHONY: all help
