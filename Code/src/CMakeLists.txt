add_library(Tools Personnage.cpp State.cpp formes.cpp Portee.cpp)

add_executable(Client client.cpp)
target_link_libraries(Client Tools ${SFML_LIBRARIES})

add_executable(Server server.cpp)
target_link_libraries(Server Tools ${SFML_LIBRARIES})
