cmake_minimum_required(VERSION 3.19)
project(BuscaminasQt LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

qt_add_executable(BuscaminasQt
    WIN32 MACOSX_BUNDLE
    main.cpp
    buscaminasmain.cpp
    buscaminasmain.h
    seleccionardificultad.h seleccionardificultad.cpp
    registrousuario.h
    RegistroUsuario.cpp
    celda.h celda.cpp
    tablero.h tablero.cpp
    vistajuego.h
    vistajuego.cpp
    ventanajuego.h
    ventanajuego.cpp
    celdagrafica.h celdagrafica.cpp
    cronometro.h cronometro.cpp
    gestorpuntajes.h gestorpuntajes.cpp
    ventanarecords.h
    ventanarecords.cpp
    VentanaLogin.h
    VentanaLogin.cpp
    gestormedallas.h gestormedallas.cpp
    indicadoricono.h indicadoricono.cpp
    ventanavictoria.h ventanavictoria.cpp
    ventanaderrota.h ventanaderrota.cpp
    gestoraudio.h gestoraudio.cpp
    ventanaopciones.h ventanaopciones.cpp
    estilos.h
    medallaimagen.h


)

target_link_libraries(BuscaminasQt
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
)

# copia los sonidos junto al ejecutable para que GestorAudio los encuentre
add_custom_command(TARGET BuscaminasQt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/sonidos"
        "$<TARGET_FILE_DIR:BuscaminasQt>/sonidos"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/musica"
        "$<TARGET_FILE_DIR:BuscaminasQt>/musica"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/recursos"
        "$<TARGET_FILE_DIR:BuscaminasQt>/recursos"
)

install(TARGETS BuscaminasQt
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET BuscaminasQt
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
