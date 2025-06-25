all:
	@cmake --build build/
	@echo ",----------------------------------------,"
	@echo "|      BUILT PROGRAM SUCCESSFULLY        |"
	@echo "|              RUNNING NOW               |"
	@echo "'----------------------------------------'"
	@build/GUITravelScraper
	