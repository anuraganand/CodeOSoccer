.PHONY: clean All

All:
	@echo ----------Building project:[ CodeOSoccer - Debug ]----------
	@cd "CodeOSoccer" && "$(MAKE)" -f "CodeOSoccer.mk"
clean:
	@echo ----------Cleaning project:[ CodeOSoccer - Debug ]----------
	@cd "CodeOSoccer" && "$(MAKE)" -f "CodeOSoccer.mk" clean
