set(SOURCES
        Card.cpp
        Country.cpp
        Deck.cpp
        DiceFacility.cpp
        Die.cpp
        Hand.cpp
        Map.cpp
        MapLoader.cpp
        Player.cpp)
set(HEADERS
        Card.h
        Country.h
        Deck.h
        DiceFacility.h
        Die.h
        Hand.h
        Map.h
        MapLoader.h
        Player.h)

add_library(Risk STATIC ${SOURCES} ${HEADERS})