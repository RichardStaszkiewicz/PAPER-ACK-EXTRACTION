# minimalna wymagana wersja cmake'a (sudo apt install cmake)
# żeby sprawdzić obecną, komenda:
# cmake --version
cmake_minimum_required(VERSION 3.16)


# tutaj (bez przecinka) można deklarować flagi kompilacji
set(FLAGS -std=c++17 -O3 -Wall -g)


# tutaj się deklaruje jaki kompilator się używa (g++, clang)
set(CMAKE_CXX_COMPILER g++)


# tutaj dopiero się wypisuje wszystkie flagi zapisane do zmiennej FLAGS
# do opcji kompilacji
add_compile_options(${FLAGS})


# Tutaj deklaruje się nazwę projektu, jego wersję, można zadeklarować też
# język programowania
project(ACK-EXTRACTION VERSION 0.1 LANGUAGES CXX)


# do zmiennej SRC są przypisywane wszystkie pliki z rozszerzeniem .cpp
# z folderu source. Wgl, przypisujemy do niej wszystkie źródła.
# Zamiast GLOB_RECURSE można dać GLOB, ale wtedy nie znajdywane są pliki z podfolderów
# Wyświetlenie zawartości zmiennej z pomocą linijki:
# message(${SRC})
file(GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)


# załączanie pakietów wymaganych do kompilacji
# w tym konkretnym wypadku, jako że zachodzi potrzeba testów
# a są one robione pod gtestem, wymagany jest pakiet Gtest
# trzeba sprawdzić w dokumentacji cmake'a jak wg. nich nazywalą się poszczególne pakiety
find_package(GTest REQUIRED)


# powiedzenie gdzie znajdują się inne CMakeLists-y, które chcemy wywołać
add_subdirectory(${CMAKE_SOURCE_DIR}/lib)


# tutaj się pisze który program będzie skompilowany do pliku wykonywalnego
# bez przecinka można dodawać kolejne pliki
# JAK NIE UŻYWAMY BIBLIOTEKI
# należy dodać za main.cpp wszystkie pliki źródłowe zapisane w zmiennej SRC:
# add_executable(program main.cpp, ${SRC})
add_executable(program main.cpp)

# powiedzenie gdzie znajdują się programy includowane (wywoływane przez #include)
# - najczęściej headery
target_include_directories(program PUBLIC BEFORE ${CMAKE_SOURCE_DIR}/include)

# załączenie biblioteki do projektu (tak by potem inni też mogli korzystać)
# najpierw GTest, potem biblioteki stworzone w lib (w tym wypadku proiekt_lib)
target_link_libraries(program PUBLIC GTest::GTest ack_extract_lib)

# target_link_libraries(program PUBLIC proiekt_lib)


# Aby uruchomić, mając zainstalowanego cmake-a należy wykonać komendy (w katalogu z głównym CMakeListem):
# cmake CMakeLists.txt
# make

# utworzony zostaje wówczas plik wykonywalny "program". Aby go uruchomić wystarczy:
# ./program