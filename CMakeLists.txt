cmake_minimum_required(VERSION 3.15)

# Настройка проекта как библиотеки
project(BpmnEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_TOOLCHAIN_FILE "D:/CPPLIB/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции сборки
option(BUILD_SHARED_LIBS "Build shared library" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)

#Установка явных путей
set(nlohmann_json_DIR "D:/CPPLIB/vcpkg/installed/x64-windows/share/nlohmann_json")
set(flatbuffers_DIR "D:/CPPLIB/vcpkg/installed/x64-windows/share/flatbuffers")
set(Boost_DIR "D:/CPPLIB/vcpkg/installed/x64-windows/share/boost")
set(BOOST_ROOT "D:/CPPLIB/vcpkg/installed/x64-windows")
set(GTest_DIR "D:/CPPLIB/vcpkg/installed/x64-windows/share/gtest")

# Находим зависимости
find_package(LibXml2 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(flatbuffers REQUIRED)
find_package(Boost REQUIRED COMPONENTS uuid algorithm)

# Создаем библиотеку
add_library(bpmn_engine
    src/bpmn/parser.cpp
    src/bpmn/executor.cpp
    src/bpmn/model.cpp
    src/bpmn/services/abstractService.cpp
    src/db/orm.cpp
    src/db/config.cpp
    src/db/models/process.cpp
    src/db/models/form.cpp
 "include/bpmn/engine.h" "src/bpmn/engine.cpp")

# Публичный интерфейс библиотеки
target_include_directories(bpmn_engine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Приватные зависимости
target_link_libraries(bpmn_engine PRIVATE
    LibXml2::LibXml2
    OpenSSL::SSL
    OpenSSL::Crypto
    PostgreSQL::PostgreSQL
    nlohmann_json::nlohmann_json
    Boost::uuid
    Boost::algorithm
)

# Настройки компилятора
if(MSVC)
    target_compile_options(bpmn_engine PRIVATE 
        /Zc:__cplusplus
        /permissive-
    )
    target_compile_definitions(bpmn_engine PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# Установка библиотеки
install(TARGETS bpmn_engine
    EXPORT bpmn_engine-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

# Файлы конфигурации для find_package
install(EXPORT bpmn_engine-targets
    FILE bpmn_engine-config.cmake
    NAMESPACE bpmn::
    DESTINATION lib/cmake/bpmn_engine
)

# Юнит-тесты
if(BUILD_TESTS)
    enable_testing()
    
    # Google Test через vcpkg
    find_package(GTest CONFIG REQUIRED)
    
    add_executable(bpmn_engine_tests
        tests/unit/test_parser.cpp
        tests/unit/test_executor.cpp
        tests/integration/test_engine.cpp
     "include/bpmn/engine.h" "src/bpmn/engine.cpp")
    
    target_link_libraries(bpmn_engine_tests
        bpmn_engine
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
    )
    
    add_test(NAME bpmn_engine_unit_tests COMMAND bpmn_engine_tests)
endif()

# Примеры использования
if(BUILD_EXAMPLES)
    add_executable(bpmn_demo examples/demo/main.cpp "include/bpmn/engine.h" "src/bpmn/engine.cpp")
    target_link_libraries(bpmn_demo bpmn_engine)
    
    # Копируем конфиг для демо
    add_custom_command(TARGET bpmn_demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/config/config.json"
        "$<TARGET_FILE_DIR:bpmn_demo>/config.json"
    )
endif()