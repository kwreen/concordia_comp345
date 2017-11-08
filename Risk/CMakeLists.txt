set(SOURCES
        Card.cpp
        Country.cpp
        Deck.cpp
        DiceFacility.cpp
        Die.cpp
	Game.cpp
        Hand.cpp
        Map.cpp
        MapLoader.cpp
        Player.cpp
	UserInterface.cpp
		Subject.cpp)
set(HEADERS
        Card.h
        Country.h
        Deck.h
        DiceFacility.h
        Die.h
	Game.h
        Hand.h
        Map.h
        MapLoader.h
        Player.h
	UserInterface.h
		Observer.h
		Subject.h)

add_library(Risk STATIC ${SOURCES} ${HEADERS})
add_executable(RiskGame RiskGame.cpp)
target_link_libraries(RiskGame Risk)