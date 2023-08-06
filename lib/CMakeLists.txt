# Można stworzyć bibliotekę statyczną bądź dynamiczną słowami STATIC/SHARED:
# add_library(nazwa (STATIC/SHARED) ${SRC})
# domyślnie biblioteki tworzone są statycznie
# Pliki w SRC są tym samym, co w głównym CMakeLists - wszystkie zmienne przechodzą
# do tego, jako że główny go wywołuje
add_library(ack_extract_lib STATIC ${SRC})


# Z jakich plików źródłowych ma się składać
target_include_directories(ack_extract_lib PUBLIC BEFORE ${CMAKE_SOURCE_DIR}/include)